#ifndef MINTVM_BCOPCODE_H
#define MINTVM_BCOPCODE_H

#include "mintvm/MintAssert.h"
#include "types.h"

namespace mintvm {

class BCOpCode {
public:
    enum OpType {
        NOP,
        LDSRZR,
        LDSRBT,
        LDSRC4,
        LDSRCA,
        LDSRSR,
        LDSRFZ,
        LDFRSR,
        LDSRSA,
        LDSRSV,
        LDSRA4,
        LDSRSZ,
        STSRSR,
        STSVSR,
        ADDI32,
        SUBI32,
        MULS32,
        DIVS32,
        MODS32,
        INCI32,
        DECI32,
        NEGS32,
        ADDF32,
        SUBF32,
        MULF32,
        DIVF32,
        INCF32,
        DECF32,
        NEGF32,
        LTS32,
        LES32,
        EQI32,
        NEI32,
        LTF32,
        LEF32,
        EQF32,
        NEF32,
        LTCMP,
        LECMP,
        EQBOOL,
        NEBOOL,
        ANDI32,
        ORI32,
        XORI32,
        NTI32,
        NTBOOL,
        SLLI32,
        SLRI32,
        JMP,
        JMPPOS,
        JMPNEG,
        FENTER,
        FLEAVE,
        FRET,
        CALL,
        YIELD,
        MCOPY,
        MZEROS,
        SPPSH,
        SPPSHZ,
        SPPOP,
        ADDOFS,
        ARPSHZ,
        ARIDX,
        ARLEN,
        ARPOP,
        OP_TYPE_NUM,
    };

    // The operands that follow the type byte. Named after the accessor that reads them.
    enum OpFormat {
        FORMAT_0,
        FORMAT_1,
        FORMAT_2,
        FORMAT_CU1_CU1,
        FORMAT_FR1_SR1,
        FORMAT_5,
        FORMAT_SR1,
        FORMAT_SR1_CS2,
        FORMAT_SR1_CTI,
        FORMAT_SR1_SR2,
        FORMAT_SR1_SR2_SR3,
        FORMAT_SR1_STI,
        FORMAT_STI,
    };

    BCOpCode(const unsigned int* code)
        : mCode(reinterpret_cast<const u8*>(code)) {}

    bool dump();
    OpType getOpType() const;
    OpFormat opFormat() const;
    static OpFormat opTypeToOpFormat(OpType type);
    const char* getOpTypeName(OpType type) const;

    unsigned char getCU1() const {
        MINT_ASSERT("BCOpCode.hpp", 179, opFormat() == FORMAT_2);
        return mCode[1];
    }

    void getCU1_CU1(unsigned char& a, unsigned char& b) const {
        MINT_ASSERT("BCOpCode.hpp", 185, opFormat() == FORMAT_CU1_CU1);
        a = mCode[1];
        b = mCode[2];
    }

    void getFR1_SR1(unsigned char& a, unsigned char& b) const {
        MINT_ASSERT("BCOpCode.hpp", 192, opFormat() == FORMAT_FR1_SR1);
        a = mCode[1];
        b = mCode[2];
    }

    unsigned char getSR1() const {
        MINT_ASSERT("BCOpCode.hpp", 199, opFormat() == FORMAT_SR1);
        return mCode[1];
    }

    void getSR1_CS2(unsigned char& a, short& offset) const {
        MINT_ASSERT("BCOpCode.hpp", 205, opFormat() == FORMAT_SR1_CS2);
        a = mCode[1];
        offset = *reinterpret_cast<const short*>(mCode + 2);
    }

    void getSR1_CTI(unsigned char& a, unsigned short& index) const {
        MINT_ASSERT("BCOpCode.hpp", 212, opFormat() == FORMAT_SR1_CTI);
        a = mCode[1];
        index = *reinterpret_cast<const unsigned short*>(mCode + 2);
    }

    void getSR1_SR2(unsigned char& a, unsigned char& b) const {
        MINT_ASSERT("BCOpCode.hpp", 219, opFormat() == FORMAT_SR1_SR2);
        a = mCode[1];
        b = mCode[2];
    }

    void getSR1_SR2_SR3(unsigned char& a, unsigned char& b, unsigned char& c) const {
        MINT_ASSERT("BCOpCode.hpp", 226, opFormat() == FORMAT_SR1_SR2_SR3);
        a = mCode[1];
        b = mCode[2];
        c = mCode[3];
    }

    void getSR1_STI(unsigned char& a, unsigned short& index) const {
        MINT_ASSERT("BCOpCode.hpp", 234, opFormat() == FORMAT_SR1_STI);
        a = mCode[1];
        index = *reinterpret_cast<const unsigned short*>(mCode + 2);
    }

    unsigned short getSTI() const {
        MINT_ASSERT("BCOpCode.hpp", 241, opFormat() == FORMAT_STI);
        return *reinterpret_cast<const unsigned short*>(mCode + 2);
    }

    short getCS2() const {
        return *reinterpret_cast<const short*>(mCode + 2);
    }

private:
    const u8* mCode;
};

}  // namespace mintvm

#endif
