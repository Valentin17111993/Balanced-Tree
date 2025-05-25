#include "AVL.h"
#include <queue>
using namespace std;

AVL::Node::Node(int& k) : key(k) { left = right = nullptr; height = 0; }
AVL::Node::Node(int &&k) : key(k) { left = right = nullptr; height = 0; }

size_t AVL::height(Node* node)
{
	return node ? node->height : 0;
}

int AVL::bfactor(Node* node)
{
	return height(node->right) - height(node->left);
}

void AVL::fix_height(Node* node)
{
	size_t h_left = height(node->left);
	size_t h_right = height(node->right);

	node->height = (h_left > h_right ? h_left : h_right) + 1;
}

AVL::Node* AVL::rotateRight(Node* node)
{
	Node* q = node->left;

	node->left = q->right;
	q->right = node;
	fix_height(node);
	fix_height(q);

	return q;
}

AVL :: Node* AVL::rotateLeft(Node* node)
{
	Node* q = node->right;

	node->right = q->left;
	q->left = node;
	fix_height(node);
	fix_height(q);

	return q;
}

AVL::Node* AVL::balance(Node* const node)
{
	fix_height(node); // вычисляем правильную высоту для узла
	if (bfactor(node) == 2) // Балансируем дерево в зависимости от фактора балансировки
	{
		if (bfactor(node->right) < 0)
		{
			node->right = rotateRight(node->right);
		}
		return rotateLeft(node);
	}

	if (bfactor(node) == -2)
	{
		if (bfactor(node->left) > 0)
		{
			node->left = rotateLeft(node->left);
		}
		return rotateRight(node);
	}

	return node; // балансировка не нужна
}

const AVL :: Node* AVL::bfs(const int& key) const
{
	if (_root == nullptr)
	{
		return nullptr;
	}
	queue<Node*> q; // Создаем пустую очередь для добавления узлов с одинакового уровня - имеющие одинаковую высоту

	q.push(_root); // кладем корень в очередь

	while (q.empty() == false)
	{
		Node* node = q.front();
		q.pop();

		if (node->key == key)
		{
			return node;
		}
		if (node->left != nullptr)
		{
			q.push(node->left);
		}
		if (node->right != nullptr)
		{
			q.push(node->right);
		}
	}
}

const AVL :: Node* AVL:: dfsRecurs(const Node* node, const int& key)
{
	// ваш код
	if (node->left == nullptr && node->right == nullptr)
	{
		cout << "No exists" << endl;
		return node;
	}

	if (node->key == key)
	{
		cout << "Found" << endl;
		return node;
	}

	if (node->key > key)
	{
		return dfsRecurs(node->left, key);
	}

	if (node->key < key)
	{
		return dfsRecurs(node->right, key);
	}
}

AVL::Node* AVL::insert(Node* root, Node* const node)
{
	if (!root)
	{
		return node;
	}

	if (node->key < root->key)
	{
		root->left = insert(root->left, node);
	}
	else
	{
		root->right = insert(root->right, node);
	}
	return balance(root);
}

void AVL::insert(int&& key)
{
	Node* node = new Node(key);
	_root = insert(_root, node);
}

AVL::Node* AVL::removemin(Node* node)
{
	if (!node->left)
	{
		return node->right;
	}
	node->left = removemin(node->left);
	return balance(node);
}

AVL::Node* AVL::findmin(Node* node)
{
	return node->left ? findmin(node->left) : node;
}

AVL::Node* AVL::delete_node(Node* node, const int& key)
{
	if (!node)
	{
		return 0;
	}
	if (key < node->key)
	{
		node->left = delete_node(node->left, key);
	}
	else if(key > node->key)
	{
		node->right = delete_node(node->right, key);
	}
	else
	{
		Node* q = node->left;
		Node* r = node->right;
		node->left = nullptr;
		node->right = nullptr;
		delete node;

		if (!r)
		{
			return q;
		}

		Node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
}

void AVL::delete_node(const int& key)
{
	_root = delete_node(_root, key);
}