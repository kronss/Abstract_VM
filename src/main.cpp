
#include "abstract_VM.hpp"


#include "Lexer.hpp"




int main(const int argc, const char **argv)
{

		Lexer lexer(argc, argv[argc - 1]);








	std::cout << "Hello World!" << std::endl;
	std::cout << argv[argc - 1] << std::endl;
//	std::cout << argv[argc] << std::endl;


	return 0;
}
