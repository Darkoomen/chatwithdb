#pragma once

#include<vector> 
#include<exception>
#include<memory>
#include "Message.h"

struct UserLoginExp : public std::exception
{
	const char* what() const noexcept override { return "error: user login is busy"; }
};

class Chat
{
public:
	std::shared_ptr<User> getCurrentUser() const;
	void start();
	bool isChatWork() const;
	void showLoginMenu();
	void showUserMenu();
	void createDatabase();

private:
	bool _isChatWork = false;
	std::vector<User> _users;
	std::vector<Message> _messages;
	std::shared_ptr<User> _currentUser = nullptr;

	void login();
	void signUp();
	void showChat() const;
	void addMessage();

	std::vector<User>& getAllUsers();
	std::vector <Message>& getAllMessages();
	std::shared_ptr<User> getUserByLogin(const std::string& login) const;
};
