#include <iostream>
#include <string>
#include <memory>
#include "distorted.h"
#include "molecule.h"
#include "util.h"
#include "debug.h"

DISTORTED::DISTORTED() {
}
DISTORTED::~DISTORTED() {}

DISTORTED::DISTORTED(std::shared_ptr<MOLECULE> ref_mole_, const std::string& dist_mode_, const std::string& dist_crds_) {
	ref_mole = ref_mole_;
	dist_mode = dist_mode_;
	dist_crds = vector_vector_stod( split_input_string(dist_crds_) );
}

// With given data and print the entire distorted geometries
void DISTORTED::distort() {
	bool one_center = false;
	std::string ref_geom = ref_mole->type();
	if ( ref_geom == "Td" || ref_geom == "td" || ref_geom == "Oh" || ref_geom == "oh" ) { one_center = true; }
	else {}

	if (one_center == true) {
		std::cout << "The reference molecule identified as an one-center transition metal complex." << std::endl;
		std::cout << "Orienting the reference molecule...coordinates: " << std::endl;
		ref_mole->orient(0);
		for ( auto i : ref_mole->at_set() ) i->print_xyz(); 
	}

	try {
		if (ref_geom == "Td" || ref_geom == "td") {
			std::cout << "Molecule type identified : Td" << std::endl;
			if (dist_mode == "t2 + t2" || dist_mode == "t2+t2") {
				std::cout << "Distortion type identified : t2 + t2" << std::endl;
				for (auto& i : dist_crds) {
					auto distMole = std::make_shared<MOLECULE>(ref_mole);
					distMole->distort_td_t2t2(i);
					distMole->print();
					std::cout << std::endl;
				}
			}
			else if (dist_mode == "t2_str") {
				std::cout << "Distortion type identified : t2_str" << std::endl;
				for (auto& i : dist_crds) {
					auto distMole = std::make_shared<MOLECULE>(ref_mole);
					distMole->distort_td_t2_str(i);
					distMole->print();
					std::cout << std::endl;
				}				
			}
			else if (dist_mode == "t2_bnd") {
				std::cout << "Distortion type identified : t2_bnd" << std::endl;
				for (auto& i : dist_crds) {
					auto distMole = std::make_shared<MOLECULE>(ref_mole);
					distMole->distort_td_t2_bnd(i);
					distMole->print();
					std::cout << std::endl;
				}
			}
			else { throw std::runtime_error("The distortion mode specified w.r.t. the reference geometry of the molecule is not supported."); }
		}

		else if (ref_geom == "Oh" || ref_geom == "oh") {
			std::cout << "Molecule type identified : Oh" << std::endl;
			if (dist_mode == "e_str") {
				std::cout << "Distortion type identified : e, stretching" << std::endl;
				for (auto& i : dist_crds) {
					auto distMole = std::make_shared<MOLECULE>(ref_mole);
					distMole->distort_oh_e_str(i);
					distMole->print();
					std::cout << std::endl;
				}
			}
			else { throw std::runtime_error("The distortion mode specified w.r.t. the reference geometry of the molecule is not supported."); }
		}

		else throw std::runtime_error("The geometry of the molecule specified is not supported.");

	}	catch (const std::exception& e) {
		std::cout << "Exception raised: " << e.what() << std::endl;
	}



}
