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









//�жϳ����Ƿ���˳�
bool flag = true;


int main(int argc, char* argv[]) {


#ifndef _DEVELOP
	Model model = commandline_parse(argc, argv, library);
#endif // _DEVELOP


	//��¼������login
	if (model == READER) {
		reader_loop();
	}
	else {
		// admin����ĺ���
		//admin opt;
		admin_loop();

	}



	return 0;
}







inline void admin_loop()
{

	while (true) {
		cout << "\n" << "*********************" << "\n";
		cout << "��ѡ�����" << "\n"
			<< "1. ����ͼ��" << "\n"
			<< "2. ɾ��ͼ��" << "\n"
			<< "3. ��ѯδ���ͼ��" << "\n"
			<< "4. ��id��ѯ�ѽ��ͼ��" << "\n"
			<< "5. �����ֲ�ѯ�ѽ��ͼ��" << '\n'
			<< "6. �޸�ͼ��" << "\n"
			<< "7. ���Ӷ���" << "\n"
			<< "8. ɾ������" << "\n"
			<< "9. ��ѯ����" << "\n"
			<< "10. ��ѯͼ����������" << "\n"
			<< "11. ���������������˳�" << endl;
		int opt;
		scanf("%d", &opt);
		switch (opt)
		{

		case INSERT_BOOK:
		{
			cout << "������Ҫ������������������Ŀ" << endl;
			string name; int num;
			cin >> name >> num;
			//library.book_num++;

			book temp(name, library.book_num + 1, num);
			admin_opt::insert_book(temp);
			break;
		}
		case DROP_BOOK:
		{
			cout << "������Ҫɾ�������id" << endl;
			int id;
			cin >> id;
			admin_opt::drop_book(id);
			break;
		}

		case QUERY_BOOK_BY_REMAIN:
		{
			admin_opt::query_book_by_remain();
			break;
		}

		case QUERY_BOOK_BY_ID:
		{
			cout << "���������ѯ�����id" << endl;
			int id;
			cin >> id;
			admin_opt::query_book_by_id(id);
			break;
		}

		case QUERY_BOOK_BY_NAME:
		{
			cout << "���������ѯ���������" << endl;
			string name;
			cin >> name;
			admin_opt::query_book_by_name(name);
			break;
		}

		case UPDATE_BOOK:
		{
			cout << "������Ҫ��������id����Ŀ" << endl;
			int id, num;
			cin >> id >> num;
			admin_opt::update_book(id, num);
			break;
		}

		case INSERT_USER:
		{
			cout << "������Ҫ������û���" << endl;
			string name;
			cin >> name;
			library.reader_num++;
			admin_opt::insert_reader(library.reader_num, name);
			break;
		}
		case DROP_USER:
		{
			int id;
			cout << "������Ҫɾ���ĵ��û�id" << endl;
			cin >> id;
			admin_opt::drop_reader(id);
			break;
		}

		case QUERY_USER:
		{
			admin_opt::query_user();
			break;
		}
		case QUERY_WHOLE_INFO:
		{
			admin_opt::query_whole();
			break;

		}
		case QUIT_ADMIN:
		{
			close_session();
			cout << "Ӧ�ý���" << endl;
			exit(0);
		}
		default:
			cout << "����������������������" << endl;
			break;
		}
		system("timeout /nobreak /t 2 ");
		cout << "\n" << "*********************" << "\n";
	}

}

inline void reader_loop()
{
	//�����û�����ĺ���
	while (true) {
		cout << "\n" << "*********************" << "\n";
		cout << "1. ����" << "\n"
			<< "2. ����" << "\n"
			<< "3. ��ѯ�ɽ��鼮" << '\n'
			<< "4. ��ѯ�ѽ�ͼ��" << '\n'
			<< "5. ���������������˳�" << endl;
		int opt;
		cin >> opt;
		switch (opt)
		{
		case BORROW_BOOK:
		{
			cout << "������Ҫ��ͼ���id:" << endl;
			int id;
			cin >> id;
			reader_opt::borrow_book(id);
			break;
		}

		case RETURN_BOOK:
		{
			cout << "Ҫ�黹ͼ��id:" << endl;
			int id;
			cin >> id;
			reader_opt::return_book(id);
			break;
		}
		case QUERY_REMAIN_BOOK:
		{

			reader_opt::query_remain_book();
			break;
		}
		case QUERY_BORROWED_BOOK:
		{
			reader_opt::query_borrowed_book();
			break;
		}
		case QUIT_USER:
		{
			cout << "�������" << endl;
			close_session();
			exit(0);
		}
		default:
			cout << "����������������������" << endl;
			break;
		}
		system("timeout /nobreak /t 2");
		cout << "\n" << "*********************" << "\n";
	}

}

// �ж���������Ϸ���
Model commandline_parse(int argc, char* argv[], Library& library)
{

	//���������в��� �ж��û�
	cmdline::parser parser;
	parser.add<string>("type", 't', "the type of user��one of {Admin,Reader}", true, "", cmdline::oneof<string>("Admin", "Reader"));
	parser.add<string>("name", 'n', "your name", true);
	parser.add<int>("id", 'i', "your id", true);
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
		if (library.check_valid_reader(id, name))
		{
			cout << "��ӭ����" << name << "��¼" << endl;
		}
		else {
			cout << "��Ϣ����������Ϣ" << endl;
			exit(0);
		}

	}



	return model;
}

//���������л�
void close_session() {

	FILE* fp = fopen(R"(./data/admin_table.csv)", "w");
	//fputs("sad", fp);
	if (fp)
	{
		for (auto& item : library.admin_list) {
			string res = to_string(item.id) + "," + item.name + "," + item.passwd + "\n";
			//cout <<res<<" "<< res.c_str() << endl;
			fputs(res.c_str(), fp);
		}
	}
	fclose(fp);

	fp = fopen(R"(./data/reader_table.csv)", "w");
	if (fp) {
		for (auto& item : library.reader_list) {
			string res = to_string(item.id) + "," + item.name + "\n";
			fputs(res.c_str(), fp);
		}
	}
	fclose(fp);

	fp = fopen(R"(./data/info_table.csv)", "w");
	if (fp) {
		for (auto& item : library.id_reader) {
			const auto& Reader = item.second;
			for (auto& id : Reader.lent_book) {
				const auto& t_book = library.id_booklist[id];
				string res = to_string(Reader.id) + "," + to_string(t_book.id) + "," + t_book.name + "\n";
				fputs(res.c_str(), fp);
			}
			//book b1 = library.id_booklist[item.first];
			///*reader r1 = library*/
			//reader r1 = library.id_reader[item.first];

			//string res = to_string(r1.id) + "," + r1.name + "," + to_string(b1.id) + "," + b1.name + ",";
			//fputs(res.c_str(), fp);

		}

	}

	fclose(fp);

	fp = fopen(R"(./data/remain_book_table.csv)", "w");
	if (fp) {
		for (auto& item : library.remain_book_list) {
			string res = to_string(item.id) + "," + item.name + "," + to_string(item.num) + "\n";
			fputs(res.c_str(), fp);
		}

	}
	fclose(fp);



	fp = fopen(R"(./data/config.csv)", "w");
	if (fp) {

		string res = to_string(library.book_num) + "," + to_string(library.admin_num) + "," + to_string(library.reader_num) + "\n";

		fputs(res.c_str(), fp);

	}
	fclose(fp);
}




