
#ifndef XYZ_VECTOR_H
#define XYZ_VECTOR_H

class xyz_vector {
	private:
		double x, y, z;
	public:
		xyz_vector();
		~xyz_vector();
		xyz_vector(const std::vector<double> & v);
		xyz_vector(const std::vector<double> & v, const double bta);
		xyz_vector(const double&, const double&, const double&);
		const double norm();
		const double get_x() const;
		const double get_y() const;
		const double get_z() const;
		void set_x(double);
		void set_y(double);
		void set_z(double);
		void set_xyz(const double&, const double&, const double&);
		const void print() const;
		xyz_vector operator* ( xyz_vector rhs);
		xyz_vector operator/ (double divisor);
		xyz_vector operator* (double mlt);
		xyz_vector operator^ ( xyz_vector rhs);
		xyz_vector operator+ (xyz_vector rhs);
		xyz_vector operator- (xyz_vector rhs);
};

void getTokens(std::ifstream & energyFile, std::vector< std::vector< std::string> > & tokens);
void getSymCrds(std::vector< std::vector<double> > & symCrds, std::vector< std::vector<std::string> > & tokens);
void print_vec_vec_double(std::vector< std::vector<double> > & symCrds);
void get_str_xyz(xyz_vector & h1, xyz_vector & h2, xyz_vector & h3, xyz_vector & h4, xyz_vector h1_ref, xyz_vector h2_ref, xyz_vector h3_ref, xyz_vector h4_ref, double s3x, double s3y, double s3z);

#endif
