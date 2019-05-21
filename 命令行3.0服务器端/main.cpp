#include"common.h"
#include"Database.h"


int main()
{
	Database data;
	char buff[1024];
	io_service service;
	//���ǵ�Ӧ�ó�����ʹ��udp��ͬ��ͨ��
	ip::udp::socket sock(service, ip::udp::endpoint(ip::udp::v4(), 6666));

	while (true)
	{
		//��¼���ͷ��˿�
		ip::udp::endpoint sender_ep;
		//����
		int bytes = sock.receive_from(buffer(buff), sender_ep);

		//����command�����û�������ѽ���洢��t��
		string t(data.command(string(buff, bytes)));
		//�ѽ�������û�
		sock.send_to(buffer(t), sender_ep);
	}
}