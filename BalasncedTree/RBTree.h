#pragma once
#include <iostream>
using namespace std;

enum Color { Black, Red };

class RBTree
{
	public:
		struct Node
		{
			int key;
			Color color;
			Node* left;
			Node* right;
			Node* parent;
			Node(int k);
		};
		void Swap(Node* a, Node* b);
		size_t height(Node* node); // обертка для работы с пустыми деревьями
		Node* rotateRight(Node* node); // Поворот направо
		Node* rotateLeft(Node* node); // Поворот налево
		void InsertFixUp(Node*& root, Node* node); // Балансировка после вставки
		void insert(Node* root, Node* node); // вставка узла
		void insert(int key);
		Node* search(Node* node, int key) const; // Поиск
		Node* search(int key); // Поиск
		void removeFixUp(Node*& root, Node* node, Node* parent); // Балансировка после удаления
		void remove(Node*& root, Node* node);
		void remove(int key);
	private:
		Node* _root;
};