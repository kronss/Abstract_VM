#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "IOperand.hpp"
#include <string>

template <class T>
class Operand : public IOperand
{
public:

    Operand(const std::string value, eOperandType type);
    ~Operand();

    template <class Lambda>
    const IOperand* operation(IOperand const& x, IOperand const& y, Lambda func) const;

    const IOperand* operator+(IOperand const& rhs) const;
    const IOperand* operator-(IOperand const& rhs) const;
    const IOperand* operator*(IOperand const& rhs) const;
    const IOperand* operator/(IOperand const& rhs) const;
    const IOperand* operator%(IOperand const& rhs) const;

    const std::string& toString() const;
    int getPrecision() const;
    eOperandType getType() const;

    Operand()                          = delete;
    Operand(const Operand&)            = delete;
    Operand& operator=(const Operand&) = delete;

private:
    const std::string toString(eOperandType type, long double value) const;

    const std::string _strValue;
    const int _precision;
    const eOperandType _type;
};

#include "Operand.tpp"

#endif // OPERAND_HPP
