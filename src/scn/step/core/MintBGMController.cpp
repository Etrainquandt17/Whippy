#include "scn/step/core/MintBGMController.h"

#include "hel/common/PointerWrapper.h"
#include "metafortress.h"
#include "scn/step/core/BGMController.h"

using hel::common::PointerWrapper;

namespace scn {
namespace step {
namespace core {

namespace {

PointerWrapper<BGMController> t_obj;

}

namespace MintBGMController {

void Register(BGMController& obj) {
    t_obj.set(obj);
}

void Unregister(BGMController&) {
    t_obj.reset();
}

void Request(int category, int id, bool flag) {
    t_obj->request(static_cast<BGMCategory>(category), id, flag);
}

void Unrequest(int category) {
    t_obj->unrequest(static_cast<BGMCategory>(category));
}

#define MF_FUNCTION Pause__Q43scn4step4core17MintBGMControllerFi
void Pause(int category) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 key;
    volatile u32 response;
    volatile u32 base;
    u32 word;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  0xD4B9D180
        opword  MF_WORD(0x28)
        opword  MF_WORD(0x2C)
        opword  0xB8E91980
    after1:
        mflr    r28
        lwz     r17, 0x4(r28)
        lwz     r20, 0x8(r28)
        stw     r20, end
        stw     r17, start
    }
    last = end;
    word = start;
    hash = 0;
    word -= 2;
    for (;;) {
        word += 2;
        if (word == last) {
            break;
        }
        hash *= 107;
        hash += *(u16*)word;
    }
    hash ^= hash >> 10;
    asm {
        bl      after2
        opword  MF_WORD(0x80)
        opword  0x13FBD12A
    after2:
        mflr    r20
        lwz     r21, 0x0(r20)
        stw     r21, expected
    }
    hash ^= hash << 20;
    if ((hash ^ expected) != 0) {
        asm {
            bl      after3
            opword  MF_WORD(0xB0)
        after3:
            mflr    r17
            lwz     r27, 0x0(r17)
            stw     r27, -0x4(r1)
            stw     r17, 0x0(r1)
            stw     r27, -0x4(r1)
            stw     r17, -0x8(r1)
            mtlr    r27
            bl      after4
            opword  MF_WORD(0xD4)
            opword  0x74E9FE90
            opword  0x8C373E81
            opword  MF_WORD(0xE0)
        after4:
            mflr    r21
            lwz     r20, 0xC(r21)
            stw     r20, key
            lwz     r20, 0x0(r21)
            stw     r21, base
            stw     r20, offset
        }
        offset = offset + 0x92;
        response = offset ^ key;
        response = response + base;
        asm {
            lwz     r30, response
            mtlr    r30
            blr
        }
    } else {
        t_obj->pause(static_cast<BGMCategory>(category));
    }
}
#undef MF_FUNCTION

void Unpause(int category) {
    t_obj->unpause(static_cast<BGMCategory>(category));
}

}}}}  // namespace scn::step::core::MintBGMController
