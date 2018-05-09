#ifndef AVM_EXCEPTION_H
#define AVM_EXCEPTION_H

#include <cstdint>
#include <cfloat>


enum Reason
{
	DEFAULT_ERROR = 0,
};


class AvmException : public std::exception
{
public:
    AvmException(const Reason &reason, const std::string &details);
    ~AvmException();
    AvmException(const AvmException &copy);
    AvmException &operator=(const AvmException &rvalue);

    const char *what() const noexcept;
private:
    AvmException();
    Reason m_reason;
    std::string m_details;
};







#endif /* AVM_EXCEPTION_H */
