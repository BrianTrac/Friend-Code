#include "Service.h"
#include "StudentList.h"
#include <fstream>
#include <sstream>
#include <iostream>

Service::Service(){}

std::unordered_map<std::string, std::string> Service::getConfigFile(std::string file_name) {
	std::unordered_map<std::string, std::string> configData;
	std::ifstream ifs(file_name);
	
	if (!ifs.is_open()) {
		std::cerr << "Error opening file" << file_name << std::endl;
	}
	else {
		std::string line;
		while (getline(ifs, line)) {
			std::istringstream iss(line);
			std::string key, value;
			if (getline(iss, key, '=') && getline(iss, value)) {
				configData[key] = value;
			}
		}

		ifs.close();
		std::cout << "Read config file successfully.\n";
	}
	return configData;
}

void Service::run() {

	int choice_1 = 0;
	int choice_2 = 0;
	bool isMultipleCall = false;

	while (choice_1 == 0) {
		std::cout << "1. Tinh ti le dua theo source code cung cap.\n";
		std::cout << "2. Su dung ti le dua theo file config.txt\n";
		std::cout << "Nhap 1 hoac 2 de chon\n";
		int x; std::cin >> x;

		if (x == 1) {
			choice_1 = x;
		}
		else if (x == 2) {
			choice_1 = x;

			// get data from config file
			std::unordered_map<std::string, std::string> configData = getConfigFile("config.txt");
			try {
				min_val = std::stod(configData["min_val"]);
				max_val = std::stod(configData["max_val"]);
			}
			catch (std::exception e) {
				std::cout << e.what() << std::endl;
			}
		}
		else {
			std::cout << "Please enter the correct input(1 or 2).\n";
		}
	}

	while (choice_2 == 0) {
		std::cout << "1. Moi sv chi đuoc goi toi da 1 lan trong 1 buoi hoc.\n";
		std::cout << "2. Moi sinh vien co the duoc goi nhieu lan.\n";
		std::cout << "Nhap 1 hoac 2 de chon\n";
		int x; std::cin >> x;
		if (x == 1) {
			choice_2 = x;
			isMultipleCall = false;
		}
		else if (x == 2) {
			choice_2 = x;
			isMultipleCall = true;
		}
		else {
			std::cout << "Please enter the correct input(1 or 2).\n";
		}
	}

	// The code in previous main method
	StudentList sl("Text.csv");
	bool ok = true;
	std::string s;
	while (ok && !sl.getMp().empty()) {
		std::cout << "The lucky students selected are: ";
		sl.randomStudent(isMultipleCall, min_val, max_val); // Add parameter here. Fixed
		std::cout << "Press Enter to continue program or type 'exit' to stop." << std::endl;
		std::getline(std::cin, s);
		if (s == "exit") ok = false;
		else ok = true;
		system("cls");
	}

	if (sl.getMp().empty()) std::cout << "All the students got to speak! End of class!" << std::endl;
	else std::cout << "End of class!" << std::endl;
	sl.updateFile("Text.csv");
}
