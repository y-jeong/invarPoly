#include <iostream>
#include <string>
#include <vector>
#include <memory>

//using namespace std;

#ifndef UTIL_H
#define UTIL_H

std::vector<std::string> split_string(const std::string&, const char&);
std::vector< std::vector<std::string> > split_input_string(const std::string&);
std::vector<double> vector_stod(const std::vector<std::string>&);
std::vector< std::vector<double> > vector_vector_stod(const std::vector< std::vector<std::string> >&);

template<class T>
typename std::vector<T>::iterator vector_find( const std::shared_ptr< std::vector<T> > data, const std::shared_ptr<T> target) {
	try {
		for (typename std::vector<T>::iterator it=data->begin(); it!=data->end(); it++) {
			if (*it == *target) // will this work?
				return it;
		}
		throw std::runtime_error("A needed keyword could not be found in the input");

	} catch (const std::exception& e) {
		std::cout << "Exception raised: " << e.what() << std::endl;
	}
}

#endif
