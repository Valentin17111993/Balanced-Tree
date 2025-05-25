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

    // проверяем свойство для левого поддерева
    if (l < heap_size && harr[l] < harr[i])
    {
        smallest = l;
    }

    // проверяем свойство для правого поддерева
    if (r < heap_size && harr[r] < harr[smallest])
    {
        smallest = r;
    }

    // если не выполнено, обмениваем, с родителем
    // вызываем снова для индекса, не удовлетворяющего условию
    if (smallest != i)
    {
        swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest);
    }
}

void MinHeap::insertKey(int k)
{
    // Проверяем на доступное место
    if (heap_size == capacity)
    {
        cout << "Overflow: could not insert new key" << endl;
        return;
    }
    // Вставка нового ключа в конец
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;

    // Исправляем дерево при необходимости. Поднимаем новый элемент на 1 уровень
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

    // Сохраняем минимальное значение, и удаляем его из кучи
    int root = harr[0];
    harr[0] = harr[heap_size - 1];
    heap_size--;

    // Восстанавливаем свойство
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
    // Строим кучу
    MinHeap h = MinHeap::buildHeap(arr, size);
    for (size_t i = 0; i < size; i++)
    {
        // Извлекаем корень
        arr[i] = h.extractMin();
        // Восстанавливаем свойство
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

    // проверяем свойство для левого поддерева
    if (l < heap_size && harr[l] > harr[i])
    {
        bigest = l;
    }

    // проверяем свойство для правого поддерева
    if (r < heap_size && harr[r] > harr[bigest])
    {
        bigest = r;
    }

    // если не выполнено, обмениваем, с родителем
    // вызываем снова для индекса, не удовлетворяющего условию
    if (bigest != i)
    {
        swap(&harr[i], &harr[bigest]);
        MaxHeapify(bigest);
    }
}

void MaxHeap::insertKey(int k)
{
    // ваш код
    // Проверяем на доступное место
    if (heap_size == capacity)
    {
        cout << "Overflow: could not insert new key" << endl;
        return;
    }
    // Вставка нового ключа в конец
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;

    // Исправляем дерево при необходимости. Поднимаем новый элемент на 1 уровень
    while (i != 0 && harr[i] > harr[parent(i)])
    {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}

int MaxHeap::extractMax()
{
    // ваш код
    if (heap_size <= 0)
    {
        return INT_MAX;
    }

    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }

    // Сохраняем минимальное значение, и удаляем его из кучи
    int root = harr[0];
    harr[0] = harr[heap_size - 1];
    heap_size--;

    // Восстанавливаем свойство
    MaxHeapify(0);
    return root;
}