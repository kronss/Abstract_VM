#include "AvmException.hpp"
#include "Parser.hpp"
#include <cstdint>
#include <limits>
#include <string>
#include <typeinfo>

#define DEBUG 0

Parser::Parser(const tTokens &tokens)
: _tokens(tokens),
  _parserFailed(false),
  _hasExit(false)
{
    DBG_MSG("born");
}

Parser::~Parser()
{
    DBG_MSG("died");
}

void Parser::read()
{
    bool parserError = false;

    DBG_MSG("Parsing start");

    for (auto& line : _tokens) {

        try {
            if (line[0] == "assert" || line[0] == "push") {
                checkOverlaping(line);
            } else {
                checkExit(line[0]);
            }

        } catch (std::exception &e) {
            _parserFailed = true;
            std::cerr << e.what() << std::endl;
        }
    }

    try {
        if (!_hasExit) {
            throw AvmException(PARSER_ERROR, "exit command is missing");
        }
    } catch (std::exception &e) {

        _parserFailed = true;
        std::cerr << e.what() << std::endl;
    }

    if (parserError) {
        throw AvmException(PARSER_ERROR, "parsing terminated");
    }
    DBG_MSG("Parsing done");
}


/*getter*/
const bool& Parser::isFailed() const
{
    return _parserFailed;
}

/*****************************************************************************/
/* PRIVATE                                                                   */
/*****************************************************************************/

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
        throw AvmException(PARSER_ERROR, "unknown type:" + line[1]);
    }
}

template<class T> /* int8 int16 int32 */
void Parser::checkInteger(const std::string& value)
{
    DBG_MSG(typeid(T).name());
    DBG_MSG("-_-");
    try {
        int64_t x = std::stoll(value);
        T min = std::numeric_limits<T>::lowest();
        T max = std::numeric_limits<T>::max();

        DBG_MSG("-_-");
        if (x < min || max < x) {
//            std::string what = typeid(T).name();
    //        what += ": " + value + "is out of boundaries.";
            throw AvmException(PARSER_ERROR, "out of limits");
        }
    } catch ( std::exception &e ) {
        std::cerr <<e.what() << std::endl;
        _parserFailed = true;
    }

}

template<class T> /* float double */
void Parser::checkFloat(const std::string& value)
{
    DBG_MSG(typeid(T).name());
    DBG_MSG("-_-");
    try {
        long double x = std::stold(value);
        T min = std::numeric_limits<T>::lowest();
        T max = std::numeric_limits<T>::max();


        //TODO:NOTE
        if (x < min || max < x) {
//            std::string what = typeid(T).name();
//            what += ": " + value + "is out of boundaries.";
            throw AvmException(PARSER_ERROR, "out of limits");
    }
    }catch ( std::exception &e ) {
            std::cerr <<e.what() << std::endl;
            _parserFailed = true;
        }

}

void Parser::checkExit(const std::string &operation)
{
    DBG_MSG(_hasExit);

    if (operation == "exit") {

        if (!_hasExit) {
            _hasExit = true;
        } else {

            throw AvmException(PARSER_ERROR, "more than one exit");
        }
    }

    DBG_MSG("Exit");
}
