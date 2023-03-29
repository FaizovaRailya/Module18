#pragma once
#include <iostream>

class Message {  
    std::string _sender;
    std::string _receiver;
	std::string _text;
public:
	Message(std::string sender, std::string receiver, std::string text) : _sender(sender), _receiver(receiver), _text(text){}

	friend std::istream& operator >>(std::istream& is, Message& mes);
	friend std::ostream& operator <<(std::ostream& os, const Message& mes);
	std::string getText() const { return _text; }
};

std::istream& operator >>(std::istream& is, Message& mes){
	is >> mes._sender;
	is >> mes._receiver;
	is >> mes._text;
	return is;
}
std::ostream& operator <<(std::ostream& os, const Message& mes){
	os << mes._sender;
	os << ' ';
	os << mes._receiver;
	os << ' ';
	os << mes._text;
	return os;
}
