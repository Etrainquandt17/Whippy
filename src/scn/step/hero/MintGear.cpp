#include "scn/step/hero/MintGear.h"

#include "g3d/MintNodeAccessor.h"
#include "gobj/NodeRepos.h"
#include "hel/common/PointerWrapper.h"
#include "metafortress.h"

namespace scn {
namespace step {
namespace hero {

namespace {

hel::common::PointerWrapper<Gear> t_obj;

}

void MintGear::RegisterForce(Gear& obj) {
    t_obj.set(obj);
    if (Obj().isAnimExist()) {
        gobj::MintGearAnim::RegisterForce(Obj().mObj->anim());
    }
}

void MintGear::Unregister() {
    t_obj.reset();
}

MintGear MintGear::Obj() {
    return t_obj->mint();
}

void MintGear::SetVisibility(bool visible) {
    Obj().setVisibility(visible);
}

#define MF_FUNCTION SetNodeVisibility__Q43scn4step4hero8MintGearFUlb
void MintGear::SetNodeVisibility(u32 node, bool visible) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 key;
    volatile u32 base;
    volatile u32 response;
    u32 last;
    u32 i;
    u32 size;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0xDFB9A19A
    after1:
        mflr    r26
        lwz     r27, 0x0(r26)
        stw     r27, expected
    }
    hash = 0;
    asm {
        bl      after2
        opword  MF_WORD(0x44)
        opword  0xF9B57F0C
        opword  0x0AE3700A
        opword  MF_WORD(0x50)
    after2:
        mflr    r18
        lwz     r24, 0xC(r18)
        stw     r24, start
        lwz     r23, 0x0(r18)
        stw     r23, end
    }
    size = start;
    size = end - size + 1;
    i = 1;
    last = end - 1;
    for (;;) {
        if (i == size) {
            break;
        }
        hash += *(u16*)(last - i);
        hash += hash << 10;
        hash ^= hash >> 6;
        i += 2;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    hash = (expected & ~hash) | (hash & ~expected);
    hash += hash * 38;
    if (hash == 0) {
        Obj().setNodeVisibility(node, visible);
    } else {
        asm {
            bl      after3
            opword  MF_WORD(0x104)
        after3:
            mflr    r27
            lwz     r26, 0x0(r27)
            stw     r26, -0x4(r1)
            stw     r27, 0x0(r1)
            stw     r26, -0x4(r1)
            stw     r27, -0x8(r1)
            mtlr    r26
            bl      after4
            opword  MF_WORD(0x128)
            opword  0x18086F80
            opword  0x60D4DE01
            opword  MF_WORD(0x134)
        after4:
            mflr    r17
            lwz     r16, 0x0(r17)
            stw     r17, base
            lwz     r15, 0xC(r17)
            stw     r16, offset
            stw     r15, key
        }
        offset = offset + 0x78;
        key = 0;
        response = offset;
        response = response + base;
        asm {
            lwz     r22, response
            mtlr    r22
            blr
        }
    }
}
#undef MF_FUNCTION

void MintGear::LoadNode(u32 node) {
    g3d::MintNodeAccessor::RegisterForce(t_obj->nodes().at(node));
}

void MintGear::BindEffect() {
    chara::MintEffect::RegisterForce(t_obj->effect());
}

void MintGear::BindEffectWarp() {
    chara::MintEffect::RegisterForce(t_obj->effectWarp());
}

}
}
}
