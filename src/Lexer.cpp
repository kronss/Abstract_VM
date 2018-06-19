#include "Lexer.hpp"
#include "AvmException.hpp"
#include <sys/stat.h>
#include <fstream>
#include <regex>

#define DEBUG 0

Lexer::Lexer(int argc, char **argv)
: _argc(argc),
  _lexerFailed(false)
{
    DBG_MSG("born");

    _tokens.reserve(100);
    switch (_argc) {
        case NO_ARGUMENT:
            _readFromFile = false;
            DBG_MSG("read from stdin");
            break;

        case ONE_ARGUMENT:
            _readFromFile = true;
            _fileName = argv[1];
            DBG_MSG("read from file");
            break;

        default:
            DBG_MSG("error");
            throw AvmException(LEXER_ERROR, "invalid numbers of argument");
    }
}

Lexer::~Lexer()
{
    DBG_MSG("died");
}

void Lexer::read()
{
    if (true == _readFromFile) {
        readFromFile();
    } else {
        readFromStdin();
    }
}

/*getter*/
const tTokens& Lexer::getTokens() const
{
    return _tokens;
}

/*getter*/
const bool& Lexer::isFailed() const
{
    return _lexerFailed;
}

/*****************************************************************************/
/* PRIVATE                                                                   */
/*****************************************************************************/

void Lexer::readFromStdin()
{
    bool flag = false;  //TODO: rename
    for (std::string line; std::getline(std::cin, line);) {

        if (line == ";;") {
            flag = true;
            break;
        }

        _buffer << line << '\n';
    }
    if (!flag) {
        //TODO: add throw
        // error
    }

    readFromStream(_buffer);
}

/*
 * function  readFromStream get data line by line
 * param[in] fin - file stream input or std::cin
 */
void Lexer::readFromStream(std::istream& fin)
{
    int lineNbr = 0;
    std::string line;
    std::regex emptyLineRegexp("^\\s*$");
    std::regex operationRegexp("^\\s*(pop|dump|add|sub|mul|div|mod|print|exit)\\s*(?:;.*)?$");
    std::regex commandAndIntRegexp("^\\s*(push|assert)\\s+(int8|int16|int32)\\(([-]?\\d+)\\)\\s*(?:;.*)?$");
    std::regex commandAndFloatingRegexp("^\\s*(push|assert)\\s+(float|double)\\(([-]?\\d+\\.\\d+)\\)\\s*(?:;.*)?$");
    std::regex commentRegexp("^\\s*(?:;.*){1}$");
    std::smatch lineMatch;

    DBG_MSG("Start reading from stream");

    /*
     * Reading from stream line by line.
     * Push valid tokens to vector _tTokens.
     * Throw invalid tokens to _lexerErrors and continue to analyze stream.
     */
    while (std::getline(fin, line)) {
        lineNbr++;

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
                DBG_MSG("emptyLineRegexp || commentRegexp");
                continue ;
            } else if (regex_search(line, lineMatch, operationRegexp)) {

                DBG_MSG(lineMatch[1].str());
                _tokens.push_back({lineMatch[1].str()});
            } else if (regex_search(line, lineMatch, commandAndIntRegexp) || regex_search(line, lineMatch, commandAndFloatingRegexp)) {

                DBG_MSG(lineMatch[1].str());
                _tokens.push_back({lineMatch[1].str(), lineMatch[2].str(), lineMatch[3].str()});
            } else {

                DBG_MSG("ERROR -> throw");
                std::string what("error in line " + std::to_string(lineNbr) + ":" + "\n\t\'" + line + "\'");
                throw AvmException(LEXER_ERROR, what);
            }
        } catch (std::exception &e) {
            //TODO: add handler exception from std::cin
//            _lexerErrors.push_back(e);
//            std::cout <<_lexerErrors[0].what() << std::endl;
//            std::cout << __LINE__ << ":" << e.what() << std::endl;
            std::cerr <<e.what() << std::endl;
            _lexerFailed = true;
        }
    }

    try {
        if (lineNbr < 1) {
            throw AvmException(LEXER_ERROR, "No input provided");
        } else if (_tokens.size() == 0) {
            throw AvmException(LEXER_ERROR, "Have not command");
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        _lexerFailed = true;
    }

    DBG_MSG("Finish reading");
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

    DBG_MSG(_fileName);

    if (!is_regular_file(_fileName.c_str())) {
        throw AvmException(LEXER_ERROR, "bad file");
    }

    readFromStream(fs);
}

//std::ostream& operator<<(std::ostream &o, const Lexer& something)
//{
//
//    return o;
//}
