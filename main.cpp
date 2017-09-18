#include <iostream>
#include <vector>
#include "MySql.hpp"

using namespace std;


int main()
{
	MySql ms;
	if( !ms.init("127.0.0.1","root","1234","KDS_MONI_JTCS") ) {
		std::cout << "init err"<<std::endl;
	}
	if( !ms.reconnect() ) {
		std::cout<< "reconnect err" << std::endl;
	}
	std::string sql = "select * from TBL_SYS_H5_VERSION;";
	// if(! ms.execute_sql(sql) ) {
	// 	std::cout << "execute_sql err" <<std::endl;
	// }
	vector<vector<string> > ves;

	ms.select_data(sql,ves);

	for(vector<vector<string> >::iterator itt=ves.begin(); itt!=ves.end(); ++itt) {
		for( vector<string>::iterator it = itt->begin(); it != itt->end(); ++it) {
			std::cout << *it <<" "; 
		}
		std::cout<<std::endl;
	}

	// cout <<"4"<<endl;
	if( !ms.close_connect() ) {
		std::cout << ms.get_err_msg() << std::endl;
	}

	return 0;
}