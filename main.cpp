
#include "src\Tree.h"

#include <vector>
#include <iostream>

void show_nodes(const std::vector<Node*>* nodes) {
	for (Node* n : *nodes) {
		std::cout << n->asstr() << "\n";
	}
}

Node* create_tree(){
	Person* Marcel = new Person("Marcel", 28);
	Node* n_Marcel = new Node(Marcel);

	Person* Angela = new Person("Angela", 26);
	Node* n_Angela = new Node(Angela);

	Person* Peter = new Person("Peter", 62);
	Node* n_Peter = new Node(Peter);

	Person* Romy = new Person("Romy", 63);
	Node* n_Romy = new Node(Romy);

	Person* Elke = new Person("Elke", 60);
	Node* n_Elke = new Node(Elke);

	Person* Amy = new Person("Amy", 55);
	Node* n_Amy = new Node(Amy);

	Person* Jason = new Person("Jason", 58);
	Node* n_Jason = new Node(Jason);


	std::vector<Node*>* all_nodes = new std::vector<Node*>{
		n_Marcel,n_Angela,n_Peter,n_Romy,n_Elke,n_Amy,n_Jason};

	// connections:
	std::vector<Node*> conns_Marcel{n_Angela, n_Peter, n_Romy};
	std::vector<Node*> conns_Angela{n_Amy, n_Jason};
	std::vector<Node*> conns_Peter{n_Elke};
	std::vector<Node*> conns_Romy{};
	std::vector<Node*> conns_Amy{};
	std::vector<Node*> conns_Jason{};
	std::vector<Node*> conns_Elke{};

	
	n_Marcel->set_connections(conns_Marcel);
	n_Angela->set_connections(conns_Angela);
	n_Peter->set_connections(conns_Peter);
	n_Romy->set_connections(conns_Romy);
	n_Amy->set_connections(conns_Amy);
	n_Jason->set_connections(conns_Jason);
	n_Elke->set_connections(conns_Elke);
	
	show_nodes(all_nodes);
	delete all_nodes;

	//std::cout << "in create_tree" << "\n";
	std::cout<< n_Marcel->data->name << "\n";
	return n_Marcel;
}

int main(){

	Node* root = create_tree();
	std::cout << root->asstr() << "\n";

	TreeNavigator nav;


	std::cout << "root is " << root->data->name << "\n\n" << "now searching" << "\n\n";

	std::vector<Node*> found = nav.find_name(root, "Elke");

	std::cout << "\nfound:\n\n" << std::endl;

	show_nodes(&found);

	delete root;
}

