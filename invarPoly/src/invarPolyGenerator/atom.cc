#include <iostream>
#include <string>
#include "atom.h"
#include "util.h"
#include "xyz_crd_generator/xyz_crd_generator.h"
#include "debug.h"

ATOM::~ATOM() {
}

ATOM::ATOM(const std::string& line) { // a line of the input
	std::vector<std::string> tokens;
	char conn0, conn1, conn2;

	tokens = split_string(line, ' ');
	elem = tokens[0];
	for(size_t i=1; i!=4; i++) conn.push_back( tokens[i] );
	x = stod( tokens[4] );
	y = stod( tokens[5] );
	z = stod( tokens[6] );

	conn0 = conn[0][0]; // first letter of the first connectivity designation 
	conn1 = conn[1][0]; // of the second
	conn2 = conn[2][0]; // of the third 
	
	try {
		if (conn0 == 'C') {
			if (conn1 == 'O') identity = 0; // central atom
			else if (conn1 == 'L') {
				if (conn2 == 'O') identity = 1; // adjacent atom
				else if (conn2 == 'T') identity = 2; // terminal atom
				else throw std::runtime_error("Atom type designation error: third"); 
			}
			else throw std::runtime_error("Atom type designation error: second");
		}
		else if (conn0 == 'B') {
			if (conn1 == 'A') {
				if (conn2 == 'O') identity = 3; // bridging atom (A)
				else if (conn2 == 'T') identity = 6; // terminal atom on bridging atom
				else throw std::runtime_error("Atom type designation error: third");
			}
			else if (conn1 == 'X') {
				if (conn2 == 'O') identity = 4; // bridge atom (X)
				else if (conn2 == 'T') identity = 5; // terminal atom on bridge atom
				else throw std::runtime_error("Atom type designation error: third");

			}
			else throw std::runtime_error("Atom type designation error: second");
		}
		else {
			throw std::runtime_error("Atom type designation error: first");
		}
	} catch (const std::exception& e) {
		std::cout << "Exception raised: " << e.what() << std::endl;
	}
}

//----------

void ATOM::xyz_add(const xyz_vector& t) {
	x += t.get_x();
	y += t.get_y();
	z += t.get_z();
}

void ATOM::xyz_subtract(const xyz_vector& t) {
	x -= t.get_x();
	y -= t.get_y();
	z -= t.get_z();
}

void ATOM::xyz_add(const double& a, const double& b, const double& c) {
	x += a;
	y += b;
	z += c;
}

void ATOM::xyz_subtract(const double& a, const double& b, const double& c) {
	x -= a;
	y -= b;
	z -= c;
}

//----------

const std::string ATOM::get_elem() const { return this->elem; }

std::string ATOM::get_conn(const std::size_t& i) { return conn[i]; }
double ATOM::get_x() { return x; }
double ATOM::get_y() { return y; }
double ATOM::get_z() { return z; }

const std::vector<double> ATOM::get_xyz() const {
	std::vector<double> r;
	r.push_back(x);	
	r.push_back(y);	
	r.push_back(z);
	return r;
}

//----------

const void ATOM::print_xyz() const {
	std::cout << "x = " << x << ", y = " << y << ", z = " << z << std::endl;
}

const void ATOM::print() const {
	std::cout << "{\"atom\" : \"" << elem << "\", \"xyz\" : [ " << x << ", " << y << ", " << z << "] }" << std::endl;
}
