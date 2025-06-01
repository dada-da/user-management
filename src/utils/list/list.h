//
// Created by Da on 1/6/25.
//

#ifndef LIST_H
#define LIST_H
#include <stdexcept>

template<typename T>

class List {
    T *data;
    int size;
    int capacity;

    void resize() {
        const int newCapacity = (this->capacity == 0) ? 1 : this->capacity * 2;
        T *new_data_ = new T[newCapacity];

        for (int i = 0; i < size; i++) {
            new_data_[i] = this->data[i];
        }

        delete[] this->data;
        data = new_data_;
        this->capacity = newCapacity;
    }

    void removeAt(int index) {
        if (index < 0 || index >= this->size) {
            throw std::out_of_range("index out of range");
        }

        for (int i = index; i < this->size - 1; i++) {
            data[i] = data[i + 1];
        }
        --this->size;
    }

    int findIndex(const T &value) {
        for (int i = 0; i < size; i++) {
            if (data[i] == value) {
                return i;
            }
        }
        return -1;
    }

public:
    List() : data(nullptr), size(0), capacity(0) {
    }

    explicit List(const int initCapacity) : size(0), capacity(initCapacity) {
        if (initCapacity > 0) {
            data = new T[capacity];
        } else {
            data = nullptr;
            capacity = 0;
        }
    }

    List(const List &other) : size(other.size), capacity(other.capacity) {
        if (capacity > 0) {
            data = new T[capacity];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        } else {
            data = nullptr;
        }
    }

    ~List() {
        delete[] data;
    }

    T getData() {
        return this->data;
    }

    std::optional<T> getDataAt(const int index) {
        if (index >= 0 && index < size) {
            return data[index];
        }
        return std::nullopt;
    }

    void insert(const T &value) {
        if (size >= capacity) {
            resize();
        }

        data[size++] = value;
    }

    bool remove(const T &value) {
        for (int i = 0; i < size; i++) {
            if (data[i] == value) {
                removeAt(i);
                return true;
            }
        }

        return false;
    }

    T find(const T &value) {
        const int index = findIndex(value);

        if (index == -1) {
            return nullptr;
        }

        return data[index];
    }


    int getSize() const {
        return size;
    }

    int getCapacity() const {
        return capacity;
    }


    bool isEmpty() const {
        return this->size == 0;
    }
};

#endif
