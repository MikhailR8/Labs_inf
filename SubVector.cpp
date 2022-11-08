#include <iostream>

struct subvector {
    int* data;
    int size, actual_size;

    subvector(int new_size) {
        size = new_size;
        data = new int[size];
        actual_size = 0;
    }

    ~subvector() {
        delete[] data;
    }

    int get(int index) {
        return data[index];
    }

    void set(int index, int value) {
        data[index] = value;
    }

    void resize(int new_size) {
        int* newArray = new int[new_size];
        if (new_size < actual_size) {
            actual_size = new_size;
        }
        for (auto i = 0; i < actual_size; i++) {
            newArray[i] = data[i];
        }
        size = new_size;
        delete[] data;
        data = newArray;
    }

    void push_back(int value) {
        if (actual_size == size) {
            size *= 2;
            resize(size);
        }
        data[actual_size++] = value;
    }

    int pop_back() {
        actual_size--;
        int last = data[actual_size];
        data[actual_size] = 0;
        return last;
    }

    void shrink_to_fit() {
        resize(actual_size);
        size = actual_size;
    }

    void clear() {
        for (auto i = 0; i < size; i++) {
            data[i] = 0;
        }
        actual_size = 0;
    }

    friend std::ostream& operator<< (std::ostream &out, const subvector &vector) {
        out << '[';
        for (auto i = 0; i < vector.actual_size; i++) {
            if (i != (vector.actual_size - 1)) {
                out << vector.data[i] << ", ";
            }
            else {
                out << vector.data[i];
            }
        }
        out << ']';
        return out;
    }
};


int main() {
    subvector array(1);
    for (auto i = 0; i < 10; i++) {
        array.push_back(i * i);
    }
    std::cout << "Size: " << array.size << std::endl;
    std::cout << array << std::endl;

    array.shrink_to_fit();
    std::cout << "Size: (after use shrink_to_fit())" << array.size << std::endl;
    std::cout << array << std::endl;
    std::cout << array.pop_back() << std::endl;
    std::cout << array << std::endl;
    array.resize(5);
    std::cout << array << std::endl;
    array.clear();
    std::cout << array;
}
