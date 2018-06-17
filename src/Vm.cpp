#include "AvmException.hpp"
#include "Vm.hpp"


Vm::Vm(const tTokens &tokens)
: _tokens(tokens),
  _VmFailed(false)
{
    DBG_MSG("born");
}

Vm::~Vm()
{
    DBG_MSG("died");
}
