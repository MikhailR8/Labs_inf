#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <numeric>
#include <random>

const size_t BOARDER_SIZE = 1000u;

template <typename Iterator, typename T>
void min_in_block(Iterator begin, Iterator end, T& result) {
    auto under_result = *begin;
    for (auto i = begin; i != end; i++) {
        if ((*i) < under_result) {
            under_result = *i;
        }
    }
    std::mutex mutex;
    std::lock_guard guard(mutex);
    if (under_result < result) {
        result = under_result;
    }
}

template <typename Iterator>
auto parrallel_min(Iterator start, Iterator end) {
    auto size = std::distance(start, end);
    auto num_threads = std::thread::hardware_concurrency();

    if (size <= BOARDER_SIZE || num_threads <= 1) {
        return *std::min_element(start, end);
    }

    std::vector<std::thread> threads;
    auto result = *start;
    for (auto i = 0u; i + 1 < num_threads; i++) {
        auto beginIt = start + (i * size / (num_threads - 1));
        auto endIt = start + ((i + 1) * size / (num_threads - 1));
        threads.emplace_back(min_in_block<Iterator, decltype(result)>, beginIt, endIt, std::ref(result));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return result;
}

int main() {
    std::vector<int> count_min(10000);
    std::iota(count_min.begin(), count_min.end(), 87);
    std::shuffle(count_min.begin(), count_min.end(), std::random_device());
    std::cout << parrallel_min(count_min.begin(), count_min.end()) << std::endl;
    return 0;
}
