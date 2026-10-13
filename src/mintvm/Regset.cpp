#include "mintvm/Regset.h"

#include "mintvm/MintSystemCall.h"
#include "mintvm/VMVariable.h"
#include "mintvm/stdc.h"

namespace mintvm {

Regset::Regset(unsigned long stackSize, IAllocator* allocator)
    : mStackSize(stackSize)
    , mStack(allocator != 0 ? *allocator : RNObject::allocator(), mStackSize)
    , mFR(RNObject::allocator(), FR_NUM)
    , mPC(0)
    , mLR(0)
    , mSRP(0)
    , mSP(0)
    , mYieldCount(0) {}

void Regset::init() {
    mPC = 0;
    mLR = 0;
    mSP = 0;
    mSRP = 0;
    mYieldCount = 0;
    clearFR();
}

void Regset::clearFR() {
    for (unsigned int i = 0; i < mFR.count(); i++) {
        internal_getFR(i).mU32 = 0;
    }
}

void Regset::init(const unsigned int* pc) {
    mPC = pc;
    mLR = 0;
    mSP = 0;
    mSRP = 0;
    mYieldCount = 1;
    clearFR();
}

void Regset::LDSRZR(unsigned char a) {
    setRegister(a).mU32 = 0;
}

void Regset::LDSRBT(unsigned char a) {
    setRegister(a).mBool = true;
}

void Regset::LDSRC4(unsigned char a, unsigned long value) {
    setRegister(a).mU32 = value;
}

void Regset::LDSRCA(unsigned char a, void* address) {
    setRegister(a).mPtr = address;
}

void Regset::LDSRSR(unsigned char a, unsigned char b) {
    setRegister(a) = getRegister(b);
}

void Regset::LDSRFZ(unsigned char a) {
    setRegister(a) = getFR(0);
}

void Regset::LDFRSR(unsigned char a, unsigned char b) {
    internal_getFR(a) = getRegister(b);
}

// The original link dropped this function: only its size and its two strings are known, the line is a guess.
void Regset::LDSRSA(unsigned char, void*) {
    MINT_ASSERT("Regset.cpp", 141, false);
}

void Regset::LDSRSV(unsigned char a, const VMVariable* variable) {
    if (variable != 0) {
        setRegister(a) = variable->mValue;
    } else {
        MValue zero;
        zero.mU32 = 0;
        setRegister(a) = zero;
    }
}

void Regset::LDSRA4(unsigned char a, unsigned char b) {
    setRegister(a).mU32 = *getRegister(b).mU32Ptr;
}

void Regset::LDSRSZ(unsigned char a, unsigned long size) {
    LDSRC4(a, size);
}

void Regset::STSRSR(unsigned char a, unsigned char b) {
    u32* dst = getRegister(a).mU32Ptr;
    *dst = getRegister(b).mU32;
}

void Regset::STSVSR(unsigned char a, VMVariable* variable) {
    if (variable != 0) {
        variable->mValue = getRegister(a);
    }
}

void Regset::ADDI32(unsigned char a, unsigned char b, unsigned char c) {
    setRegister(a).mS32 = getRegister(b).mS32 + getRegister(c).mS32;
}

void Regset::SUBI32(unsigned char a, unsigned char b, unsigned char c) {
    setRegister(a).mS32 = getRegister(b).mS32 - getRegister(c).mS32;
}

void Regset::MULS32(unsigned char a, unsigned char b, unsigned char c) {
    setRegister(a).mS32 = getRegister(b).mS32 * getRegister(c).mS32;
}

void Regset::DIVS32(unsigned char a, unsigned char b, unsigned char c) {
    if (getRegister(c).mS32 == 0.0f) {
        MintSystemCall::panic(
            "Regset.cpp", 190,
            "[error] sr%d = %d / %d : DIVI32"
            "\x96\xBD\x97\xDF\x82\xC9\x82\xC4\x81\x41\x30\x8F\x9C\x8E\x5A\x82\xAA\x8E\xC0\x8D\x73\x82\xB3\x82\xEA\x82\xDC\x82\xB5\x82\xBD\n",
            a, getRegister(b).mS32, getRegister(c).mS32
        );
    }
    setRegister(a).mS32 = getRegister(b).mS32 / getRegister(c).mS32;
}

void Regset::MODS32(unsigned char a, unsigned char b, unsigned char c) {
    setRegister(a).mS32 = getRegister(b).mS32 % getRegister(c).mS32;
}

void Regset::INCI32(unsigned char a) {
    setRegister(a).mS32++;
}

void Regset::DECI32(unsigned char a) {
    setRegister(a).mS32--;
}

void Regset::NEGS32(unsigned char a, unsigned char b) {
    setRegister(a).mS32 = -getRegister(b).mS32;
}

void Regset::ADDF32(unsigned char a, unsigned char b, unsigned char c) {
    setRegister(a).mF32 = getRegister(b).mF32 + getRegister(c).mF32;
}

void Regset::SUBF32(unsigned char a, unsigned char b, unsigned char c) {
    setRegister(a).mF32 = getRegister(b).mF32 - getRegister(c).mF32;
}

void Regset::MULF32(unsigned char a, unsigned char b, unsigned char c) {
    setRegister(a).mF32 = getRegister(b).mF32 * getRegister(c).mF32;
}

void Regset::DIVF32(unsigned char a, unsigned char b, unsigned char c) {
    if (getRegister(c).mF32 == 0.0f) {
        MintSystemCall::panic(
            "Regset.cpp", 231,
            "[error] sr%d = %f / %f : DIVF32"
            "\x96\xBD\x97\xDF\x82\xC9\x82\xC4\x81\x41\x30\x8F\x9C\x8E\x5A\x82\xAA\x8E\xC0\x8D\x73\x82\xB3\x82\xEA\x82\xDC\x82\xB5\x82\xBD\n",
            a, getRegister(b).mF32, getRegister(c).mF32
        );
    }
    setRegister(a).mF32 = getRegister(b).mF32 / getRegister(c).mF32;
}

void Regset::INCF32(unsigned char a) {
    setRegister(a).mF32 += 1.0f;
}

void Regset::DECF32(unsigned char a) {
    setRegister(a).mF32 -= 1.0f;
}

void Regset::NEGF32(unsigned char a, unsigned char b) {
    setRegister(a).mF32 = -getRegister(b).mF32;
}

void Regset::LTS32(unsigned char a, unsigned char b, unsigned char c) {
    setRegister(a).mBool = getRegister(b).mS32 < getRegister(c).mS32;
}

void Regset::LES32(unsigned char a, unsigned char b, unsigned char c) {
    setRegister(a).mBool = getRegister(b).mS32 <= getRegister(c).mS32;
}

void Regset::EQI32(unsigned char a, unsigned char b, unsigned char c) {
    setRegister(a).mBool = getRegister(b).mS32 == getRegister(c).mS32;
}

void Regset::NEI32(unsigned char a, unsigned char b, unsigned char c) {
    setRegister(a).mBool = getRegister(b).mS32 != getRegister(c).mS32;
}

void Regset::LTF32(unsigned char a, unsigned char b, unsigned char c) {
    setRegister(a).mBool = getRegister(b).mF32 < getRegister(c).mF32;
}

void Regset::LEF32(unsigned char a, unsigned char b, unsigned char c) {
    setRegister(a).mBool = getRegister(b).mF32 <= getRegister(c).mF32;
}

void Regset::EQF32(unsigned char a, unsigned char b, unsigned char c) {
    setRegister(a).mBool = getRegister(b).mF32 == getRegister(c).mF32;
}

void Regset::NEF32(unsigned char a, unsigned char b, unsigned char c) {
    setRegister(a).mBool = getRegister(b).mF32 != getRegister(c).mF32;
}

void Regset::LTCMP(unsigned char a, unsigned char b) {
    setRegister(a).mBool = getRegister(b).mS32 < 0;
}

void Regset::LECMP(unsigned char a, unsigned char b) {
    setRegister(a).mBool = getRegister(b).mS32 <= 0;
}

void Regset::EQBOOL(unsigned char a, unsigned char b, unsigned char c) {
    setRegister(a).mBool = getRegister(b).mBool == getRegister(c).mBool;
}

void Regset::NEBOOL(unsigned char a, unsigned char b, unsigned char c) {
    setRegister(a).mBool = getRegister(b).mBool != getRegister(c).mBool;
}

void Regset::ANDI32(unsigned char a, unsigned char b, unsigned char c) {
    setRegister(a).mU32 = getRegister(b).mU32 & getRegister(c).mU32;
}

void Regset::ORI32(unsigned char a, unsigned char b, unsigned char c) {
    setRegister(a).mU32 = getRegister(b).mU32 | getRegister(c).mU32;
}

void Regset::XORI32(unsigned char a, unsigned char b, unsigned char c) {
    setRegister(a).mU32 = getRegister(b).mU32 ^ getRegister(c).mU32;
}

void Regset::NTI32(unsigned char a, unsigned char b) {
    setRegister(a).mU32 = ~getRegister(b).mU32;
}

void Regset::NTBOOL(unsigned char a, unsigned char b) {
    setRegister(a).mBool = !getRegister(b).mBool;
}

void Regset::SLLI32(unsigned char a, unsigned char b, unsigned char c) {
    setRegister(a).mU32 = getRegister(b).mU32 << getRegister(c).mU32;
}

void Regset::SLRI32(unsigned char a, unsigned char b, unsigned char c) {
    setRegister(a).mU32 = getRegister(b).mU32 >> getRegister(c).mU32;
}

void Regset::JMP(short offset) {
    jump(offset);
}

void Regset::JMPPOS(unsigned char a, short offset) {
    if (getRegister(a).mBool) {
        jump(offset);
    } else {
        next();
    }
}

void Regset::JMPNEG(unsigned char a, short offset) {
    if (!getRegister(a).mBool) {
        jump(offset);
    } else {
        next();
    }
}

MValue& Regset::saveR(StackSaveValue value) {
    return mStack[mSP + value];
}

const MValue& Regset::restoreR(unsigned int base, StackSaveValue value) const {
    return mStack[base - (SAVE_NUM - value)];
}

void Regset::FENTER(unsigned char frameSize, unsigned char argCount) {
    saveR(SAVE_SP).mU32 = mSP;
    saveR(SAVE_SRP).mU32 = mSRP;
    saveR(SAVE_LR).mCode = mLR;
    spInc(SAVE_NUM);
    mSRP = mSP;
    for (unsigned int i = 0; i < argCount; i++) {
        mStack[mSP + i] = getFR(i);
    }
    spInc(frameSize);
}

void Regset::FLEAVE() {
    unsigned int srp = mSRP;
    mPC = mLR = restoreR(srp, SAVE_LR).mCode;
    mSRP = restoreR(srp, SAVE_SRP).mU32;
    mSP = restoreR(srp, SAVE_SP).mU32;
}

void Regset::FRET() {
    mFR[0] = getRegister(0);
    FLEAVE();
}

void Regset::CALL(const unsigned int* target) {
    mLR = mPC;
    mPC = target;
}

void Regset::YIELD(unsigned char a) {
    int count = getRegister(a).mS32;
    if (count < 0) {
        MintSystemCall::panic(
            "Regset.cpp", 432,
            "[error] yield(%d) : yield"
            "\x96\xBD\x97\xDF\x82\xC9\x93\x6E\x82\xB7\x92\x6C\x82\xCD\x30\x88\xC8\x8F\xE3\x82\xC5\x96\xB3\x82\xAF\x82\xEA\x82\xCE\x82\xC8\x82\xE8\x82\xDC\x82\xB9\x82\xF1\n",
            count
        );
    }
    mYieldCount = count;
}

void Regset::MCOPY(unsigned char a, unsigned char b, unsigned char c) {
    void* dst = getRegister(a).mPtr;
    void* src = getRegister(b).mPtr;
    unsigned long size = getRegister(c).mU32;
    memcpy(dst, src, size);
}

void Regset::MZEROS(unsigned char a, unsigned long size) {
    memset(getRegister(a).mPtr, 0, size);
}

void Regset::SPPSH(unsigned char a, unsigned long size) {
    setRegister(a).mPtr = &mStack[mSP];
    spInc(ds2rn(size));
}

void Regset::SPPSHZ(unsigned char a, unsigned long size) {
    SPPSH(a, size);
    MZEROS(a, size);
}

void Regset::SPPOP(unsigned char, unsigned long size) {
    spDec(ds2rn(size));
}

void Regset::ADDOFS(unsigned char a, unsigned long offset) {
    setRegister(a).mU32 += offset;
}

void Regset::ARPSHZ(unsigned char a) {
    int length = getRegister(a).mS32;
    if (length <= 0) {
        MintSystemCall::panic(
            "Regset.cpp", 481,
            "[error] Array.length == %d : "
            "\x94\x7A\x97\xF1\x82\xC9\x93\x6E\x82\xB3\x82\xEA\x82\xBD\x83\x54\x83\x43\x83\x59\x82\xAA\x90\xB3\x82\xB5\x82\xAD\x82\xA0\x82\xE8\x82\xDC\x82\xB9\x82\xF1\n",
            length
        );
    }
    SPPSHZ(a, (length + 1) * 4);
    *getRegister(a).mS32Ptr = length;
    setRegister(a).mS32Ptr++;
}

void Regset::ARIDX(unsigned char a, unsigned char b) {
    int length = getLength(a);
    int index = getRegister(b).mS32;
    if (index < 0 || index >= length) {
        MintSystemCall::panic(
            "Regset.cpp", 504,
            "[error] "
            "\x94\x7A\x97\xF1\x82\xCC\x8B\xAB\x8A\x45\x8A\x4F\x82\xC5\x82\xB7"
            " -> a[%d] (a.length=%d)\n"
            "                             ^^^\n",
            index, length
        );
    }
    ADDOFS(a, index * 4);
}

void Regset::ARLEN(unsigned char a, unsigned char b) {
    LDSRC4(a, getLength(b));
}

void Regset::ARPOP(unsigned char a) {
    SPPOP(a, (getLength(a) + 1) * 4);
}

unsigned long Regset::stackOffset(unsigned long address) const {
    unsigned long offset = (address - reinterpret_cast<unsigned long>(&mStack[0])) >> 2;
    return offset < mStackSize ? offset : 0;
}

void Regset::dump() const {
    printf("=== Regset ===\n");
    printf("-- main --\n");
    printf("pc         = %p\n", mPC);
    printf("lr         = %p\n", mLR);
    printf("stack_head = %p(%d)\n", &mStack[0], 0);
    printf("srp        = %u\n", mSRP);
    printf("sp         = %u\n", mSP);
    printf("-- stack --\n");
    printf("%3d : ", 0);
    int column = 0;
    for (unsigned int i = 0; i < mStackSize; i++) {
        printf("%08x", mStack[i].mU32);
        const MValue* head = &mStack[0];
        unsigned long offset = (mStack[i].mU32 - reinterpret_cast<unsigned long>(head)) >> 2;
        if (offset >= mStackSize) {
            offset = 0;
        }
        printf("(%2d) ", offset);
        column++;
        if (column == 5) {
            printf("\n");
            printf("%3d : ", i + 1);
            column = 0;
        }
    }
    printf("\n");
    printf("-- fr --\n");
    printf("%3d : ", 0);
    int frColumn = 0;
    for (unsigned int i = 0; i < FR_NUM; i++) {
        printf("%08x(%2d) ", mFR[i].mU32, stackOffset(mFR[i].mU32));
        frColumn++;
        if (frColumn == 5) {
            printf("\n");
            printf("%3d : ", i + 1);
            frColumn = 0;
        }
    }
    printf("\n");
}

}  // namespace mintvm
