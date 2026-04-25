// each node stores element 
// pointer to left child, right child, optionally parent

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
using namespace std;


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

	// ###########note for next person to code #############
	// We now need to put the function in part C. of the pdf: tree analysis; including binary tree checker, proper, perfect, and balanced
	// after that its pretty much just getting the writing in main: file i/ and user interface (via terminal prob)

	bool binary_detector(Node *root) { // recursive checker
		if (root == NULL) { 
			return true;
		}
		if (root->children.size() > 2) {
			return false;
		}
		for (int i = 0; i < root->children.size(); i++) {
			if(!binary_detector(root->children[i])) {
				return false;
			}
		}
		return true;
	}

	bool proper_detector(Node *root) {
		if (root == NULL) {	
			return true;
		}
		if (root->children.size() != 0 && root->children.size() != 2) {	// if there aren't 0 or 2 children, then its not proper
			return false;
		}
		for (int i = 0; i < root->children.size(); i++) { // recursively iterates
			if (!proper_detector(root->children[i])){ 
				return false;
			}
		}
		return true;
	}	

	bool perfect_detector(Node *root, int height) { // returns true if full, no missing children, equal height leaves
		if (root == NULL) {	
			return true; // if nothing, then its perfect by default
		}	
		// ->level contains leaf height		
		if (root->children.empty()){
			return root->level == height; 
		}
	
		if (root->children.size() != 2) { // if our leaves dont have 2, then its not perfect
			return false; // false ends recursion
		}
		
		return perfect_detector(root->children[0], height) && perfect_detector(root->children[1], height);
	}

	bool balanced_detector(Node *root) {
		if (root == NULL) {	
			return true;
		}
		if (root->children.empty()) { // when no longer children to explore
			return true; // if we reach the end of the tree without finding imbalance
		}
		// balanced means that the heights of left - right must fall within 0,1,-1

		int c_left = tree_height(root->children[0]);
		int c_right = tree_height(root->children[1]);
		int balance = c_left - c_right;
		if (balance && -1 && balance != 0 && balance != 1) { // if the balance is not within 1 height
			return false; // it is not balanced
		}
		return balanced_detector(root->children[0]) && balanced_detector(root->children[1]); // recursive call for the next two children
	}
	
	void tree_visual(Node *root) { // level n * 2 for the tree node
		// edge label in [] "[yes]"
		// node data print afterward
		if (root == NULL) {
			return;
		}	
		cout << root->data << endl; // root prints without dashes, just the data
		for (int i = 0; i < root->children.size(); i++) {
			for (int j = 0; j < root->children[i]->level*2; j++) {
				cout << "-"; // printing level n "-" *2	
				}		
			cout << "[" << root->children[i]->data_label << "] "; // label and data print 
			tree_visual(root->children[i]); // recursive call for next children until null
		}
		
	}	

	Node* node_explorer(Node *root, int pos) {
		if (root == NULL) {
			return NULL; // if not found we return null
		}
		// positon input check
		if (root->preorder == pos) {
			return root;
		}
		for (int i = 0; i < root->children.size(); i++) {
			Node *result = node_explorer(root->children[i], pos);
			if(result != NULL) { // if not end
				return result; // we return the current node to recurse from
			}
		}
		return NULL;
		
	}

};

int main() {

	Tree t;

	string file;
	cout << "Enter the file name: 'tree-car.txt' or 'tree-investment.txt'" << endl;
	cin >> file; // file holds the filename 
	
	ifstream myFile(file.c_str());
	if(!myFile.is_open()) {
		cout << "Could not open file" << endl;
		return 1;	
	}
		
	vector<Node*> last_lvl;

	string line;
	while (getline(myFile, line)) {
		stringstream ss(line);
		string lvl, pre, label, data; // the tab separated fields
		ss >> lvl >> pre; 
		
		int level = atoi(lvl.c_str()); // changes string to integer
		int preorder = atoi(pre.c_str());
	
		if (level == 0) {
			string rest;
			getline(ss, rest);
			if (!rest.empty() && rest[0] == ' ') {
				rest = rest.substr(1);
			}
			t.add_root(rest, "", level, preorder);
			last_lvl.push_back(t.get_root());
		
		}
		else {
			string label, data;
			ss >> label;
			getline(ss, data);
			if (!data.empty() && data[0] == ' ') {
				data = data.substr(1);
			}
			Node *par = last_lvl[level-1];
			t.add_child(data, label, level, preorder, par);
			Node *newNode = par->children.back();
			
			if ((last_lvl.size()) > level) {
				last_lvl[level] = newNode;
			}
			else {
				last_lvl.push_back(newNode);
			}
		}
	}

	myFile.close(); // file io finished

	// we follow that tree constructor takes (data, data_label "yes"/"no", level, prerder pos, parent (possibly)
	
	// ###tree properties : root node, no. internal node, no. external node, tree height, internal nodes, external

	t.tree_visual(t.get_root());

	cout << "-----------\nTree Properties\n------------\n" << endl;
	cout << "Root: " << t.get_root()->data << endl;
	cout << "Number of internal nodes: " << t.count_internal_nodes(t.get_root()) << endl;
	cout << "Number of external nodes: " << t.count_external_nodes(t.get_root()) << endl;
	cout << "Tree Height: " << t.tree_height(t.get_root()) << endl;
	cout << "\nInternal Nodes:" << endl;
	t.print_internal_preorder(t.get_root());
	cout << "\nExternal Nodes: " << endl;
	t.print_external_preorder(t.get_root());



	cout << "\n-----------\nBinary Tree Properties\n----------" << endl;
	cout << "\nBinary Tree: ";
	if (!t.binary_detector(t.get_root())) {
		cout << "No" << endl;
	}	
	else {
		cout << "Yes" << endl;
		cout << "Proper Tree: " << (t.proper_detector(t.get_root()) ? "Yes" : "No") << endl;
		cout << "Perfect Tree: " << (t.perfect_detector(t.get_root(), t.tree_height(t.get_root())) ? "Yes" : "No") << endl;
		cout << "Balanced Tree: " << (t.balanced_detector(t.get_root()) ? "Yes" : "No") << endl;
	}


	// ###user exploration###
/*	string user_input;
	while (user_input != "exit") {
	// here we're gonna let the user explore the tree
		cout << "Which node would youlike to explore ('exit' to exit)" << endl;
		cin >> user_input;	
			
	}
		
*/
	cout << "Goodbye!" << endl;
	return 0;
}
