#include <string>
#include <sstream>
#include <memory>
#include <cmath>
#include <iomanip> // for std::setprecision(int)
#include "molecule.h"
#include "debug.h"
#include "util.h"
#include "xyz_crd_generator/xyz_crd_generator.h"

MOLECULE::~MOLECULE() {
}

MOLECULE::MOLECULE(const std::string& m_t, const std::string& at_n, const std::string& at_data) {
	mole_type = m_t;
	this->atom_number_in(at_n);
	this->atom_data_in(at_data);
}

MOLECULE::MOLECULE(std::shared_ptr<MOLECULE> ref) {
	mole_type = ref->type();
	atom_number = ref->at_num();
	atom_set = ref->at_set();
}

//----------

void MOLECULE::atom_number_in(const std::string& at_n) {
	atom_number = stoi(at_n);
}

void MOLECULE::atom_data_in(const std::string& at_data) {
	std::vector<std::string> lines;

	lines = split_string(at_data, ',');
	for (size_t i=0; i!=atom_number; i++) {
		atom_set.push_back( std::make_shared<ATOM>( lines[i] ) );
	}	
}

//----------

void MOLECULE::orient(const std::size_t& type) {
	try {
		// One-center transition metal complex
		if (type == 0) {
			std::shared_ptr<ATOM> cen = ( this->find_atom("C1","OO","OO") )[0];
			xyz_vector cen_xyz( cen->get_x(), cen->get_y(), cen->get_z() );
			for (auto& i : atom_set) {
				i->xyz_subtract(cen_xyz);
			}
		}
		else throw std::runtime_error("An error in MOLECULE::orient.");
	} catch (const std::exception& e) {
		std::cout << "Exception raised: " << e.what() << std::endl;
	}
}

void MOLECULE::distort_td_t2_str(const std::vector<double>& dist_crd) {
	std::shared_ptr<ATOM> l1 = find_atom("C1","L1","OO")[0]; // index 0 because find_atom gives a vector of ATOM pointers
	std::shared_ptr<ATOM> l2 = find_atom("C1","L2","OO")[0];
	std::shared_ptr<ATOM> l3 = find_atom("C1","L3","OO")[0];
	std::shared_ptr<ATOM> l4 = find_atom("C1","L4","OO")[0];
	xyz_vector v1 = l1->get_xyz();
	xyz_vector v2 = l2->get_xyz();
	xyz_vector v3 = l3->get_xyz();
	xyz_vector v4 = l4->get_xyz();
	double t1 = dist_crd[0];
	double t2 = dist_crd[1];
	double t3 = dist_crd[2];
	l1->xyz_add( v1 * ( t1 + t2 + t3 ) );
	l2->xyz_add( v2 * (-t1 + t2 - t3 ) );
	l3->xyz_add( v3 * ( t1 - t2 - t3 ) );
	l4->xyz_add( v4 * (-t1 - t2 + t3 ) );
}

void MOLECULE::distort_td_t2_bnd(const std::vector<double>& dist_crd) {
	const double zl = 0.00000001;
	std::shared_ptr<ATOM> l1 = find_atom("C1","L1","OO")[0]; // index 0 because find_atom gives a vector of ATOM pointers
	std::shared_ptr<ATOM> l2 = find_atom("C1","L2","OO")[0];
	std::shared_ptr<ATOM> l3 = find_atom("C1","L3","OO")[0];
	std::shared_ptr<ATOM> l4 = find_atom("C1","L4","OO")[0];

	xyz_vector l1_disp;
	xyz_vector l2_disp;
	xyz_vector l3_disp;
	xyz_vector l4_disp;
	std::vector<xyz_vector> l_disp;
	l_disp.push_back( l1_disp );
	l_disp.push_back( l2_disp );
	l_disp.push_back( l3_disp );
	l_disp.push_back( l4_disp );

	xyz_vector v1_ref( l1->get_xyz() );
	xyz_vector v2_ref( l2->get_xyz() );
	xyz_vector v3_ref( l3->get_xyz() );
	xyz_vector v4_ref( l4->get_xyz() );
	std::vector<xyz_vector> v_ref;
	v_ref.push_back(v1_ref);
	v_ref.push_back(v2_ref);
	v_ref.push_back(v3_ref);
	v_ref.push_back(v4_ref);

	xyz_vector v21;
	xyz_vector v31;
	xyz_vector v41;
	xyz_vector v32;
	xyz_vector v42;
	xyz_vector v43;

	std::vector<xyz_vector> w;
	xyz_vector w1;
	xyz_vector w2;
	xyz_vector w3;
	xyz_vector w4;

	double s4x = dist_crd[0];
	double s4y = dist_crd[1];
	double s4z = dist_crd[2];

	double a;
	double x1, x2, x3;
	double r1, r2, r3, r4, r5, r6, r7, r8, r9;
	double X,Y,Z;
	xyz_vector x = xyz_vector();

	if( fabs(s4x)>zl || fabs(s4y)>zl || fabs(s4z)>zl ) {

		v21 = (v2_ref ^ v1_ref) / (v2_ref ^ v1_ref).norm(); 
		v31 = (v3_ref ^ v1_ref) / (v3_ref ^ v1_ref).norm(); 
		v41 = (v4_ref ^ v1_ref) / (v4_ref ^ v1_ref).norm(); 
		v32 = (v3_ref ^ v2_ref) / (v3_ref ^ v2_ref).norm(); 
		v42 = (v4_ref ^ v2_ref) / (v4_ref ^ v2_ref).norm(); 
		v43 = (v4_ref ^ v3_ref) / (v4_ref ^ v3_ref).norm(); 

		w1 = ((v21*s4z) + (v31*s4x)) - (v41*s4y);
		w2 = ( ((v21*s4z)*(-1)) + (v32*s4y) ) - (v42*s4x);
		w3 = (v32*s4y)*(-1) - v31*s4x - v43*s4z;
		w4 = v42*s4x + v41*s4y + v43*s4z;

		w.push_back(w1);
		w.push_back(w2);
		w.push_back(w3);
		w.push_back(w4);

		for (std::size_t i=0; i!=4; i++) {
			a = w[i].norm();
			x = w[i] / a;
			x1 = x.get_x();
			x2 = x.get_y();
			x3 = x.get_z();	
			r1 = cos(a) + pow(x1, 2) * (1 - cos(a));
			r2 = x1 * x2 * (1-cos(a)) - x3 * sin(a);
			r3 = x1 * x3 * (1-cos(a)) + x2 * sin(a);
			r4 = x2 * x1 * (1-cos(a)) + x3 * sin(a);
			r5 = cos(a) + pow(x2, 2) * (1 - cos(a));
			r6 = x2 * x3 * (1-cos(a)) - x1 * sin(a);
			r7 = x3 * x1 * (1-cos(a)) - x2 * sin(a);
			r8 = x3 * x2 * (1-cos(a)) + x1 * sin(a);
			r9 = cos(a) + pow(x3, 2) * (1 - cos(a));
			X = r1*v_ref[i].get_x() + r2*v_ref[i].get_y() + r3*v_ref[i].get_z();
			Y = r4*v_ref[i].get_x() + r5*v_ref[i].get_y() + r6*v_ref[i].get_z();
			Z = r7*v_ref[i].get_x() + r8*v_ref[i].get_y() + r9*v_ref[i].get_z();

			l_disp[i].set_xyz( X - v_ref[i].get_x(), Y - v_ref[i].get_y(), Z - v_ref[i].get_z() );
		}
	}
	else {
		for (std::size_t i=0; i!=4; i++) {
			X = v_ref[i].get_x();
			Y = v_ref[i].get_y();
			Z = v_ref[i].get_z();

			l_disp[i].set_xyz( X - v_ref[i].get_x(), Y - v_ref[i].get_y(), Z - v_ref[i].get_z() );
		}
	}

	std::cout << find_atom("C1", "L1", "XX").size() << std::endl;
	for (auto& i : this->find_atom("C1", "L1", "XX") ) { i->xyz_add(l_disp[0]); } // displace all first-ligand atoms
	for (auto& i : find_atom("C1", "L2", "XX") ) { i->xyz_add(l_disp[1]); } 
	for (auto& i : find_atom("C1", "L3", "XX") ) { i->xyz_add(l_disp[2]); } 
	for (auto& i : find_atom("C1", "L4", "XX") ) { i->xyz_add(l_disp[3]); } 	
}

void MOLECULE::distort_td_t2t2(const std::vector<double>& dist_crd) {
	const double zl = 0.00000001;
	std::shared_ptr<ATOM> l1 = find_atom("C1","L1","OO")[0]; // index 0 because find_atom gives a vector of ATOM pointers
	std::shared_ptr<ATOM> l2 = find_atom("C1","L2","OO")[0];
	std::shared_ptr<ATOM> l3 = find_atom("C1","L3","OO")[0];
	std::shared_ptr<ATOM> l4 = find_atom("C1","L4","OO")[0];

	xyz_vector l1_disp;
	xyz_vector l2_disp;
	xyz_vector l3_disp;
	xyz_vector l4_disp;
	std::vector<xyz_vector> l_disp;
	l_disp.push_back( l1_disp );
	l_disp.push_back( l2_disp );
	l_disp.push_back( l3_disp );
	l_disp.push_back( l4_disp );

	xyz_vector v1_ref( l1->get_xyz() );
	xyz_vector v2_ref( l2->get_xyz() );
	xyz_vector v3_ref( l3->get_xyz() );
	xyz_vector v4_ref( l4->get_xyz() );
	std::vector<xyz_vector> v_ref;
	v_ref.push_back(v1_ref);
	v_ref.push_back(v2_ref);
	v_ref.push_back(v3_ref);
	v_ref.push_back(v4_ref);

	xyz_vector v1_str;
	xyz_vector v2_str;
	xyz_vector v3_str;
	xyz_vector v4_str;

	xyz_vector v21;
	xyz_vector v31;
	xyz_vector v41;
	xyz_vector v32;
	xyz_vector v42;
	xyz_vector v43;

	std::vector<xyz_vector> w;
	xyz_vector w1;
	xyz_vector w2;
	xyz_vector w3;
	xyz_vector w4;

	double s3x = dist_crd[0];
	double s3y = dist_crd[1];
	double s3z = dist_crd[2];
	double s4x = dist_crd[3];
	double s4y = dist_crd[4];
	double s4z = dist_crd[5];

	double a;
	double x1, x2, x3;
	double r1, r2, r3, r4, r5, r6, r7, r8, r9;
	double X,Y,Z;
	xyz_vector x = xyz_vector();

	
	get_str_xyz(v1_str, v2_str, v3_str, v4_str, v1_ref, v2_ref, v3_ref, v4_ref, s3x, s3y, s3z);
	std::vector<xyz_vector> v_str;
	v_str.push_back(v1_str);
	v_str.push_back(v2_str);
	v_str.push_back(v3_str);
	v_str.push_back(v4_str);

	if( fabs(s4x)>zl || fabs(s4y)>zl || fabs(s4z)>zl ) {

		v21 = (v2_ref ^ v1_ref) / (v2_ref ^ v1_ref).norm(); 
		v31 = (v3_ref ^ v1_ref) / (v3_ref ^ v1_ref).norm(); 
		v41 = (v4_ref ^ v1_ref) / (v4_ref ^ v1_ref).norm(); 
		v32 = (v3_ref ^ v2_ref) / (v3_ref ^ v2_ref).norm(); 
		v42 = (v4_ref ^ v2_ref) / (v4_ref ^ v2_ref).norm(); 
		v43 = (v4_ref ^ v3_ref) / (v4_ref ^ v3_ref).norm(); 

		w1 = ((v21*s4z) + (v31*s4x)) - (v41*s4y);
		w2 = ( ((v21*s4z)*(-1)) + (v32*s4y) ) - (v42*s4x);
		w3 = (v32*s4y)*(-1) - v31*s4x - v43*s4z;
		w4 = v42*s4x + v41*s4y + v43*s4z;

		w.push_back(w1);
		w.push_back(w2);
		w.push_back(w3);
		w.push_back(w4);

		for (std::size_t i=0; i!=4; i++) {
			a = w[i].norm();
			x = w[i] / a;
			x1 = x.get_x();
			x2 = x.get_y();
			x3 = x.get_z();	
			r1 = cos(a) + pow(x1, 2) * (1 - cos(a));
			r2 = x1 * x2 * (1-cos(a)) - x3 * sin(a);
			r3 = x1 * x3 * (1-cos(a)) + x2 * sin(a);
			r4 = x2 * x1 * (1-cos(a)) + x3 * sin(a);
			r5 = cos(a) + pow(x2, 2) * (1 - cos(a));
			r6 = x2 * x3 * (1-cos(a)) - x1 * sin(a);
			r7 = x3 * x1 * (1-cos(a)) - x2 * sin(a);
			r8 = x3 * x2 * (1-cos(a)) + x1 * sin(a);
			r9 = cos(a) + pow(x3, 2) * (1 - cos(a));
			X = r1*v_str[i].get_x() + r2*v_str[i].get_y() + r3*v_str[i].get_z();
			Y = r4*v_str[i].get_x() + r5*v_str[i].get_y() + r6*v_str[i].get_z();
			Z = r7*v_str[i].get_x() + r8*v_str[i].get_y() + r9*v_str[i].get_z();

			l_disp[i].set_xyz( X - v_ref[i].get_x(), Y - v_ref[i].get_y(), Z - v_ref[i].get_z() );
		}
	}
	else {
		for (std::size_t i=0; i!=4; i++) {
			X = v_str[i].get_x();
			Y = v_str[i].get_y();
			Z = v_str[i].get_z();

			l_disp[i].set_xyz( X - v_ref[i].get_x(), Y - v_ref[i].get_y(), Z - v_ref[i].get_z() );
		}
	}

	std::cout << find_atom("C1", "L1", "XX").size() << std::endl;
	for (auto& i : this->find_atom("C1", "L1", "XX") ) { i->xyz_add(l_disp[0]); } // displace all first-ligand atoms
	for (auto& i : find_atom("C1", "L2", "XX") ) { i->xyz_add(l_disp[1]); } 
	for (auto& i : find_atom("C1", "L3", "XX") ) { i->xyz_add(l_disp[2]); } 
	for (auto& i : find_atom("C1", "L4", "XX") ) { i->xyz_add(l_disp[3]); } 	
}

void MOLECULE::distort_oh_e_str(const std::vector<double>& dist_crd) {
	std::shared_ptr<ATOM> l1 = find_atom("C1","L1","OO")[0];
	std::shared_ptr<ATOM> l2 = find_atom("C1","L2","OO")[0];
	std::shared_ptr<ATOM> l3 = find_atom("C1","L3","OO")[0];
	std::shared_ptr<ATOM> l4 = find_atom("C1","L4","OO")[0];
	std::shared_ptr<ATOM> l5 = find_atom("C1","L5","OO")[0];
	std::shared_ptr<ATOM> l6 = find_atom("C1","L6","OO")[0];

	double e1 = dist_crd[0]; // E_nu
	double e2 = dist_crd[1]; // E_epsilon

	l1->xyz_add( 0, 0, e1/sqrt(3) );
	l2->xyz_add( -e1/ (2*sqrt(3)) + e2/2, 0, 0 );
	l3->xyz_add( 0, -e1/(2*sqrt(3)) - e2/2, 0 );
	l4->xyz_add( 0, 0, -e1/sqrt(3) );
	l5->xyz_add( e1/ (2*sqrt(3)) - e2/2, 0, 0 );
	l6->xyz_add( 0, e1/(2*sqrt(3)) + e2/2, 0 );
}


std::vector< std::shared_ptr<ATOM> > MOLECULE::find_atom(const std::string& a, const std::string& b, const std::string& c) { // define as a private memeber?
	std::vector< std::shared_ptr<ATOM> > r;
	std::vector<bool> satis(3,false);
	std::vector<std::string> conditions;
	conditions.push_back(a);
	conditions.push_back(b);
	conditions.push_back(c);

	for (auto& i : atom_set) {
		for (std::size_t l=0; l!=3; l++) {
			if (conditions[l] == "XX") { // includes "OO"
				satis[l] = true;
			}
			else if (conditions[l] == "OO") {
				if ( i->get_conn(l) == "OO" ) satis[l] = true;
			}
			else {
				if ( i->get_conn(l) == conditions[l] ) satis[l] = true;
			}
		}
		if ( satis[0] && satis[1] && satis[2] ) r.push_back(i);
		for (auto p : satis) p = false;
	}
	return r;
}

//----------

std::string MOLECULE::type() { return mole_type; }
std::size_t MOLECULE::at_num() { return atom_number; }
std::vector< std::shared_ptr<ATOM> > MOLECULE::at_set() { return atom_set; }

//----------

void MOLECULE::print() {
	for (auto& i : atom_set) { i->print(); }
}
