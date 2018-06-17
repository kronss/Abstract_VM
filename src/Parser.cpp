#include "Parser.hpp"
#include "avmException.hpp"

#include <cstdint>
#include <limits>
#include <string>
#include <typeinfo>

#define DEBUG 0


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

    DBG_MSG("======== Parsing ========");

    for (auto& line : _tokens) {

        try {
            if (line[0] == "assert" || line[0] == "push") {
                checkOverlaping(line);
            }
            else {
    //            checkExit(line[0], has_exit);
            }
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    try {
        if (!hasExit) {
//            addError(std::string("ParserException: exit command is missing"));
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }




    if (parserError) {
        throw AvmException(PARSER_ERROR, "parsing terminated");
    }
    DBG_MSG("======== Parsed =========");
}



template<class T> /* int8 int16 int32 */
void Parser::checkInteger(const std::string& value)
{
    DBG_MSG(typeid(T).name());

    int64_t x = std::stoll(value);
    T min = std::numeric_limits<T>::lowest();
    T max = std::numeric_limits<T>::max();

    if (x < min || max < x) {
        std::string what = typeid(T).name();
        what += ": " + value + "is out of boundaries.";

        throw AvmException(PARSER_ERROR, what);
    }
}

template<class T> /* float double */
void Parser::checkFloat(const std::string& value)
{
    long double x = std::stold(value);
    T min = std::numeric_limits<T>::lowest();
    T max = std::numeric_limits<T>::max();

    if (x < min || max < x) {
        std::string what = typeid(T).name();
        what += ": " + value + "is out of boundaries.";

        throw AvmException(PARSER_ERROR, what);
    }
}



void Parser::checkOverlaping(const std::vector<std::string> &line)
{
    if (line[1] == "int8") {
        checkInteger<int8_t>(line[2]);
    }
    else if (line[1] == "int16") {
        checkInteger<int16_t>(line[2]);
    }
    else if (line[1] == "int32") {
        checkInteger<int32_t>(line[2]);
    }
    else if (line[1] == "float") {
        checkFloat<float>(line[2]);
    }
    else if (line[1] == "double") {
        checkFloat<double>(line[2]);
    }
    else {
//        addError(std::string("ParserException: unknown type: ") + line[1]);
    }
}





