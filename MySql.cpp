#include "MySql.hpp"


MySql::MySql(){}

MySql::~MySql(){
	mysql_close(&m_mysql);
}

/*
 * @brief 初始化mysql连接 
 * @parameter host IP / user 用户 / pw 数据库密码  / db  数据库  / port 端口
 * @return bool 值
 */
bool MySql::init(const string& host,const string& user,
				const string& pw,const string& db,
				int port,const string code )
{
	m_host = host;  
    m_user = user;  
    m_pw = pw;  
    m_db = db;  
    m_port = port;  
    m_code = code;  
    return NULL != mysql_init(&m_mysql) && connect() && execute_sql(("set names " + m_code+";") );
}

/*
 * @brief 执行sql语句，SQL语句无返回
 * @parameter sql语句
 * @return bool类型返回
 */
bool MySql::execute_sql(const string& sql){
    int res = mysql_real_query(&m_mysql,sql.c_str(),sql.size());
    // cout <<"sql:"<<sql <<"res:"<< res<<endl;
    return (0 ==  res);
}


/*
 * @brief 私有函数 连接函数
 * @parameter MYSQL* 指针, 
 * @return bool 值
 */
bool MySql::connect(){
	return NULL != mysql_real_connect(&m_mysql, m_host.c_str(), m_user.c_str(), m_pw.c_str(), m_db.c_str(), m_port, NULL, 0);
}

/*
 * @brief 关闭连接
 * @parameter void
 * @return bool 值
 */
bool MySql::close_connect(){
	mysql_close(&m_mysql);
    return true;
}

/*
 * @brief 重连
 * @parameter void
 * @return bool 值
 */
bool MySql::reconnect(){
	close_connect();
	return connect() && execute_sql(("set names " + m_code+";") );
}

/*
 * @brief 数据查询
 * @parameter 入参 
 * @parameter result_matrix 二维可变长数组
 * @return bool 值
 */
bool MySql::select_data(const string& sql, vector< vector<string> >& result_matrix ){
	if( ! execute_sql(sql) ) {
        // cout <<"1"<<endl;
		return false;
	}
	MYSQL_RES *res = mysql_store_result(&m_mysql);  
    if(NULL == res) {   
        // cout <<"2"<<endl;
        mysql_free_result(res);  
        return false;  
    }  
    int numcols = mysql_num_fields(res);  
    MYSQL_ROW row;  
    while(row =  mysql_fetch_row(res)) {  
    	vector<string> row_vec;  
        row_vec.reserve(numcols);  
        for(int i = 0; i < numcols; i++)  
        {  
            row_vec.push_back(row[i]);  
        }  
        result_matrix.push_back(row_vec);  
    }  
    mysql_free_result(res);  
    return true;  
}


/*
 * @brief 错误信息返回
 * @parameter 
 * @return bool 值
 */
string MySql::get_err_msg(){
	char buf[2048] = {0};  
    snprintf(buf, 2047, "error_code=%d, error_msg=%s", mysql_errno(&m_mysql), mysql_error(&m_mysql) );   
    return buf;
}


