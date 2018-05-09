
#include "Lexer.hpp"

Lexer::Lexer() {}
Lexer::~Lexer() {}

Lexer::Lexer(const Lexer &obj)
{
	*this = obj;
}

Lexer & Lexer::operator=(const Lexer &rvl)
{
	if (this == &rvl) { return *this; }
	/*TODO: add some data for copying*/
	return *this;
}











std::ostream& operator<<(std::ostream &o, const Lexer& something)
{

	return o;
}
