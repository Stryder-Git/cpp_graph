#ifndef TREE_H
#define TREE_H

#include <vector>
#include <iostream>
#include <unordered_map>
#include <deque>
#include <fstream>
#include "Person.h"
#include "utils.h"

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

std::vector<std::pair<int, std::vector<int>>> _get_conns(std::ifstream* file) {
	
	std::vector<std::pair<int, std::vector<int>>> conns;

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
			logger.log(0, "line number " + std::to_string(nline) + " is invalid");
			continue;
		}

		logger.log(0, "found " + std::to_string(conn.size()) + " connections for " + std::to_string(id));
		std::pair<int, std::vector<int>> pair(id, conn);
		conns.push_back(pair);
	}
	file->close();
	return conns;

}

Node* build_tree(std::unordered_map<int, Person*>* people, std::ifstream* file) {

	std::vector<std::pair<int, std::vector<int>>> conns = _get_conns(file);


	std::unordered_map<int, Node*> all_nodes;
	// this just creates actual nodes from people
	for (auto& d : *people) {
		Node* n = new Node(d.second);
		all_nodes[d.first] = n;
	}

	Node* root;
	std::vector<Node*> cnodes;
	bool found = false;
	// for each pair of id-conns
	for (auto& d : conns) {
		if (!found) {
			root = all_nodes[d.first];
			found = true;
		}		
		// create array of Node* that are the children
		cnodes.clear();
		for (int cid : d.second) {
			cnodes.push_back(all_nodes[cid]);
		}
		// set connections of node
		all_nodes[d.first]->set_connections(cnodes);
	}

	for (auto& d : all_nodes) {
		logger.log(0, "created Node for " + std::to_string(d.first) + ": " + d.second->asstr());
	}

	return root;

	}


class DepthFirstSearch{
	private:

		void _find_name(std::vector<Node*>& found, 
						Node* node,
						const std::string& name){
			
			logger.log(1, "checking name " + node->data->name);
			if (node->data->name == name) {
				found.push_back(node);
			}

			for (Node* conn: node->connections){
				_find_name(found, conn, name);
			}
		}

	public:
		std::vector<Node*> find_name(Node* root, const std::string& name){

			std::vector<Node*> found;
			_find_name(found, root, name);
			return found;
		}

};


class BreadthFirstSearch {

private:
	void _add(std::deque<Node*>& visit, const std::vector<Node*>& conns) {
		for (Node* n : conns) {visit.push_back(n);}
	}

public:
	std::vector<Node*> find_name(Node* root, const std::string& name) {
		std::vector<Node*> found;
		std::deque<Node*> visit{root};

		Node* now;
		while (visit.size() != 0) {
			now = visit.front(); visit.pop_front();

			logger.log(1, "checking " + now->data->name);
			if (now->data->name == name) { found.push_back(now); }

			for (Node* n : now->connections) { visit.push_back(n); }
		}

		return found;

	}
};

#endif // TREE_H