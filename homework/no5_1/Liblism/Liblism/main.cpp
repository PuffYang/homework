#include"bits/stdc++.h"
#include"Library.h"
#include"cmdline.h"

using namespace std;

Library library;

enum Model {
	ADMIN = 0, READER = 1
};
//��¼����Ϣ
Login login;

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




//�жϳ����Ƿ���˳�
bool flag = true;



Model commandline_parse(int argc, char* argv[], Library& library)
{

	//���������в��� �ж��û�
	cmdline::parser parser;
	parser.add<string>("type", 't', "the type of user��one of {Admin,Reader}", true, "", cmdline::oneof<string>("Admin", "Reader"));
	parser.add<string>("name", 'n', "your name", true);
	parser.add<int>("id",'i',"your id",true);
	parser.add<string>("passwd", 'p', "the passwd of admin if login as admin", false, "");
	parser.parse_check(argc, argv);



	cout << "----------------------------" << endl;
	string type = parser.get<string>("type"), name = parser.get<string>("name"), passwd = parser.get<string>("passwd");
	int id = parser.get<int>("id");
	login.name = name;
	login.id = id;

	Model model;

	if (type == "Admin") {
		model = ADMIN;
		if (library.check_valid_admin(id, name, passwd)) {
			cout << "��ӭ����Ա" << name << "��¼" << endl;
		}
		else {
			cout << "��Ϣ����������Ϣ" << endl;
			exit(0);
		}
	}
	else {
		model = READER;

		cout << "��ӭ����" << name << "��¼" << endl;



	}



	return model;
}




class admin_opt {
public:
	void static insert_book(const book& src) {
		bool flag = true;
		for (auto& item : library.remain_book_list) {
			if (item.name == src.name) {
				auto temp = item;
				temp.num++;
				library.remain_book_list.erase(item);
				library.remain_book_list.insert(temp);
				flag = false;
			}
		}
		if (flag) {
			library.remain_book_list.insert(src);

		}
		return;

	}

};


int main(int argc, char* argv[]) {
	
	
#ifndef _DEVELOP
	Model model = commandline_parse(argc, argv, library);
#endif // _DEVELOP


	//��¼������login
	if (model == READER) {
		//�����û�����ĺ���
		;
	}
	else {
		// admin����ĺ���
		//admin opt;
		////admin.
		//admin_opt::insert_book({ "x",1,1 });

		
	}



	return 0;
}
