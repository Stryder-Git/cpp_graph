
#include "src\Tree.h"

#include <vector>
#include <iostream>

void show_nodes(std::vector<Node*> nodes) {
	for (Node* n : nodes) {
		std::cout << n->asstr() << "\n";
	}
}

Node* create_tree(){
	Person Marcel = Person("Marcel", 28);
	Node n_Marcel = Node(Marcel);

	Person Angela = Person("Angela", 26);
	Node n_Angela = Node(Angela);

	Person Peter = Person("Peter", 62);
	Node n_Peter = Node(Peter);

	Person Romy = Person("Romy", 63);
	Node n_Romy = Node(Romy);

	Person Elke = Person("Elke", 60);
	Node n_Elke = Node(Elke);

	Person Amy = Person("Amy", 55);
	Node n_Amy = Node(Amy);

	Person Jason = Person("Jason", 58);
	Node n_Jason = Node(Jason);


	std::vector<Node*> all_nodes{&n_Marcel,&n_Angela,&n_Peter,
								&n_Romy,&n_Elke,&n_Amy,&n_Jason};

	// connections:
	std::vector<Node*> conns_Marcel{&n_Angela, &n_Peter, &n_Romy};
	std::vector<Node*> conns_Angela{&n_Marcel, &n_Amy, &n_Jason};
	std::vector<Node*> conns_Peter{&n_Marcel, &n_Elke};
	std::vector<Node*> conns_Romy{&n_Marcel};
	std::vector<Node*> conns_Amy{&n_Angela};
	std::vector<Node*> conns_Jason{&n_Angela};
	std::vector<Node*> conns_Elke{&n_Peter};

	
	n_Marcel.set_connections(conns_Marcel);
	n_Angela.set_connections(conns_Angela);
	n_Peter.set_connections(conns_Peter);
	n_Romy.set_connections(conns_Romy);
	n_Amy.set_connections(conns_Amy);
	n_Jason.set_connections(conns_Jason);
	n_Elke.set_connections(conns_Elke);
	
	show_nodes(all_nodes);

	Node* root = &n_Marcel;

	//std::cout << "in create_tree" << "\n";
	std::cout<< n_Marcel.data->name << "\n";
	return root;
}

int main(){

	Node* root = create_tree();
	std::cout << root->asstr() << "\n";

	TreeNavigator nav;

	std::cout << "in main " << nav.var << "\n";

	nav.show_names(root);

	//std::cout<< "end";

	std::cout << (root->data->name).length() << "\n";

	std::cout << "again" << "\n"; 

	std::vector<Node*> found = nav.find_name(root, "Elke");

	show_nodes(found);

	delete root
}

