#ifndef PERSON_H
#define PERSON_H


#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>

#include "utils.h"


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


std::unordered_map<int, Person*>* get_people(std::string path) {

	CSVReader data(path);
	std::unordered_map<int, Person*>* people = new std::unordered_map<int, Person*>;
	std::vector<std::string> fields;

	while (!data.eof) {
		fields = data.next();
		if (data.eof) { break; }
		int id = std::stoi(fields[0]);
		std::string name = fields[1];
		int age = std::stoi(fields[2]);

		Person* p = new Person(name, age);
		logger.log(0, "found " + std::to_string(id) + ": " + p->asstr());
		(*people)[id] = p;
	}

	return people;
}
#endif // PERSON_H