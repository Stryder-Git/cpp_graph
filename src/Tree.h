#include <vector>
#include <iostream>

class Person{
	public:
		std::string name{"NONE"};
		int age{0};

		Person(){}
		Person(std::string n, int a){
			name = n;
			age = a;
		}

		std::string asstr(){
			std::string string{"Name: "};
			return string + name + ", age: " + std::to_string(age);

		}
};


class Node{
	private:
		int m_n_connections{0};

	public:
		const int& n_connections{m_n_connections};	
		Person data;
		std::vector<Node*> connections;
		std::vector<float> costs;

		Node(const Person& d){
			data = d;
		}

		void set_connections(std::vector<Node*> conns,
							 std::vector<float> csts){
			m_n_connections = conns.size();
			connections = conns;
			costs = costs;
		}
		void set_connections(std::vector<Node*> conns){
			m_n_connections = conns.size();
			connections = conns;
		}

		std::string asstr(){
			std::string string{data.asstr()};
			return string + ", with: " + std::to_string(n_connections) + " connections";
		}
};


class TreeNavigator{
	private:
		void _find_name(std::vector<Node*>& found, 
						const Node* node,
						const std::string& name){

			for (Node* conn: node->connections){
				std::cout << "checking name " << conn->data.name << "\n";

				if (conn->data.name == name){
					found.push_back(conn);
				}
				_find_name(found, conn, name);
			}
		}

	public:

		std::vector<Node*> find_name(Node& root, std::string name){

			std::cout << "searching " << "\n";

			std::cout << root.data.name << "\n";

			std::vector<Node*> found;
			_find_name(found, &root, name);
			return found;
		}
};
