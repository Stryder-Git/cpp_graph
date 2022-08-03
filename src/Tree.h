#include <vector>
#include <iostream>

class Node{
	private:
		size_t m_n_connections{1};

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

/*
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
*/