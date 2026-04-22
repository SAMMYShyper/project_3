
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

	int count_external_nodes(Node *root) {
		if (root == NULL) { // if there's nothing then there's no external node, return 0
			return 0;
		}
	
		else if (root->children.empty()) { // if there's no children left, make selected node return 1
			return 1;
		}
			
		int count = 0; // if there are more childen, this executes	
		for (int i = 0; i < root->children.size(); i++) { // recursively calls and adds counts
				count += count_external_nodes(root->children[i]);
			}
		return count;
	}

	int tree_height(Node *root) {
		if (root == NULL) {
			return -1; // if empty, its less than a height of 0, so -1
		}
		else if (root->children.empty()) {
			return 0; // if theres one node and no children then teh height at instance is 0		
		}
		int max_height = 0;
		for (int i = 0; i < root->children.size(); i++) { // traverse tree
			int child_height = tree_height(root->children[i]); 
			if (max_height < child_height) { // comparing child height to max height
				max_height = child_height; // if the child height is ever greater than out saved, change max
			}
		}
		return 1 + max_height;
	}	
	
	void print_internal_preorder(Node *root) {
		if (root == NULL) {
			return; // if theres nothing we return without printing
		}	
		if (!root->children.empty()) {
			cout << root->data << endl; // if theres children current must be internal therefore print
		}
		for (int i = 0; i < root->children.size(); i++) {
			print_internal_preorder(root->children[i]);
		}
	}
	
	void print_external_preorder(Node *root) {
		if (root == NULL) {	
			return; // nothing prints
		}
		if (root->children.empty()) {
			cout << root->data << endl;
		}
		for (int i = 0; i < root->children.size(); i++) {
			print_external_preorder(root->children[i]);
		}
	}
};


int main() {
	
	return 0;
}
