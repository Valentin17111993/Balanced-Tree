#pragma once
#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <iostream>
#include <cstddef>
using namespace std;

void swap(int& a, int& b);

class MinHeap
{
	int* harr; // ��������� �� ������ ���������
	int capacity; // ������������ ������ ����
	int heap_size; // ������� ����� ��������� ����

	private:
		// ������� ��������� ��� ��������� ��������, � ������� �� ������� ����
		int parent(int i) { return (i - 1) / 2; }
		int left(int i) { return (2 * i + 1); }
		int right(int i) { return (2 * i + 2); }

	public:
		MinHeap(int cap);
		void MinHeapify(int i); // �������������� �������� ���� ��� ��������� � ������ �� �������
        void insertKey(int k); // �������
        int extractMin(); // ���������� ������������ ��������
        MinHeap buildHeap(int* arr, size_t size);
        void heapSort(int*& arr, size_t size);
};

class MaxHeap
{
    int* harr; 
    int capacity; 
    int heap_size;

private:
    
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return (2 * i + 1); }
    int right(int i) { return (2 * i + 2); }

public:
    MaxHeap(int capacity);
    ~MaxHeap();
    
    void MaxHeapify(int);
    
    int extractMax();
    
    int getMax() { return harr[0]; }

    
    void insertKey(int k);
    void buildHeap(int arr[], size_t size);
    size_t getCount();
    void printHeap();
    int* getHeap();
};
#endif // MAXHEAP_H