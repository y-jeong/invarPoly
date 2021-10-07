#include <vector>
#include <sstream>
#include <string>
#include "util.h"
#include "debug.h"

std::vector<std::string> split_string(const std::string& str, const char& delim ) {
	std::istringstream ss(str);
	std::string token;
	std::vector< std::string > tokens;
	while ( std::getline(ss, token, delim) ) {
		if ( token.size() != 0 ) // Exclude null strings
			tokens.push_back(token);
	}
	return tokens;
}

std::vector< std::vector<std::string> > split_input_string(const std::string& data) {
	std::vector<std::string> lines;
	std::vector< std::vector<std::string> > data_split;
	std::vector<std::string> tmp_line;

	lines = split_string(data, '\n');
	for (auto& item : lines) {
		tmp_line = split_string(item, ' ');
		data_split.push_back(tmp_line);
		tmp_line.clear();
	}
	return data_split;
}

std::vector<double> vector_stod(const std::vector<std::string>& v) {
	std::vector<double> r;
	for (auto& i : v) r.push_back( std::stod(i) );
	return r;
}

std::vector< std::vector<double> > vector_vector_stod(const std::vector< std::vector<std::string> >& v) {
	std::vector< std::vector<double> > r;
	for (auto& i : v) r.push_back( vector_stod(i) );
	return r;
}
