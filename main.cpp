
#include "src\Person.h"
#include "src\Tree.h"
#include "src\utils.h"

#include <vector>
#include <iostream>


void show_nodes(const std::vector<Node*>* nodes) {
	for (Node* n : *nodes) {
		std::cout << n->asstr() << "\n";
	}
}


int main(int n, char* argv[]) {

	/// PARSE ARGS
	std::string explanation = "Currently, You can only pass a name to be searched by passing : "
		"'--bfs=NAME' or '--dfs=NAME' for doing a breadth-first or depth-first search for NAME. "
		"Alternatively, you can pass --show and it will show you the data.\n";

	std::invalid_argument too_many("\n\nToo many arguments\n\n" + explanation);
	std::invalid_argument incorrect("\n\nInvalid argument\n\n" + explanation);

	std::string action;
	std::string target;

	if (n > 2) { 
		throw too_many;
	}
	else if (n < 2) {
		std::cout << "No args passed\n";
		exit(0);
	}
	else{
		action = argv[1];
		target = action.substr(6);
		action = action.substr(0, 6);
		if (action != "--show" && action != "--bfs=" && action != "--dfs=") {
			//std::cout << "received " 
			throw incorrect;
		}		
	}


	/// BUILD GRAPH
	std::unordered_map<int, Person*>* data = get_people(get_file("data\\people.txt"));
	std::cout << "\n\nBuilding Tree:\n\n";
	Node* root = build_tree(data, get_file("data\\people\\one.txt"));
	std::cout << "\nroot is:\n" << root->asstr()<< "\n\n";


	// SHOW
	if (action == "--show") {
		std::cout << "Available Data: \n\n";
		for (auto& id_p : *data) {
			std::cout << "id: " << id_p.first << " " << id_p.second->asstr() << "\n";
		}
		return 0;
	}



	
	// SEARCH
	std::cout << "\n\nsearching for " + target << " :\n\n";
	std::vector<Node*> found;
	if (action == "--bfs=") {
		BreadthFirstSearch searcher;
		found = searcher.find_name(root, target);
	}
	else {
		DepthFirstSearch searcher;
		found = searcher.find_name(root, target);
	}

	
	std::cout << "\nFound " << found.size() << ":\n";
	show_nodes(&found);
	
	delete_map(data);
	//nav.delete_tree(root);
}

