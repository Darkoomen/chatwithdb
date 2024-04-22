#pragma once
#include <string>
#include <mysql.h>

struct MYSQL;

class Database
{
private:
	MYSQL* m_mysql{ nullptr };
	const char* m_host{ nullptr };
	const char* m_user{ nullptr };
	const char* m_password{ nullptr };
	const char* m_database{ nullptr };
	unsigned int m_port{0};

public:
	Database(const char* host, const char* user, const char* password, const char* database, unsigned int port)
		: m_host(host),
		m_user(user),
		m_password(password),
		m_database(database),
		m_port(port)
	{}
	~Database();

	void init();
	void connect();
	int query(const char* sql_query);
	void getQueryResult(std::string& result, int& row_num, int& column_num);

};