#include "avmException.hpp"
#include <iostream>

AvmException::AvmException()
: _reason(UNKNOWN_ERROR),
  _details(NULL)
{
	std::cout << "EXC born" << std::endl;
}
AvmException::~AvmException()
{
	std::cout << "EXC die" << std::endl;
}
AvmException::AvmException(const AvmException &cpy)
: _reason(cpy._reason)
{

//	*this = cpy;
}

AvmException &AvmException::operator=(const AvmException &rvl)
{
	if (this == &rvl) { return *this; }
//
//    _reason = rvl._reason;
//    _what = rvl._what;
    return *this;
}

AvmException::AvmException(const Reason &reason, const std::string &details)
: _reason(reason),
  _details(details)
{

}

const char *AvmException::what() const noexcept
{
    std::string what;
//    auto log = [&](const std::string &text){ what += text; };








    switch(_reason)
    {
    case Reason::LEXER_ERROR:     what = "Lexer error: ";       break;


    case Reason::UNKNOWN_ERROR:
    default:
    	;
//        case Reason::LEXER_ERROR:           log("Lexer error: "); break;
//        case Reason::INPUT_ERROR:           log("Input error: "); break;
//        case Reason::OVERFLOW_INT8_ERROR:   log("Int8 overflow error: "); break;
//        case Reason::UNDERFLOW_INT8_ERROR:  log("Int8 underflow error: "); break;
//        case Reason::OVERFLOW_INT16_ERROR:  log("Int16 overflow error: "); break;
//        case Reason::UNDERFLOW_INT16_ERROR: log("Int16 underflow error: "); break;
//        case Reason::OVERFLOW_INT32_ERROR:  log("Int32 overflow error: "); break;
//        case Reason::UNDERFLOW_INT32_ERROR: log("Int32 underflow error: "); break;
//        case Reason::OVERFLOW_FLT_ERROR:    log("Float overflow error: "); break;
//        case Reason::UNDERFLOW_FLT_ERROR:   log("Float underflow error: "); break;
//        case Reason::OVERFLOW_DBL_ERROR:    log("Double overflow error: "); break;
//        case Reason::UNDERFLOW_DBL_ERROR:   log("Double underflow error: "); break;
//        case Reason::UNKNOWN_OPERAND:       log("Operand template error: "); break;
//        case Reason::DIVISION_BY_ZERO:      log("Division by zero error: "); break;
//        case Reason::MODULO_BY_ZERO:        log("Modulo by zero error: "); break;
//        case Reason::POP_OF_EMPTY_STACK:    log("Pop of empty stack error: "); break;
//        case Reason::ASSERTION_FAILLURE:    log("Assertion faillure: "); break;
//        case Reason::EXIT_MISSING:          log("Execution terminate error: "); break;
//        case Reason::NO_ARGS_FOR_BIN_EXPR:  log("Binary expression error: "); break;
//        case Reason::EMPTY_STACK:           log("Requested op execution on empty stack error: "); break;
//        case Reason::PRINT_OF_NOT_CHAR:     log("Print of not int8 type error: "); break;
//        default: log("Unknown error: ");
    }

//    what += _details;

//    switch(m_reason)
//    {
//        case Reason::OVERFLOW_INT8_ERROR:   log("\nNote: Upper-bound of int8 is: " + std::to_string(INT8_MAX)); break;
//        case Reason::UNDERFLOW_INT8_ERROR:  log("\nNote: Lower-bound of int8 is: " + std::to_string(INT8_MIN)); break;
//        case Reason::OVERFLOW_INT16_ERROR:  log("\nNote: Upper-bound of int16: " + std::to_string(INT16_MAX)); break;
//        case Reason::UNDERFLOW_INT16_ERROR: log("\nNote: Lower-bound of int16: " + std::to_string(INT16_MIN)); break;
//        case Reason::OVERFLOW_INT32_ERROR:  log("\nNote: Upper-bound of int32: " + std::to_string(INT32_MAX)); break;
//        case Reason::UNDERFLOW_INT32_ERROR: log("\nNote: Lower-bound of int32: " + std::to_string(INT32_MIN)); break;
//        case Reason::OVERFLOW_FLT_ERROR:    log("\nNote: Upper-bound of float: " + std::to_string(FLT_MAX)); break;
//        case Reason::UNDERFLOW_FLT_ERROR:   log("\nNote: Lower-bound of float: " + std::to_string(-FLT_MAX)); break;
//        case Reason::OVERFLOW_DBL_ERROR:    log("\nNote: Upper-bound of double: " + std::to_string(DBL_MAX)); break;
//        case Reason::UNDERFLOW_DBL_ERROR:   log("\nNote: Lower-bound of double: " + std::to_string(-DBL_MAX)); break;
//        case Reason::NO_ARGS_FOR_BIN_EXPR:  log("\nNote: stack size should be equal or greater than 2"); break;
//        default: {}
//    }
    return what.c_str();
}
