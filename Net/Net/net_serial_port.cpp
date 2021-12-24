/*******************************************************************************
 * 文 件 名 称 ： net_Serial_port.cpp
 * 功 能 描 述 ： 串口发送模块（测试代码）
 * 开 发 人 员 ： GongMinghao
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2021-08-18 V1.0    GongMinghao   Create
 *
 * @Copyright (C)  2021  .wanji. all right reserved
*******************************************************************************/
#include <asio2/asio2.hpp>


std::string_view device = "/dev/ttyS0"; //要看bsp那边串口
std::string_view baud_rate = "9600";    //波特率

asio2::scp sp;


static void SerialPortConnect()
{

	sp.start_timer(1, std::chrono::seconds(1), []() {});

	sp.bind_init([&]()
	{
		// Set other serial port parameters at here
		sp.socket().set_option(asio::serial_port::flow_control(asio::serial_port::flow_control::type::none));
		sp.socket().set_option(asio::serial_port::parity(asio::serial_port::parity::type::none));
		sp.socket().set_option(asio::serial_port::stop_bits(asio::serial_port::stop_bits::type::one));
		sp.socket().set_option(asio::serial_port::character_size(8));

	}).bind_recv([&](std::string_view sv)
	{
		printf("recv : %u %.*s\n", (unsigned)sv.size(), (int)sv.size(), sv.data());

		std::string s;
		s = "测试数据fjdaklhfqekjerhgjegr";
		sp.send(s, []() {});

	}).bind_start([&](asio::error_code ec)
	{
		printf("start : %d %s\n", asio2::last_error_val(), asio2::last_error_msg().c_str());
	}).bind_stop([&](asio::error_code ec)
	{
		printf("stop : %d %s\n", asio2::last_error_val(), asio2::last_error_msg().c_str());
	});

	//sp.start(device, baud_rate);
	sp.start(device, baud_rate, '>');
	//sp.start(device, baud_rate, "\r\n");
	//sp.start(device, baud_rate, match_role);
	//sp.start(device, baud_rate, asio::transfer_at_least(1));
	//sp.st;art(device, baud_rate, asio::transfer_exactly(10));
};

void SerialPortSend(const char* p_data, unsigned int p_len)
{
	sp.send(p_data,p_len);
	// sp.send(p_data, [](std::size_t bytes_sent)
	// {
	// 	printf("send : %u %d %s\n", (unsigned)bytes_sent,
	// 		asio2::last_error_val(), asio2::last_error_msg().c_str());
	// });
} 

static void NetSerialPortThread()
{
	SerialPortConnect();
}

void NetSerialPortInit(void)
{
	//初始化

	//创建线程
	std::thread m_netSerialPort(NetSerialPortThread);

	if (m_netSerialPort.joinable())
		m_netSerialPort.detach();
}