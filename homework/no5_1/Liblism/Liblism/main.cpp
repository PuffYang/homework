#include"bits/stdc++.h"
#include"Library.h"
#include"cmdline.h"
#include "main.h"

using namespace std;

Library library;

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








// ---------------------------------��ģ��-------------------------------//
class reader_opt {
public:
	void static return_book(int id) {
		auto& tar = library.id_reader[login.id];
		//auto res = lower_bound(tar.lent_book.begin(), tar.lent_book.end(), id);
		//bool flag = true;
		int mark = -1;
		for (int i = 0; i < tar.lent_book.size(); ++i) {
			if (tar.lent_book[i] == id) {
				mark = i;
				break;
			}

		}
		
		if (mark==-1) {
			cout << "���޴���,��������" << endl;
		}

		else {
			tar.lent_book.erase(mark+tar.lent_book.begin());
			cout << "�ѹ黹ͼ��" << library.id_booklist[id].name << "," << "��idΪ" << id << endl;
			bool flag = true;
			for (auto& item : library.remain_book_list) {
				
				if (item.id == id) {
					auto temp = item;
					temp.num++;
					//���޷�������Ǳ�ڷ���
					library.remain_book_list.erase(item);
					library.remain_book_list.insert(temp);
					remove_relation_book_lent_reader(id);

					flag = false;
					break;
				}
			}
			if (flag) {
				book temp = library.id_booklist[id];
				temp.num = 1;
				library.remain_book_list.insert(temp);
				remove_relation_book_lent_reader(id);
			}
		}


	}

	void static borrow_book(int id) {
		auto& tar = library.remain_book_list;
		auto res = lower_bound(tar.begin(), tar.end(), book{ "_",id ,1 });
		if (res != tar.end()) {
			bool flag = false;
			if ((*res).num != 1) {
				//tar.erase(res);
				flag = true;
			}
			//else (*res).num -= 1;
			string name = (*res).name;
			tar.erase(res);
			if (flag) {
				auto temp = *res;
				temp.num--;
				tar.insert(temp);
			}
			cout << "���" << name << "�ɹ�!" << endl;
			//library.lent_book[login.id].push_back(id);
			
			library.id_reader[login.id].lent_book.push_back(id);
			library.lent_book[id].push_back(login.id);

		}
		else cout << "���޴���" << endl;

	}


	void static query_remain_book() {
		cout << "ʣ�����" << endl << "id" << "---" << "name" << "---" << "num" << endl;
		for (auto& item : library.remain_book_list) {
			cout << item.id << " " << item.name << " " << item.num << endl;

		}
	}

	void static query_borrowed_book() {
		cout << "���Ľ���ͼ���idΪ:" << endl;
		for (auto item : library.id_reader[login.id].lent_book) {
			cout << library.id_booklist[item].name << " " << library.id_booklist[item].id << endl;
		}
	}

private:
	void static remove_relation_book_lent_reader(int id) {
		auto& relation = library.lent_book[id];
		for (int i = 0; i < relation.size(); ++i) {
			if (relation[i] == login.id) {
				relation.erase(relation.begin() + i);
				break;
			}
		}
	}
};


class admin_opt {
public:
	void static query_book_by_remain() {
		cout << "ʣ�����" << endl << "id" << "---" << "name" << "---" << "num" << endl;
		for (auto& item : library.remain_book_list) {
			cout << item.id << " " << item.name << " " << item.num << endl;

		}

	}


	void static insert_book(const book& src) {
		//auto& tar = library.remain_book_list;
		//auto get = lower_bound(tar.begin(), tar.end(), book("asd", src, 1));
		bool flag = true;
		for (auto& item : library.remain_book_list) {
			if (item.name == src.name) {
				/*auto temp = item;
				temp.num++;
				library.remain_book_list.erase(item);
				library.remain_book_list.insert(temp);
				flag = false;*/
				cout << "���д��飬��ʹ�ø��²���" << endl;
				flag = false;
			}
		}
		if (flag) {
			library.book_num++;
			library.remain_book_list.insert(src);
			cout << "��" << src.name << "����ӳɹ�,idΪ" << src.id << endl;
		}

		return;

	}
	void static drop_book(int id) {
		auto& tar = library.remain_book_list;
		auto get = lower_bound(tar.begin(), tar.end(), book("asd", id, 1));
		if (get != tar.end() && (*get).id == id) {
			string name = (*get).name;
			tar.erase(get);

			cout << "�����ɹ�����ɾ��" << name << endl;
		}
		else cout << "���޴��飬ɾ������" << endl;

	}

	void static update_book(int id, int num) {
		auto& tar = library.remain_book_list;
		auto get = lower_bound(tar.begin(), tar.end(), book("_", id, 1));
		if (get != tar.end() && (*get).id == id) {
			tar.erase(get);
			auto temp = *get;
			if (temp.num + num <= 0) {
				cout << "���´��󣬼���Ƿ񳬳�����Ŀ�ķ�Χ" << endl;
			}
			else {
				temp.num += num;
				tar.insert(temp);
				cout << "���³ɹ�," << temp.name << "���" << num << "��" << endl;
			}
			//cout << "�����ɹ�����ɾ��" << src.name << endl;
		}
		else cout << "���޴��飬�޸Ĵ������" << endl;

	}

	void static insert_reader(int id, string name) {
		auto& tar = library.reader_list;
		tar.insert({ id,name });
		cout << "����" << name << "����ɹ�. idΪ" << id << endl;
	}

	void static drop_reader(int id) {
		auto& tar = library.reader_list;
		auto ans = lower_bound(tar.begin(), tar.end(), reader{ id,"_" });
		if (ans != tar.end()) {
			cout << (*ans).name << "�Ѿ�ɾ��" << endl;
			tar.erase(ans);
			auto book_name = library.id_booklist[id].name;
			library.id_booklist.erase(id);
			library.name_book_id.erase(book_name);
		}
		else {
			cout << "���޴��ˣ���������" << endl;
		}
	}

	void static query_user() {
		auto& tar = library.reader_list;
		cout << "id---" << "name" << endl;
		for (auto item : tar) {
			cout << item.id << " " << item.name << endl;
		}

	}
	void static query_whole() {
		cout << "ͼ��ܵ�ǰͼ����ĿΪ:" << library.book_num << endl;
		cout << "ͼ��ݹ���Ա����Ϊ:" << library.admin_num << endl;
		cout << "ͼ��ݵ�ǰ�û�����Ϊ" << library.reader_num << endl;

	}

	void static query_book_by_id(int id) {
		if (id > library.book_num) {
			cout << "�����ڴ��飬��������" << endl;
		}
		else {
			auto& tar = library.lent_book;
			
			if (!tar.count(id)) {
				cout << "����δ���" << endl;
			}
			else {
				auto& res = tar[id];
				cout << "�������Ķ���Ϊ:";
				for (int idx : (res)) {
					auto& get = library.id_reader[idx];
					cout << " " << get.name;
				}
				cout << endl;
			}
		}
	}
	void static query_book_by_name(string name) {
		auto& tar = library.name_book_id;
		if (!tar.count(name)) {
			cout << "���޴�����߸���δ�����" << endl;
		}
		else {
			int book_id = tar[name];
			query_book_by_id(book_id);
		}

	}
};


void admin_loop()
{

	while (true) {
		cout << "\n" << "*********************" << "\n";
		cout << "��ѡ�����" << "\n"
			<< "1. ����ͼ��" << "\n"
			<< "2. ɾ��ͼ��" << "\n"
			<< "3. ��ѯδ���ͼ��" << "\n"
			<<"4. ��id��ѯ�ѽ��ͼ��"<<"\n"
			<<"5. �����ֲ�ѯ�ѽ��ͼ��"<<'\n'
			<< "6. �޸�ͼ��" << "\n"
			<< "7. ���Ӷ���" << "\n"
			<< "8. ɾ������" << "\n"
			<< "9. ��ѯ����" << "\n"
			<< "10. ��ѯͼ����������" << "\n"
			<< "11. �˳�����" << endl;
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
		_sleep(1000);
		cout << "\n" << "*********************" << "\n";
	}

}

void reader_loop()
{
	//�����û�����ĺ���
	while (true) {
		cout << "\n" << "*********************" << "\n";
		cout << "1. ����" << "\n"
			<< "2. ����" << "\n"
			<< "3. ��ѯ�ɽ��鼮" << '\n'
			<< "4. ��ѯ�ѽ�ͼ��" << '\n'
		<< "5. ��������" << endl;
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
		_sleep(1000);
		cout << "\n" << "*********************" << "\n";
	}

}
//���������л�
//todo: ����
void close_session() {

	FILE* fp = fopen(R"(./data/admin_table.csv)", "w");
	//fputs("sad", fp);
	if (fp)
	{
		for (auto& item : library.admin_list) {
			string res = to_string(item.id) + "," + item.name + "," + item.passwd+"\n";
			//cout <<res<<" "<< res.c_str() << endl;
			fputs(res.c_str(), fp);
		}
	}
	fclose(fp);

	fp = fopen(R"(./data/reader_table.csv)", "w");
	if (fp) {
		for (auto& item : library.reader_list) {
			string res = to_string(item.id) + "," + item.name+"\n";
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
				string res = to_string(Reader.id) + "," + to_string(t_book.id) + "," + t_book.name+"\n";
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
			string res = to_string(item.id) + "," + item.name + "," + to_string(item.num)+"\n";
			fputs(res.c_str(), fp);
		}

	}
	fclose(fp);



	fp = fopen(R"(./data/config.csv)", "w");
	if (fp) {

		string res = to_string(library.book_num) + "," + to_string(library.admin_num) + "," + to_string(library.reader_num)+"\n";

		fputs(res.c_str(), fp);

	}
	fclose(fp);
}


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