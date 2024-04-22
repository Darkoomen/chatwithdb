#include<iostream>
#include "User.h"
#include "Message.h"
#include "Chat.h"
#include "Client.h"
#include "Database.h"


User::User(const std::string& login, const std::string& password, const std::string& name) :
	_login(login), _password(password), _name(name) {}

const std::string& User::getUserLogin() const { return _login; }
const std::string& User::getUserPassword() const { return _password; }
const std::string& User::getUserName() const { return _name; }
const std::string& User::getUserEmail() const { return _email; }

void User::setUserPassword(const std::string& password) { _password = password; }
void User::setUserName(const std::string& name) { _name = name; }
void User::setUserEmail(const std::string& email) { _email = email; }

User::~User() {}

Message::Message(const std::string& from, const std::string& to, const std::string& text) :
	_from(from), _to(to), _text(text) {};

const std::string& Message::getFrom() const { return _from; }
const std::string& Message::getTo() const { return _to; }
const std::string& Message::getText() const { return _text; }


void Chat::start() {
	_isChatWork = true;
	std::cout << "Welcome to the program 'Open Console Chat'" << std::endl;
}
bool Chat::isChatWork() const { return _isChatWork; }

void Chat::showLoginMenu() 
{
	_currentUser = nullptr;
	char choice;
	do {
		std::cout << "1 - Login" << "\n"
			<< "2 - Registration" << "\n"
			<< "0 - Quit" << "\n";
		std::cout << ">> ";
		std::cin >> choice;

		switch (choice)
		{
		case '1':
			login();
			break;
		case '2':
			try
			{
				signUp();
			}
			catch (std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
			break;
		case '0':
			_isChatWork = false;
			std::cout << "Goodbye ";
			break;
		default:
			std::cout << "Select 1 or 2 (0 - exit): " << std::endl;
		}
	} while (!_currentUser && _isChatWork);
}

void Chat::showUserMenu()
{
	char operation;
	std::cout << "Hello, " << _currentUser->getUserName() << std::endl;
	while (_currentUser)
	{
		std::cout << "Menu: " << "\n"
			<< "1 - ShowChat" << "\n"
			<< "2 - Add message" << "\n"
			<< "0 - Logout ";

		std::cout << "\n"
			<< ">> ";
		std::cin >> operation;
		switch (operation)
		{
		case '1':
			showChat();
			break;
		case '2':
			addMessage();
			break;
		case '0':
			_currentUser = nullptr;
			break;
		default:
			std::cout << "unknown operation " << std::endl;
			break;
		}
	}
}

void Chat::createDatabase()
{
	MYSQL m_mysql;
	mysql_query(&m_mysql, "CREATE TABLE IF NOT EXISTS Users (id INT AUTO_INCREMENT PRIMARY KEY,"
		"name VARCHAR(255) NOT NULL,"
		"login VARCHAR(255) NOT NULL UNIQUE,"
		"email VARCHAR(100) NOT NULL UNIQUE,"
		"regdate DATETIME NOT NULL)");

	mysql_query(&m_mysql, "CREATE TABLE IF NOT EXISTS Chat (id INT AUTO_INCREMENT PRIMARY KEY,"
		"first_user id INT REFERENCES Users(id), "
		"second_user id INT REFERENCES Users(id))");

	mysql_query(&m_mysql, "CREATE TABLE IF NOT EXISTS Messages (id INT AUTO_INCREMENT PRIMARY KEY,"
		"chat_id INT REFERENCES Chat(id),"
		"user_id INT REFERENCES Users(id),"
		"message VARCHAR(255) NOT NULL,"
		"status VARCHAR(100) NOT NULL CHECK(status IN ('done','in progress', 'delivery')))");
}

std::shared_ptr<User> Chat::getCurrentUser() const { return _currentUser; }

void Chat::login()
{
	std::string login, password;
	char operation;
	do
	{
		std::cout << "login: ";
		std::cin >> login;
		std::cout << "password: ";
		std::cin >> password;

		_currentUser = getUserByLogin(login);
		if (_currentUser == nullptr || (password != _currentUser->getUserPassword()))
		{
			_currentUser = nullptr;

			std::cout << "login error " << std::endl;
			std::cout << "(0)quit or (any key)repeat: ";
			std::cin >> operation;

			if (operation == '0')
				break;
		}
	} while (!_currentUser);
}

void Chat::signUp()
{
	std::string login, password, name;
	std::cout << "login: ";
	std::cin >> login;
	std::cout << "password: ";
	std::cin >> password;
	std::cout << "name: ";
	std::cin >> name;

	if (getUserByLogin(login) || login == "all")
	{
		throw UserLoginExp();
	}

	User user = User(login, password, name);
	_users.push_back(user);
	_currentUser = std::make_shared<User>(user);
}

void Chat::showChat() const
{
	std::string from, to;

	std::cout << "**** Chat ****" << std::endl;
	for (auto& mess : _messages)
	{
		if (_currentUser->getUserLogin() == mess.getFrom() || _currentUser->getUserLogin() == mess.getTo() || mess.getTo() == "all")
			from = (_currentUser->getUserLogin() == mess.getFrom() ? "me" : getUserByLogin(mess.getFrom())->getUserName());
		if (mess.getTo() == "all")
		{
			to = "(all)";
		}
		else
		{
			to = (_currentUser->getUserLogin() == mess.getTo() ? "me" : getUserByLogin(mess.getTo())->getUserName());
		}
		std::cout << "Message from " << from << " to " << to << std::endl;
		std::cout << "text: " << mess.getText() << std::endl;
	}
}
void Chat::addMessage()
{
	ClientC client;
	std::string to, text;
	std::cout << "To (name or all): ";
	std::cin >> to;
	std::cout << "Text: ";
	client.ClientConnection();

	//std::cin.ignore();
	//getline(std::cin, text);
	
	if (to == "all")
		_messages.push_back(Message{ _currentUser->getUserLogin(),"all", text });

}

std::vector<User>& Chat::getAllUsers() { return _users; }
std::vector<Message>& Chat::getAllMessages() { return _messages; }

std::shared_ptr<User> Chat::getUserByLogin(const std::string& login) const
{
	for (auto& user : _users)
	{
		if (login == user.getUserLogin())
			return std::make_shared<User>(user);
	}
	return nullptr;
}


