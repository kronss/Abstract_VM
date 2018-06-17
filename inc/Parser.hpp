#ifndef PARSER_HPP
#define PARSER_HPP

#include "Lexer.hpp"

#include <iostream>
#include <string>

class Parser {
    public:
        Parser(const tTokens &tokens);
        ~Parser();

        Parser()                               = delete;
        Parser(const Parser &rhs)              = delete;
        Parser &operator = (const Parser &rhs) = delete;

        void read();

        /*getter*/
        const bool& isFailed() const;
    private:
        tTokens      _tokens;
        bool         _parserFailed;
        bool         _hasExit;


        void checkOverlaping(const std::vector<std::string> &line);

        template<class T> /* float double */
        void checkFloat(const std::string& value);

        template<class T> /* int8 int16 int32 */
        void checkInteger(const std::string& value);

        void checkExit(const std::string &operation);
};

//std::ostream & operator << (std::ostream & o, Lexer const & rhs);

#endif /*PARSER_HPP*/
