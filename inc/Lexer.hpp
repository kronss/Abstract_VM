
#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <string>


enum {
	NO_ARGUMENT     = 0,
	ONE_ARGUMENT    = 1,
	MORE_THEN_ONE   = 2,
};



class Lexer {
	public:
		Lexer (int argc, std::string fileName);
		~Lexer();

		void readTokens(int argv, char **argc);

	private:
		const int _argc;
		const std::string _fileName;


		Lexer(const Lexer &rhs);
		Lexer &operator = (const Lexer &rhs);
		Lexer();

		void readFromStdInput();
		void readFromFile();

};

//std::ostream & operator << (std::ostream & o, Lexer const & rhs);


#endif /* LEXER_HPP */

