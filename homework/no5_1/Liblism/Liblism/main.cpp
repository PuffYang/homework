#include"bits/stdc++.h"
#include"Library.h"
#include"cmdline.h"
#include "main.h"
using namespace std;

//������ѭ���ο�����
//while (true) {
//	//todo: ��ʾ�����  ��ȡ���� �жϲ���
//	switch (1)
//	{
//	case quit:
//		cout << "�������" << endl;
//		flag = false;
//	}
//	if (!flag)break;
//}



//#define _DEVELOP  // ������������в�����⣬��ע�͵�����




// todo:��ö���������������case���Ŀɶ���
enum Choice {
	quit = 10,
};

enum Model {
	admin = 0, reader = 1
};



//�жϳ����Ƿ���˳�
bool flag = true;




int main(int argc, char* argv[]) {


#ifndef _DEVELOP
	Model model = commandline_parse(argc, argv);
#endif // _DEVELOP

	
	if (model == reader) {
		//�����û�����ĺ���
		;
	}
	else {
		// 1. �жϹ���������ȷ�ĺ���  2. admin����ĺ���

		
	}



	return 0;
}

Model commandline_parse(int argc, char* argv[])
{

	//���������в��� �ж��û�
	cmdline::parser parser;
	parser.add<string>("type", 't', "the type of user��one of {admin,reader}", true, "", cmdline::oneof<string>("admin", "reader"));
	parser.add<string>("passwd", 'p', "the passwd of admin", false, "");
	parser.parse_check(argc, argv);


	//�����������Դ
	Library library;

	string type = parser.get<string>("type"), passwd = parser.get<string>("passwd");
	Model model;
	if (type == "admin") {
		model = admin;
	}
	else model = reader;


	return model;
}
