/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the LGPLv3 License.
*/

#ifndef LIGHT_VERSION

#ifndef XCHGIRBUILDER_H
#define XCHGIRBUILDER_H

#include "BaseIRBuilder.h"
#include "EflagsBuilder.h"
#include "Inst.h"
#include "TwoOperandsTemplate.h"


class XchgIRBuilder: public BaseIRBuilder, public TwoOperandsTemplate {

  public:
    XchgIRBuilder(__uint address, const std::string &disassembly);

    // From BaseIRBuilder
    virtual Inst *process(void) const;

    // From TwoOperandsTemplate
    virtual void regImm(Inst &inst) const;

    virtual void regReg(Inst &inst) const;

    virtual void regMem(Inst &inst) const;

    virtual void memImm(Inst &inst) const;

    virtual void memReg(Inst &inst) const;
};

#endif // XCHGIRBUILDER_H
#endif // LIGHT_VERSION

