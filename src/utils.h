#ifndef UTILS_H
#define UTILS_H

#include <fstream>

std::ifstream* get_file(std::string path) {
	std::ifstream* file = new std::ifstream(path);
	
	if (!(*file)) {
		std::cerr << "Cannot open file " << path << "\n\n";
		exit(1);
	}
	else {
		std::cout << "opened file " << path << "\n\n";
	}
	return file;
}

template <class T>
void delete_map(std::unordered_map<int, T*>* m) {

	for (auto& t : *m) {
		delete t.second;
	}
	std::cout << "\ndeleteing data" << "\n";
	delete m;
}

#endif // UTILS_H