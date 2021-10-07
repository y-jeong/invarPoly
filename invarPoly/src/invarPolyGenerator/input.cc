#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "input.h"
#include "util.h"
#include "debug.h"

INPUT::INPUT() {
}

INPUT::~INPUT() {
}

INPUT::INPUT(const std::string& fileName) {

	std::ifstream inFile(fileName, std::ifstream::in);
	std::string line, all;

	job = std::make_shared<JOB>();

	while( getline(inFile,line) ) {
		all += line;
	}
	this->gather_info(all);

  inFile.close();
}

std::shared_ptr< std::vector<std::string> > INPUT::get_strings_inside(const std::shared_ptr<std::string> str, const std::shared_ptr<std::string> delim) {
	std::size_t start = 0, found;
	std::vector<std::size_t> deli_loc;
	auto data = std::make_shared< std::vector<std::string> >();

	found = str->find(*delim, start);
	while (found != std::string::npos) {
		deli_loc.push_back(found);
		start = found + 1;
		found = str->find(*delim, start);
	}
	
	for(std::vector<std::size_t>::iterator it=deli_loc.begin(); it!=deli_loc.end(); it += 2) {
	  data->push_back( str->substr( (*it)+1, *(it+1)-(*it)-1 ) );
	}

	return data;
}


void INPUT::gather_info(const std::string& all) {

	// collect all information in the input file inside ""
  auto data_ = this->get_strings_inside( std::make_shared<std::string>(all), std::make_shared<std::string>("\"") ); // This is a shared pointer

	// save the job name
	auto job_data = vector_find<std::string>( data_, std::make_shared<std::string>("job") ) + 1;
	this->job->name_in( *job_data );

	// depending on the job type do different things
	try {
		if( job->name() == "mole_dist" || job->name() == "moledist") {
			auto mole_type = vector_find<std::string>( data_, std::make_shared<std::string>("mole_type") ) + 1;
			auto atom_number_data = vector_find<std::string>( data_, std::make_shared<std::string>("atom_number") ) + 1; // vector<string>::iterator
			auto atom_positions_data = vector_find<std::string>( data_, std::make_shared<std::string>("atom_positions") ) + 1; // vector<string>::iterator

			// build the reference molecule directly from the input file
			molecule = std::make_shared<MOLECULE>(*mole_type, *atom_number_data, *atom_positions_data);

			// save distortion mode and distortion data
			dist_mode = *( vector_find<std::string>( data_, std::make_shared<std::string>("dist_mode") ) + 1 ); // e.g. "t2 + t2"
			std::string distFileName = *( vector_find<std::string>( data_, std::make_shared<std::string>("dist_file") ) + 1 );
			std::ifstream distFile(distFileName);
			std::string tmp_str;
			while ( std::getline(distFile, tmp_str) ) {
				dist_crds += tmp_str;
				dist_crds += '\n';
			}
			distFile.close();

			//
		}
		else if( job->name() == "pes_fit" ) {
		}
		else throw std::runtime_error("Job name is invalid");

	}	catch(const std::exception& e) {
		std::cout << "Exception raised: " << e.what() << std::endl;
	}
}

std::string INPUT::get_jobName() {
	return this->job->name();
}

std::shared_ptr<MOLECULE> INPUT::get_molecule() {
	return this->molecule;
}

std::string INPUT::get_dist_mode() {
	return this->dist_mode;
}

std::string INPUT::get_dist_crds() {
	return this->dist_crds;
}

