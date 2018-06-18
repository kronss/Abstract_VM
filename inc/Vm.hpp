#ifndef VM_HPP
#define VM_HPP

#include "IOperand.hpp"
#include "Lexer.hpp"

#include <deque>
#include <map>


//typedef void (*pfunc)();


class Vm {
    public:
        Vm(const tTokens &tokens);
        ~Vm();

        Vm()                           = delete;
        Vm(const Vm &rhs)              = delete;
        Vm &operator = (const Vm &rhs) = delete;

        void execution();

        /*getter*/
        const bool& isFailed() const;
    private:
        tTokens      _tokens;
        bool         _VmFailed;

        std::deque<const IOperand*> _deque;
        std::map<std::string, eOperandType> _typesMap;
        std::map<std::string, void (Vm::*)()> _opMap;


        void push(const std::string& type, const std::string& value);
        void pop();
        void dump();
        void assert(const std::string& type, const std::string& value);
        void add();
        void sub();
        void mul();
        void div();
        void mod();
        void print();
        void exit();





};

#endif /*VM_HPP*/

