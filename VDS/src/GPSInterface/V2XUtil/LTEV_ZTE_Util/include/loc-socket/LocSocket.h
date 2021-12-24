/* Copyright (c) 2019 The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of The Linux Foundation, nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __LOC_SOCKET__
#define __LOC_SOCKET__

#include <string>
#include <memory>
#include <unistd.h>
#include <poll.h> // qxocket.h
#include <sys/ioctl.h> // qsocket_ipcr.h

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>

#include <linux/types.h>
#include <linux/socket.h>

#include <log_util.h>
#include <LocIpc.h>
#include <LocThread.h>

namespace loc_util {

struct sockaddr_qrtr {
    __kernel_sa_family_t sq_family;
    __u32 sq_node;
    __u32 sq_port;
};

#define RETRY_FINDNEWSERVICE_MAX_COUNT 10000
#define RETRY_FINDNEWSERVICE_SLEEP_MS  5
#define SOCKET_TIMEOUT_SEC 2

class LocSocketSender;

class LocSocket : public LocIpc {
friend LocSocketSender;
public:
    inline LocSocket() :
            mService(0), mInstance(0),
            mFdMe(-1), mRunnable(nullptr) {}
    inline virtual ~LocSocket() { stopListening(); }

    // Listen for new messages in current thread. The socket to listen on
    // is identified by the argument name, which contains the service and
    // instance id of the socket.
    // Calling this funciton will block current thread. The listening can
    // be stopped by calling stopListening().
    bool startListeningBlocking(const std::string& name);

    // Create a new LocThread and listen for new messages in it.
    // The socket to listen on is identified by the argument name,
    // which contains the service and instance id of the socket.
    // Calling this function will return immediately and won't block current thread.
    // The listening can be stopped by calling stopListening().
    bool startListeningNonBlocking(const std::string& name);

    // Stop listening to new messages.
    void stopListening();

    // Send out a message.
    // Argument:
    //   service and instance id for socket to send data to
    //   data to be sent specified in string format
    static bool send(int service, int instance, const std::string& data);

    // Send out a message.
    // Argument:
    //   service and instance for socket to send data to
    //   data to be sent specified in the byte array and array length
    static bool send(int service, int instance, const uint8_t data[], uint32_t length);

protected:
    // Callback function for receiving incoming messages.
    // Override this function in your derived class to process incoming messages.
    // For each received message, this callback function will be called once.
    // This callback function will be called in the calling thread of startListeningBlocking
    // or in the new LocThread created by startListeningNonBlocking.
    //
    // Argument data contains the received message. You need to parse it.
    inline virtual void onReceive(const std::string& /*data*/) {}

    // LocSocket client can overwrite this function to get notification
    // when the socket for LocSocket is ready to receive messages.
    inline virtual void onListenerReady() {}

private:
    // This function will send byte array data to the socket with
    // socket file descriptor specified in "fd" and node and port
    // provided in "addr". The data to be sent is specified as
    // byte array "data" and its length is specified via "length".
    static bool sendData(int fd, const sockaddr_qrtr& addr,
            const uint8_t data[], uint32_t length);

    // This function will find the service node and port for the socket.
    // The socket to be found is specified by "fd" and service id and instance id.
    // The service node and port if found, will be returned in output parameter of
    // "addr".
    static bool findService(int fd, sockaddr_qrtr& addr, int service, int instance,
                            bool & serviceDeleted);

    // This call will find service with retry attempt of
    // default retry count (defined in RETRY_FINDNEWSERVICE_MAX_COUNT) and
    // interval (defined in RETRY_FINDNEWSERVICE_SLEEP_MS).
    // The service node and port if found, will be returned in output parameter of
    // "addr". If the service is deleted, then the output parameter of "serviceDeleted"
    // will be set to true.
    static bool findServiceWithRetry(int fd, sockaddr_qrtr& addr, int service, int instance,
                                     bool & serviceDeleted);

    int mService;
    int mInstance;
    int mFdMe;
    struct sockaddr_qrtr mDestAddr;
    LocThread mThread;
    LocRunnable *mRunnable;
};

class LocSocketSender {
public:
    // Constructor of LocSocketSender class
    //
    // Argument service/instance contain destination port.
    // This class hides generated fd and destination address object from user.
    inline LocSocketSender(int service, int instance) {

        mService = service;
        mInstance = instance;
        mServiceDeleted = false;
        memset(&mDestAddr, 0, sizeof(mDestAddr));

        mSocket = socket(AF_QIPCRTR, SOCK_DGRAM, 0);
        if (mSocket < 0) {
            return;
        }

        // 2 second timeout value for socket operation
        timeval timeout;
        timeout.tv_sec = SOCKET_TIMEOUT_SEC;
        timeout.tv_usec = 0;
        setsockopt(mSocket, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));

        // find the server address
        LocSocket::findServiceWithRetry(mSocket, mDestAddr, mService, mInstance,
                                        mServiceDeleted);
    }

    inline ~LocSocketSender() {
        if (mSocket >= 0) {
            close(mSocket);
        }
    }

    // Send out a message.
    // Call this function to send a message
    //
    // Argument data and length contains the message to be sent out.
    // Return true when succeeded
    inline bool send(const uint8_t data[], uint32_t length) {
        bool rtv = true;

        if ((nullptr != data) && (false == mServiceDeleted)){
            if ((mDestAddr.sq_node == 0) && (mDestAddr.sq_port == 0)) {
                LOC_LOGe("service not ready");
            } else{
                rtv = LocSocket::sendData(mSocket, mDestAddr, data, length);
            }
        }
        return rtv;
    }

    // This routine will attempt to find new service when service
    // has crashed and restarted.
    // We need to make sure that we get the new dest info (node/port) as the
    // crashed service may lingering around for some time and findService may
    // return the node/port belong to the crashed service.
    inline bool findNewService() {
        bool rtv = false;
        bool newServiceFound = false;
        int retryCount = 0;
        sockaddr_qrtr newDestAddr;

        do {
            memset(&newDestAddr, 0, sizeof(newDestAddr));
            mServiceDeleted = false;
            rtv = LocSocket::findServiceWithRetry(mSocket, newDestAddr, mService, mInstance,
                                                  mServiceDeleted);
            if (true == rtv) {
                if ((mDestAddr.sq_node != newDestAddr.sq_node) ||
                    (mDestAddr.sq_port != newDestAddr.sq_port)) {
                    mDestAddr = newDestAddr;
                    newServiceFound = true;
                    break;
                }
            }
            usleep(RETRY_FINDNEWSERVICE_SLEEP_MS*1000);
            retryCount++;
        } while (retryCount < RETRY_FINDNEWSERVICE_MAX_COUNT);

        LOC_LOGd("service found %d, new service found %d, "
                 "retry count %d", rtv, newServiceFound, retryCount);
        return rtv;
    }

private:
    int mService;
    int mInstance;
    int mSocket;
    sockaddr_qrtr mDestAddr;
    bool mServiceDeleted;
};

}

#endif //__LOC_SOCKET__
