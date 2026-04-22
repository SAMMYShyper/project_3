
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

struct Node { // need the data, pointer to left & right child, optional parent 
	string data; // contains the question posed e.g. "do you own a car?"
	string data_label; // the "yes" or "no" we get
	vector<Node *> children; // could vary in size; cause its a general tree  
	Node *parent; 
	int level; // stores the level of the node
	int preorder; // the position defined in .txt
};

int main() {
	
	return 0;
}
