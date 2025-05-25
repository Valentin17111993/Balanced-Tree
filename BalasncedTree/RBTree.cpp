#include "RBTree.h"
#include <queue>
using namespace std;

void RBTree :: Swap(Node* a, Node* b)
{
	Node temp = *a;
	*a = *b;
	*b = temp;
}

RBTree::Node::Node(int k) : key(k), color(Red), parent(nullptr), left(nullptr), right(nullptr) 
{
}

RBTree::Node* RBTree::rotateRight(Node* node)
{
	Node* q = node->left;

	node->left = q->right;
	q->right = node;

	return q;
}

RBTree::Node* RBTree::rotateLeft(Node* node)
{
	Node* q = node->right;

	node->right = q->left;
	q->left = node;

	return q;
}

void RBTree::InsertFixUp(Node*& root, Node* node)
{
	Node* parent;
	parent = node->parent;

	while (node != RBTree::_root && parent->color == Red)
	{
		Node* gparent = parent->parent;
		if (gparent->left == parent)
		{
			Node* uncle = gparent->right;
			if (uncle != nullptr && uncle->color == Red)
			{
				parent->color = Black;
				uncle->color = Black;
				gparent->color = Red;
				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->right = node)
				{
					rotateLeft(parent);
					swap(node, parent);
				}
				rotateRight(gparent);
				gparent->color = Red;
				parent->color = Black;
				break;
			}
		}
		else
		{
			Node* uncle = gparent->left;
			if (uncle != nullptr && uncle->color == Red)
			{
				gparent->color = Red;
				parent->color = Black;
				uncle->color = Black;

				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->left == node)
				{
					rotateRight(parent);
					swap(parent, node);
				}
				rotateLeft(gparent);
				parent->color = Black;
				gparent->color = Red;
				break;
			}
		}
	}
	root->color = Black;
}

void RBTree::insert(Node* root, Node* node)
{
	Node* currentNode = root;
	Node* parentNode = nullptr;
	while (currentNode != nullptr)
	{
		parentNode = currentNode;
		if (node->key > currentNode->key)
		{
			currentNode = currentNode->right;
		}
		if (node->key < currentNode->key)
		{
			currentNode = currentNode->left;
		}
	}

	node->parent = parentNode;

	if (parentNode != nullptr)
	{
		if (node->key > parentNode->key)
		{
			parentNode->right = node;
		}
		else
		{
			parentNode->left = node;
		}
	}
	else
	{
		root = node;
	}

	node->color = Red;
	InsertFixUp(root, node);
}

void RBTree::insert(int key)
{
	Node* z = new Node(key);
	insert(_root, z);
}

RBTree::Node* RBTree::search(Node* node, int key) const
{
	if (node == nullptr || node->key == key)
	{
		return node;
	}
	if (node->key < key)
	{
		return search(node->left, key);
	}
	else
	{
		return search(node->right, key);
	}
}

RBTree::Node* RBTree::search(int key)
{
	return search(_root, key);
}

void RBTree::removeFixUp(Node*& root, Node* node, Node* parent)
{
	Node* othernode;
	while ((!node) || node->color == Black && node != RBTree::_root)
	{
		if (parent->left == node)
		{
			othernode = parent->right;
			if (othernode->color == Red)
			{
				othernode->color = Black;
				parent->color = Red;
				rotateLeft(parent);
				othernode = parent->right;
			}
			else
			{
				if (!(othernode->right) || othernode->right->color == Black)
				{
					othernode->left->color = Black;
					othernode->color = Red;
					rotateRight(othernode);
					othernode = parent->right;
				}
				othernode->color = parent->color;
				parent->color = Black;
				othernode->right->color = Black;
				rotateLeft(parent);
				node = root;
				break;
			}
		}
		else
		{
			othernode = parent->left;
			if (othernode->color == Red)
			{
				othernode->color = Black;
				parent->color = Red;
				rotateRight(parent);
				othernode = parent->left;
			}
			
			if ((!othernode->left || othernode->left->color == Black)
				&& (!othernode->right || othernode->right->color == Black))
			{
				othernode->color = Red;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!(othernode->left) || othernode->left->color == Black)
				{
					othernode->right->color = Black;
					othernode->color = Red;
					rotateLeft(othernode);
					othernode = parent->left;
				}
				othernode->color = parent->color;
				parent->color = Black;
				othernode->left->color = Black;
				rotateRight(parent);
				node = root;
				break;
			}
		}
	}

	if (node)
	{
		node->color = Black;
	}
}

void RBTree::remove(Node*& root, Node* node)
{
	Node* child;
	Node* parent;
	Color color;
	// ”зел слева и справа от удал€емого узла не пуст
	if (node->left != nullptr && node->right != nullptr)
	{
		Node* replace = node;
		// Ќаходим узел-преемник (самый нижний узел правого поддерева текущего узла)
		replace = node->right;
		while (replace->left != nullptr)
		{
			replace = replace->left;
		}

		// ”даленный узел не €вл€етс€ корнем
		if (node->parent != nullptr)
		{
			if (node->parent->left == node)
				node->parent->left = replace;
			else
				node->parent->right = replace;
		}
		else
			root = replace;
		// сохран€ем нужные указатели замен€емого элемента и цвет
		child = replace->right;
		parent = replace->parent;
		color = replace->color;

		// ”зел замен€етс€ родительским узлом замены
		if (parent == node)
			parent = replace;
		else
		{
			// ≈сть дочерние узлы
			if (child != nullptr)
				child->parent = parent;
			parent->left = child;

			replace->right = node->right;
			node->right->parent = replace;
		}
		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;
		if (color == Black)
			removeFixUp(root, child, parent);

		delete node;
		return;
	}
	//  огда удаленный узел имеет только левый (правый) узел, находим дочерний узел удаленного узла
	if (node->left != nullptr)
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	color = node->color;
	if (child)
	{
		child->parent = parent;
	}
	// ”даленный узел не корень
	if (parent)
	{
		if (node == parent->left)
			parent->left = child;
		else
			parent->right = child;
	}
	// ”даленный узел - корень
	else
		RBTree::_root = child;

	if (color == Black && root)
	{
		removeFixUp(root, child, parent);
	}
	delete node;
}

void RBTree::remove(int key)
{
	Node* deletenode = search(_root, key);
	if (deletenode != nullptr)
	{
		remove(_root, deletenode);
	}
}