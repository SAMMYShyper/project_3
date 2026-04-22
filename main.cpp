
// learning to build linked tree data structure
// each node stores element 
// pointer to left child, right child, optionally parent
// typically provide:
// 	T.add_root(e)
// 	T.add_left(p, e)
// 	T.add_right(p,e)
// 	T.replace(p, e)
// 	T.delete(p)
// 	T.attach(p, T1, T3)


using namespace std;
#include <iostream>
#include <vector>

class Node { // need the data, pointer to left & right child, optional parent 
public:
	string data; // contains the question posed e.g. "do you own a car?"
	string data_label; // the "yes" or "no" we get
	vector<Node *> children; // could vary in size; cause its a general tree  
	Node *parent; 
	int level; // stores the level of the node
	int preorder; // the position defined in .txt
	Node(string d, string d_label, int lvl, int pre_pos, Node *par = NULL) : data(d), data_label(d_label), level(lvl), preorder(pre_pos), parent(par) {} 
};


class Tree {
private:
	Node *root; // pointer to the root node	
public:
	Tree() : root(NULL) {} // initializing the empty tree
	
	void add_root(string d, string d_label, int lvl, int pre_pos ) {
		root = new Node(d, d_label, lvl, pre_pos);
	}
	
	Node *get_root() const{
		return root;
	}
	
	void add_child(string d, string d_label, int lvl, int pre_pos, Node *par) {
		Node *newNode = new Node(d, d_label, lvl, pre_pos, par);
		par->children.push_back(newNode);
	}

	int count_internal_nodes(Node *root){
		if (root == NULL) {
			return 0;
		}
		int count = 0;
		
		if (!root->children.empty()){
			count = 1;
			for (int i = 0; i < root->children.size(); i++) {
				count += count_internal_nodes(root->children[i]);
			}
		}
		return count;
	}
};


int main() {
	
	return 0;
}
