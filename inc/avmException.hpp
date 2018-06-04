#ifndef AVM_EXCEPTION_HPP
#define AVM_EXCEPTION_HPP

#include <string>
#include <exception>

enum Reason
{
	LEXER_ERROR,
	PARSER_ERROR,
	OPEN_ERROR,

	UNKNOWN_ERROR,
};


class AvmException : public std::exception {
public:
    AvmException(const Reason &reason, const std::string &details);
    ~AvmException();
    AvmException(const AvmException &cpy);

    const char *what() const noexcept;
private:
    const Reason _reason;
    const std::string _details;

    AvmException();
    AvmException &operator=(const AvmException &rvl);
};

#endif /*AVM_EXCEPTION_HPP*/
