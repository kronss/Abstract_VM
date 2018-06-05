
#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <string>


enum {
    NO_ARGUMENT     = 1,
    ONE_ARGUMENT,
    MORE_THEN_ONE,
};



class Lexer {
    public:
        Lexer(int argc, char **argv);
        ~Lexer();

        void readTokens(int argv, char **argc);

    private:
        const int _argc;
        std::string _fileName;


        Lexer(const Lexer &rhs);
        Lexer &operator = (const Lexer &rhs) = delete;
        Lexer() = delete;

        void readFromStream(std::istream&  fin);
        void readFromFile(char *fileName);

};

//std::ostream & operator << (std::ostream & o, Lexer const & rhs);


#endif /*LEXER_HPP*/

