#include <vector>
#include <iostream>
#include <unordered_map>
#include <map>
#include <fstream>
#include "Person.h"

class Node{
	private:
		size_t m_n_connections{0};

	public:
		const size_t& n_connections{m_n_connections};
		Person* data;
		std::vector<Node*> connections;
		std::vector<float> costs;// not used yet

		Node() {};
		Node(Person* d){data = d;}

		void set_connections(std::vector<Node*>& conns,
							 std::vector<float>& csts){
			m_n_connections = conns.size();
			connections = conns;
			costs = csts;
		}
		void set_connections(std::vector<Node*>& conns){
			m_n_connections = conns.size();
			connections = conns;
		}
		std::string asstr(){
			std::string string{data->asstr()};
			return string + ", with: " + std::to_string(n_connections) + " connections";
		}
};

std::map<int, std::vector<int>> _get_conns(std::ifstream* file) {
	
	std::map<int, std::vector<int>> conns;

	std::string line;
	std::vector<int> conn;
	int nline = 0;
	while (!file->eof()) {
		nline += 1;
		std::getline(*file, line);
		int length = line.length();
		if (length == 0) { continue; }
		conn.clear();

		int id = 0;
		int cid = 0;
		char c;
		int field = 0;
		for (int i = 0; i < length; i++) {
			c = line[i];

			if (c == ',') {
				field += 1;
				continue;
			}
			if (c == ' ') { continue; }

			if (field == 0) {
				id = c - 48;
			}
			else {
				cid = c - 48;
				conn.push_back(cid);
			}
		}

		if (id == 0) {
			std::cout << "line number " << nline << " is invalid\n\n";
			continue;
		}

		std::cout << "found " << conn.size() << " connections for " << id << "\n";
		conns[id] = conn;
	}
	return conns;

}

Node* build_tree(std::unordered_map<int, Person*>* people, std::ifstream* file) {

	std::map<int, std::vector<int>> conns = _get_conns(file);

	std::unordered_map<int, Node*> all_nodes;

	for (auto& d : *people) {
		Node* n = new Node(d.second);
		all_nodes[d.first] = n;
	}

	for (auto& d : all_nodes) {
		std::cout << "created Node for " << d.first << ": " << d.second->asstr() << "\n";
	}

	/*
	for each person,
		create a node, and set_connections
	*/
	
	Node* n;
	return n;









	}



class TreeNavigator{
	private:
		void _find_name(std::vector<Node*>& found, 
						const Node* node,
						const std::string& name){

			for (Node* conn: node->connections){
				std::cout << "checking name " << conn->data->name << "\n";

				if (conn->data->name == name){
					found.push_back(conn);
				}
				_find_name(found, conn, name);
			}
		}

	public:

		int var = 1;

		std::vector<Node*> find_name(const Node* root, const std::string& name){

			std::vector<Node*> found;

			_find_name(found, root, name);

			return found;
		}
};
