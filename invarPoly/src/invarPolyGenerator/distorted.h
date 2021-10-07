#include <string>
#include <memory>
#include "molecule.h"

#ifndef DISTORTED_H
#define DISTERTED_H

class DISTORTED {
	private:
		std::shared_ptr<MOLECULE> ref_mole;
		std::string dist_mode;
		std::vector< std::vector<double> > dist_crds;

	public:
		DISTORTED();
		~DISTORTED();
		DISTORTED(std::shared_ptr<MOLECULE>, const std::string&, const std::string&);
		void distort();

};

#endif 
