#include "Parser.hpp"
#include "avmException.hpp"
//#include <fstream>
//#include <regex>

Parser::Parser(const tTokens &tokens)
: _tokens(tokens)
{}

Parser::~Parser()
{}



void Parser::read()
{
    bool hasExit = false;
    bool parserError = false;

    DEBUG_MESSAGE("======== Parsing ========");

    for (auto& line : _tokens) {

        try {
            if (line[0] == "assert" || line[0] == "push") {
                checkLine(line);
            }
            else {
    //            checkExit(line[0], has_exit);
            }
        } catch (...) {

        }
    }

    try {
        if (!hasExit) {
//            addError(std::string("ParserException: exit command is missing"));
        }
    } catch ( ... ) {

    }




    if (parserError) {
        throw AvmException(PARSER_ERROR, "parsing terminated");
    }
    DEBUG_MESSAGE("======== Parsed =========");
}











