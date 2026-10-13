#ifndef MINTVM_REGSET_H
#define MINTVM_REGSET_H

#include "mintvm/IAllocator.h"
#include "mintvm/MArray.h"
#include "mintvm/MValue.h"
#include "mintvm/MintAssert.h"
#include "mintvm/RNObject.h"
#include "types.h"

namespace mintvm {

class VMVariable;

class Regset : public RNObject {
public:
    enum StackSaveValue {
        SAVE_SP,
        SAVE_SRP,
        SAVE_LR,
        SAVE_NUM,
    };

    enum {
        FR_NUM = 16,
    };

    Regset(unsigned long stackSize, IAllocator* allocator);
    virtual ~Regset() {}

    void init();
    void init(const unsigned int* pc);
    void clearFR();

    void LDSRZR(unsigned char a);
    void LDSRBT(unsigned char a);
    void LDSRC4(unsigned char a, unsigned long value);
    void LDSRCA(unsigned char a, void* address);
    void LDSRSR(unsigned char a, unsigned char b);
    void LDSRFZ(unsigned char a);
    void LDFRSR(unsigned char a, unsigned char b);
    void LDSRSA(unsigned char a, void* address);
    void LDSRSV(unsigned char a, const VMVariable* variable);
    void LDSRA4(unsigned char a, unsigned char b);
    void LDSRSZ(unsigned char a, unsigned long size);
    void STSRSR(unsigned char a, unsigned char b);
    void STSVSR(unsigned char a, VMVariable* variable);
    void ADDI32(unsigned char a, unsigned char b, unsigned char c);
    void SUBI32(unsigned char a, unsigned char b, unsigned char c);
    void MULS32(unsigned char a, unsigned char b, unsigned char c);
    void DIVS32(unsigned char a, unsigned char b, unsigned char c);
    void MODS32(unsigned char a, unsigned char b, unsigned char c);
    void INCI32(unsigned char a);
    void DECI32(unsigned char a);
    void NEGS32(unsigned char a, unsigned char b);
    void ADDF32(unsigned char a, unsigned char b, unsigned char c);
    void SUBF32(unsigned char a, unsigned char b, unsigned char c);
    void MULF32(unsigned char a, unsigned char b, unsigned char c);
    void DIVF32(unsigned char a, unsigned char b, unsigned char c);
    void INCF32(unsigned char a);
    void DECF32(unsigned char a);
    void NEGF32(unsigned char a, unsigned char b);
    void LTS32(unsigned char a, unsigned char b, unsigned char c);
    void LES32(unsigned char a, unsigned char b, unsigned char c);
    void EQI32(unsigned char a, unsigned char b, unsigned char c);
    void NEI32(unsigned char a, unsigned char b, unsigned char c);
    void LTF32(unsigned char a, unsigned char b, unsigned char c);
    void LEF32(unsigned char a, unsigned char b, unsigned char c);
    void EQF32(unsigned char a, unsigned char b, unsigned char c);
    void NEF32(unsigned char a, unsigned char b, unsigned char c);
    void LTCMP(unsigned char a, unsigned char b);
    void LECMP(unsigned char a, unsigned char b);
    void EQBOOL(unsigned char a, unsigned char b, unsigned char c);
    void NEBOOL(unsigned char a, unsigned char b, unsigned char c);
    void ANDI32(unsigned char a, unsigned char b, unsigned char c);
    void ORI32(unsigned char a, unsigned char b, unsigned char c);
    void XORI32(unsigned char a, unsigned char b, unsigned char c);
    void NTI32(unsigned char a, unsigned char b);
    void NTBOOL(unsigned char a, unsigned char b);
    void SLLI32(unsigned char a, unsigned char b, unsigned char c);
    void SLRI32(unsigned char a, unsigned char b, unsigned char c);
    void JMP(short offset);
    void JMPPOS(unsigned char a, short offset);
    void JMPNEG(unsigned char a, short offset);
    void FENTER(unsigned char frameSize, unsigned char argCount);
    void FLEAVE();
    void FRET();
    void CALL(const unsigned int* target);
    void YIELD(unsigned char a);
    void MCOPY(unsigned char a, unsigned char b, unsigned char c);
    void MZEROS(unsigned char a, unsigned long size);
    void SPPSH(unsigned char a, unsigned long size);
    void SPPSHZ(unsigned char a, unsigned long size);
    void SPPOP(unsigned char a, unsigned long size);
    void ADDOFS(unsigned char a, unsigned long offset);
    void ARPSHZ(unsigned char a);
    void ARIDX(unsigned char a, unsigned char b);
    void ARLEN(unsigned char a, unsigned char b);
    void ARPOP(unsigned char a);

    MValue& saveR(StackSaveValue value);
    const MValue& restoreR(unsigned int base, StackSaveValue value) const;
    unsigned long stackOffset(unsigned long address) const;
    void dump() const;

    MValue& setRegister(unsigned int index) {
        return mStack[mSRP + index];
    }

    const MValue& getRegister(unsigned int index) const {
        return mStack[mSRP + index];
    }

    MValue& setFR(unsigned int index) {
        return mFR[index];
    }

    const MValue& getFR(unsigned int index) const {
        return mFR[index];
    }

    MValue& internal_getFR(unsigned int index) {
        return mFR[index];
    }

    void jump(short offset) {
        mPC += offset;
    }

    void next() {
        mPC++;
    }

    bool isYieldContinue() const {
        return mYieldCount > 0;
    }

    void decYieldCount() {
        MINT_ASSERT("Regset.hpp", 70, isYieldContinue());
        mYieldCount--;
    }

    const unsigned int* pc() const {
        return mPC;
    }

    bool spInc(unsigned int count) {
        unsigned int sp = mSP + count;
        if (sp < mStackSize) {
            mSP = sp;
            return true;
        }
        MINT_ASSERT("Regset.hpp", 231, false);
        return false;
    }

    bool spDec(unsigned int count) {
        if (mSP >= count) {
            mSP -= count;
            return true;
        }
        MINT_ASSERT("Regset.hpp", 242, false);
        return false;
    }

    unsigned int ds2rn(unsigned long size) const {
        return (size >> 2) + ((size & 3) != 0);
    }

    int getLength(unsigned char a) {
        return getRegister(a).mS32Ptr[-1];
    }

private:
    unsigned long mStackSize;
    MArray<MValue> mStack;
    MArray<MValue> mFR;
    const unsigned int* mPC;
    const unsigned int* mLR;
    unsigned int mSRP;
    unsigned int mSP;
    int mYieldCount;
};

}  // namespace mintvm

#endif
