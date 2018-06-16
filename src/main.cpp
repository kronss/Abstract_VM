//#include "abstract_VM.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"


int main(const int argc, char **argv)
{
    try {
        Lexer lexer(argc, argv);
        lexer.read();

        Parser parser(lexer.getTokens());
        //
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "Uncaught exception" << std::endl;
    }

    return 0;
}
