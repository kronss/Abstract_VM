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
            throw AvmException(LEXER_ERROR, "parsing terminated");

        /*run-time*/
        Vm vm(lexer.getTokens());
        vm.execution();

    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Uncaught exception" << std::endl;
    }

    return 0;
}
