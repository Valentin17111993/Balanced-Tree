#pragma once
#include <iostream>
using namespace std;

class AVL
{
	public:
		struct Node
		{
			int key;
			Node* left;
			Node* right;
			size_t height;

			Node(int& k);
			Node(int&& k);
		};
		size_t height(Node* node); // обертка для работы с пустыми деревьями
		int bfactor(Node* node); // находим разницу высот
		void fix_height(Node* node); // Исправление высоты
		Node* rotateRight(Node* node); // Поворот направо
		Node* rotateLeft(Node* node); // Поворот налево
		Node* balance(Node* const node); // выполняем балансировку дерева вокруг узла
		const Node* bfs(const int& key) const; // Поиск в ширину
		const Node* dfsRecurs(const Node* node, const int& key); // Поиск в глубину
		void insert(int&& key); // Вставка элемента
		Node* insert(Node* root, Node* const node); // Вставка элемента
		Node* removemin(Node* node); // Удаление минимального
		Node* findmin(Node* node);
		Node* delete_node(Node* node, const int& key);
		void delete_node(const int& key);
	private:
		Node* _root;
};