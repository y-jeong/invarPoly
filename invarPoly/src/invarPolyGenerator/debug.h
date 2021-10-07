#include <iostream>
#include <vector>

template <class T>
void print_vector (std::vector<T>& v) {
	for(std::size_t i=0; i!=v.size(); i++) {
		std::cout << v.at(i) << " ";
	}
	std::cout << std::endl;
}

template <class T>
void print_vector_vector (const std::vector< std::vector<T> >& v) {
	for (auto& i : v) {
		for(auto& j : i) {
			std::cout << j << " ";
		}
		std::cout << std::endl;
	}
}

template <class T>
void print_line (T thing) {
	std::cout << thing << std::endl;
}

template <class T>
void print (T thing) {
	std::cout << thing << " ";
}

void print_check (size_t);
