#include <string>
#include <vector>
#include <memory>
#include "atom.h"

#ifndef MOLECULE_H
#define MOLECULE_H

class MOLECULE {
	private:
		std::string mole_type;
		std::size_t atom_number;
		std::vector< std::shared_ptr<ATOM> > atom_set;

		void atom_number_in(const std::string&);
		void atom_data_in(const std::string&);

	public:
		~MOLECULE();
		MOLECULE(const std::string&, const std::string&, const std::string&);
		MOLECULE(std::shared_ptr<MOLECULE>);

		void orient(const std::size_t&);
		void distort_td_t2_str(const std::vector<double>&);
		void distort_td_t2_bnd(const std::vector<double>&);
		void distort_td_t2t2(const std::vector<double>&);
		void distort_oh_e_str(const std::vector<double>&);
		std::vector< std::shared_ptr<ATOM> > find_atom(const std::string&, const std::string&, const std::string&); 

		std::string type();
		std::size_t at_num();
		std::vector< std::shared_ptr<ATOM> > at_set();

		void print();
};

#endif
