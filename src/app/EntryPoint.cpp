#include "app/EntryPoint.h"

#include "app/Application.h"
#include "app/System.h"
#include "mem/Memory.h"
#include "metafortress.h"
#include "types.h"

namespace app {

#define MF_FUNCTION Run__Q23app10EntryPointFb
void EntryPoint::Run(bool flag) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u16* word;
    u16* last;

    asm {
        bl      after1
        opword  MF_WORD(0x1C)
        opword  0x3261B8D7
    after1:
        mflr    r28
        lwz     r16, 0x0(r28)
        stw     r16, expected
    }
    hash = 0;
    mem::Memory::SetupIfNotSetup();
    asm {
        bl      after2
        opword  0x950ED10D
        opword  0x5CF8F292
        opword  MF_WORD(0x44)
        opword  0x1C165E81
        opword  0xCFD24D0C
        opword  MF_WORD(0x50)
        opword  0xB54CD506
        opword  0x33BD3004
    after2:
        mflr    r30
        lwz     r18, 0x14(r30)
        lwz     r27, 0x8(r30)
        stw     r27, start
        stw     r18, end
    }
    last = (u16*)end;
    word = (u16*)start;
    System system;
    for (;;) {
        if (word == last) {
            break;
        }
        hash += *word;
        hash += hash << 10;
        hash ^= hash >> 6;
        word++;
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    Application::Run(system, flag);
    hash ^= hash >> 17;
    hash += hash << 5;
    while (hash - expected != 0) {
    }
}
#undef MF_FUNCTION

}
