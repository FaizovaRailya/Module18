// main.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "User.h"
#include "Message.h"
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void demo_perms(fs::perms p){
    std::cout << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
        << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
        << ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
        << ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
        << ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
        << ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
        << ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
        << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
        << ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-")
        << '\n';
}

int main(){
	std::fstream user_file = std::fstream("users.txt", std::ios::in | std::ios::out);
	if (!user_file)
		// Для создания файла используем параметр ios::trunc
		user_file = std::fstream("users.txt", std::ios::in | std::ios::out | std::ios::trunc);

	fs::permissions("users.txt", fs::perms::group_all | fs::perms::others_all, fs::perm_options::remove);
	std::cout << "Permissions for 'users.txt': ";
	demo_perms(fs::status("users.txt").permissions());

	if (user_file) {
		User user1("Railya", "qwerty", "12345");		
		user_file << user1 << std::endl;			// Запишем данные в файл		
		user_file.seekg(0, std::ios_base::beg);     // Устанавливаем позицию для чтения в начало файла	
		user_file >> user1;							// Считываем данные из файла
		std::cout << user1 << std::endl;

		user_file.clear();
		user_file.seekg(0, std::ios_base::end);
		user_file.seekp(0, std::ios_base::end);

		User user2("Mira", "qwertyMira", "12345Mira");		
		user_file << user2 << std::endl;			// Запишем данные в файл

		// Устанавливаем позицию на чтение для следующего пользователя в начало последней строки (размер строки фиксирован и равен 53)
		user_file.clear();
		user_file.seekg(-54, std::ios_base::cur);
		user_file >> user2;							// Считываем данные из файла
		std::cout << user2 << std::endl;
	}
	else{
		std::cout << "Could not open file users.txt!" << std::endl;
		return 0;
	}

	std::fstream message_file = std::fstream("messages.txt", std::ios::in | std::ios::out);
	if (!message_file)
		// Для создания файла используем параметр ios::trunc
		message_file = std::fstream("messages.txt", std::ios::in | std::ios::out | std::ios::trunc);

	fs::permissions("messages.txt", fs::perms::group_all| fs::perms::others_all, fs::perm_options::remove);

	std::cout << "\nPermissions for 'messages.txt': ";
	demo_perms(fs::status("messages.txt").permissions());

	if (message_file) {
		Message message1("Railya", "Mira", "Hi!");
		message_file << message1 << std::endl;			// Запишем данные в файл	
		message_file.seekg(0, std::ios_base::beg);		// Устанавливаем позицию для чтения в начало файла
		message_file >> message1;						// Считываем данные из файла
		std::cout << message1 << std::endl;
		
		message_file.clear();
		message_file.seekg(0, std::ios_base::end);
		message_file.seekp(0, std::ios_base::end);

		Message message2("Mira", "Railya", "Hi Railya, how are you?");
		message_file << message2 << std::endl;									// Запишем данные в файл
		message_file.seekg(54 - message2.getText().size(), std::ios_base::cur);
		message_file >> message2;												// Считываем данные из файла
		std::cout << message2 << std::endl;	
	}
	else{
		std::cout << "Could not open file messages.txt!" << std::endl;
		return 0;
	}
	user_file.close();
	message_file.close();
	
}
