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
		size_t height(Node* node); // ������� ��� ������ � ������� ���������
		int bfactor(Node* node); // ������� ������� �����
		void fix_height(Node* node); // ����������� ������
		Node* rotateRight(Node* node); // ������� �������
		Node* rotateLeft(Node* node); // ������� ������
		Node* balance(Node* const node); // ��������� ������������ ������ ������ ����
		const Node* bfs(const int& key) const; // ����� � ������
		const Node* dfsRecurs(const Node* node, const int& key); // ����� � �������
		void insert(int&& key); // ������� ��������
		Node* insert(Node* root, Node* const node); // ������� ��������
		Node* removemin(Node* node); // �������� ������������
		Node* findmin(Node* node);
		Node* delete_node(Node* node, const int& key);
		void delete_node(const int& key);
	private:
		Node* _root;
};