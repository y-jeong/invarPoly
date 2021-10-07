#include <iostream>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <tr1/memory>
#include <cmath>
#include <iomanip>
#include "xyz_crd_generator.h"

int main() {
	std::ifstream refCrdFile;
	std::ofstream cartCrdFile;
	std::ofstream symCrdFile;
	refCrdFile.open("ch4p_ref_crd.txt");
	cartCrdFile.open("ch4p_cart_crd_short_2.txt");
	symCrdFile.open("ch4p_sym_crd_short_2.txt");

	std::vector< std::vector<std::string> > tokens;
	std::vector< std::vector<double> > ref_crds;
	std::vector< std::vector<double> > crds; //array of s3x,s3y,s3z,s4x,s4y,s4z 
	//const double bohrToAng = 0.5291772106712;

	getTokens(refCrdFile, tokens);
	getSymCrds(ref_crds, tokens);

	//print_vec_vec_double(ref_crds);


	//std::tr1::shared_ptr<double> s4x(new double[100], array_deleter<double>() );
	std::unique_ptr<double[]> s3x_(new double[1000] );
	std::unique_ptr<double[]> s3y_(new double[500] );
	std::unique_ptr<double[]> s3z_(new double[200] );
	std::unique_ptr<double[]> s4x_(new double[1000] );
	std::unique_ptr<double[]> s4y_(new double[500] );
	std::unique_ptr<double[]> s4z_(new double[200] );

	for(int i=0; i!=6; i++) {
		s3x_[i] = (i-2)*0.10;
	}
	for(int i=0; i!=6; i++) {
		s3y_[i] = (i-2)*0.10;
	}
	for(int i=0; i!=6; i++) {
		s3z_[i] = (i-2)*0.10;
	}
	for(int i=0; i!=6; i++) {
		s4x_[i] = (i-2)*0.10;
	}
	for(int i=0; i!=6; i++) {
		s4y_[i] = (i-2)*0.10;
	}
	for(int i=0; i!=6; i++) {
		s4z_[i] = (i-2)*0.10;
	}

	std::vector<double> crd;
/*
	for(int i=0; i!=5; i++) {
		for(int j=0; j!=5; j++) {
			for(int k=0; k!=5; k++) {
				for(int l=0; l!=5; l++) {
					for(int m=0; m!=5; m++) {
						for(int n=0; n!=5; n++) {
							crd.push_back(s3x_[i]);
							crd.push_back(s3y_[j]);
							crd.push_back(s3z_[k]);
							crd.push_back(s4x_[l]);
							crd.push_back(s4y_[m]);
							crd.push_back(s4z_[n]);
							crds.push_back(crd);
							crd.clear();
						}
					}
				}
			}
		}
	}
*/

	for(int i=0; i!=6; i++) {
		for(int j=0; j!=6; j++) {
			crd.push_back(s3x_[i]);
			crd.push_back(s3y_[j]);
			crd.push_back(0);
			crd.push_back(0);
			crd.push_back(0);
			crd.push_back(0);
			crds.push_back(crd);
			crd.clear();
		}
	}
	for(int i=0; i!=6; i++) {
		for(int j=0; j!=6; j++) {
			crd.push_back(s3x_[i]);
			crd.push_back(0);
			crd.push_back(s3z_[j]);
			crd.push_back(0);
			crd.push_back(0);
			crd.push_back(0);
			crds.push_back(crd);
			crd.clear();
		}
	}
	for(int i=0; i!=6; i++) {
		for(int j=0; j!=6; j++) {
			crd.push_back(s3x_[i]);
			crd.push_back(0);
			crd.push_back(0);
			crd.push_back(s4x_[j]);
			crd.push_back(0);
			crd.push_back(0);
			crds.push_back(crd);
			crd.clear();
		}
	}
	for(int i=0; i!=6; i++) {
		for(int j=0; j!=6; j++) {
			crd.push_back(s3x_[i]);
			crd.push_back(0);
			crd.push_back(0);
			crd.push_back(0);
			crd.push_back(s4y_[j]);
			crd.push_back(0);
			crds.push_back(crd);
			crd.clear();
		}
	}
	for(int i=0; i!=6; i++) {
		for(int j=0; j!=6; j++) {
			crd.push_back(s3x_[i]);
			crd.push_back(0);
			crd.push_back(0);
			crd.push_back(0);
			crd.push_back(0);
			crd.push_back(s4z_[j]);
			crds.push_back(crd);
			crd.clear();
		}
	}
	for(int i=0; i!=6; i++) {
		for(int j=0; j!=6; j++) {
			crd.push_back(0);
			crd.push_back(s3y_[i]);
			crd.push_back(s3z_[j]);
			crd.push_back(0);
			crd.push_back(0);
			crd.push_back(0);
			crds.push_back(crd);
			crd.clear();
		}
	}
	for(int i=0; i!=6; i++) {
		for(int j=0; j!=6; j++) {
			crd.push_back(0);
			crd.push_back(s3y_[i]);
			crd.push_back(0);
			crd.push_back(s4x_[j]);
			crd.push_back(0);
			crd.push_back(0);
			crds.push_back(crd);
			crd.clear();
		}
	}
	for(int i=0; i!=6; i++) {
		for(int j=0; j!=6; j++) {
			crd.push_back(0);
			crd.push_back(s3y_[i]);
			crd.push_back(0);
			crd.push_back(0);
			crd.push_back(s4y_[j]);
			crd.push_back(0);
			crds.push_back(crd);
			crd.clear();
		}
	}
	for(int i=0; i!=6; i++) {
		for(int j=0; j!=6; j++) {
			crd.push_back(0);
			crd.push_back(s3y_[i]);
			crd.push_back(0);
			crd.push_back(0);
			crd.push_back(0);
			crd.push_back(s4z_[j]);
			crds.push_back(crd);
			crd.clear();
		}
	}
	for(int i=0; i!=6; i++) {
		for(int j=0; j!=6; j++) {
			crd.push_back(0);
			crd.push_back(0);
			crd.push_back(s3z_[i]);
			crd.push_back(s4x_[j]);
			crd.push_back(0);
			crd.push_back(0);
			crds.push_back(crd);
			crd.clear();
		}
	}
	for(int i=0; i!=6; i++) {
		for(int j=0; j!=6; j++) {
			crd.push_back(0);
			crd.push_back(0);
			crd.push_back(s3z_[i]);
			crd.push_back(0);
			crd.push_back(s4y_[j]);
			crd.push_back(0);
			crds.push_back(crd);
			crd.clear();
		}
	}
	for(int i=0; i!=6; i++) {
		for(int j=0; j!=6; j++) {
			crd.push_back(0);
			crd.push_back(0);
			crd.push_back(s3z_[i]);
			crd.push_back(0);
			crd.push_back(0);
			crd.push_back(s4z_[j]);
			crds.push_back(crd);
			crd.clear();
		}
	}
	for(int i=0; i!=6; i++) {
		for(int j=0; j!=6; j++) {
			crd.push_back(0);
			crd.push_back(0);
			crd.push_back(0);
			crd.push_back(s4x_[i]);
			crd.push_back(s4y_[j]);
			crd.push_back(0);
			crds.push_back(crd);
			crd.clear();
		}
	}
	for(int i=0; i!=6; i++) {
		for(int j=0; j!=6; j++) {
			crd.push_back(0);
			crd.push_back(0);
			crd.push_back(0);
			crd.push_back(s4x_[i]);
			crd.push_back(0);
			crd.push_back(s4z_[j]);
			crds.push_back(crd);
			crd.clear();
		}
	}
	for(int i=0; i!=6; i++) {
		for(int j=0; j!=6; j++) {
			crd.push_back(0);
			crd.push_back(0);
			crd.push_back(0);
			crd.push_back(0);
			crd.push_back(s4y_[i]);
			crd.push_back(s4z_[j]);
			crds.push_back(crd);
			crd.clear();
		}
	}

	//print_vec_vec_double(crds);

	xyz_vector h1_ref = xyz_vector(ref_crds[1]);
	xyz_vector h2_ref = xyz_vector(ref_crds[2]);
	xyz_vector h3_ref = xyz_vector(ref_crds[3]);
	xyz_vector h4_ref = xyz_vector(ref_crds[4]);
	xyz_vector h1;
	xyz_vector h2;
	xyz_vector h3;
	xyz_vector h4;

	xyz_vector v21;// = (h2 ^ h1) / (h2 ^ h1).norm(); 
	xyz_vector v31;// = (h3 ^ h1) / (h3 ^ h1).norm(); 
	xyz_vector v41;// = (h4 ^ h1) / (h4 ^ h1).norm(); 
	xyz_vector v32;// = (h3 ^ h2) / (h3 ^ h2).norm(); 
	xyz_vector v42;// = (h4 ^ h2) / (h4 ^ h2).norm(); 
	xyz_vector v43;// = (h4 ^ h3) / (h4 ^ h3).norm();

	std::vector<xyz_vector> w;
	xyz_vector w1;
	xyz_vector w2;
	xyz_vector w3;
	xyz_vector w4;

	double a;
	double x1, x2, x3;
	double r1, r2, r3, r4, r5, r6, r7, r8, r9;
	double X,Y,Z;
	size_t cnt = 1;
	xyz_vector x = xyz_vector();

	double s3x;
	double s3y;
	double s3z;
	double s4x;
	double s4y;
	double s4z;
	const double zl = 0.00000001;


	for(std::vector< std::vector<double> >::iterator it=crds.begin(); it!=crds.end(); it++) {
		s3x = it->at(0);
		s3y = it->at(1);
		s3z = it->at(2);
		s4x = it->at(3);
		s4y = it->at(4);
		s4z = it->at(5);

		get_str_xyz(h1, h2, h3, h4, h1_ref, h2_ref, h3_ref, h4_ref, s3x, s3y, s3z);		

		symCrdFile << s3x << " " << s3y << " " << s3z << " " <<  s4x << " " << s4y << " " << s4z << std::endl;

		if( fabs(s4x)>zl || fabs(s4y)>zl || fabs(s4z)>zl ) {
					
			v21 = (h2 ^ h1) / (h2 ^ h1).norm(); 
			v31 = (h3 ^ h1) / (h3 ^ h1).norm(); 
			v41 = (h4 ^ h1) / (h4 ^ h1).norm(); 
			v32 = (h3 ^ h2) / (h3 ^ h2).norm(); 
			v42 = (h4 ^ h2) / (h4 ^ h2).norm(); 
			v43 = (h4 ^ h3) / (h4 ^ h3).norm();

			w1 = ((v21*s4z) + (v31*s4x)) - (v41*s4y);
			w2 = ( ((v21*s4z)*(-1)) + (v32*s4y) ) - (v42*s4x);
			w3 = (v32*s4y)*(-1) - v31*s4x - v43*s4z;
			w4 = v42*s4x + v41*s4y + v43*s4z;

			w.push_back(w1);
			w.push_back(w2);
			w.push_back(w3);
			w.push_back(w4);
	
			cartCrdFile << "C, "  << std::setprecision(10) << ref_crds[0][0] << ", " << ref_crds[0][1] << ", " << ref_crds[0][2] << std::endl;
			for(std::vector<xyz_vector>::iterator it=w.begin(); it!=w.end(); it++) {
				a = it->norm();
				x = (*it) / a;
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
				X = r1*ref_crds[cnt][0] + r2*ref_crds[cnt][1] + r3*ref_crds[cnt][2];
				Y = r4*ref_crds[cnt][0] + r5*ref_crds[cnt][1] + r6*ref_crds[cnt][2];
				Z = r7*ref_crds[cnt][0] + r8*ref_crds[cnt][1] + r9*ref_crds[cnt][2];
				//std::cout << "X = " << X << ", Y = " << Y << ", Z = " << Z << std::endl;

				cartCrdFile << std::setprecision(10) << "H, " << X << ", " << Y << ", " << Z << std::endl;

				cnt++;
			}
			//std::cout << std::endl;
			cartCrdFile << std::endl;

			w.clear();
			cnt = 1;
		}

		else {
			cartCrdFile << "C, "  << std::setprecision(10) << ref_crds[0][0] << ", " << ref_crds[0][1] << ", " << ref_crds[0][2] << std::endl;
			cartCrdFile << std::setprecision(10) << "H, " << h1.get_x() << ", " << h1.get_y() << ", " << h1.get_z() << std::endl;
			cartCrdFile << std::setprecision(10) << "H, " << h2.get_x() << ", " << h2.get_y() << ", " << h2.get_z() << std::endl;
			cartCrdFile << std::setprecision(10) << "H, " << h3.get_x() << ", " << h3.get_y() << ", " << h3.get_z() << std::endl;
			cartCrdFile << std::setprecision(10) << "H, " << h4.get_x() << ", " << h4.get_y() << ", " << h4.get_z() << std::endl;
			cartCrdFile << std::endl;
		}

	}


	refCrdFile.close();
	cartCrdFile.close();
	symCrdFile.close();
	return 0;
}

