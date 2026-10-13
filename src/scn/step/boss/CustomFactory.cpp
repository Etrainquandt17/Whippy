#include "scn/step/boss/CustomFactory.h"

#include "scn/step/boss/Boss.h"
#include "scn/step/boss/CustomBase.h"
#include "scn/step/boss/ICustom.h"
#include "scn/step/boss/bonkers/Custom.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/dubior/Custom.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/boss/gigantedge/Custom.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/grandlowper/Custom.h"
#include "scn/step/boss/hrd3/Custom.h"
#include "scn/step/boss/hrd3pilot/Custom.h"
#include "scn/step/boss/kingsdoo/Custom.h"
#include "scn/step/boss/landia/Custom.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/mahoroabattle1/Custom.h"
#include "scn/step/boss/mahoroabattle2/Custom.h"
#include "scn/step/boss/mahoroaroah/Custom.h"
#include "scn/step/boss/metalgeneral/Custom.h"
#include "scn/step/boss/moundeath/Custom.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/boss/watergalboros/Custom.h"
#include "scn/step/boss/whispy/Custom.h"
#include "scn/step/boss/zankibble/Custom.h"
#include "scn/step/enemy/ICustom.h"
#include "std/tr1/reference_wrapper.h"

namespace hel {
namespace common {

// TODO: each of these belongs in the header of its class. The original emits them in every unit that
// includes one, in the order of the includes, and the link keeps the copies of this unit.
#define CUSTOM_RUNTIME_TYPE_INFO(T) \
    template <> \
    const RuntimeTypeInfo& RuntimeTypeInfoImpl<T>() { \
        static RuntimeTypeInfo ti(&RuntimeTypeInfoImpl<scn::step::boss::ICustom>(), RuntimeTypeInfo::NoName()); \
        return ti; \
    }

CUSTOM_RUNTIME_TYPE_INFO(scn::step::boss::bonkers::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::boss::dubior::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::boss::doubter::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::boss::fattybuffer::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::boss::galactaknight::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::boss::gigantedge::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::boss::goliath::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::boss::grandlowper::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::boss::hrd3pilot::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::boss::hrd3::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::boss::kingsdoo::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::boss::landia::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::boss::lowper::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::boss::mahoroabattle1::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::boss::mahoroabattle2::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::boss::mahoroaroah::Custom)
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::ICustom>() {
    static RuntimeTypeInfo ti(0, RuntimeTypeInfo::NoName());
    return ti;
}

CUSTOM_RUNTIME_TYPE_INFO(scn::step::boss::metalgeneral::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::boss::moundeath::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::boss::roah::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::boss::watergalboros::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::boss::whispy::Custom)
CUSTOM_RUNTIME_TYPE_INFO(scn::step::boss::zankibble::Custom)

#undef CUSTOM_RUNTIME_TYPE_INFO

}
}

namespace scn {
namespace step {
namespace boss {

void CustomFactory::Create(Boss& boss, mem::ExplicitScopedPtr<ICustom>& custom) {
    switch (boss.kind()) {
    case map::BinBossKind_Bonkers:
        custom.constructE<bonkers::Custom>(std::tr1::ref(boss));
        break;
    case map::BinBossKind_Doubter:
        custom.constructE<doubter::Custom>(std::tr1::ref(boss));
        break;
    case map::BinBossKind_Dubior:
        custom.constructE<dubior::Custom>(std::tr1::ref(boss));
        break;
    case map::BinBossKind_Fattybuffer:
        custom.constructE<fattybuffer::Custom>(std::tr1::ref(boss));
        break;
    case map::BinBossKind_Galactaknight:
        custom.constructE<galactaknight::Custom>(std::tr1::ref(boss));
        break;
    case map::BinBossKind_Gigantedge:
        custom.constructE<gigantedge::Custom>(std::tr1::ref(boss));
        break;
    case map::BinBossKind_Goliath:
        custom.constructE<goliath::Custom>(std::tr1::ref(boss));
        break;
    case map::BinBossKind_Grandlowper:
        custom.constructE<grandlowper::Custom>(std::tr1::ref(boss));
        break;
    case map::BinBossKind_Hrd3:
        custom.constructE<hrd3::Custom>(std::tr1::ref(boss));
        break;
    case map::BinBossKind_Hrd3pilot:
        custom.constructE<hrd3pilot::Custom>(std::tr1::ref(boss));
        break;
    case map::BinBossKind_Kingsdoo:
        custom.constructE<kingsdoo::Custom>(std::tr1::ref(boss));
        break;
    case map::BinBossKind_Landia:
        custom.constructE<landia::Custom>(std::tr1::ref(boss));
        break;
    case map::BinBossKind_Lowper:
        custom.constructE<lowper::Custom>(std::tr1::ref(boss));
        break;
    case map::BinBossKind_Mahoroabattle1:
        custom.constructE<mahoroabattle1::Custom>(std::tr1::ref(boss));
        break;
    case map::BinBossKind_Mahoroabattle2:
        custom.constructE<mahoroabattle2::Custom>(std::tr1::ref(boss));
        break;
    case map::BinBossKind_Mahoroaroah:
        custom.constructE<mahoroaroah::Custom>(std::tr1::ref(boss));
        break;
    case map::BinBossKind_Metalgeneral:
        custom.constructE<metalgeneral::Custom>(std::tr1::ref(boss));
        break;
    case map::BinBossKind_Moundeath:
        custom.constructE<moundeath::Custom>(std::tr1::ref(boss));
        break;
    case map::BinBossKind_Roah:
        custom.constructE<roah::Custom>(std::tr1::ref(boss));
        break;
    case map::BinBossKind_Watergalboros:
        custom.constructE<watergalboros::Custom>(std::tr1::ref(boss));
        break;
    case map::BinBossKind_Whispy:
        custom.constructE<whispy::Custom>(std::tr1::ref(boss));
        break;
    case map::BinBossKind_Zankibble:
        custom.constructE<zankibble::Custom>(std::tr1::ref(boss));
        break;
    default:
        custom.constructE<CustomBase>(std::tr1::ref(boss));
        break;
    }
}

}
}
}
