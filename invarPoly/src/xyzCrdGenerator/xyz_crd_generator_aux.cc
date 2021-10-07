#include <vector>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <cmath>
#include "xyz_crd_generator.h"

xyz_vector::xyz_vector() {
	x=0; y=0; z=0;
}

xyz_vector::~xyz_vector() {
}

xyz_vector::xyz_vector(const std::vector<double> & v) {
	x = v[0];
	y = v[1];
	z = v[2];
}

xyz_vector::xyz_vector(const std::vector<double> & v, const double bta) {
	x = v[0] * bta;
	y = v[1] * bta;
	z = v[2] * bta;

	//std::cout << "x = " << x << std::endl;
}

xyz_vector::xyz_vector(const double& x_, const double& y_, const double& z_) {
	x = x_;
	y = y_;
	z = z_;
}

xyz_vector xyz_vector::operator* ( xyz_vector rhs) {
	xyz_vector prod = xyz_vector();
	prod.set_x(x * rhs.get_x());
	prod.set_y(y * rhs.get_y());
	prod.set_z(z * rhs.get_z());
	return prod;
}
xyz_vector xyz_vector::operator^ ( xyz_vector rhs) {
	xyz_vector prod = xyz_vector();
	prod.set_x(y * rhs.get_z() - z * rhs.get_y());
	prod.set_y(z * rhs.get_x() - x * rhs.get_z());
	prod.set_z(x * rhs.get_y() - y * rhs.get_x());
	return prod;
}
xyz_vector xyz_vector::operator* (double mlt) {
	xyz_vector prod = xyz_vector();	
	prod.set_x(mlt * x);
	prod.set_y(mlt * y);
	prod.set_z(mlt * z);
	return prod;
}
xyz_vector xyz_vector::operator/ (double divisor) {
	xyz_vector result = xyz_vector();
	result.set_x(x / divisor);
	result.set_y(y / divisor);
	result.set_z(z / divisor);
	return result;
}
xyz_vector xyz_vector::operator+ (xyz_vector rhs) {
	xyz_vector result = xyz_vector();
	result.set_x(x + rhs.get_x());
	result.set_y(y + rhs.get_y());
	result.set_z(z + rhs.get_z());
	return result;
}
xyz_vector xyz_vector::operator- (xyz_vector rhs) {
	xyz_vector result = xyz_vector();
	result.set_x(x - rhs.get_x());
	result.set_y(y - rhs.get_y());
	result.set_z(z - rhs.get_z());
	return result;
}

const double xyz_vector::norm() {
	return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
}

const double xyz_vector::get_x() const {
	return x;
}
const double xyz_vector::get_y() const {
	return y;
}
const double xyz_vector::get_z() const {
	return z;
}
void xyz_vector::set_x(double val) {
	x = val;
}
void xyz_vector::set_y(double val) {
	y = val;
}
void xyz_vector::set_z(double val) {
	z = val;
}

void xyz_vector::set_xyz(const double& x_, const double& y_, const double& z_) {
	x = x_;
	y = y_;
	z = z_;
}

const void xyz_vector::print() const {
	std::cout << "x = " << x << ", y = " << y << ", z = " << z << std::endl;
}

void getTokens(std::ifstream & energyFile, std::vector< std::vector<std::string> > & tokens) {
  std::string line,token;
  std::vector<std::string> crds;

	tokens.clear();  //CRITICAL
  while(getline(energyFile,line)) {
    std::istringstream iss(line);
    while(getline(iss,token,' ')) {
      if(token.size() != 0) {
        crds.push_back(token.c_str());
      }
    }
    tokens.push_back(crds);
    crds.clear();
  }
}

void getSymCrds(std::vector< std::vector<double> > & symCrds, std::vector< std::vector<std::string> > & tokens) {
  std::vector< std::vector<std::string> >::iterator it1;
  std::vector<std::string>::iterator it2;
  std::vector<double> tmpCrd;

	symCrds.clear();

  for(it1=tokens.begin(); it1 != tokens.end(); it1++) {
    for(it2=it1->begin(); it2 != it1->end(); it2++) {
      tmpCrd.push_back(atof((*it2).c_str()));
    }
    symCrds.push_back(tmpCrd);
    tmpCrd.clear();
  }
}

void print_vec_vec_double(std::vector< std::vector<double> > & symCrds) {
  std::vector< std::vector<double> >::iterator it1;
  std::vector<double>::iterator it2;

  for(it1=symCrds.begin(); it1!=symCrds.end(); it1++) {
    for(it2=it1->begin(); it2 != it1->end(); it2++) {
      std::cout << *it2 << " ";
    }
    std::cout << std::endl;
  }
}

void get_str_xyz(xyz_vector & h1, xyz_vector & h2, xyz_vector & h3, xyz_vector & h4, xyz_vector h1_ref, xyz_vector h2_ref, xyz_vector h3_ref, xyz_vector h4_ref, double s3x, double s3y, double s3z) {
	h1 = h1_ref + ( ( h1_ref / h1_ref.norm() ) * (-s3x + s3y - s3z) / 2 );
	h2 = h2_ref + ( ( h2_ref / h2_ref.norm() ) * ( s3x - s3y - s3z) / 2 );
	h3 = h3_ref + ( ( h3_ref / h3_ref.norm() ) * (-s3x - s3y + s3z) / 2 );
	h4 = h4_ref + ( ( h4_ref / h4_ref.norm() ) * ( s3x + s3y + s3z) / 2 );
}
