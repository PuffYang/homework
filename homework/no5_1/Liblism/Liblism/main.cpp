#include"bits/stdc++.h"
#include"Library.h"
using namespace std;

#define _VSSTUDIO

int main(int argc, char* argv[]) {
	//�����������Դ
	Library library;

	//���������в��� �ж��û�
	#ifndef _VSSTUDIO
		cmdline::parser parser;
		parser.add<string>("type", 't', "the type of user��one of {admin,reader}", true, "", cmdline::oneof<string>("admin", "reader"));
		parser.add<string>("passwd", 'p', "the passwd of admin", false, "");
		parser.parse_check(argc, argv);
	#endif // !_VSSTUDIO


	while (true) {
		//todo: ��ʾ�����  ��ȡ���� �жϲ���

		break;
	}

	return 0;
}
