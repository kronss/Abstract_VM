#include <iostream>
#include "../inc/AvmException.hpp"

AvmException::~AvmException()
{}
AvmException::AvmException(const AvmException &cpy)
: _reason(cpy._reason),
  _details(cpy._details)
{}

AvmException::AvmException(const Reason &reason, const std::string &details)
: _reason(reason),
  _details(details)
{}

const char *AvmException::what() const noexcept
{
    std::string what;

    switch(_reason)
    {
    case Reason::LEXER_ERROR:     what = "\e[0;31m Lexer error: \e[0m"   ; break;
    case Reason::PARSER_ERROR:    what = "\e[0;35m Parser error: \e[0m"  ; break;
    case Reason::VM_ERROR:        what = "\e[1;31m Vm error: \e[0m"      ; break;
    case Reason::OPEN_ERROR:      what = "Open error: \e[0m"             ; break;
    case Reason::FATAL_ERROR:     what = "\e[0;31m Fatal error: \e[0m"   ; break;

    case Reason::UNKNOWN_ERROR:
    default:
        what = "Unknown error:";
    }

    what += _details;

    return what.c_str();
}

/*****************************************************************************/
/* PRIVATE                                                                   */
/*****************************************************************************/

//AvmException::AvmException()
//: _reason(UNKNOWN_ERROR),
//  _details(NULL)
//{}
//
//AvmException &AvmException::operator=(const AvmException &rvl)
//{
//    if (this == &rvl) { return *this; }
////    _reason = rvl._reason;
////    _what = rvl._what;
//    return *this;
//}
