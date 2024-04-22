#pragma once
#include "User.h"

class Message
{
public:
	Message(const std::string& from, const std::string& to, const std::string& text);

	const std::string& getFrom() const;
	const std::string& getTo() const;
	const std::string& getText() const;
private:
	const std::string _from;
	const std::string _to;
	const std::string _text;
};