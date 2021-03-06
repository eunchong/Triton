/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the LGPLv3 License.
*/

#ifndef LIGHT_VERSION

#include <algorithm>
#include <sstream>
#include <stdexcept>

#include <CmovnbeIRBuilder.h>
#include <Registers.h>
#include <SMT2Lib.h>
#include <SymbolicExpression.h>


CmovnbeIRBuilder::CmovnbeIRBuilder(__uint address, const std::string &disassembly):
  BaseIRBuilder(address, disassembly){
}


void CmovnbeIRBuilder::regImm(Inst &inst) const {
  TwoOperandsTemplate::stop(this->disas);
}


void CmovnbeIRBuilder::regReg(Inst &inst) const {
  SymbolicExpression *se;
  smt2lib::smtAstAbstractNode *expr, *reg1e, *reg2e, *cf, *zf;
  auto reg1 = this->operands[0].getReg();
  auto reg2 = this->operands[1].getReg();
  auto regSize1 = this->operands[0].getReg().getSize();
  auto regSize2 = this->operands[1].getReg().getSize();

  /* Create the SMT semantic */
  cf = ap.buildSymbolicFlagOperand(ID_TMP_CF);
  zf = ap.buildSymbolicFlagOperand(ID_TMP_ZF);
  reg1e = ap.buildSymbolicRegOperand(reg1, regSize1);
  reg2e = ap.buildSymbolicRegOperand(reg2, regSize2);

  expr = smt2lib::ite(
            smt2lib::equal(
              smt2lib::bvand(
                smt2lib::bvnot(cf),
                smt2lib::bvnot(zf)
              ),
              smt2lib::bvtrue()),
            reg2e,
            reg1e);

  /* Create the symbolic expression */
  se = ap.createRegSE(inst, expr, reg1, regSize1);

  /* Apply the taint via the concretization */
  if (ap.getFlagValue(ID_TMP_CF) == 0 && ap.getFlagValue(ID_TMP_ZF) == 0)
    ap.assignmentSpreadTaintRegReg(se, reg1, reg2);

}


void CmovnbeIRBuilder::regMem(Inst &inst) const {
  SymbolicExpression *se;
  smt2lib::smtAstAbstractNode *expr, *reg1e, *mem1e, *cf, *zf;
  auto memSize = this->operands[1].getMem().getSize();
  auto mem = this->operands[1].getMem();
  auto reg = this->operands[0].getReg();
  auto regSize = this->operands[0].getReg().getSize();

  /* Create the SMT semantic */
  cf = ap.buildSymbolicFlagOperand(ID_TMP_CF);
  zf = ap.buildSymbolicFlagOperand(ID_TMP_ZF);
  reg1e = ap.buildSymbolicRegOperand(reg, regSize);
  mem1e = ap.buildSymbolicMemOperand(mem, memSize);

  expr = smt2lib::ite(
            smt2lib::equal(
              smt2lib::bvand(
                smt2lib::bvnot(cf),
                smt2lib::bvnot(zf)
              ),
              smt2lib::bvtrue()),
            mem1e,
            reg1e);

  /* Create the symbolic expression */
  se = ap.createRegSE(inst, expr, reg, regSize);

  /* Apply the taint via the concretization */
  if (ap.getFlagValue(ID_TMP_CF) == 0 && ap.getFlagValue(ID_TMP_ZF) == 0)
    ap.assignmentSpreadTaintRegMem(se, reg, mem, memSize);

}


void CmovnbeIRBuilder::memImm(Inst &inst) const {
  TwoOperandsTemplate::stop(this->disas);
}


void CmovnbeIRBuilder::memReg(Inst &inst) const {
  TwoOperandsTemplate::stop(this->disas);
}


Inst *CmovnbeIRBuilder::process(void) const {
  checkSetup();

  Inst *inst = new Inst(ap.getThreadID(), this->address, this->disas);

  try {
    this->templateMethod(*inst, this->operands, "CMOVNBE");
    ControlFlow::rip(*inst, this->nextAddress);
    ap.incNumberOfExpressions(inst->numberOfExpressions()); /* Used for statistics */
  }
  catch (std::exception &e) {
    delete inst;
    throw;
  }

  return inst;
}

#endif /* LIGHT_VERSION */

