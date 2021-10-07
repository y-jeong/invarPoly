//#include "intree.h"
#include <string>
#include <vector>
#include <memory>
#include "job.h"
#include "molecule.h"

#ifndef INPUT_H
#define INPUT_H

class INPUT {
	private:
		std::shared_ptr<JOB> job;
		std::shared_ptr<MOLECULE> molecule;
		std::string dist_mode;
		std::string dist_crds;

		std::shared_ptr< std::vector<std::string> > get_strings_inside( const std::shared_ptr<std::string>, const std::shared_ptr<std::string> );
	public:
		INPUT();
		~INPUT();
		INPUT(const std::string&);

		void gather_info(const std::string&);

		std::string get_jobName();
		std::shared_ptr<MOLECULE> get_molecule();
		std::string get_dist_mode();
		std::string get_dist_crds();
		
};

#endif
