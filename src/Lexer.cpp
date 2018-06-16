#include "Lexer.hpp"
#include "avmException.hpp"
#include <sys/stat.h>
#include <fstream>
#include <regex>



Lexer::Lexer(int argc, char **argv)
: _argc(argc)
//,
//  _fileName(NULL),
//  _readFromFile(false)
//  _lexerFailed(false)
{
//    _tokens.reserve(100);
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

const tTokens& Lexer::getTokens() const
{
    return _tokens;
}

/*****************************************************************************/
/* PRIVATE                                                                   */
/*****************************************************************************/


//const std::regex Lexer::m_unaryRegex("\\s*(pop|dump|add|sub|mul|div|mod|square|sqrt|log|log10|abs|print|exit)\\s*(?:;.*)?");


/*
 * param[in] fin - file input
 */
void Lexer::readFromStream(std::istream& fin)
{
    int lineNbr = 0;
    std::string line;
    bool lexerError = false;

    std::cout << __func__ << ":" << __LINE__ << std::endl;

    std::regex emptyLineRegexp("^\\s*$");
    std::regex operationRegexp("^\\s*(pop|dump|add|sub|mul|div|mod|print|exit)\\s*(?:;.*)?$");
    std::regex commandAndIntRegexp("^\\s*(push|assert)\\s+(int8|int16|int32)\\(([-]?\\d+)\\)\\s*(?:;.*)?$");
    std::regex commandAndFloatingRegexp("^\\s*(push|assert)\\s+(float|double)\\(([-]?\\d+\\.\\d+)\\)\\s*(?:;.*)?$");
    std::regex commentRegexp("^\\s*(?:;.*){1}$");
    std::smatch lineMatch;


    /*
     * Reading from stream line by line.
     * Push valid tokens to vector _tTokens.
     * Throw invalid tokens to _lexerErrors and continue to analyze stream.
     */
    while (std::getline(fin, line)) {
        lineNbr++;
//        std::cout << __func__ << ":" << __LINE__ << std::endl;

        /*
         * Hack!
         * Diferent logic betwean input data by std::cin and fStream.
         * std::cin terminated by ';;'
         * fStream terminated by EOF
         */
        if (!_readFromFile && line == ";;") {
            break ;
        }
        try {
            if (regex_search(line, lineMatch, emptyLineRegexp) || regex_search(line, lineMatch, commentRegexp)) {
                /*skip line*/
                continue ;
//                std::cout << __func__ << ":" << __LINE__ << std::endl;
            } else if (regex_search(line, lineMatch, operationRegexp)) {
//                std::cout << lineMatch[1].str() << std::endl;
                _tokens.push_back({lineMatch[1].str()});
                std::cout << __func__ << ":" << __LINE__ << std::endl;
            } else if (regex_search(line, lineMatch, commandAndIntRegexp) || regex_search(line, lineMatch, commandAndFloatingRegexp)) {
                _tokens.push_back({lineMatch[1].str(), lineMatch[2].str(), lineMatch[3].str()});
//                std::cout << __func__ << ":" << __LINE__ << std::endl;
            } else {
//                std::cout << "error:" << __LINE__ << std::endl;
                std::string what("error in line " + std::to_string(lineNbr) + ":" + "\n\t\'" + line + "\'");
                throw AvmException(LEXER_ERROR, what);
            }
        } catch(std::exception &e) {
            //TODO: add handler exception from std::cin
//            _lexerErrors.push_back(e);
//            std::cout <<_lexerErrors[0].what() << std::endl;
//            std::cout << __LINE__ << ":" << e.what() << std::endl;
            std::cout <<e.what() << std::endl;
            lexerError = true;
        }
    }

//    if (lineNbr == 1)
//        throw AvmException(LEXER_ERROR, "No input provided");
//    }

    if (lexerError) {
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

//    std::cout << __func__ << ":" << __LINE__ << std::endl;
    if (!is_regular_file(_fileName.c_str())) {
        throw AvmException(LEXER_ERROR, "bad file");
    }

    readFromStream(fs);
}



//Lexer::Lexer()
//: _argc(0),
//  _fileName(NULL)
//{}

//Lexer::Lexer(const Lexer &obj)
//: _argc(obj._argc),
//  _fileName(obj._fileName),
//  _readFromFile(obj._readFromFile),
//_lexerFailed(obj._lexerFailed)
//{
//}
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
