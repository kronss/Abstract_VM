#include "Lexer.hpp"
#include "avmException.hpp"
#include <sys/stat.h>
#include <fstream>

Lexer::~Lexer() {}

Lexer::Lexer(int argc, char **argv)
: _argc(argc),
//  _fileName(NULL),
  _readFromFile(false)
{
    switch (_argc) {
    case NO_ARGUMENT:
        readFromStream(std::cin);
        break;

    case ONE_ARGUMENT:
        readFromFile(argv[1]);
        break;

    default:
        throw AvmException(LEXER_ERROR, "invalid numbers of argument");
    }
}


void Lexer::readFromStream(std::istream& fin)
{
    int lineNbr = 1;
    std::string line;
    bool isErr = false;

    std::cout << fin << std::endl;

    while (std::getline(fin, line)) {
//        if (line == ";;") break ;

//        validateLineAndPush(line, lineNbr);
//        checkLine();

        std::cout << lineNbr << " " << line << std::endl;//
        lineNbr++;
    }
    if (isErr) {
        throw AvmException(LEXER_ERROR, "No input provided");
    }

    if (lineNbr == 1) {
        throw AvmException(LEXER_ERROR, "parsing terminated");
    }
}

static inline int is_regular_file(const char *fileName)
{
    struct stat fileStat;
    stat(fileName, &fileStat);
    return S_ISREG(fileStat.st_mode);
}

void Lexer::readFromFile(char *fileName)
{
    std::fstream fs(fileName);
    _readFromFile = true;

    if (!is_regular_file(fileName)) {
        throw AvmException(LEXER_ERROR, "bad file");
    }

    readFromStream(fs);
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
  _fileName(obj._fileName),
  _readFromFile(obj._readFromFile)
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
