
#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>

class Lexer {
	public:
		Lexer();
		~Lexer();

		void readTokens(int argv, char **argc);

	private:
		Lexer(const Lexer &rhs);
		Lexer &operator = (const Lexer &rhs);

};

std::ostream & operator << (std::ostream & o, Lexer const & rhs);


#endif /* LEXER_HPP */

