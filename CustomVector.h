#pragma once
#include <iostream>
#include <stdlib.h> 

using namespace std;

template <typename T>
class CustomVector
{
public:
    CustomVector();
    ~CustomVector();
    void addItem(const T& item);
    void removeItem(const T& item);
    bool isEmpty() const;
    void swap(size_t index1, size_t index2);
    const size_t& Size() const { return size; };


    T* begin() { return data; }
    T* end() { return data + size; }

    //Read-Only Variant
    const T* begin() const { return data; }
    const T* end() const { return data + size; }

    const T& operator[](const size_t& index) const;

private:
    T* data;
    size_t size;
    size_t capacity;
    static const size_t DEFAULT_CAPACITY = 1;
    static const size_t DEFAULT_SIZE = 0;
    void resize();
};

template <typename T>
CustomVector<T>::CustomVector() : size(DEFAULT_SIZE), capacity(DEFAULT_CAPACITY)
{
    data = new T[capacity]; 
}

template <typename T>
CustomVector<T>::~CustomVector()
{
    delete[] data; 
}

template <typename T>
bool CustomVector<T>::isEmpty() const
{
    return size > 0 ? false : true;
}

template <typename T>
const T& CustomVector<T>::operator[](const size_t& index) const
{
    if (index < 0 || index >= size)
    {
      throw out_of_range("Index selected is out of bounds.");
    }
    return data[index];
}

template <typename T>
void CustomVector<T>::addItem(const T& item)
{
    if (size >= capacity)
    {
        resize();
    }
    data[size++] = item;
    //_CrtCheckMemory();
}

template <typename T>
void CustomVector<T>::removeItem(const T& item) {
    for (size_t i = 0; i < size; i++)
    {
        if (data[i] == item) 
        {
            delete data[i];

            // Shift all elements to the left
            for (size_t j = i; j < size - 1; ++j) 
            {
                data[j] = data[j + 1];
            }
            data[size - 1] = nullptr;
            size--;
            return;
        }
    }
    
}

template <typename T>
void CustomVector<T>::resize()
{
    capacity++; 

    T* temp = new T[capacity]; 
    for (size_t i = 0; i < size; i++)
    {
        temp[i] = data[i]; 
    }

    delete[] data; 
    data = temp; 
}

template <typename T>
void CustomVector<T>::swap(size_t index1, size_t index2) {

    if (index1 >= size || index2 >= size) 
    {
        throw out_of_range("Indexes to be swapped are out of bounds.");
    }
    T temp = data[index1];
    data[index1] = data[index2];
    data[index2] = temp;
}



