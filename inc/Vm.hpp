#ifndef VM_HPP
#define VM_HPP

#include "Lexer.hpp"
//#include "IOperand.hpp"

#include <deque>
#include <map>


class Vm {
    public:
        Vm(const tTokens &tokens);
        ~Vm();

        Vm()                           = delete;
        Vm(const Vm &rhs)              = delete;
        Vm &operator = (const Vm &rhs) = delete;

        void read();

        /*getter*/
        const bool& isFailed() const;
    private:

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
//         void exit();
//        typedef void (Machine::*pfunc)();



        tTokens      _tokens;
        bool         _VmFailed;

};

#endif /*VM_HPP*/

