
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
	std::cout << "\n";
	/// PARSE ARGS
	std::string explanation = "Currently, You can only pass a name to be searched by passing : "
		"'--bfs=NAME' or '--dfs=NAME' for doing a breadth-first or depth-first search for NAME. "
		"Alternatively, you can pass --show and it will show you the data.\n";

	std::invalid_argument too_many("\n\nToo many arguments\n\n" + explanation);
	std::invalid_argument incorrect("\n\nInvalid argument\n\n" + explanation);

	std::string action;
	std::string target;
	logger.level = 2;

	if (n > 3) { 
		throw too_many;
	}
	else if (n < 2) {
		std::cout << "No args passed\n";
		exit(0);
	}
	else{
		// possibly setting loglevel
		if (n == 3) { logger.level = std::stoi(argv[2]); }

		// extract how to search and what name to search for
		action = argv[1];
		target = action.substr(6);
		action = action.substr(0, 6);
		if (action != "--show" && action != "--bfs=" && action != "--dfs=") {
			//std::cout << "received " 
			throw incorrect;
		}		
	}

	/// BUILD GRAPH
	logger.log(4, "reading data");
	std::unordered_map<int, Person*>* data = get_people("data\\people.txt");
	logger.log(4, "building tree:");
	Node* root = build_tree(data, "data\\people\\one.txt");
	logger.log(2, "root is:" + root->asstr());


	// SHOW
	std::string divider = "\n----------------------------------------------------------\n";
	if (action == "--show") {
		std::cout << divider + "\nAvailable Data: \n\n";
		for (auto& id_p : *data) {
			std::cout << "id: " << id_p.first << " " << id_p.second->asstr() << "\n";
		}
		delete_map(data);
		return 0;
	}


	// SEARCH
	logger.log(4, "Searching for " + target + " :");
	std::vector<Node*> found;
	if (action == "--bfs=") {
		BreadthFirstSearch searcher;
		found = searcher.find_name(root, target);
	}
	else {
		DepthFirstSearch searcher;
		found = searcher.find_name(root, target);
	}

	
	std::cout << divider + "\nFound " + std::to_string(found.size()) + ":\n\n";
	show_nodes(&found);
	
	delete_map(data);
	//nav.delete_tree(root);
}

