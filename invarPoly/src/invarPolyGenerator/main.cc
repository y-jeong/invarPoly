#include <iostream>
#include <memory>
#include "input.h"
#include "distorted.h"
#include "debug.h"

using namespace std;

int main(int argc, char* argv[]) {

	try {
		if (argc != 2)
			throw std::runtime_error("One input file should be given.");
		auto input = make_shared<INPUT>(argv[1]);
		string jobName = input->get_jobName();

		if ( jobName == "mole_dist" || jobName == "moledist" ) {
			auto distorted = make_shared<DISTORTED>( input->get_molecule(), input->get_dist_mode(), input->get_dist_crds() );
			distorted->distort();
		}

	} catch (const exception& e) {
			cout << "Exception raised: " << e.what() << endl;
	}

	return 0;
}
