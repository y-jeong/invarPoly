#include <vector>
#include "intree.h"

class INTREE {
	private:
		//std::string head;
		//INTREE subTree;
		//auto heads = std::make_unique<std::string>(10);
		//auto subTrees = std::make_unique<INTREE>(10);
		std::vector<std::string> heads;
		std::vector<INTREE> subTrees;

	public:
		~INTREE();

		template<class T>
		INTREE(const T&);
		
};
