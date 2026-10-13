#include "scn/step/weapon/IndiviUtil.h"

#include "metafortress.h"
#include "scn/step/weapon/EffectLocatorModelDesc.h"
#include "scn/step/weapon/airball/ModelDesc.h"
#include "scn/step/weapon/bombbomb/ModelDesc.h"
#include "scn/step/weapon/bowbyarrow/ModelDesc.h"
#include "scn/step/weapon/buraburarope/ModelDesc.h"
#include "scn/step/weapon/combinationairball/ModelDesc.h"
#include "scn/step/weapon/combinationdeeshot/ModelDesc.h"
#include "scn/step/weapon/comothread/ModelDesc.h"
#include "scn/step/weapon/crackershot/ModelDesc.h"
#include "scn/step/weapon/cutter/ModelDesc.h"
#include "scn/step/weapon/dededehammer/ModelDesc.h"
#include "scn/step/weapon/deespear/ModelDesc.h"
#include "scn/step/weapon/enemywaterbullet/ModelDesc.h"
#include "scn/step/weapon/enemywaterbulletwarp/ModelDesc.h"
#include "scn/step/weapon/fattybufferwaterwarp/ModelDesc.h"
#include "scn/step/weapon/foleyleaf/ModelDesc.h"
#include "scn/step/weapon/galactacrystal/ModelDesc.h"
#include "scn/step/weapon/galactarevolutionsword/ModelDesc.h"
#include "scn/step/weapon/gigatzobullet/ModelDesc.h"
#include "scn/step/weapon/glunkbullet/ModelDesc.h"
#include "scn/step/weapon/hammerhammer/ModelDesc.h"
#include "scn/step/weapon/hotheadfire/ModelDesc.h"
#include "scn/step/weapon/hrd3eyelaser/ModelDesc.h"
#include "scn/step/weapon/hrd3laser/ModelDesc.h"
#include "scn/step/weapon/jucklecutter/ModelDesc.h"
#include "scn/step/weapon/landiaburst/ModelDesc.h"
#include "scn/step/weapon/landiacannon/ModelDesc.h"
#include "scn/step/weapon/landiasinglegrandcross/ModelDesc.h"
#include "scn/step/weapon/landiastar/ModelDesc.h"
#include "scn/step/weapon/leafanpollen/ModelDesc.h"
#include "scn/step/weapon/leafcutter/ModelDesc.h"
#include "scn/step/weapon/leafcutter2/ModelDesc.h"
#include "scn/step/weapon/leapershot/ModelDesc.h"
#include "scn/step/weapon/leaperthorn/ModelDesc.h"
#include "scn/step/weapon/liepashot/ModelDesc.h"
#include "scn/step/weapon/lowpericespine/ModelDesc.h"
#include "scn/step/weapon/lupashot/ModelDesc.h"
#include "scn/step/weapon/mahoroablackhole/ModelDesc.h"
#include "scn/step/weapon/mahoroablackholebg/ModelDesc.h"
#include "scn/step/weapon/mahoroaicethorn/ModelDesc.h"
#include "scn/step/weapon/mahoroaicicle/ModelDesc.h"
#include "scn/step/weapon/mahoroalaser/ModelDesc.h"
#include "scn/step/weapon/mahoroaneedle/ModelDesc.h"
#include "scn/step/weapon/mahoroawarphole/ModelDesc.h"
#include "scn/step/weapon/mahoroawarphole2/ModelDesc.h"
#include "scn/step/weapon/mahoroawarpholemagicball/ModelDesc.h"
#include "scn/step/weapon/mahoroawarpneedle/ModelDesc.h"
#include "scn/step/weapon/metalgeneralneedle/ModelDesc.h"
#include "scn/step/weapon/needleshot/ModelDesc.h"
#include "scn/step/weapon/ninjakunai/ModelDesc.h"
#include "scn/step/weapon/owgulffeather/ModelDesc.h"
#include "scn/step/weapon/roahboomerang/ModelDesc.h"
#include "scn/step/weapon/roahbullet/ModelDesc.h"
#include "scn/step/weapon/roahoar/ModelDesc.h"
#include "scn/step/weapon/roahstar/ModelDesc.h"
#include "scn/step/weapon/shotzobullet/ModelDesc.h"
#include "scn/step/weapon/sirkibblecutter/ModelDesc.h"
#include "scn/step/weapon/sleepsnotbubble/ModelDesc.h"
#include "scn/step/weapon/spearspear/ModelDesc.h"
#include "scn/step/weapon/starshotlv1/ModelDesc.h"
#include "scn/step/weapon/starshotlv2/ModelDesc.h"
#include "scn/step/weapon/starshotlv3/ModelDesc.h"
#include "scn/step/weapon/tsukikageshuriken/ModelDesc.h"
#include "scn/step/weapon/vacuumedblock/ModelDesc.h"
#include "scn/step/weapon/waterbigwave/ModelDesc.h"
#include "scn/step/weapon/waterbullet/ModelDesc.h"
#include "scn/step/weapon/waterbulletwarp/ModelDesc.h"
#include "scn/step/weapon/waterunderwater/ModelDesc.h"
#include "scn/step/weapon/whispyairball/ModelDesc.h"
#include "scn/step/weapon/whispyroot/ModelDesc.h"
#include "scn/step/weapon/wingshot/ModelDesc.h"

namespace scn {
namespace step {
namespace weapon {

namespace {

struct IndiviEntry {
    chara::ModelDesc& (*mCreate)();
    chara::ModelDesc& (*mCreateEx)();
};

const IndiviEntry T_INDIVI_TABLE[] = {
    { starshotlv1::ModelDesc::Create, 0 },
    { starshotlv2::ModelDesc::Create, 0 },
    { starshotlv3::ModelDesc::Create, 0 },
    { airball::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { cutter::ModelDesc::Create, 0 },
    { cutter::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { leafcutter::ModelDesc::Create, 0 },
    { leafcutter2::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { whispyairball::ModelDesc::Create, whispyairball::ModelDesc::CreateEx },
    { comothread::ModelDesc::Create, 0 },
    { sirkibblecutter::ModelDesc::Create, 0 },
    { shotzobullet::ModelDesc::Create, 0 },
    { leafanpollen::ModelDesc::Create, 0 },
    { needleshot::ModelDesc::Create, 0 },
    { sleepsnotbubble::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { waterbullet::ModelDesc::Create, 0 },
    { waterbulletwarp::ModelDesc::Create, 0 },
    { waterunderwater::ModelDesc::Create, 0 },
    { waterbigwave::ModelDesc::Create, 0 },
    { bombbomb::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { spearspear::ModelDesc::Create, 0 },
    { hammerhammer::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { wingshot::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { ninjakunai::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { crackershot::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { enemywaterbullet::ModelDesc::Create, 0 },
    { enemywaterbulletwarp::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { glunkbullet::ModelDesc::Create, 0 },
    { gigatzobullet::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { owgulffeather::ModelDesc::Create, 0 },
    { foleyleaf::ModelDesc::Create, 0 },
    { bowbyarrow::ModelDesc::Create, 0 },
    { jucklecutter::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { tsukikageshuriken::ModelDesc::Create, 0 },
    { gigatzobullet::ModelDesc::CreateVolt, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { metalgeneralneedle::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { roahboomerang::ModelDesc::Create, roahboomerang::ModelDesc::CreateEx },
    { roahbullet::ModelDesc::Create, roahbullet::ModelDesc::CreateEx },
    { roahoar::ModelDesc::Create, roahoar::ModelDesc::CreateEx },
    { roahstar::ModelDesc::Create, roahstar::ModelDesc::CreateEx },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { gigatzobullet::ModelDesc::CreateCold, 0 },
    { mahoroaneedle::ModelDesc::Create, mahoroaneedle::ModelDesc::CreateEx },
    { mahoroaneedle::ModelDesc::Create2, mahoroaneedle::ModelDesc::Create2Ex },
    { buraburarope::ModelDesc::Create, 0 },
    { landiastar::ModelDesc::Create, 0 },
    { landiaburst::ModelDesc::Create, 0 },
    { landiacannon::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { mahoroalaser::ModelDesc::Create, mahoroalaser::ModelDesc::CreateEx },
    { whispyroot::ModelDesc::Create, 0 },
    { combinationairball::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { combinationdeeshot::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { mahoroablackhole::ModelDesc::Create, mahoroablackhole::ModelDesc::CreateEx },
    { mahoroablackholebg::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { dededehammer::ModelDesc::Create, 0 },
    { deespear::ModelDesc::Create, 0 },
    { fattybufferwaterwarp::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { mahoroawarphole::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { landiasinglegrandcross::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { vacuumedblock::ModelDesc::CreateStar, 0 },
    { vacuumedblock::ModelDesc::CreateHeavy1x1, 0 },
    { vacuumedblock::ModelDesc::CreateHeavy2x2, 0 },
    { vacuumedblock::ModelDesc::CreateHeavy3x3, 0 },
    { vacuumedblock::ModelDesc::CreateHeavy4x4, 0 },
    { vacuumedblock::ModelDesc::CreateHeavyA1x2x1, 0 },
    { vacuumedblock::ModelDesc::CreateHeavyB1x2x1, 0 },
    { vacuumedblock::ModelDesc::CreateHeavy1x2x3, 0 },
    { vacuumedblock::ModelDesc::CreateHeavy1x3, 0 },
    { vacuumedblock::ModelDesc::CreateHeavy3x1, 0 },
    { vacuumedblock::ModelDesc::CreateHeavy2x4x4x2, 0 },
    { vacuumedblock::ModelDesc::CreateHeavy3x2x1, 0 },
    { liepashot::ModelDesc::Create, 0 },
    { lupashot::ModelDesc::Create, 0 },
    { leapershot::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { leaperthorn::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { lowpericespine::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { galactarevolutionsword::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { galactacrystal::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { mahoroawarphole2::ModelDesc::Create, 0 },
    { mahoroawarpneedle::ModelDesc::Create, 0 },
    { hrd3laser::ModelDesc::Create, 0 },
    { hrd3eyelaser::ModelDesc::Create, 0 },
    { bowbyarrow::ModelDesc::CreateHalcan, 0 },
    { hotheadfire::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { mahoroaicethorn::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { mahoroaicicle::ModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { EffectLocatorModelDesc::Create, 0 },
    { mahoroawarpholemagicball::ModelDesc::Create, 0 },
    { mahoroalaser::ModelDesc::CreateWarpHole, mahoroalaser::ModelDesc::CreateWarpHoleEx },
};

}

#define MF_FUNCTION ModelDesc__Q43scn4step6weapon10IndiviUtilFQ43scn4step6weapon4Kindb
chara::ModelDesc& IndiviUtil::ModelDesc(Kind kind, bool isEx) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0x31A40C61
    after1:
        mflr    r20
        lwz     r19, 0x0(r20)
        stw     r19, expected
        bl      after2
        opword  MF_WORD(0x40)
        opword  0xB8556392
        opword  0xA8CBA480
        opword  MF_WORD(0x4C)
        opword  0x1CE7BF90
        opword  0x8B15950D
    after2:
        mflr    r20
        lwz     r26, 0x0(r20)
        lwz     r14, 0xc(r20)
        stw     r14, end
        stw     r26, start
    }
    limit = end - start;
    base = start;
    hash = 0;
    i = -1;
    while (i != limit - 1) {
        i += 2;
        hash *= 37;
        hash += *(u16*)(base + i - 1);
    }
    hash -= expected;
    if (hash != 0) {
        volatile u32 base2;
        volatile u32 addend;
        volatile u32 offset;
        volatile u32 response;

        asm {
            bl      after3
            opword  0x38DEFA93
            opword  0xC848A291
            opword  MF_WORD(0xC4)
        after3:
            mflr    r29
            lwz     r19, 0x8(r29)
            stw     r19, -0x4(r1)
            stw     r29, 0x0(r1)
            stw     r19, -0x4(r1)
            stw     r29, -0x8(r1)
            mtlr    r19
            bl      after4
            opword  MF_WORD(0xE8)
            opword  0xE0BF3581
            opword  MF_WORD(0xF0)
        after4:
            mflr    r22
            lwz     r17, 0x0(r22)
            lwz     r21, 0x8(r22)
            stw     r21, addend
            stw     r17, offset
            stw     r22, base2
        }
        offset = offset ^ 0xB7;
        response = offset + addend;
        response = response + base2;
        asm {
            lwz     r22, response
            mtlr    r22
            blr
        }
    } else {
        if (isEx && T_INDIVI_TABLE[kind].mCreateEx != 0) {
            return T_INDIVI_TABLE[kind].mCreateEx();
        }
        return T_INDIVI_TABLE[kind].mCreate();
    }
}
#undef MF_FUNCTION

}
}
}
