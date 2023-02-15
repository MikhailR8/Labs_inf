#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>

//Task 15
std::ostream& operator<<(std::ostream& os, std::vector<int>& v) {
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(os, " "));
	return os;
}

std::ostream& operator<<(std::ostream& os, std::pair<std::vector<int>, int>& p) {
	std::copy(p.first.begin(), p.first.begin() + p.second, std::ostream_iterator<int>(os, " "));
	return os;
}

bool simple(int num) {
	if (num == 1) { return false; }
	for (auto i = 2; i <= std::sqrt(num); i++) {
		if (num % i == 0) {
			return false;
		}
	}
	return true;
}


int main() {
	std::vector<int> array = std::vector<int>(10);

	//Task 1;
	std::iota(array.begin(), array.end(), 1);
	std::cout << array << std::endl;

	//Task 2;
	std::cout << "How many numbers do you need to add? " << std::endl;
	int count;
	std::cin >> count;
	if (count > 0){ std::cout << "Write here the numbers: " << std::endl; }
	for (auto i = 0; i < count; i++) {
		int temp;
		std::cin >> temp;
		array.push_back(temp);
	}
	std::cout << array << std::endl;

	//Task 3
	std::shuffle(array.begin(), array.end(), std::random_device());
	std::cout << "Array after using std::shuffle: " << array << std::endl;

	//Task 4
	auto coutedOdd = std::count_if(array.begin(), array.end(), [](int num) {return num % 2 != 0; });
	std::cout << "Quantity of odd number: " << coutedOdd << std::endl;

	//Task 5
	auto minMax = std::minmax_element(array.begin(), array.end());
	std::cout << "Min value of array is " << *minMax.first << std::endl;
	std::cout << "Max value of array is " << *minMax.second << std::endl;

	//Task 6
	auto haveSimple = std::find_if(array.begin(), array.end(), simple);
	(haveSimple != array.end())
		? std::cout << "Array contains simple number(numbers), first is " << *haveSimple << std::endl
		: std::cout << "Array doesnt't contains simple numbers" << std::endl;

	//Task 7
	auto squares = std::vector<int>(array.size());
	std::transform(array.begin(), array.end(), squares.begin(), [](int num) {return num * num; });
	std::cout << "Squares: " << squares << std::endl;

	//Task 8
	auto summary = std::accumulate(array.begin(), array.end(), 0);
	std::cout << "Sum of elements of array is " << summary << std::endl;

	//Task 9
	std::replace_if(array.begin(), array.begin() + 3, [](int num) {return num != 1; }, 1);
	std::cout << "First three element is 1: " << array << std::endl;

	//Task 10
	auto newEnd = std::remove_if(array.begin(), array.end(), [](int num) {return num == 0; });
	array.erase(newEnd, array.end());
	std::cout << "Array after delete all 0 elements: " << array << std::endl;

	//Task 11
	std::reverse(array.begin(), array.end());
	std::cout << "Array after reverse: " << array << std::endl;

	//Task 12
	std::partial_sort(array.begin(), array.begin() + 3, array.end(), [](int lhs, int rhs) {return lhs > rhs; });
	auto out = std::pair<std::vector<int>, int>(array, 3);
	std::cout << "Top 3 elements " << out << std::endl;

	//Task 13
	std::sort(array.begin(), array.end());
	std::cout << "Array sorted in ascending order: " << array << std::endl;

	//Task 14
	auto startStop3 = std::equal_range(array.begin(), array.end(), 3);
	(startStop3.first != startStop3.second) 
		? std::cout << "3 is present in the sorted vector from index " <<
		startStop3.first - array.begin() << " till " << startStop3.second - array.begin() << std::endl
		: std::cout << "You may add 3 to index " << startStop3.first - array.begin() << std::endl;
	return 0;
}