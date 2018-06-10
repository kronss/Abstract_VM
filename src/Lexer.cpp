#include "Lexer.hpp"
#include "avmException.hpp"
#include <sys/stat.h>
#include <fstream>
#include <regex>
//#include <boost/regex.hpp>



Lexer::Lexer(int argc, char **argv)
: _argc(argc)
//  _fileName(NULL),
//  _readFromFile(false)
{
    switch (_argc) {
    case NO_ARGUMENT:
        _readFromFile = false;
//        readFromStream(std::cin);
        break;

    case ONE_ARGUMENT:
        _readFromFile = true;
        _fileName = argv[1];
//        readFromFile(argv[1]);
        break;

    default:
        throw AvmException(LEXER_ERROR, "invalid numbers of argument");
    }
}

Lexer::~Lexer() {}

void Lexer::read()
{
    if (true == _readFromFile) {
        readFromFile();
    } else {
        readFromStream(std::cin);
    }
}

/*****************************************************************************/
/* PRIVATE                                                                   */
/*****************************************************************************/


//const std::regex Lexer::m_unaryRegex("\\s*(pop|dump|add|sub|mul|div|mod|square|sqrt|log|log10|abs|print|exit)\\s*(?:;.*)?");



void Lexer::readFromStream(std::istream& fin)
{
    int lineNbr = 1;
    std::string line;
    bool isErr = false;

    std::cout << __func__ << ":" << __LINE__ << std::endl;
//    std::regex empty_line("^\\s*$");

    std::regex emptyLine("^\\s*$");

//    std::regex operation("^\\s*(pop|dump|add|sub|mul|div|mod|print|exit)\\s*(?:;.*)?$");

    std::smatch line_match;

    while (std::getline(fin, line)) {


        std::cout << "empty line\n";
        if (regex_search(line, line_match, emptyLine)) {
            std::cout << "empty line\n";
        }






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

static inline bool is_regular_file(const char *fileName)
{
    struct stat fileStat;
    stat(fileName, &fileStat);
    return !!S_ISREG(fileStat.st_mode);
}

void Lexer::readFromFile()
{
    std::fstream fs(_fileName);
    _readFromFile = true;

    if (!is_regular_file(_fileName.c_str())) {
        throw AvmException(LEXER_ERROR, "bad file");
    }

    readFromStream(fs);
}



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
