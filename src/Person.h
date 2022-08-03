#ifndef PERSON_H
#define PERSON_H


#include <iostream>
#include <unordered_map>
#include <fstream>


class Person {
public:
	std::string name;
	int age;
	Person(std::string n, int a) : name{ n }, age{ a }{}
	std::string asstr() {
		std::string string{ "Name: " };
		return string + name + ", age: " + std::to_string(age);
	}
};


std::unordered_map<int, Person*>* get_people(std::ifstream* file) {

	std::unordered_map<int, Person*>* people = new std::unordered_map<int, Person*>;
	std::string line;
	int nline = 0;
	while (!file->eof()) {
		nline += 1;
		std::getline(*file, line);
		int length = line.length();
		if (length == 0) { continue; }

		int id = 0;
		std::string name = "";
		int age = 0;

		int field = 0;
		char c;
		for (int i = 0; i < length; i++) {
			c = line[i];

			if (c == ',') {
				field += 1;
				continue;
			}
			else if (c == ' ') {
				continue;
			}
			if (field == 0) {
				id = c - 48;
			}
			else if (field == 1) {
				name += c;
			}
			else if (field == 2) {
				age = std::stoi(line.substr(i));
				break;
			}
		}

		if (id == 0 || name == "" || age == 0) {
			std::cout << "line number " << nline << " is invalid\n\n";
			continue;
		}
		
		Person* p = new Person(name, age);
		std::cout << "found " << id << ": " << p->asstr() << "\n\n";
		(*people)[id] = p;
	}

	file->close();
	delete file;
	return people;
}
#endif // PERSON_H