/*******************************************************************************
 * 文 件 名 称 ： net_udp_Server.cpp
 * 功 能 描 述 ： UDP Server
 * 开 发 人 员 ： GongMinghao
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2021-08-18 V1.0    GongMinghao   Create
 *
 * @Copyright (C)  2021  .wanji. all right reserved
*******************************************************************************/
#include <set>
#include <thread>
#include <chrono>
#include <iostream>
#include <signal.h>
#include <asio2/asio2.hpp>


std::string_view host = "0.0.0.0";
std::string_view port = "5555";

asio2::udp_server server;
static void udpServerConnect()
{
	server.bind_recv([](std::shared_ptr<asio2::udp_session>& session_ptr, std::string_view s)
    {
        char dst[255];
        printf("recv : %u \n", (unsigned)s.size());
        printf("udp recv is:");
        for(int i=0; i <s.length(); ++i)
        { 
            dst[i]=s[i];
            printf("%0.2X ",dst[i]);     
        }
        printf("\n");
            
        //session_ptr->send("你才是傻逼", []() {});
    }).bind_connect([](auto& session_ptr)
    {
        printf("client enter : %s %u %s %u\n", session_ptr->remote_address().c_str(), session_ptr->remote_port(),
            session_ptr->local_address().c_str(), session_ptr->local_port());
    }).bind_disconnect([](auto& session_ptr)
    {
        printf("client leave : %s %u %s\n", session_ptr->remote_address().c_str(),
            session_ptr->remote_port(), asio2::last_error_msg().c_str());
    }).bind_handshake([](auto& session_ptr, asio::error_code ec)
    {
        printf("client handshake : %d %s\n", asio2::last_error_val(), asio2::last_error_msg().c_str());
    }).bind_start([&](asio::error_code ec)
    {
        if (asio2::get_last_error())
            printf("start udp server kcp failure : %d %s\n", asio2::last_error_val(), asio2::last_error_msg().c_str());
        else
            printf("start udp server kcp success : %s %u\n", server.listen_address().c_str(), server.listen_port());
        //server.stop();
    }).bind_stop([&](asio::error_code ec)
    {
        printf("stop : %d %s\n", asio2::last_error_val(), asio2::last_error_msg().c_str());
    }).bind_init([&]()
    {

    });

	server.start(host, port);
}
static void NetUdpServerThread()
{
	udpServerConnect();
}
void NetUdpServerInit(void)
{
	//初始化

	//创建线程
	std::thread m_netUdpServer(NetUdpServerThread);

	if (m_netUdpServer.joinable())
		m_netUdpServer.detach();
}