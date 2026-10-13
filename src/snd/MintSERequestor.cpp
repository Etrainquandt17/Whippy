#include "snd/MintSERequestor.h"

#include "hel/common/PointerWrapper.h"
#include "metafortress.h"
#include "snd/SERequestor.h"

namespace snd {

namespace {

hel::common::PointerWrapper<SERequestor> t_obj;

}

namespace MintSERequestor {

void RegisterForce(SERequestor& obj) {
    t_obj.set(obj);
}

void Unregister() {
    t_obj.reset();
}

void Start(u32 id) {
    t_obj->start(id);
}

#define MF_FUNCTION Stop__Q23snd15MintSERequestorFv
void Stop() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 base;
    volatile u32 key;
    volatile u32 offset;
    u32 word;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  0xF1C92701
        opword  MF_WORD(0x24)
        opword  0x02DB7209
        opword  0x484CE793
        opword  MF_WORD(0x30)
    after1:
        mflr    r14
        lwz     r29, 0x4(r14)
        lwz     r26, 0x10(r14)
        stw     r26, end
        stw     r29, start
    }
    hash = 0x811C9DDB;
    asm {
        bl      after2
        opword  MF_WORD(0x54)
        opword  0xE8FC93B8
    after2:
        mflr    r29
        lwz     r24, 0x0(r29)
        stw     r24, expected
    }
    word = start;
    last = end;
    for (;;) {
        if (word == last) {
            break;
        }
        hash ^= *(u16*)word;
        hash *= 0x01000193;
        word += 2;
    }
    if (hash == expected) {
        t_obj->stop();
    } else {
        asm {
            bl      after3
            opword  0xBC8BB380
            opword  MF_WORD(0xB4)
        after3:
            mflr    r14
            lwz     r20, 0x4(r14)
            stw     r20, -0x4(r1)
            stw     r14, 0x0(r1)
            stw     r20, -0x4(r1)
            stw     r14, -0x8(r1)
            mtlr    r20
            bl      after4
            opword  MF_WORD(0xD8)
            opword  0xA41CC092
            opword  MF_WORD(0xE0)
        after4:
            mflr    r25
            lwz     r18, 0x8(r25)
            stw     r18, key
            lwz     r18, 0x0(r25)
            stw     r25, base
            stw     r18, offset
        }
        offset = offset + 0x7E;
        response = offset ^ key;
        response = response + base;
        asm {
            lwz     r19, response
            mtlr    r19
            blr
        }
    }
}
#undef MF_FUNCTION

}}  // namespace snd::MintSERequestor
