#pragma once
#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <iostream>
#include <cstddef>
using namespace std;

void swap(int& a, int& b);

class MinHeap
{
	int* harr; // указатель на массив элементов
	int capacity; // максимальный размер кучи
	int heap_size; // текущее число элементов кучи

	private:
		// Функции помощники для получения родителя, и сыновей по индексу узла
		int parent(int i) { return (i - 1) / 2; }
		int left(int i) { return (2 * i + 1); }
		int right(int i) { return (2 * i + 2); }

	public:
		MinHeap(int cap);
		void MinHeapify(int i); // Восстановление свойства кучи для поддерева с корнем по индексу
        void insertKey(int k); // вставка
        int extractMin(); // Извлечение минимального элемента
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