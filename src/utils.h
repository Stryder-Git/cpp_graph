#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <vector>

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




class CSVReader {
private:
	std::ifstream* _get_file(std::string path) {
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

	std::string _clean_entry(std::string s) {
		int j = s.length() - 1;
		int i = 0;
		for (; i <= j; i++) {
			if (s[i] != ' ') { break; }
		}
		for (; j >= 0; j--) {
			if (s[j] != ' ') { j++; break; }
		}
		return s.substr(i, j - i);
	}

	std::vector<std::string> _parse_line(std::string line) {
		std::vector<std::string> parsed;
		int length = line.length();
		int i = 0;
		for (int j = 0; j < length; j++) {
			if (line[j] == ',') {
				parsed.push_back(_clean_entry(line.substr(i, j - i)));
				i = j + 1;
			}
		}
		parsed.push_back(_clean_entry(line.substr(i)));
		return parsed;

	}

	std::vector<std::string> _next() {
		std::string line;
		std::vector<std::string> fields;
		bool notvalid = line.length() == 0;

		while (notvalid && !file->eof()) {
			std::getline(*file, line);
			fields = _parse_line(line);

			notvalid = false;
			for (auto& s : fields) {
				if (s.size() == 0) {
					notvalid = true; break;
				}
			}
			nline++;
		}

		eof = file->eof();
		if (eof) {
			logger.log(0, "closing file " + path);
			file->close(); delete file;
		}
		return fields;
	}

public:
	std::string path;
	std::ifstream* file;
	std::vector<std::string> next_line;
	bool eof = false;
	int nline = 0;

	CSVReader(std::string p){
		path = p;
		file = _get_file(p);
		next_line = _next();
	}

	std::vector<std::string> next() {
		std::vector<std::string> l = next_line;
		next_line = _next();
		return l;

	}
	

};








template <class T>
void delete_map(std::unordered_map<int, T*>* m) {

	for (auto& t : *m) {
		delete t.second;
	}
	logger.log(0, "deleting data");
	delete m;
}

#endif // UTILS_H
