#pragma once
//
// Created by choco on 10/4/2022.
//

#ifndef LIBSIM_LIBRARY_H
#define LIBSIM_LIBRARY_H

#pragma once

#include "bits/stdc++.h"
#include "basic_member.h"
#include <regex>

using namespace std;
// using namespace std;

class Library
{
	//ͨ��id ������
	std::map<int, book> id_booklist;

	//ͨ��id�Ҷ���
	std::map<int, reader> id_reader;

	//ͨ�����������Ҷ���id (����������)
	std::map<std::string, int> name_reader_id;

	//ͨ����������id
	std::map<std::string, int> name_booklistname_id;

	//ͨ�������ҽ�����˵�id
	std::map<int, std::vector<int>> lent_book;

	std::map<int, admin> admin_list;

	void info_parser(string mess)
	{
		regex pat(R"(,)");
		sregex_token_iterator pos(mess.begin(), mess.end(), pat, -1);
		sregex_token_iterator end;
		int user_id = stoi(pos->str());
		pos++;
		string user_name = pos->str();
		pos++;
		int book_id = stoi(pos->str());
		pos++;
		string book_name = pos->str();
		add_id_book_list(book_id, book_name);
		add_id_reader(user_id, user_name);
		add_lent_book(user_id, book_id);
	}

	void admin_parser(string mess)
	{
		regex pat(R"(,)");
		sregex_token_iterator pos(mess.begin(), mess.end(), pat, -1);
		sregex_token_iterator end;
		int admin_id = stoi(pos->str());
		pos++;
		string admin_name = pos->str();
		pos++;
		string admin_passwd = pos->str();
		admin_list[admin_id] = admin{ admin_id, admin_name, admin_passwd };
	}

	void add_lent_book(int user_id, int book_id)
	{
		if (!lent_book.count(book_id))
		{
			lent_book[book_id] = vector<int>(1, user_id);
		}
		else
			lent_book[book_id].push_back(user_id);
	}

	void add_id_reader(int user_id, const string& user_name)
	{
		if (!id_reader.count(user_id))
		{
			id_reader[user_id] = reader{ user_id, user_name };
			name_reader_id[user_name] = user_id;
		}
		else
		{
			cout << "����id�ظ������ʧ��" << endl;
		}
	}

	void add_id_book_list(int book_id, const string& book_name)
	{
		if (!id_booklist.count(book_id))
		{
			id_booklist[book_id] = book{ book_name, book_id, 1 };
			name_booklistname_id[book_name] = book_id;
		}
		else
		{
			id_booklist[book_id].setNum(id_booklist[book_id].getNum() + 1);
		}
	}

	void data_loader()
	{
		info_loader();
		admin_loader();
	}

	void info_loader()
	{
		FILE* fp = fopen("info_table.csv", "r");
		if (!fp)
		{

			cout << "�������ʧ�ܣ������Ƿ���ڳ�ʼ���ļ�info_table.csv" << endl;
			std::cout << "�Զ����ɳ�ʼ���ļ�info_table.csv��" << std::endl;
			//freopen("info_table.csv", "w", stdout);
			fp = fopen("info_table.csv", "w");
			fputs("1,user,1,����֮�������ԭ", fp);
	
			fclose(fp);
		}

		{
			/*freopen("info_table.csv", "r", stdin);*/
			ifstream inFile("info_table.csv");
			string temp;
			while (getline(inFile,temp))
			{
				cout << temp << endl;
				info_parser(temp);
			}
			inFile.close();
		}
	}

	void admin_loader()
	{

		FILE* fp = fopen("admin_table.csv", "r");

		if (fp == NULL)
		{
			cout << "�������ʧ�ܣ������Ƿ���ڳ�ʼ���ļ�admin_table.csv" << endl;
			std::cout << "�Զ����ɳ�ʼ���ļ�admin_table.csv��" << std::endl;
			fp = fopen("admin_table.csv", "w");
			fputs("1,admin,123456", fp);
			//cout << "1,admin,123456" << endl;
			fclose(fp);
		}

		{
			//freopen("admin_table.csv","r",stdin);
			ifstream inFile("admin_table.csv");

			string temp;
			while (getline(inFile,temp))
			{
				cout << temp << endl;
				admin_parser(temp);
			}
			inFile.close();
		}
	}








public:
	Library()
	{
		cout << "��ӭʹ��ͼ�����ϵͳ,���ݼ�����" << endl;
		data_loader();
		cout << "���ݼ��ؽ���" << endl;
	}
};

#endif // LIBSIM_LIBRARY_H
