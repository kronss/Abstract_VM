#include "Lexer.hpp"
#include "avmException.hpp"
#include <fstream>

Lexer::~Lexer() {}

Lexer::Lexer(int argc, char **argv)
: _argc(argc)
{
    switch (_argc) {
    case NO_ARGUMENT:
        readFromStream(std::cin);
        break;

    case ONE_ARGUMENT:
        readFromFile(argv[1]);
        break;

    case MORE_THEN_ONE:
    default:
        throw AvmException(LEXER_ERROR, "invalid numbers of argument");
    }
}


void Lexer::readFromStream(std::istream&  in)
{
//    int line = 0;
    (void)in;


//    while (fin.get)
//    {
//        ;
//        line++;
//    }
}

void Lexer::readFromFile(char *fileName)
{
    std::ifstream fs(fileName);

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
//
//Lexer & Lexer::operator=(const Lexer &rvl)
//{
//    if (this == &rvl) { return *this; }
//    /*TODO: add some data for copying*/
//    return *this;
//}







//std::ostream& operator<<(std::ostream &o, const Lexer& something)
//{
//
//
//    return o;
//}
