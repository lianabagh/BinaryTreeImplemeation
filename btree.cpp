// ConsoleApplication53.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#define max(a,b) ((a) < (b) ? (a) : (b))
using namespace std;
struct node {
	int value;
	node *left;
	node *right;
};

class btree
{
public:
	btree();
	~btree();

	void Insert(int key);
	int  NodesCount();
	bool Search(int key);
	int Height();
	node* Delete(int key);
	node* GetMin();
	void Destroy_tree();
	void Inorder_print();
	int IsBinarySearchTree();
	void Postorder_print();
	void Preorder_print();

private:
	void Destroy_tree(node* root);
	void Insert(int key, node* root);
	int NodesCount(node* root);
	bool Search(int key, node* root);
	int Height(node* root);
	node* Delete(int key, node* root);
	node* GetMin(node* root);
	void Inorder_print(node* root);
	void Postorder_print(node* root);
	void Preorder_print(node* root);
	int BinaryTreeUtility(node *root, int max, int min);
	node *root;
};


btree::btree()
{
	root = 0;
}

btree::~btree()
{
	Destroy_tree();
}

void btree::Destroy_tree(node *root) {
	if (root != 0)
	{
		Destroy_tree(root->left);
		Destroy_tree(root->right);
		delete root;
	}
}
int btree::NodesCount(node* root)
{
	if (root == 0) return 0;
	else return 1 + NodesCount(root->left) + NodesCount(root->right);
}

int btree::Height(node* root)
{
	if (root == 0) return 0;
	else return 1 + max(Height(root->left), Height(root->right));
}

void btree::Insert(int key, node* root) {

	if (key < root->value)
	{
		if (root->left != 0)
		{
			Insert(key, root->left);
		}
		else
		{
			root->left = new node;
			root->left->value = key;
			root->left->left = 0;
			root->left->right = 0;
		}
	}
	else if (key >= root->value)
	{
		if (root->right != 0)
		{
			Insert(key, root->right);
		}
		else {
			root->right = new node;
			root->right->value = key;
			root->right->right = 0;
			root->right->left = 0;
		}
	}

}
node* btree::Delete(int data, node *root) {
	if (root == 0) return root;
	else if (data < root->value) root->left = Delete(data, root->left);
	else if (data > root->value) root->right = Delete(data, root->right);
	else {
		// Case 1:  No child
		if (root->left == 0 && root->right == 0)
		{
			delete root;
			root = 0;
		}
		//Case 2: One child 
		else if (root->left == 0)
		{
			node *temp = root;
			root = root->right;
			delete temp;
		}
		else if (root->right == 0)
		{
			node *temp = root;
			root = root->left;
			delete temp;
		}
		// case 3: 2 children
		else
		{
			node *temp = GetMin(root->right);
			root->value = temp->value;
			root->right = Delete(temp->value, root->right);
		}
	}
	return root;
}




void btree::Insert(int key)
{
	if (root != 0)
	{
		Insert(key, root);
	}
	else
	{
		root = new node;
		root->value = key;
		root->left = NULL;
		root->right = NULL;
	}
}

bool btree::Search(int key, node* root)
{
	if (root != 0)
	{
		if (key == root->value)
		{
			return true;
		}
		if (key < root->value)
		{
			return Search(key, root->left);
		}
		else
		{
			return Search(key, root->right);
		}
	}
	else
	{
		return false;
	}
}
int btree::BinaryTreeUtility(node* root, int min, int max)
{

	if (root == 0)
		return 1;
	if (root->value<min || root->value>max)  return 0;
	return BinaryTreeUtility(root->left, min, root->value) && BinaryTreeUtility(root->right, root->value, max);
}
int btree::IsBinarySearchTree()
{
	return BinaryTreeUtility(root, INT_MIN, INT_MAX);
}
node* btree::GetMin(node* root)
{
	if (root == 0)
	{
		return 0;
	}
	while (root->left != 0)
	{
		root = root->left;
	}
	return root;

}

bool btree::Search(int key)
{
	return Search(key, root);
}


node* btree::Delete(int key)
{
	return Delete(key, root);
}
int btree::NodesCount()
{
	return NodesCount(root);
}
int btree::Height()
{
	return Height(root);
}

node* btree::GetMin()
{
	return GetMin(root);
}
void btree::Destroy_tree()
{
	Destroy_tree(root);
}

void btree::Inorder_print()
{
	Inorder_print(root);
	cout << "\n";
}

void btree::Inorder_print(node* root)
{
	if (root != 0)
	{
		Inorder_print(root->left);
		cout << root->value << ",";
		Inorder_print(root->right);
	}
}


int main()
{
	btree *tree = new btree();
	tree->Insert(10);
	tree->Insert(6);
	tree->Insert(14);
	tree->Insert(5);
	tree->Insert(8);
	tree->Insert(11);
	tree->Insert(18);
	cout << "Height=" << tree->Height() << endl;
	cout << "Min=" << tree->GetMin()->value << endl;
	cout << tree->IsBinarySearchTree() << endl;
	tree->Delete(6);
	cout << "Quantity of Nodes   " << tree->NodesCount() << endl;
	tree->Inorder_print();
	cout << tree->Search(6) << endl;
	delete tree;
}
