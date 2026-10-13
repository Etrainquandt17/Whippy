#include "scn/step/hero/AbilityManager.h"

#include "metafortress.h"
#include "scn/step/Component.h"
#include "scn/step/carryitem/User.h"
#include "scn/step/hero/AbilityKind.h"
#include "scn/step/hero/Heap.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/hero/beam/Beam.h"
#include "scn/step/hero/bomb/Bomb.h"
#include "scn/step/hero/crash/Crash.h"
#include "scn/step/hero/cutter/Cutter.h"
#include "scn/step/hero/dedede/Dedede.h"
#include "scn/step/hero/dee/Custom.h"
#include "scn/step/hero/dee/Dee.h"
#include "scn/step/hero/fighter/Custom.h"
#include "scn/step/hero/fighter/Fighter.h"
#include "scn/step/hero/fire/Fire.h"
#include "scn/step/hero/hammer/Hammer.h"
#include "scn/step/hero/highjump/Highjump.h"
#include "scn/step/hero/ice/Ice.h"
#include "scn/step/hero/landia/Landia.h"
#include "scn/step/hero/leaf/Leaf.h"
#include "scn/step/hero/meta/Meta.h"
#include "scn/step/hero/mike/Mike.h"
#include "scn/step/hero/needle/Custom.h"
#include "scn/step/hero/needle/Needle.h"
#include "scn/step/hero/ninja/Custom.h"
#include "scn/step/hero/ninja/Ninja.h"
#include "scn/step/hero/parasol/Custom.h"
#include "scn/step/hero/parasol/Parasol.h"
#include "scn/step/hero/sleep/Sleep.h"
#include "scn/step/hero/spark/Custom.h"
#include "scn/step/hero/spark/Spark.h"
#include "scn/step/hero/spear/Custom.h"
#include "scn/step/hero/spear/Spear.h"
#include "scn/step/hero/stone/Stone.h"
#include "scn/step/hero/superbeam/SuperBeam.h"
#include "scn/step/hero/superfire/SuperFire.h"
#include "scn/step/hero/superhammer/SuperHammer.h"
#include "scn/step/hero/superice/Custom.h"
#include "scn/step/hero/superice/SuperIce.h"
#include "scn/step/hero/supersword/Custom.h"
#include "scn/step/hero/supersword/SuperSword.h"
#include "scn/step/hero/sword/Sword.h"
#include "scn/step/hero/tornado/Tornado.h"
#include "scn/step/hero/water/Water.h"
#include "scn/step/hero/whip/Whip.h"
#include "scn/step/hero/wing/Wing.h"
#include "scn/step/info/HeroPanel.h"
#include "std/tr1/reference_wrapper.h"

namespace scn {
namespace step {
namespace hero {

#define MF_FUNCTION initAbility__Q43scn4step4hero14AbilityManagerFi
void AbilityManager::initAbility(int kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 i;
    u32 base;
    u32 limit;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0x281F3D90
        opword  MF_WORD(0x34)
        opword  0xE513740E
        opword  0xC43DA792
    after1:
        mflr    r20
        lwz     r24, 0x0(r20)
        add     r24, r24, r20
        lwz     r25, 0x8(r20)
        stw     r24, start
        add     r25, r25, r24
        stw     r25, end
    }
    limit = end - start + 1;
    i = 1;
    base = start;
    for (; i != limit; i += 2) {
        hash += *(u16*)(base + i - 1);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    asm {
        bl      after2
        opword  MF_WORD(0xA4)
        opword  0xA728258D
    after2:
        mflr    r29
        lwz     r17, 0x0(r29)
        stw     r17, expected
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    reserveChangeAbility(kind, expected != hash);
}
#undef MF_FUNCTION

#define MF_FUNCTION startAbilitySilent__Q43scn4step4hero14AbilityManagerFv
void AbilityManager::startAbilitySilent() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 last;
    u32 i;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x1C)
        opword  0x65EBCC75
    after1:
        mflr    r22
        lwz     r29, 0x0(r22)
        stw     r29, expected
    }
    hash = 0x811C9DC5;
    asm {
        bl      after2
        opword  0x2CDD8002
        opword  0x9ED4740A
        opword  MF_WORD(0x44)
        opword  0x893F520A
        opword  MF_WORD(0x4C)
        opword  0xF028590D
        opword  0xDC707B92
    after2:
        mflr    r22
        lwz     r26, 0x10(r22)
        lwz     r28, 0x8(r22)
        stw     r28, start
        stw     r26, end
    }
    i = 1;
    last = end;
    limit = last - start + 1;
    last = last - 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - i);
        hash *= 0x01000181;
        i += 2;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    startAbilityCore(expected == hash);
}
#undef MF_FUNCTION

#define MF_FUNCTION tryToChangeStateOnDamage__Q43scn4step4hero14AbilityManagerFv
bool AbilityManager::tryToChangeStateOnDamage() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 p;
    u32 stop;
    u32 hash = 0;

    asm {
        bl      after1
        opword  0x30D35B92
        opword  0x86D43304
        opword  MF_WORD(0x28)
        opword  0x1C618780
        opword  0x28EFD693
        opword  MF_WORD(0x34)
        opword  0xE0B38C80
    after1:
        mflr    r27
        lwz     r23, 0x8(r27)
        lwz     r15, 0x14(r27)
        stw     r23, end
        stw     r15, start
    }
    p = start;
    stop = end;
    asm {
        bl      after2
        opword  MF_WORD(0x5C)
        opword  0x32156E7A
    after2:
        mflr    r14
        lwz     r25, 0x0(r14)
        stw     r25, expected
    }
    for (; p != stop; p += 2) {
        hash += *(u16*)p;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash - expected != 0 || !haveAbility()) {
        return false;
    }
    if (hash - expected != 0 || _4C) {
        return false;
    }
    if (hash - expected != 0 || mHero.carryItemUser().isItemExist()) {
        return false;
    }
    return mAbility->tryToChangeStateOnDamage();
}
#undef MF_FUNCTION

#define MF_FUNCTION setFuel__Q43scn4step4hero14AbilityManagerFUl
void AbilityManager::setFuel(u32 fuel) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 i;
    u32 last;
    u32 limit;

    hash = 0x811C9E07;
    asm {
        bl      after1
        opword  0x70D6FE93
        opword  0xC4CE0290
        opword  MF_WORD(0x38)
        opword  MF_WORD(0x3C)
        opword  0x87446F00
    after1:
        mflr    r27
        lwz     r19, 0xc(r27)
        stw     r19, start
        lwz     r18, 0x8(r27)
        stw     r18, end
    }
    mFuel = fuel;
    i = 1;
    last = end;
    limit = last - start + 1;
    for (; i != limit; i += 2) {
        hash ^= *(u16*)(last - 1 - i);
        hash *= 0x010001A7;
    }
    if (mFuel > mFuelMax) {
        mFuel = mFuelMax;
    }
    asm {
        bl      after2
        opword  MF_WORD(0xB4)
        opword  0x1C57EDBC
    after2:
        mflr    r16
        lwz     r24, 0x0(r16)
        stw     r24, expected
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash - expected != 0 || mFuelMax != 0) {
        mHero.infoHeroPanel().spGaugeSetRate(f32(mFuel) / f32(mFuelMax));
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION initAbilityCore__Q43scn4step4hero14AbilityManagerFi
void AbilityManager::initAbilityCore(int kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 i;
    u32 limit;
    u32 last;

    hash = 0xBF;
    asm {
        bl      after1
        opword  0xBC415F90
        opword  0xC5E3B207
        opword  MF_WORD(0x34)
        opword  MF_WORD(0x38)
        opword  0xE8EEFA91
    after1:
        mflr    r15
        lwz     r23, 0x8(r15)
        lwz     r24, 0xc(r15)
        stw     r23, end
        stw     r24, start
    }
    limit = end - start + 1;
    last = end;
    clearAbilityCore(false);
    i = -1;
    const u32& base = last - 1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(base - i);
    }
    asm {
        bl      after2
        opword  MF_WORD(0xA8)
        opword  0xD44AE9F0
    after2:
        mflr    r22
        lwz     r28, 0x0(r22)
        stw     r28, expected
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    if ((hash - expected == 0 || haveAbility()) && _1C) {
        return;
    }
    mHero.heap().flipGearAllocDir();
    mKind = kind;
    switch (kind) {
    case ABILITY_KIND_NORMAL:
        break;
    case ABILITY_KIND_SWORD:
        mAbility.constructE<sword::Sword>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_CUTTER:
        mAbility.constructE<cutter::Cutter>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_LEAF:
        mAbility.constructE<leaf::Leaf>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_WHIP:
        mAbility.constructE<whip::Whip>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_FIRE:
        mAbility.constructE<fire::Fire>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_NEEDLE:
        mAbility.constructE<needle::Needle>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_BEAM:
        mAbility.constructE<beam::Beam>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_SPARK:
        mAbility.constructE<spark::Spark>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_STONE:
        mAbility.constructE<stone::Stone>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_SLEEP:
        mAbility.constructE<sleep::Sleep>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_PARASOL:
        mAbility.constructE<parasol::Parasol>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_WATER:
        mAbility.constructE<water::Water>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_HIGHJUMP:
        mAbility.constructE<highjump::Highjump>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_TORNADO:
        mAbility.constructE<tornado::Tornado>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_BOMB:
        mAbility.constructE<bomb::Bomb>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_SPEAR:
        mAbility.constructE<spear::Spear>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_HAMMER:
        mAbility.constructE<hammer::Hammer>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_ICE:
        mAbility.constructE<ice::Ice>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_WING:
        mAbility.constructE<wing::Wing>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_NINJA:
        mAbility.constructE<ninja::Ninja>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_FIGHTER:
        mAbility.constructE<fighter::Fighter>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_CRASH:
        mAbility.constructE<crash::Crash>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_MIKE:
        mAbility.constructE<mike::Mike>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_LANDIA:
        mAbility.constructE<landia::Landia>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_SUPER_SWORD:
        mAbility.constructE<supersword::SuperSword>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_SUPER_FIRE:
        mAbility.constructE<superfire::SuperFire>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_SUPER_BEAM:
        mAbility.constructE<superbeam::SuperBeam>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_SUPER_HAMMER:
        mAbility.constructE<superhammer::SuperHammer>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_SUPER_ICE:
        mAbility.constructE<superice::SuperIce>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case 30:
        mAbility.constructE<mike::Mike>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case 31:
        mAbility.constructE<mike::Mike>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_META:
        mAbility.constructE<meta::Meta>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_DEDEDE:
        mAbility.constructE<dedede::Dedede>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_DEE:
        mAbility.constructE<dee::Dee>(std::tr1::ref(mComponent), std::tr1::ref(mHero));
        break;
    default:
        mKind = ABILITY_KIND_NORMAL;
        break;
    }
    if (hash - expected == 0 || isSuper()) {
        mHero.comp().heroManager().clearOthersSuperAbility(mHero.padChan());
    }
    switch (kind) {
    case ABILITY_KIND_NEEDLE:
        mCustom.constructE<needle::Custom>(std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_SPARK:
        mCustom.constructE<spark::Custom>(std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_PARASOL:
        mCustom.constructE<parasol::Custom>(std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_SPEAR:
        mCustom.constructE<spear::Custom>(std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_NINJA:
        mCustom.constructE<ninja::Custom>(std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_FIGHTER:
        mCustom.constructE<fighter::Custom>(std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_SUPER_SWORD:
        mCustom.constructE<supersword::Custom>(std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_SUPER_ICE:
        mCustom.constructE<superice::Custom>(std::tr1::ref(mHero));
        break;
    case ABILITY_KIND_DEE:
        mCustom.constructE<dee::Custom>(std::tr1::ref(mHero));
        break;
    default:
        mCustom.constructE<AbilityCustomBase>(std::tr1::ref(mHero));
        break;
    }
}
#undef MF_FUNCTION

}
}
}
