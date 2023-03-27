#include <iostream>
#include <vector>
#include <future>
#include <numeric>
#include <chrono>
#include <fstream>

const size_t BORDER_SIZE = 1000u;
using steady_clock = std::chrono::steady_clock;

class Timer {
public:
    Timer(std::fstream& w) : start(steady_clock::now()), writer(w) {}
    ~Timer() {
        writer << std::chrono::duration_cast<std::chrono::microseconds>(steady_clock::now()
            - start).count()
            << std::endl;
    }
private:
    steady_clock::time_point start;
    std::fstream& writer;
};

template <typename Iterator, typename T>
T future_accumulate(Iterator begin, Iterator end, T init, int count_threads) {
    auto size = std::distance(begin, end);
    auto num_threads = count_threads;
    std::vector<std::future<T>> threads;
    std::vector<T> results(num_threads - 1);
    auto block_size = size / num_threads;

    if (size <= BORDER_SIZE) {
        return std::accumulate(begin, end, init);
    }

    for (auto i = 0u; i + 1 < num_threads; i++) {
        threads.push_back(std::async(std::launch::async, std::accumulate<Iterator, T>,
            std::next(begin, i * block_size), std::next(begin, (i + 1) * block_size), 0));
    }

    T result = std::accumulate(std::next(begin, (num_threads - 1) * block_size), end, init);
    for (auto& thread : threads) {
        result += thread.get();
    }
    return result;
}

int main() {
    std::vector<long double> numbers(1'000'000'000);
    std::iota(numbers.begin(), numbers.end(), 1);
    std::fstream out("result.txt", std::ios_base::app);
    for (auto i = 1; i < std::thread::hardware_concurrency(); i++) {
        {
            Timer t(out);
            future_accumulate(numbers.begin(), numbers.end(), 0.l, i);
        }
    }
    out.close();
    return 0;
}
