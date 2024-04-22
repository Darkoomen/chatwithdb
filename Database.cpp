#include <iostream>
#include <mysql.h>
#include "Database.h"

Database::~Database()
{
	mysql_close(m_mysql);
}

void Database::init()
{
	m_mysql = mysql_init(NULL);
	if (m_mysql == nullptr)
	{
		std::cout << "Error can't create MySQL-descriptor\n";
	}
}

void Database::connect()
{
	if (!mysql_real_connect(m_mysql, m_host, m_user, m_password, m_database, m_port, NULL, 0))
	{
		std::cout << "Error can't connect to database " << mysql_error(m_mysql) << std::endl;
	}
	else 
	{
		std::cout << "Success!!!\n";
	}
	mysql_set_character_set(m_mysql, "utf8");
}

int Database::query(const char* sql_query)
{
	return mysql_query(m_mysql, sql_query);
}

void Database::getQueryResult(std::string& result, int& row_num, int& column_num)
{
	MYSQL_RES* res{ nullptr };
	MYSQL_ROW row{};

	row_num = 0;
	column_num = 0;
	res = mysql_store_result(m_mysql);
	if (res)
	{
		column_num = mysql_num_fields(res);
		row = mysql_fetch_row(res);
		if (row)
		{
			do
			{
				++row_num;
				for (size_t i = 0; i < column_num; ++i)
				{
					if (row[i])
						result += row[i];
					else
						result += "NULL";
					result.push_back('\0');
				}
				row = mysql_fetch_row(res);
			} while (row);
		}
	}
	else {
		std::cout << "Îøèáêà MYSQL: " << mysql_error(m_mysql);
	}
}