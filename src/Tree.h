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

std::vector<std::pair<int, std::vector<int>>> _get_conns(std::string path) {
	
	CSVReader data(path);
	std::vector<std::pair<int, std::vector<int>>> conns;
	std::vector<std::string> fields;
	std::vector<int> conn;

	while (!data.eof) {
		fields = data.next();
		if (data.eof) { break; }
		int id = std::stoi(fields[0]);
		int fsize = fields.size();
		for (int i = 1; i < fsize; i++) {
			conn.push_back(std::stoi(fields[i]));
		}

		logger.log(0, "found " + std::to_string(conn.size()) + " connections for " + std::to_string(id));
		std::pair<int, std::vector<int>> pair(id, conn);
		conns.push_back(pair);
		conn.clear();
	}
	return conns;

}

Node* build_tree(std::unordered_map<int, Person*>* people, std::string path) {

	std::vector<std::pair<int, std::vector<int>>> conns = _get_conns(path);
	std::unordered_map<int, Node*> all_nodes;
	// this just creates actual nodes from people 
	// simpler to do it right now, since not all nodes may be in conns
	for (auto& d : *people) {
		all_nodes[d.first] = new Node(d.second);
	}
	std::vector<Node*> cnodes;
	// for each pair of id-conns
	for (auto& d : conns) {
		// create array of Node* that are the children
		for (int cid : d.second) {
			cnodes.push_back(all_nodes[cid]);
		}
		// set connections of node
		all_nodes[d.first]->set_connections(cnodes);
		cnodes.clear();
	}

	if (logger.level == 0) {
		for (auto& d : all_nodes) {
			logger.log(0, "created Node for " + std::to_string(d.first) + ": " + d.second->asstr());
		}
	}
	return all_nodes[conns[0].first];

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