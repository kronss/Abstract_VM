#ifndef IOPERAND_HPP
#define IOPERAND_HPP

#include <string>

enum eOperandType {
    INT8 = 0,
    INT16,
    INT32,
    FLOAT,
    DOUBLE,
};

class IOperand
{
public:

    virtual int getPrecision() const = 0;            // Precision of the type of the instance
    virtual eOperandType getType() const = 0;        // Type of the instance

    virtual const IOperand* operator+(IOperand const& rhs) const = 0; //Sum
    virtual const IOperand* operator-(IOperand const& rhs) const = 0; //Difference
    virtual const IOperand* operator*(IOperand const& rhs) const = 0; //Product
    virtual const IOperand* operator/(IOperand const& rhs) const = 0; //Quotient
    virtual const IOperand* operator%(IOperand const& rhs) const = 0; //Modulo

    virtual const std::string& toString() const = 0; // String representation of the instance

    virtual ~IOperand() {}
};

#endif /*IOPERAND_HPP*/
