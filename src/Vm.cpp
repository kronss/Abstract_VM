#include "AvmException.hpp"
#include "Vm.hpp"

#include <iostream>

#include "OperandFactory.hpp"
#include "Operand.hpp"


#define DEBUG 1

Vm::Vm(const tTokens &tokens)
: _tokens(tokens)
 ,_VmFailed(false)
 ,_typesMap {
        {  "int8", INT8  },
        { "int16", INT16 },
        { "int32", INT32 },
        { "float", FLOAT },
        {"double", DOUBLE}
    }
 ,_opMap {
        {  "pop", &Vm::pop  },
        { "dump", &Vm::dump },
        {  "add", &Vm::add  },
        {  "sub", &Vm::sub  },
        {  "mul", &Vm::mul  },
        {  "div", &Vm::div  },
        {  "mod", &Vm::mod  },
        {"print", &Vm::print}
    }
{
    DBG_MSG("born");
}

Vm::~Vm()
{
    DBG_MSG("died");

    for (auto& ptr : _deque) {
        if (ptr) {
            delete ptr;
            ptr = NULL;
        }
    }
}

void Vm::execution()
{
    for (auto& line : _tokens) {
        if (line[0] == "push") {
            push(line[1], line[2]);
        }
        else if (line[0] == "assert") {
            assert(line[1], line[2]);
        }
        else if (line[0] == "exit"){
            // do nothing()
        }
        else {
            (this->*_opMap[line[0]])();
        }
    }
}


void Vm::push(const std::string& type, const std::string& value)
{
    DBG_MSG(type); DBG_MSG(value);
    eOperandType etype = _typesMap[type];
    _deque.push_back(OperandFactory::getInstance().makeOperand(etype, value));
}

void Vm::pop()
{
//    std::cout << "pop\n";
    if (_deque.size() == 0) {
        throw (AvmException(VM_ERROR, "pop on empty stack"));
    }
    auto a = *(_deque.end() - 1);
    _deque.pop_back();
    delete a;
}

void Vm::dump()
{
    DBG_MSG("dump");
    for (auto it = _deque.rbegin(); it != _deque.rend(); ++it) {
        std::cout << (*it)->toString() << "\n";
    }
}

void Vm::assert(const std::string& type, const std::string& value)
{
//    std::cout << "assert " << type << " " << value << "\n";
    if (_deque.size() == 0) {
        throw (AvmException(VM_ERROR, "assert on empty stack"));
    }
    auto a = *(_deque.end() - 1);
    auto b = OperandFactory::getInstance().makeOperand(_typesMap[type], value);
    if (a->getType() != b->getType() || a->toString() != b->toString()) {
        delete b;
        throw (AvmException(VM_ERROR, "assert failed"));
    }
    delete b;
}

void Vm::add()
{
//    std::cout << "add\n";
    if (_deque.size() < 2) {
        throw (AvmException(VM_ERROR, "add on less than 2 operands"));
    }
    auto b = *(_deque.end() - 1);
    auto a = *(_deque.end() - 2);
    auto res = *a + *b;
    _deque.pop_back();
    _deque.pop_back();
    delete a;
    delete b;
    _deque.push_back(res);
}

void Vm::sub()
{
//    std::cout << "sub\n";
    if (_deque.size() < 2) {
        throw (AvmException(VM_ERROR, "sub on less than 2 operands"));
    }
    auto b = *(_deque.end() - 1);
    auto a = *(_deque.end() - 2);
    auto res = *a - *b;
    _deque.pop_back();
    _deque.pop_back();
    delete a;
    delete b;
    _deque.push_back(res);
}

void Vm::mul()
{
//    std::cout << "mul\n";
    if (_deque.size() < 2) {
        throw (AvmException(VM_ERROR, "mul on less than 2 operands"));
    }
    auto b = *(_deque.end() - 1);
    auto a = *(_deque.end() - 2);
    auto res = *a * *b;
    _deque.pop_back();
    _deque.pop_back();
    delete a;
    delete b;
    _deque.push_back(res);
}

void Vm::div()
{
//    std::cout << "div\n";
    if (_deque.size() < 2) {
        throw (AvmException(VM_ERROR, "div on less than 2 operands"));
    }
    auto b = *(_deque.end() - 1);
    auto a = *(_deque.end() - 2);
    auto res = *a / *b;
    _deque.pop_back();
    _deque.pop_back();
    delete a;
    delete b;
    _deque.push_back(res);
}

void Vm::mod()
{
//    std::cout << "mod\n";
    if (_deque.size() < 2) {
        throw (AvmException(VM_ERROR, "mod on less than 2 operands"));
    }
    auto b = *(_deque.end() - 1);
    auto a = *(_deque.end() - 2);
    auto res = *a % *b;
    _deque.pop_back();
    _deque.pop_back();
    delete a;
    delete b;
    _deque.push_back(res);
}

void Vm::print()
{
//    std::cout << "print\n";
    if (_deque.size() == 0) {
        throw (AvmException(VM_ERROR, "print on empty stack"));
    }
    auto a = *(_deque.end() - 1);
    if (a->getPrecision() != INT8) {
        throw (AvmException(VM_ERROR, "print on non Int8 value"));
    }
    char c = static_cast<char>(std::stoi(a->toString().c_str()));
    if (32 <= c && c <= 126) {
        std::cout << c << std::endl;
    }
//    std::cout << "print:" << c << std::endl;
}
