#include"common.h"
#include"Database.h"


int main()
{
	Database data;
	char buff[1024];
	io_service service;
	//考虑到应用场景，使用udp和同步通信
	ip::udp::socket sock(service, ip::udp::endpoint(ip::udp::v4(), 6666));

	while (true)
	{
		//记录发送方端口
		ip::udp::endpoint sender_ep;
		//接收
		int bytes = sock.receive_from(buffer(buff), sender_ep);

		//调用command解析用户的命令，把结果存储在t中
		string t(data.command(string(buff, bytes)));
		//把结果发回用户
		sock.send_to(buffer(t), sender_ep);
	}
}