#include <mysql/mysql.h>
#include <string>
#include "BlackGlow.h"


class sql_connection
{
public:
	
	std::string database, username, password, host;
	int port;
	MYSQL *conn = mysql_init(NULL);

	sql_connection()
	{

	}
	sql_connection(std::string hos, int por, std::string uname, std::string pass, std::string db)
	{
		this->port = por;
		this->host = hos;
		this->username = uname;
		this->password = pass;
		this->database = db;
		if (mysql_real_connect(this->conn, this->host.c_str(), this->username.c_str(), this->password.c_str(), this->database.c_str(), this->port, NULL, 0)==NULL) printf("Cannot connect to database\n");
	}
	
	sql_connection( std::string hos, std::string uname, std::string pass)
	{
		this->host = hos;
		this->username = uname;
		this->password = pass;
		if("hasil: %d\n", mysql_real_connect(this->conn, this->host.c_str(), this->username.c_str(), this->password.c_str(), NULL, 0, NULL, 0)==NULL)printf("Cannot connect to database\n");
	}
	
	void query(std::string quer)
	{
		mysql_query(this->conn,(char *) quer.c_str());
	}
	MYSQL_ROW* queryi(std::string quer, int &size)
	{
		mysql_query(this->conn,(char *) quer.c_str());
		MYSQL_RES *results = mysql_store_result(this->conn);
		MYSQL_ROW row;
		MYSQL_ROW *toreturn = (MYSQL_ROW *)calloc(sizeof(MYSQL_ROW), 1);
		int index = 0;
		while(row = mysql_fetch_row(results))
		{
			/*
			//change NULL to "NULL"

			for (int i = 0; i < mysql_num_fields(row))
			{
				row[i] = (row[i]) ? row[i] : "NULL"; 
			}
			*/
			toreturn[index] = row;
			index++;
			toreturn = (MYSQL_ROW*)realloc(toreturn, sizeof(MYSQL_ROW)*(index+1));
		}
		size = index;
		return toreturn;
	}
	void printrow(MYSQL_ROW *dat)
	{

	}
	void close()
	{
		mysql_close(this->conn);
	}
	~sql_connection()
	{
		this->close();
	}
	
};
