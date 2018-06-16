
#ifndef PARSER_HPP
#define PARSER_HPP

#include<Lexer.hpp>

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


    private:
        tTokens      _tokens;

        void checkLine(const std::vector<std::string> &line);
};

//std::ostream & operator << (std::ostream & o, Lexer const & rhs);


#endif /*PARSER_HPP*/
