
#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <string>


enum {
    NO_ARGUMENT     = 1,
    ONE_ARGUMENT,
};



class Lexer {
    public:
        Lexer(int argc, char **argv);
        ~Lexer();

        void read();

    private:
        const int   _argc;
        std::string _fileName;
        bool        _readFromFile;




        Lexer(const Lexer &rhs);
        Lexer &operator = (const Lexer &rhs) = delete;
        Lexer() = delete;

        void readFromStream(std::istream& fin);
        void readFromFile();

};

//std::ostream & operator << (std::ostream & o, Lexer const & rhs);


#endif /*LEXER_HPP*/

