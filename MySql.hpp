#ifndef __MYSQL_HPP__
#define __MYSQL_HPP__
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <mysql/mysql.h>

// #define DEFAULT_RECONNECT_TIME	5   //默认重连次数
// #define DEFAULT_PORT    		7379
// #define DEFAULT_IP       		127.0.0.1


using namespace std;

class MySql
{
public:
	MySql();
	~MySql();
public:
	bool init(const string& host,const string& user,
				const string& pw,const string& db,
				int port = 3306,const string code="utf8");

	bool reconnect();

	bool close_connect();

	bool execute_sql(const string& sql);

	bool select_data(const string& sql, vector< vector<string> >& result_matrix );

	string get_err_msg();

private:
	bool connect();

private:
	MYSQL m_mysql;
	string m_host;
	string m_user;
	string m_pw;
	string m_db;
	int    m_port;
	string m_code;	
};



#endif