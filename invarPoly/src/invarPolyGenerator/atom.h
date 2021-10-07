#include <string>
#include <vector>
#include "xyz_crd_generator/xyz_crd_generator.h"

#ifndef ATOM_H
#define ATOM_H

class ATOM {
	private:
		std::string elem; // element name
		std::vector<std::string> conn; // connectivity; defined with three two-letter strings; all atoms that are not central nor adjacent are considered connected to the adjacent atom of the ligand group
		double x, y, z; // positions
		std::size_t identity;
		// 0: central atom, 1: adjacent atom, 2: terminal atom (on metal side in the case of a dimer)
		// 3: bridging atom (A), 4: bridge atom (X), 5: terminal atom on bridge atom, 6: terminal atom on bridging atom
	public:
		~ATOM();
		ATOM(const std::string&);

		void xyz_add(const xyz_vector&);
		void xyz_subtract(const xyz_vector&);
		void xyz_add(const double&, const double&, const double&);
		void xyz_subtract(const double&, const double&, const double&);

		const std::string get_elem() const;
		std::string get_conn(const std::size_t&);
		double get_x();
		double get_y();
		double get_z();
		const std::vector<double> get_xyz() const;

		const void print_xyz() const;
		const void print() const;
};

#endif
