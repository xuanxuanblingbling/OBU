/*
*  Copyright (c) 2019, The Linux Foundation. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are
*  met:
*    * Redistributions of source code must retain the above copyright
*      notice, this list of conditions and the following disclaimer.
*    * Redistributions in binary form must reproduce the above
*      copyright notice, this list of conditions and the following
*      disclaimer in the documentation and/or other materials provided
*      with the distribution.
*    * Neither the name of The Linux Foundation nor the names of its
*      contributors may be used to endorse or promote products derived
*      from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
*  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
*  ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
*  BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
*  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
*  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
*  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
*  IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 * @file    AudioManager.hpp
 *
 * @brief   Audio Manager is a primary interface for audio operations. It provides
 *          APIs to manage Voice, Audio and Sound Cards.
 *
 * @note    Eval: This is a new API and is being evaluated. It is subject to change
 *          and could break backwards compatibility.
 */

#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include <future>
#include <memory>
#include <vector>

#include "../../../../_01_AG15Layer/Include/telux/audio/AudioDefines.hpp"
#include "../../../../_01_AG15Layer/Include/telux/common/CommonDefines.hpp"

namespace telux {

namespace audio {
/** @addtogroup telematics_audio
 * @{ */

class IAudioDevice;
class IAudioStream;
class IAudioVoiceStream;
class IAudioPlayStream;
class IAudioCaptureStream;

/**
 * @brief   Stream Buffer manages the buffer to be used for read and write operations on Audio
 *          Streams. For write operations, applications should request a stream buffer, populate
 *          it with the data and then pass it to the write operation and set the dataSize that is
 *          to be written to the stream. Similarly for read operations,the application should
 *          request a stream buffer and use that in the read operation.
 *          At the end of the read, the stream buffer will contain the data read. Once an operation
 *          (read/write) has completed, the stream buffer could be reused for a subsequent
 *          read/write operation, provided reset() API called on stream buffer between
 *          subsequent calls.
 *
 */
class IStreamBuffer {
public:
   /**
    * Returns the minimum size (in bytes) of data that caller needs to read/write
    * before calling a read/write operation on the stream.
    *
    * @returns    minimum size
    *
    * @note       Eval: This is a new API and is being evaluated. It is subject to change
    *             and could break backwards compatibility.
    */
   virtual size_t getMinSize() = 0;

   /**
    * Returns the maximum size (in bytes) that the buffer can hold.
    *
    * @returns    maximum size
    *
    * @note       Eval: This is a new API and is being evaluated. It is subject to change
    *             and could break backwards compatibility.
    */
   virtual size_t getMaxSize() = 0;

   /**
    * Gets the raw buffer that IStreamBuffer manages. Application should write in between(include)
    * of  getMinSize() to getMaxSize() number of bytes in this buffer. Application is not
    * responsible to free the raw buffer. It will be free'ed when the IStreamBuffer is destroyed.
    *
    * @returns    raw buffer
    *
    * @note       Eval: This is a new API and is being evaluated. It is subject to change
    *             and could break backwards compatibility.
    */
   virtual uint8_t *getRawBuffer() = 0;

   /**
    * Gets the size (in bytes) of valid data present in the buffer.
    *
    *
    * @returns size of valid data in the buffer
    *
    * @note        Eval: This is a new API and is being evaluated. It is subject to change
    *              and could break backwards compatibility.
    */
   virtual uint32_t getDataSize() = 0;

   /**
    * Sets the size (in bytes) of valid data present in the buffer.
    *
    *
    * @param size  size of valid data in the buffer
    *
    * @note        Eval: This is a new API and is being evaluated. It is subject to change
    *              and could break backwards compatibility.
    */
   virtual void setDataSize(uint32_t size) = 0;

   /**
    * Reset all state and data of the buffer. This is to be called when reusing the same buffer
    * for multiple operations.
    *
    * @returns status   Status of the operation
    *
    * @note        Eval: This is a new API and is being evaluated. It is subject to change
    *              and could break backwards compatibility.
    */
   virtual telux::common::Status reset() = 0;

   virtual ~IStreamBuffer() {};
};



/**
 * This function is called with the response to getDevices API.
 *
 * The callback can be invoked from multiple different threads.
 * The implementation should be thread safe.
 *
 * @param [in] devices  Devices list.
 * @param [in] error    Return code which indicates whether the operation
 *                      succeeded or not.
 *                      @ref ErrorCode
 *
 * @note   Eval: This is a new API and is being evaluated. It is subject to
 *         change and could break backwards compatibility.
 */
using GetDevicesResponseCb = std::function<void(std::vector<std::shared_ptr<IAudioDevice>> devices,
                                                telux::common::ErrorCode error)>;

/**
 * This function is called with the response to getStreamTypes API.
 *
 * The callback can be invoked from multiple different threads.
 * The implementation should be thread safe.
 *
 * @param [in] streamTypes  Stream type list.
 * @param [in] error        Return code which indicates whether the operation
 *                          succeeded or not.
 *                          @ref ErrorCode
 *
 * @note   Eval: This is a new API and is being evaluated. It is subject to
 *         change and could break backwards compatibility.
 */
using GetStreamTypesResponseCb
   = std::function<void(std::vector<StreamType> streamTypes, telux::common::ErrorCode error)>;

/**
 * This function is called with the response to createStream API.
 *
 * The callback can be invoked from multiple different threads.
 * The implementation should be thread safe.
 *
 * @param [in] stream  Interface pointer of Stream created.
 *                     VOICE_CALL - Provides IAudioVoiceStream pointer
 *                     PLAY - Provides IAudioPlayStream pointer
 *                     CAPTURE - Provides IAudioCaptureStream pointer
 * @param [in] error   Return code which indicates whether the operation
 *                     succeeded or not.
 *                     @ref ErrorCode
 *
 * @note   Eval: This is a new API and is being evaluated. It is subject to
 *         change and could break backwards compatibility.
 */
using CreateStreamResponseCb
   = std::function<void(std::shared_ptr<IAudioStream> &stream, telux::common::ErrorCode error)>;

/**
 * This function is called with the response to deleteStream API.
 *
 * The callback can be invoked from multiple different threads.
 * The implementation should be thread safe.
 *
 * @param [in] error  Return code which indicates whether the operation
 *                    succeeded or not.
 *                    @ref ErrorCode
 *
 * @note   Eval: This is a new API and is being evaluated. It is subject to
 *         change and could break backwards compatibility.
 */
using DeleteStreamResponseCb = std::function<void(telux::common::ErrorCode error)>;

/**
 * @brief   Audio Manager is a primary interface for audio operations. It provide
 *          APIs to manage Streams ( like voice, play, record etc) and sound cards.
 */
class IAudioManager {
public:
   /**
    * Checks the status of audio subsystems and returns the result.
    *
    * @returns    If true that means AudioManager is ready for performing audio operations.
    *
    * @note       Eval: This is a new API and is being evaluated. It is subject to change
    *             and could break backwards compatibility.
    */
   virtual bool isSubsystemReady() = 0;

   /**
    * Wait for Audio subsystem to be ready.
    *
    * @returns    A future that caller can wait on to be notified when audio
    *             subsystem is ready.
    *
    * @note       Eval: This is a new API and is being evaluated. It is subject to change
    *             and could break backwards compatibility.
    */
   virtual std::future<bool> onSubsystemReady() = 0;

   /**
    * Get the list of supported audio devices, which are currently supported in the audio subsystem
    *
    * @param [in] callback    callback pointer to get the response of getDevices.
    *
    * @returns Status of request i.e. success or suitable status code.
    *
    * @note       Eval: This is a new API and is being evaluated. It is subject to change
    *             and could break backwards compatibility.
    */
   virtual telux::common::Status getDevices(GetDevicesResponseCb callback = nullptr) = 0;

   /**
    * Get the list of supported audio streams types, which are currently supported in the audio
    * subsystem
    *
    * @param [in] callback    callback pointer to get the response of getStreamTypes.
    *
    * @returns Status of request i.e. success or suitable status code.
    *
    * @note        Eval: This is a new API and is being evaluated. It is subject to change
    *              and could break backwards compatibility.
    */
   virtual telux::common::Status getStreamTypes(GetStreamTypesResponseCb callback = nullptr) = 0;

   /**
    * Creates the stream for audio operation
    *
    * @param [in] streamConfig    stream configuration.
    * @param [in] callback        callback pointer to get the response of createStream.
    *
    * @returns Status of request i.e. success or suitable status code.
    *
    * @note        Eval: This is a new API and is being evaluated. It is subject to change
    *              and could break backwards compatibility.
    */
   virtual telux::common::Status createStream(StreamConfig streamConfig,
                                              CreateStreamResponseCb callback = nullptr)
      = 0;

   /**
    * Deletes the specified stream which was created before
    *
    * @param [in] stream      reference to stream to be deleted.
    * @param [in] callback    callback pointer to get the response of deleteStream.
    *
    * @returns Status of request i.e. success or suitable status code.
    *
    * @note        Eval: This is a new API and is being evaluated. It is subject to change
    *              and could break backwards compatibility.
    */
   virtual telux::common::Status deleteStream(std::shared_ptr<IAudioStream> stream,
                                              DeleteStreamResponseCb callback = nullptr)
      = 0;
};

/**
 * @brief   Audio device and it's characteristics like Direction (Sink or Source), type
 */
class IAudioDevice {
public:
   /**
    * Get the type of Device (i.e SPEAKER, MIC etc)
    *
    * @returns    DeviceType
    *
    * @note       Eval: This is a new API and is being evaluated. It is subject to change
    *             and could break backwards compatibility.
    */
   virtual DeviceType getType() = 0;

   /**
    * Provide direction of device whether is Sink for audio data ( RX i.e. speaker, etc)
    * or Source for audio data ( TX i.e. mic, etc)
    *
    * @returns    DeviceDirection
    *
    * @note       Eval: This is a new API and is being evaluated. It is subject to change
    *             and could break backwards compatibility.
    */
   virtual DeviceDirection getDirection() = 0;

 };

/**
 * This function is called with the response to stream getDevice API.
 *
 * The callback can be invoked from multiple different threads.
 * The implementation should be thread safe.
 *
 * @param [in] devices   Devices list.
 * @param [in] error     Return code which indicates whether the operation
 *                       succeeded or not.
 *                       @ref ErrorCode
 *
 * @note   Eval: This is a new API and is being evaluated. It is subject to
 *         change and could break backwards compatibility.
 */
using GetStreamDeviceResponseCb
   = std::function<void(std::vector<DeviceType> devices, telux::common::ErrorCode error)>;

/**
 * This function is called with the response to stream getVolume API.
 *
 * The callback can be invoked from multiple different threads.
 * The implementation should be thread safe.
 *
 * @param [in] volume   stream volume details.
 * @param [in] error    Return code which indicates whether the operation
 *                      succeeded or not.
 *                      @ref ErrorCode
 *
 * @note   Eval: This is a new API and is being evaluated. It is subject to
 *         change and could break backwards compatibility.
 */
using GetStreamVolumeResponseCb
   = std::function<void(StreamVolume volume, telux::common::ErrorCode error)>;

/**
 * This function is called with the response to stream getMute API.
 *
 * The callback can be invoked from multiple different threads.
 * The implementation should be thread safe.
 *
 * @param [in] mute   stream mute details.
 * @param [in] error  Return code which indicates whether the operation
 *                    succeeded or not.
 *                    @ref ErrorCode
 *
 * @note   Eval: This is a new API and is being evaluated. It is subject to
 *         change and could break backwards compatibility.
 */
using GetStreamMuteResponseCb
   = std::function<void(StreamMute mute, telux::common::ErrorCode error)>;

/**
 * @brief   IAudioStream represents single audio stream with base properties
 */
class IAudioStream {
public:
   /**
    * Get the stream type like VOICE, PLAY, CAPTURE
    *
    * @returns    StreamType
    *
    * @note       Eval: This is a new API and is being evaluated. It is subject to change
    *             and could break backwards compatibility.
    */
   virtual StreamType getType() = 0;

   /**
    * Set Device of audio stream
    *
    * @param [in] devices     Devices list.
    * @param [in] callback    callback to get the response of setDevice.
    *
    * @returns Status of the request i.e. success or suitable status code.
    *
    * @note       Eval: This is a new API and is being evaluated. It is subject to change
    *             and could break backwards compatibility.
    */
   virtual telux::common::Status setDevice(std::vector<DeviceType> devices,
                                           telux::common::ResponseCallback callback = nullptr)
      = 0;

   /**
    * Get Device of audio stream
    *
    * @param [in] callback    callback to get the response of getDevice
    *
    * @returns Status of the request i.e. success or suitable status code.
    *
    * @note       Eval: This is a new API and is being evaluated. It is subject to change
    *             and could break backwards compatibility.
    */
   virtual telux::common::Status getDevice(GetStreamDeviceResponseCb callback = nullptr) = 0;

   /**
    * Set Volume of audio stream
    *
    * @param [in] volume     volume setting per channel for direction.
    * @param [in] callback   callback to get the response of setVolume.
    *
    * @returns Status of the request i.e. success or suitable status code.
    *
    * @note       Eval: This is a new API and is being evaluated. It is subject to change
    *             and could break backwards compatibility.
    */
   virtual telux::common::Status setVolume(StreamVolume volume,
                                           telux::common::ResponseCallback callback = nullptr)
      = 0;

   /**
    * Get Volume of audio stream
    *
    * @param [in] dir         Stream Direction to query volume details.
    * @param [in] callback    callback to get the response of getVolume.
    *
    * @returns Status of the request i.e. success or suitable status code.
    *
    * @note       Eval: This is a new API and is being evaluated. It is subject to change
    *             and could break backwards compatibility.
    */
   virtual telux::common::Status getVolume(StreamDirection dir,
                                           GetStreamVolumeResponseCb callback = nullptr)
      = 0;

   /**
    * Set Mute of audio stream
    *
    * @param [in] mute        mute setting for direction.
    * @param [in] callback    callback to know the status of the request.
    *
    * @returns Status of the request i.e. success or suitable status code.
    *
    * @note        Eval: This is a new API and is being evaluated. It is subject to change
    *              and could break backwards compatibility.
    */
   virtual telux::common::Status setMute(StreamMute mute,
                                         telux::common::ResponseCallback callback = nullptr)
      = 0;

   /**
    * Get Mute of audio stream
    *
    * @param [in] dir         Stream Direction to query mute details.
    * @param [in] callback    callback to get the response of getMute.
    *
    * @returns Status of the request i.e. success or suitable status code.
    *
    * @note        Eval: This is a new API and is being evaluated. It is subject to change
    *              and could break backwards compatibility.
    */
   virtual telux::common::Status getMute(StreamDirection dir,
                                         GetStreamMuteResponseCb callback = nullptr)
      = 0;
};

/**
 * @brief   IAudioVoiceStream represents single voice stream
 */
class IAudioVoiceStream : virtual public IAudioStream {
public:

   /**
    * Starts audio stream
    *
    * @param [in] callback    callback to get the response of startAudio.
    *
    * @returns Status of the request i.e. success or suitable status code.
    *
    * @note       Eval: This is a new API and is being evaluated. It is subject to change
    *             and could break backwards compatibility.
    */
   virtual telux::common::Status startAudio(telux::common::ResponseCallback callback = nullptr) = 0;

   /**
    * Stops audio stream
    *
    * @param [in] callback    callback to get the response of stopAudio.
    *
    * @returns Status of the request i.e. success or suitable status code.
    *
    * @note       Eval: This is a new API and is being evaluated. It is subject to change
    *             and could break backwards compatibility.
    */
   virtual telux::common::Status stopAudio(telux::common::ResponseCallback callback = nullptr) = 0;
};

/**
 * This function is called with the response to IAudioPlayStream::write().
 *
 * The callback can be invoked from multiple different threads.
 * The implementation should be thread safe.
 *
 * @param [in] buffer       Buffer that was used for the write operation. Application could call
 *                          IStreamBuffer::reset() and reuse this buffer for subsequent write
 *                          operations on the same stream.
 *
 * @param [in] bytesWritten Return how many bytes are written to the stream.
 *
 * @param [in] error        Return code which indicates whether the operation
 *                          succeeded or not.
 *                          @ref ErrorCode
 *
 * @note   Eval: This is a new API and is being evaluated. It is subject to
 *         change and could break backwards compatibility.
 */
using WriteResponseCb
    = std::function<void(std::shared_ptr<IStreamBuffer> buffer, uint32_t bytesWritten,
                                                            telux::common::ErrorCode error)>;

/**
 * @brief   IAudioPlayStream represents single audio playback stream
 */
class IAudioPlayStream : virtual public IAudioStream {
public:

   /**
    * Get an Audio StreamBuffer to be used for playback operations
    *
    * @returns            an Audio Buffer or a nullptr in case of error
    *
    * @note    Eval: This is a new API and is being evaluated. It is subject to change
    *          and could break backwards compatibility.
    */
   virtual std::shared_ptr<IStreamBuffer> getStreamBuffer() = 0;

   /**
    * Write Samples to audio stream. First write starts playback operation.
    *
    * @param [in] buffer       stream buffer for write.
    * @param [in] callback     callback to get the response of write.
    *
    * @returns Status of the request i.e. success or suitable status code.
    *
    * @note       Eval: This is a new API and is being evaluated. It is subject to change
    *             and could break backwards compatibility.
    */
   virtual telux::common::Status write(std::shared_ptr<IStreamBuffer> buffer,
                    WriteResponseCb callback = nullptr) = 0;
};


/**
 * This function is called with the response to IAudioCaptureStream::read().
 *
 * The callback can be invoked from multiple different threads.
 * The implementation should be thread safe.
 *
 * @param [in] buffer Buffer that was used to capture the data from the read operation.
 *                    Applications could call IStreamBuffer::reset() and reuse this buffer for
 *                    subsequent read operations on the same stream. Also buffer.getDataSize()
 *                    will represent the number of bytes read.
 *
 * @param [in] error  Return code which indicates whether the operation
 *                    succeeded or not.
 *                    @ref ErrorCode
 *
 * @note   Eval: This is a new API and is being evaluated. It is subject to
 *         change and could break backwards compatibility.
 */
using ReadResponseCb
    = std::function<void(std::shared_ptr<IStreamBuffer> buffer,
                                        telux::common::ErrorCode error)>;

/**
 * @brief   IAudioCaptureStream represents single audio capture stream
 */
class IAudioCaptureStream : virtual public IAudioStream {
public:

   /**
    * Get an Audio Stream Buffer to be used for capture operations
    *
    * @returns            an Audio Buffer or nullptr in case of failure
    *
    * @note    Eval: This is a new API and is being evaluated. It is subject to change
    *          and could break backwards compatibility.
    */
   virtual std::shared_ptr<IStreamBuffer> getStreamBuffer() = 0;

   /**
    * Read Samples from audio stream. First read starts capture operation.
    *
    * @param [in] buffer       stream buffer for read.
    * @param [in] bytesToRead  specifying how many bytes to be read from stream.
    * @param [in] callback     callback to get the response of read.
    *
    * @returns Status of the request i.e. success or suitable status code.
    *
    * @note       Eval: This is a new API and is being evaluated. It is subject to change
    *             and could break backwards compatibility.
    */
   virtual telux::common::Status read(std::shared_ptr<IStreamBuffer> buffer, uint32_t bytesToRead,
                                      ReadResponseCb callback = nullptr) = 0;
};


/** @} */ /* end_addtogroup telematics_audio */
}  // End of namespace audio

}  // End of namespace telux

#endif  // end of AUDIOMANAGER_HPP
