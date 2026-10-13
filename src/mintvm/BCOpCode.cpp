#include "mintvm/BCOpCode.h"

#include "mintvm/stdc.h"

namespace mintvm {

bool BCOpCode::dump() {
    OpType type = getOpType();
    printf("        %-8s", getOpTypeName(type));

    switch (opTypeToOpFormat(type)) {
    case FORMAT_1:
        printf("    %d\n", getCS2());
        break;
    case FORMAT_2:
        printf("    %d\n", getCU1());
        break;
    case FORMAT_CU1_CU1: {
        unsigned char a;
        unsigned char b;
        getCU1_CU1(a, b);
        printf("    %d,    %d\n", a, b);
        break;
    }
    case FORMAT_FR1_SR1: {
        unsigned char a;
        unsigned char b;
        getFR1_SR1(a, b);
        printf("    %d,    %d\n", a, b);
        break;
    }
    case FORMAT_5:
        printf("\n");
        break;
    case FORMAT_SR1:
        printf("    %d\n", getSR1());
        break;
    case FORMAT_SR1_CS2: {
        unsigned char a;
        short offset;
        getSR1_CS2(a, offset);
        printf("    %d,    %d\n", a, offset);
        break;
    }
    case FORMAT_SR1_CTI: {
        unsigned char a;
        unsigned short index;
        getSR1_CTI(a, index);
        printf("    %d,    %d\n", a, index);
        break;
    }
    case FORMAT_SR1_SR2: {
        unsigned char a;
        unsigned char b;
        getSR1_SR2(a, b);
        printf("    %d,    %d\n", a, b);
        break;
    }
    case FORMAT_SR1_SR2_SR3: {
        unsigned char a;
        unsigned char b;
        unsigned char c;
        getSR1_SR2_SR3(a, b, c);
        printf("    %d,    %d,    %d\n", a, b, c);
        break;
    }
    case FORMAT_SR1_STI: {
        unsigned char a;
        unsigned short index;
        getSR1_STI(a, index);
        printf("    %d,    %d\n", a, index);
        break;
    }
    case FORMAT_STI:
        printf("    %d\n", getSTI());
        break;
    default:
        MINT_ASSERT("BCOpCode.cpp", 102, false);
        break;
    }

    return type == FLEAVE || type == FRET;
}

BCOpCode::OpType BCOpCode::getOpType() const {
    return static_cast<OpType>(mCode[0]);
}

BCOpCode::OpFormat BCOpCode::opFormat() const {
    return opTypeToOpFormat(getOpType());
}

BCOpCode::OpFormat BCOpCode::opTypeToOpFormat(OpType type) {
    switch (type) {
    case LDSRZR:
        return FORMAT_SR1;
    case LDSRBT:
        return FORMAT_SR1;
    case LDSRC4:
    case LDSRCA:
        return FORMAT_SR1_CTI;
    case LDSRSR:
        return FORMAT_SR1_SR2;
    case LDSRFZ:
        return FORMAT_SR1;
    case LDFRSR:
        return FORMAT_FR1_SR1;
    case LDSRSA:
    case LDSRSV:
        return FORMAT_SR1_STI;
    case LDSRA4:
        return FORMAT_SR1_SR2;
    case LDSRSZ:
        return FORMAT_SR1_STI;
    case STSRSR:
        return FORMAT_SR1_SR2;
    case STSVSR:
        return FORMAT_SR1_STI;
    case ADDI32:
    case SUBI32:
    case MULS32:
    case DIVS32:
    case MODS32:
    case ADDF32:
    case SUBF32:
    case MULF32:
    case DIVF32:
        return FORMAT_SR1_SR2_SR3;
    case INCI32:
    case DECI32:
    case INCF32:
    case DECF32:
        return FORMAT_SR1;
    case NEGS32:
    case NEGF32:
        return FORMAT_SR1_SR2;
    case LTS32:
    case LES32:
    case EQI32:
    case NEI32:
        return FORMAT_SR1_SR2_SR3;
    case LTF32:
    case LEF32:
    case EQF32:
    case NEF32:
        return FORMAT_SR1_SR2_SR3;
    case LTCMP:
    case LECMP:
        return FORMAT_SR1_SR2;
    case EQBOOL:
    case NEBOOL:
        return FORMAT_SR1_SR2_SR3;
    case ANDI32:
    case ORI32:
    case XORI32:
        return FORMAT_SR1_SR2_SR3;
    case NTI32:
    case NTBOOL:
        return FORMAT_SR1_SR2;
    case SLLI32:
    case SLRI32:
        return FORMAT_SR1_SR2_SR3;
    case JMP:
        return FORMAT_1;
    case JMPPOS:
    case JMPNEG:
        return FORMAT_SR1_CS2;
    case FENTER:
        return FORMAT_CU1_CU1;
    case FLEAVE:
    case FRET:
        return FORMAT_5;
    case CALL:
        return FORMAT_STI;
    case YIELD:
        return FORMAT_SR1;
    case MCOPY:
        return FORMAT_SR1_SR2_SR3;
    case MZEROS:
        return FORMAT_SR1_STI;
    case SPPSH:
    case SPPSHZ:
    case SPPOP:
        return FORMAT_SR1_STI;
    case ADDOFS:
        return FORMAT_SR1_STI;
    case ARPSHZ:
    case ARPOP:
        return FORMAT_SR1;
    case ARIDX:
    case ARLEN:
        return FORMAT_SR1_SR2;
    }
    return FORMAT_0;
}

// TODO: the original calls this from dump() although nothing else in the unit does, and no flag
// reproduces that. The pragma stands in for whatever kept it from being inlined.
#pragma dont_inline on
const char* BCOpCode::getOpTypeName(OpType type) const {
    static const char* table[] = {
        "NOP",    "LDSRZR", "LDSRBT", "LDSRC4", "LDSRCA", "LDSRSR", "LDSRFZ", "LDFRSR", "LDSRSA", "LDSRSV", "LDSRA4",
        "LDSRSZ", "STSRSR", "STSVSR", "ADDI32", "SUBI32", "MULS32", "DIVS32", "MODS32", "INCI32", "DECI32", "NEGS32",
        "ADDF32", "SUBF32", "MULF32", "DIVF32", "INCF32", "DECF32", "NEGF32", "LTS32",  "LES32",  "EQI32",  "NEI32",
        "LTF32",  "LEF32",  "EQF32",  "NEF32",  "LTCMP",  "LECMP",  "EQBOOL", "NEBOOL", "ANDI32", "ORI32",  "XORI32",
        "NTI32",  "NTBOOL", "SLLI32", "SLRI32", "JMP",    "JMPPOS", "JMPNEG", "FENTER", "FLEAVE", "FRET",   "CALL",
        "YIELD",  "MCOPY",  "MZEROS", "SPPSH",  "SPPSHZ", "SPPOP",  "ADDOFS", "ARPSHZ", "ARIDX",  "ARLEN",  "ARPOP",
    };
    return table[type];
}
#pragma dont_inline reset

}
