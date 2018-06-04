#include "Lexer.hpp"
#include "avmException.hpp"
Lexer::~Lexer() {}

Lexer::Lexer(int argc, std::string fileName)
try : _argc(argc),
      _fileName(fileName)
{
    switch (_argc) {
    case NO_ARGUMENT:
        readFromStream(std::cin);
        break;

    case ONE_ARGUMENT:
        readFromFile(fileName);
        break;

    case MORE_THEN_ONE:
    default:
        throw AvmException(LEXER_ERROR, "invalid numbers of argument");
	}
} catch (std::exception &e) {
	std::cout << e.what() << std::endl;
}

void Lexer::readFromStream(std::istream&  fin)
{

    int line = 0;

    while ()
    {
        ;
        line++;
    }
}

void Lexer::readFromFile(std::string &fileName)
{
    std::ifstream fs;


    if (!fs.is_open()) {
                    throw AvmException(OPEN_ERROR, "bad file");
                }

}



/*****************************************************************************/
/* PRIVATE                                                                   */
/*****************************************************************************/
//Lexer::Lexer()
//: _argc(0),
//  _fileName(NULL)
//{}

Lexer::Lexer(const Lexer &obj)
: _argc(obj._argc),
  _fileName(obj._fileName)
{
}

Lexer & Lexer::operator=(const Lexer &rvl)
{
	if (this == &rvl) { return *this; }
	/*TODO: add some data for copying*/
	return *this;
}







//std::ostream& operator<<(std::ostream &o, const Lexer& something)
//{
//
//
//	return o;
//}
