#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <random>
#include <string>


//Функция, которая меняет местами два элемента по индексам
void replace(int index1, int index2, std::vector<int>& array) { 
    array[index1] = array[index1] + array[index2];
    array[index2] = array[index1] - array[index2];
    array[index1] = array[index1] - array[index2];
}

//Функция просеивания вверх для heapsort, меняет местами нижний элемент узла с его родителем до тех пор,
//пока нижний элемент строго больше верхнего
void siftingUp(std::vector<int>& out, int index) {
    for (int i = index; i > 0;) {
        if (out[i] <= out[(i - 1) / 2]) break;
        else {
            replace(i, (i - 1) / 2, out);
            i = (i - 1) / 2;
        }
    }
}

//Функция просеивания вниз для heapsort, меняет местами родителя с большим из потомков при их наличии
//до тех пор, пока родитель строго меньше потомка
void siftingDown(std::vector<int>& out, int index) {
    for (int i = 0;;) {
        if ((2 * i + 1) > index) break;
        else if ((2 * i + 2) > index) {
            if (out[i] < out[2 * i + 1]) {
                replace(i, 2 * i + 1, out);
            }
            break;
        }
        if (out[i] >= out[2 * i + 1] && out[i] >= out[2 * i + 2]) break;
        else {
            if (out[2 * i + 1] > out[2 * i + 2]) {
                replace(i, 2 * i + 1, out);
                i = 2 * i + 1;
            }
            else {
                replace(i, 2 * i + 2, out);
                i = 2 * i + 2;
            }
        }
    }
}

//Функция heapsort, меняет сначала создаёт массив и добаляет в него элементы, при каждом добавлении
//просеивая вверх, затем меняет местами первый(наибольший) и последний, делая просеивание вниз без учёта
//последних элементов
std::vector<int> heapsort(const std::vector<int>& array) {
    std::vector<int> sorted;
    auto lastElement = array.size() - 1;
    for (auto i = 0; i < array.size(); i++) {
        sorted.push_back(array[i]);
        siftingUp(sorted, i);
    }
    for (auto i = 0; i < array.size() - 1; i++) {
        replace(0, lastElement, sorted);
        lastElement--;
        siftingDown(sorted, lastElement);
    }
    return sorted;

}

//Функция склейки для mergesort, склеивает два массива по возрастанию элементов
std::vector<int> merge(const std::vector<int>& lhs, const std::vector<int>& rhs) {
    std::vector<int> merged;
    auto i = 0, j = 0;
    for (; i < lhs.size() && j < rhs.size(); ) {
        if (lhs[i] < rhs[j]) {
            merged.push_back(lhs[i++]);
        }
        else {
            merged.push_back(rhs[j++]);
        }
    }
    for (; i < lhs.size(); merged.push_back(lhs[i++]));
    for (; j < rhs.size(); merged.push_back(rhs[j++]));
    return merged;
}

//Mergesort, разбивает массив на два, сортирует части и склеивает их
std::vector<int> merge_sort(std::vector<int> array) {
    if (array.size() > 1) {
        auto middle = array.size() / 2;
        std::vector<int> left, right;
        for (auto i = 0; i < middle; i++) {
            left.push_back(array[i]);
        }
        for (auto i = middle; i < array.size(); i++) {
            right.push_back(array[i]);
        }
        auto sorted_left = merge_sort(left);
        auto sorted_right = merge_sort(right);
        return merge(sorted_left, sorted_right);
    }
    return array;
}

std::vector<int> bubblesort(std::vector<int> array) {
    for (int i = 0; i < array.size() - 1; i++) {
        for (int j = 0; j < array.size() - 1 - i; j++) {
            if (array[j] >= array[j + 1]) {
                replace(j, j + 1, array);
            }
        }
    }
    return array;
}

//Генерация рандомного значения в диапазоне
int rand_uns(int min, int max) {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::default_random_engine e(seed);
    std::uniform_int_distribution<int> d(min, max);
    return d(e);

}

//Стуруктура Timer, автоматически стартует и завершается, дописывает время в файл
struct Timer {
    std::chrono::high_resolution_clock::time_point start;
    std::ofstream f;
    int x;
    std::string label;

    Timer(int count, std::string input) {
        x = count;
        label = input;
        f.open("1.csv", std::ios_base::app);
        start = std::chrono::high_resolution_clock::now();
    }

    ~Timer() {
        auto end = std::chrono::high_resolution_clock::now();
        f << (end - start).count() << "," << x << "," << label << " ";
        f.close();
    }
};


int main() {
    for(int j = 1; j < 2001; j++){
        std::vector<int> arr;
        for (int k = 0; k < j; k++) {
            arr.push_back(rand_uns(-1000, 1000));
        }
        {
            Timer t(j, "b");
            bubblesort(arr);
        }
        {
            Timer t(j, "h");
            heapsort(arr);
        }
        {
            Timer t(j, "m");
            merge_sort(arr);
        }
    }
    return 0;
}

