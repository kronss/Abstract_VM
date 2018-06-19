#include "AvmException.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Vm.hpp"

#define DEBUG 0

int main(const int argc, char **argv)
{
    try {
        Lexer lexer(argc, argv);
        lexer.read();

        Parser parser(lexer.getTokens());
        parser.read();

        if (lexer.isFailed() || parser.isFailed())
            throw AvmException(FATAL_ERROR, "parsing terminated");

        /*run-time*/
        Vm vm(lexer.getTokens());
        vm.execution();

    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Uncaught exception" << std::endl;
    }


//    system("leaks --queit avm");


    return 0;
}
