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
		size_t height(Node* node); // ������� ��� ������ � ������� ���������
		Node* rotateRight(Node* node); // ������� �������
		Node* rotateLeft(Node* node); // ������� ������
		void InsertFixUp(Node*& root, Node* node); // ������������ ����� �������
		void insert(Node* root, Node* node); // ������� ����
		void insert(int key);
		Node* search(Node* node, int key) const; // �����
		Node* search(int key); // �����
		void removeFixUp(Node*& root, Node* node, Node* parent); // ������������ ����� ��������
		void remove(Node*& root, Node* node);
		void remove(int key);
	private:
		Node* _root;
};