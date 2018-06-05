
#include "abstract_VM.hpp"


#include "Lexer.hpp"




int main(const int argc, char **argv)
{

    try {
        Lexer lexer(argc, argv);




    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }



	std::cout << "Hello World!" << std::endl;
	std::cout << argv[argc - 1] << std::endl;
//	std::cout << argv[argc] << std::endl;


	return 0;
}
