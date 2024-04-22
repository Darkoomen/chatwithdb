#pragma once

#include<string>

class User {
public:

	User(const std::string& login, const std::string& password, const std::string& name);
	~User();

	const std::string& getUserLogin() const;
	const std::string& getUserPassword() const;
	const std::string& getUserName() const;
	const std::string& getUserEmail() const;

	void setUserPassword(const std::string& password);
	void setUserName(const std::string& name);
	void setUserEmail(const std::string& email);

private:
	const std::string _login;
	std::string _password;
	std::string _name;
	std::string _email;
};
