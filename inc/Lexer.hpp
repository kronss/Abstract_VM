#ifndef LEXER_HPP
#define LEXER_HPP

#define DBG_MSG(x) do { \
  if (DEBUG) { std::cerr << __func__ << ":" << __LINE__ << ":" << (x) << std::endl; } \
} while (0)


#include <iostream>
#include <string>
#include <vector>

typedef std::vector<std::vector<std::string>> tTokens;

enum {
    NO_ARGUMENT     = 1,
    ONE_ARGUMENT,
};


class Lexer {
    public:
        Lexer(int argc, char **argv);
        ~Lexer();

        Lexer()                              = delete;
        Lexer(const Lexer &rhs)              = delete;
        Lexer &operator = (const Lexer &rhs) = delete;

        void read();

        /*getter*/
        const tTokens& getTokens() const;
        const bool& isFailed() const;
    private:
        const int    _argc;
        std::string  _fileName;
        bool         _readFromFile;
        tTokens      _tokens;
        bool         _lexerFailed;

        void readFromStream(std::istream& fin);
        void readFromFile();
};

//std::ostream & operator << (std::ostream & o, Lexer const & rhs);

#endif /*LEXER_HPP*/
