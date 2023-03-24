#include <iostream>
#include <vector>
#include <string>
#include <exception>

template <typename T>
class Stack {
public:
	Stack() : size(0) {}

	void push(T task) {
		tasks.push_back(task);
		size++;
	}

	template <typename ...Types>
	void emplase(Types ...Args) {
		tasks.push_back(T(Args...));
		size++;
	}

	T top() const{
		return tasks.back();
	}

	void pop() {
		if (size > 1) {
			tasks.pop_back();
			size--;
		}
		else {
			throw std::out_of_range("Stack is already empty");
		}
	}

	unsigned int get_size() const{
		return size;
	}

	~Stack() = default;

private:
	std::vector<T> tasks;
	unsigned size;
};

class Task {
public:
	template <typename ...Types>
	Task(Types ...t) : text(std::string(t...)) {}
	
	void print() const{
		std::cout << text << std::endl;
	}

	~Task() = default;
private:
	std::string text;
};

int main() {
	Stack<Task> work;
	Task mathan("Mathan");
	work.push(mathan);
	std::cout << work.get_size() << std::endl;
	work.emplase("Linal");
	work.emplase("Info");
	work.top().print();
	work.pop();
	work.top().print();
	std::cout << work.get_size() << std::endl;
	try {
		work.pop();
		work.pop();
		work.pop();
	}
	catch (std::exception& e) {
		std::cout << "Exception happened: " << e.what() << std::endl;
	}
}
