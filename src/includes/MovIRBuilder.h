/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the LGPLv3 License.
*/

#ifndef LIGHT_VERSION

#ifndef MOVIRBUILDER_H
#define MOVIRBUILDER_H

#include "BaseIRBuilder.h"
#include "Inst.h"
#include "TwoOperandsTemplate.h"


class MovIRBuilder: public BaseIRBuilder, public TwoOperandsTemplate  {
  public:
    MovIRBuilder(__uint address, const std::string &disassembly);

    // From BaseIRBuilder
    virtual Inst *process(void) const;

    // From TwoOperandsTemplate
    virtual void regImm(Inst &inst) const;

    virtual void regReg(Inst &inst) const;

    virtual void regMem(Inst &inst) const;

    virtual void memImm(Inst &inst) const;

    virtual void memReg(Inst &inst) const;
};

#endif // MOVIRBUILDER_H
#endif // LIGHT_VERSION

