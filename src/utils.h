#ifndef UTILS_H
#define UTILS_H

#include <fstream>

class Logger {
	/*
	logger with a level indicating minimum significance to log

	messages are logged at different levels
	   3 - very few only big steps
	   2 - info level
	   1 - details
	   0 - every step along the way

	when setting level = x
	   everything above that level gets pushed to std::cout

	*/
public:
	int level = 0;
	Logger(int l) : level(l) {}
	void log(int l, std::string m) {
		if (l >= level) {
			std::cout << "[" << l << "] " << m << "\n";
		}
	}
};

Logger logger(0);


std::ifstream* get_file(std::string path) {
	std::ifstream* file = new std::ifstream(path);
	
	if (!(*file)) {
		logger.log(3, "Cannot open file " + path);
		exit(1);
	}
	else {
		logger.log(2, "opened file " + path);
	}
	return file;
}

template <class T>
void delete_map(std::unordered_map<int, T*>* m) {

	for (auto& t : *m) {
		delete t.second;
	}
	logger.log(0, "deleting data");
	delete m;
}

#endif // UTILS_H
