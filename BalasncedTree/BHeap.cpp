#include <iostream> 
#include <climits>
#include <algorithm>
#include "BHeap.h"
using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

MinHeap::MinHeap(int cap)
{
    heap_size = 0;
    capacity = cap;
    harr = new int[cap];
}

void MinHeap::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;

    // ��������� �������� ��� ������ ���������
    if (l < heap_size && harr[l] < harr[i])
    {
        smallest = l;
    }

    // ��������� �������� ��� ������� ���������
    if (r < heap_size && harr[r] < harr[smallest])
    {
        smallest = r;
    }

    // ���� �� ���������, ����������, � ���������
    // �������� ����� ��� �������, �� ���������������� �������
    if (smallest != i)
    {
        swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest);
    }
}

void MinHeap::insertKey(int k)
{
    // ��������� �� ��������� �����
    if (heap_size == capacity)
    {
        cout << "Overflow: could not insert new key" << endl;
        return;
    }
    // ������� ������ ����� � �����
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;

    // ���������� ������ ��� �������������. ��������� ����� ������� �� 1 �������
    while (i != 0 && harr[i] < harr[parent(i)])
    {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}

int MinHeap::extractMin()
{
    if (heap_size <= 0)
    {
        return INT_MAX;
    }

    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }

    // ��������� ����������� ��������, � ������� ��� �� ����
    int root = harr[0];
    harr[0] = harr[heap_size - 1];
    heap_size--;

    // ��������������� ��������
    MinHeapify(0);
    return root;
}

MinHeap MinHeap::buildHeap(int* arr, size_t size)
{
    MinHeap h(size);
    h.heap_size = size;
    copy(arr, arr + size, h.harr);
    for (int i = size / 2; i >= 0; i--)
    {
        h.MinHeapify(i);
    }

    return h;
}

void MinHeap :: heapSort(int *&arr, size_t size)
{
    // ������ ����
    MinHeap h = MinHeap::buildHeap(arr, size);
    for (size_t i = 0; i < size; i++)
    {
        // ��������� ������
        arr[i] = h.extractMin();
        // ��������������� ��������
        h.MinHeapify(0);
    }
}

MaxHeap::MaxHeap(int cap)
{
    heap_size = 0;
    capacity = cap;
    harr = new int[cap];
}

void MaxHeap::MaxHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int bigest = i;

    // ��������� �������� ��� ������ ���������
    if (l < heap_size && harr[l] > harr[i])
    {
        bigest = l;
    }

    // ��������� �������� ��� ������� ���������
    if (r < heap_size && harr[r] > harr[bigest])
    {
        bigest = r;
    }

    // ���� �� ���������, ����������, � ���������
    // �������� ����� ��� �������, �� ���������������� �������
    if (bigest != i)
    {
        swap(&harr[i], &harr[bigest]);
        MaxHeapify(bigest);
    }
}

void MaxHeap::insertKey(int k)
{
    // ��� ���
    // ��������� �� ��������� �����
    if (heap_size == capacity)
    {
        cout << "Overflow: could not insert new key" << endl;
        return;
    }
    // ������� ������ ����� � �����
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;

    // ���������� ������ ��� �������������. ��������� ����� ������� �� 1 �������
    while (i != 0 && harr[i] > harr[parent(i)])
    {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}

int MaxHeap::extractMax()
{
    // ��� ���
    if (heap_size <= 0)
    {
        return INT_MAX;
    }

    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }

    // ��������� ����������� ��������, � ������� ��� �� ����
    int root = harr[0];
    harr[0] = harr[heap_size - 1];
    heap_size--;

    // ��������������� ��������
    MaxHeapify(0);
    return root;
}