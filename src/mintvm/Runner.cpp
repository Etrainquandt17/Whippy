#include "mintvm/Runner.h"

// The order decides the order of the assertion strings in .data.
#include "mintvm/VMConstantTable.h"
#include "mintvm/VMSymbolTable.h"
#include "mintvm/VMFunction.h"
#include "mintvm/BCOpCode.h"
#include "mintvm/MintFuncProxy.h"
#include "mintvm/VMCore.h"
#include "mintvm/VMModule.h"

namespace mintvm {

Runner::Runner(const VMCore& core, unsigned long stackSize, IAllocator* allocator)
    : mCore(core)
    , mModules(allocator ? *allocator : RNObject::allocator(), stackSize)
    , mModuleCount(0)
    , mRegset(stackSize, allocator) {}

void Runner::setEntryPoint(const char* name) {
    const VMModule* module;
    const VMFunction* function = mCore.findFunction(name, &module);
    MINT_ASSERT("Runner.cpp", 45, function);
    MINT_ASSERT("Runner.cpp", 48, function->isMint());
    mModuleCount = 0;
    pushModule(module);
    mRegset.init(function->instruction());
}

void Runner::reset() {
    mModuleCount = 0;
    mRegset.init();
}

inline unsigned long Runner::constant(unsigned short offset) const {
    const VMModule* module = currentModule();
    return *static_cast<const unsigned long*>(module->constantTable().get(offset));
}

inline const void* Runner::constantAddress(unsigned short offset) const {
    const VMModule* module = currentModule();
    return module->constantTable().get(offset);
}

void Runner::execute() {
    if (mRegset.isYieldContinue()) {
        mRegset.decYieldCount();
    }
    while (mRegset.pc()) {
        if (mRegset.isYieldContinue()) {
            return;
        }
        BCOpCode op(mRegset.pc());
        switch (op.getOpType()) {
        case BCOpCode::LDSRZR:
            mRegset.LDSRZR(op.getSR1());
            mRegset.next();
            break;
        case BCOpCode::LDSRBT:
            mRegset.LDSRBT(op.getSR1());
            mRegset.next();
            break;
        case BCOpCode::LDSRC4: {
            unsigned char a;
            unsigned short index;
            op.getSR1_CTI(a, index);
            mRegset.LDSRC4(a, constant(index));
            mRegset.next();
            break;
        }
        case BCOpCode::LDSRCA: {
            unsigned char a;
            unsigned short index;
            op.getSR1_CTI(a, index);
            mRegset.LDSRC4(a, reinterpret_cast<unsigned long>(constantAddress(index)));
            mRegset.next();
            break;
        }
        case BCOpCode::LDSRSR: {
            unsigned char a;
            unsigned char b;
            op.getSR1_SR2(a, b);
            mRegset.LDSRSR(a, b);
            mRegset.next();
            break;
        }
        case BCOpCode::LDSRFZ:
            mRegset.LDSRFZ(op.getSR1());
            mRegset.next();
            break;
        case BCOpCode::LDFRSR: {
            unsigned char a;
            unsigned char b;
            op.getFR1_SR1(a, b);
            mRegset.LDFRSR(a, b);
            mRegset.next();
            break;
        }
        case BCOpCode::LDSRSA: {
            unsigned char a;
            unsigned short index;
            op.getSR1_STI(a, index);
            MINT_ASSERT("Runner.cpp", 159, false);
            mRegset.next();
            break;
        }
        case BCOpCode::LDSRSV: {
            unsigned char a;
            unsigned short index;
            op.getSR1_STI(a, index);
            mRegset.LDSRSV(a, mCore.findVariable(currentModule()->symbolTable().symbol(index)));
            mRegset.next();
            break;
        }
        case BCOpCode::LDSRA4: {
            unsigned char a;
            unsigned char b;
            op.getSR1_SR2(a, b);
            mRegset.LDSRA4(a, b);
            mRegset.next();
            break;
        }
        case BCOpCode::LDSRSZ: {
            unsigned char a;
            unsigned short index;
            op.getSR1_STI(a, index);
            mRegset.LDSRSZ(a, mCore.sizeOf(currentModule()->symbolTable().symbol(index)));
            mRegset.next();
            break;
        }
        case BCOpCode::STSRSR: {
            unsigned char a;
            unsigned char b;
            op.getSR1_SR2(a, b);
            mRegset.STSRSR(a, b);
            mRegset.next();
            break;
        }
        case BCOpCode::STSVSR: {
            unsigned char a;
            unsigned short index;
            op.getSR1_STI(a, index);
            mRegset.STSVSR(a, mCore.findVariable(currentModule()->symbolTable().symbol(index)));
            mRegset.next();
            break;
        }
        case BCOpCode::ADDI32: {
            unsigned char a;
            unsigned char b;
            unsigned char c;
            op.getSR1_SR2_SR3(a, b, c);
            mRegset.ADDI32(a, b, c);
            mRegset.next();
            break;
        }
        case BCOpCode::SUBI32: {
            unsigned char a;
            unsigned char b;
            unsigned char c;
            op.getSR1_SR2_SR3(a, b, c);
            mRegset.SUBI32(a, b, c);
            mRegset.next();
            break;
        }
        case BCOpCode::MULS32: {
            unsigned char a;
            unsigned char b;
            unsigned char c;
            op.getSR1_SR2_SR3(a, b, c);
            mRegset.MULS32(a, b, c);
            mRegset.next();
            break;
        }
        case BCOpCode::DIVS32: {
            unsigned char a;
            unsigned char b;
            unsigned char c;
            op.getSR1_SR2_SR3(a, b, c);
            mRegset.DIVS32(a, b, c);
            mRegset.next();
            break;
        }
        case BCOpCode::MODS32: {
            unsigned char a;
            unsigned char b;
            unsigned char c;
            op.getSR1_SR2_SR3(a, b, c);
            mRegset.MODS32(a, b, c);
            mRegset.next();
            break;
        }
        case BCOpCode::INCI32:
            mRegset.INCI32(op.getSR1());
            mRegset.next();
            break;
        case BCOpCode::DECI32:
            mRegset.DECI32(op.getSR1());
            mRegset.next();
            break;
        case BCOpCode::NEGS32: {
            unsigned char a;
            unsigned char b;
            op.getSR1_SR2(a, b);
            mRegset.NEGS32(a, b);
            mRegset.next();
            break;
        }
        case BCOpCode::ADDF32: {
            unsigned char a;
            unsigned char b;
            unsigned char c;
            op.getSR1_SR2_SR3(a, b, c);
            mRegset.ADDF32(a, b, c);
            mRegset.next();
            break;
        }
        case BCOpCode::SUBF32: {
            unsigned char a;
            unsigned char b;
            unsigned char c;
            op.getSR1_SR2_SR3(a, b, c);
            mRegset.SUBF32(a, b, c);
            mRegset.next();
            break;
        }
        case BCOpCode::MULF32: {
            unsigned char a;
            unsigned char b;
            unsigned char c;
            op.getSR1_SR2_SR3(a, b, c);
            mRegset.MULF32(a, b, c);
            mRegset.next();
            break;
        }
        case BCOpCode::DIVF32: {
            unsigned char a;
            unsigned char b;
            unsigned char c;
            op.getSR1_SR2_SR3(a, b, c);
            mRegset.DIVF32(a, b, c);
            mRegset.next();
            break;
        }
        case BCOpCode::INCF32:
            mRegset.INCF32(op.getSR1());
            mRegset.next();
            break;
        case BCOpCode::DECF32:
            mRegset.DECF32(op.getSR1());
            mRegset.next();
            break;
        case BCOpCode::NEGF32: {
            unsigned char a;
            unsigned char b;
            op.getSR1_SR2(a, b);
            mRegset.NEGF32(a, b);
            mRegset.next();
            break;
        }
        case BCOpCode::LTS32: {
            unsigned char a;
            unsigned char b;
            unsigned char c;
            op.getSR1_SR2_SR3(a, b, c);
            mRegset.LTS32(a, b, c);
            mRegset.next();
            break;
        }
        case BCOpCode::LES32: {
            unsigned char a;
            unsigned char b;
            unsigned char c;
            op.getSR1_SR2_SR3(a, b, c);
            mRegset.LES32(a, b, c);
            mRegset.next();
            break;
        }
        case BCOpCode::EQI32: {
            unsigned char a;
            unsigned char b;
            unsigned char c;
            op.getSR1_SR2_SR3(a, b, c);
            mRegset.EQI32(a, b, c);
            mRegset.next();
            break;
        }
        case BCOpCode::NEI32: {
            unsigned char a;
            unsigned char b;
            unsigned char c;
            op.getSR1_SR2_SR3(a, b, c);
            mRegset.NEI32(a, b, c);
            mRegset.next();
            break;
        }
        case BCOpCode::LTF32: {
            unsigned char a;
            unsigned char b;
            unsigned char c;
            op.getSR1_SR2_SR3(a, b, c);
            mRegset.LTF32(a, b, c);
            mRegset.next();
            break;
        }
        case BCOpCode::LEF32: {
            unsigned char a;
            unsigned char b;
            unsigned char c;
            op.getSR1_SR2_SR3(a, b, c);
            mRegset.LEF32(a, b, c);
            mRegset.next();
            break;
        }
        case BCOpCode::EQF32: {
            unsigned char a;
            unsigned char b;
            unsigned char c;
            op.getSR1_SR2_SR3(a, b, c);
            mRegset.EQF32(a, b, c);
            mRegset.next();
            break;
        }
        case BCOpCode::NEF32: {
            unsigned char a;
            unsigned char b;
            unsigned char c;
            op.getSR1_SR2_SR3(a, b, c);
            mRegset.NEF32(a, b, c);
            mRegset.next();
            break;
        }
        case BCOpCode::LTCMP: {
            unsigned char a;
            unsigned char b;
            op.getSR1_SR2(a, b);
            mRegset.LTCMP(a, b);
            mRegset.next();
            break;
        }
        case BCOpCode::LECMP: {
            unsigned char a;
            unsigned char b;
            op.getSR1_SR2(a, b);
            mRegset.LECMP(a, b);
            mRegset.next();
            break;
        }
        case BCOpCode::EQBOOL: {
            unsigned char a;
            unsigned char b;
            unsigned char c;
            op.getSR1_SR2_SR3(a, b, c);
            mRegset.EQBOOL(a, b, c);
            mRegset.next();
            break;
        }
        case BCOpCode::NEBOOL: {
            unsigned char a;
            unsigned char b;
            unsigned char c;
            op.getSR1_SR2_SR3(a, b, c);
            mRegset.NEBOOL(a, b, c);
            mRegset.next();
            break;
        }
        case BCOpCode::ANDI32: {
            unsigned char a;
            unsigned char b;
            unsigned char c;
            op.getSR1_SR2_SR3(a, b, c);
            mRegset.ANDI32(a, b, c);
            mRegset.next();
            break;
        }
        case BCOpCode::ORI32: {
            unsigned char a;
            unsigned char b;
            unsigned char c;
            op.getSR1_SR2_SR3(a, b, c);
            mRegset.ORI32(a, b, c);
            mRegset.next();
            break;
        }
        case BCOpCode::XORI32: {
            unsigned char a;
            unsigned char b;
            unsigned char c;
            op.getSR1_SR2_SR3(a, b, c);
            mRegset.XORI32(a, b, c);
            mRegset.next();
            break;
        }
        case BCOpCode::NTI32: {
            unsigned char a;
            unsigned char b;
            op.getSR1_SR2(a, b);
            mRegset.NTI32(a, b);
            mRegset.next();
            break;
        }
        case BCOpCode::NTBOOL: {
            unsigned char a;
            unsigned char b;
            op.getSR1_SR2(a, b);
            mRegset.NTBOOL(a, b);
            mRegset.next();
            break;
        }
        case BCOpCode::SLLI32: {
            unsigned char a;
            unsigned char b;
            unsigned char c;
            op.getSR1_SR2_SR3(a, b, c);
            mRegset.SLLI32(a, b, c);
            mRegset.next();
            break;
        }
        case BCOpCode::SLRI32: {
            unsigned char a;
            unsigned char b;
            unsigned char c;
            op.getSR1_SR2_SR3(a, b, c);
            mRegset.SLRI32(a, b, c);
            mRegset.next();
            break;
        }
        case BCOpCode::JMP:
            mRegset.JMP(op.getCS2());
            break;
        case BCOpCode::JMPPOS: {
            unsigned char a;
            short offset;
            op.getSR1_CS2(a, offset);
            mRegset.JMPPOS(a, offset);
            break;
        }
        case BCOpCode::JMPNEG: {
            unsigned char a;
            short offset;
            op.getSR1_CS2(a, offset);
            mRegset.JMPNEG(a, offset);
            break;
        }
        case BCOpCode::FENTER: {
            unsigned char a;
            unsigned char b;
            op.getCU1_CU1(a, b);
            mRegset.FENTER(a, b);
            mRegset.next();
            break;
        }
        case BCOpCode::FLEAVE:
            mRegset.FLEAVE();
            popModule();
            break;
        case BCOpCode::FRET:
            mRegset.FRET();
            popModule();
            break;
        case BCOpCode::CALL:
            mRegset.next();
            call(currentModule()->symbolTable().symbol(op.getSTI()));
            break;
        case BCOpCode::YIELD:
            mRegset.YIELD(op.getSR1());
            mRegset.next();
            break;
        case BCOpCode::MCOPY: {
            unsigned char a;
            unsigned char b;
            unsigned char c;
            op.getSR1_SR2_SR3(a, b, c);
            mRegset.MCOPY(a, b, c);
            mRegset.next();
            break;
        }
        case BCOpCode::MZEROS: {
            unsigned char a;
            unsigned short index;
            op.getSR1_STI(a, index);
            mRegset.MZEROS(a, mCore.sizeOf(currentModule()->symbolTable().symbol(index)));
            mRegset.next();
            break;
        }
        case BCOpCode::SPPSH: {
            unsigned char a;
            unsigned short index;
            op.getSR1_STI(a, index);
            mRegset.SPPSH(a, mCore.sizeOf(currentModule()->symbolTable().symbol(index)));
            mRegset.next();
            break;
        }
        case BCOpCode::SPPSHZ: {
            unsigned char a;
            unsigned short index;
            op.getSR1_STI(a, index);
            mRegset.SPPSHZ(a, mCore.sizeOf(currentModule()->symbolTable().symbol(index)));
            mRegset.next();
            break;
        }
        case BCOpCode::SPPOP: {
            unsigned char a;
            unsigned short index;
            op.getSR1_STI(a, index);
            mRegset.SPPOP(a, mCore.sizeOf(currentModule()->symbolTable().symbol(index)));
            mRegset.next();
            break;
        }
        case BCOpCode::ADDOFS: {
            unsigned char a;
            unsigned short index;
            op.getSR1_STI(a, index);
            mRegset.ADDOFS(a, mCore.offsetOf(currentModule()->symbolTable().symbol(index)));
            mRegset.next();
            break;
        }
        case BCOpCode::ARPSHZ:
            mRegset.ARPSHZ(op.getSR1());
            mRegset.next();
            break;
        case BCOpCode::ARIDX: {
            unsigned char a;
            unsigned char b;
            op.getSR1_SR2(a, b);
            mRegset.ARIDX(a, b);
            mRegset.next();
            break;
        }
        case BCOpCode::ARLEN: {
            unsigned char a;
            unsigned char b;
            op.getSR1_SR2(a, b);
            mRegset.ARLEN(a, b);
            mRegset.next();
            break;
        }
        case BCOpCode::ARPOP:
            mRegset.ARPOP(op.getSR1());
            mRegset.next();
            break;
        default:
            printf("[NOT IMPLEMENT]");
            op.dump();
            mRegset.next();
            break;
        }
    }
    MINT_ASSERT("Runner.cpp", 643, mModuleCount == 0);
}

void Runner::execute(const char* name) {
    setEntryPoint(name);
    execute();
}

bool Runner::isEnd() const {
    return !mRegset.isYieldContinue();
}

void Runner::call(const char* name) {
    const VMModule* module;
    const VMFunction* function = mCore.findFunction(name, &module);
    if (function) {
        if (function->isMint()) {
            mRegset.CALL(function->instruction());
            pushModule(module);
        } else {
            MintFuncProxy proxy(mRegset, !function->isBuiltInReturn());
            function->nativeFunc()(proxy);
        }
    }
}

}  // namespace mintvm
