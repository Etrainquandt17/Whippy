#ifndef SCN_STEP_HERO_MODELDESC_MODELDESC_H
#define SCN_STEP_HERO_MODELDESC_MODELDESC_H

#include "types.h"

namespace dynamics {
class Desc;
}

namespace gobj {
class GearModelDesc;
struct GearAnimDesc;
}

namespace scn {
namespace step {
namespace hero {
namespace modeldesc {

// TODO: the type the Model() functions return. Only the place of its node name table is known.
struct ModelDesc {
    u32 _0[0x15];
    const char* const* mNodeNames;
};

enum NodeKind {
    NODE_HAVE_WEAPON = 18,
    NODE_HAVE_WEAPON_PARENT,
    NODE_HAVE_WEAPON_WEAR_BACK,
};

// TODO: the type the Anim() functions return.
struct AnimDesc;

namespace Kirby {
const ModelDesc& Model();
const AnimDesc& Anim();
}

namespace Meta {
const ModelDesc& Model();
const AnimDesc& Anim();
}

namespace Dedede {
const ModelDesc& Model();
const AnimDesc& Anim();
}

namespace Dee {
const ModelDesc& Model();
const AnimDesc& Anim();
}

namespace Sword {
const gobj::GearModelDesc& SwordModel();
const gobj::GearAnimDesc& SwordAnim();
const char* SwordPath();
const char* HatPath();
const gobj::GearModelDesc& HatModel();
const dynamics::Desc& HatDyna();
}

namespace Whip {
const gobj::GearModelDesc& WhipModel();
const gobj::GearAnimDesc& WhipAnim();
}

namespace Beam {
const gobj::GearModelDesc& StickModel();
const gobj::GearAnimDesc& StickAnim();
const char* StickPath();
const char* HatPath();
const gobj::GearModelDesc& HatModel();
const dynamics::Desc& HatDynaL();
const dynamics::Desc& HatDynaR();
}

namespace Parasol {
const gobj::GearModelDesc& ParasolModel();
const gobj::GearAnimDesc& ParasolAnim();
const char* ParasolPath();
}

namespace Spear {
const gobj::GearModelDesc& SpearModel();
const gobj::GearAnimDesc& SpearAnim();
}

namespace Hammer {
const char* HatPath();
const char* HammerPath();
const gobj::GearModelDesc& HammerModel();
const gobj::GearAnimDesc& HammerAnim();
}

namespace Leaf {
const char* HatPath();
const gobj::GearModelDesc& HatModel();
const dynamics::Desc& HatDynaL();
const dynamics::Desc& HatDynaR();
}

namespace Highjump {
const char* HatPath();
const gobj::GearModelDesc& HatModel();
const dynamics::Desc& HatDynaL();
const dynamics::Desc& HatDynaR();
}

namespace Wing {
const char* HatPath();
const gobj::GearModelDesc& HatModel();
const gobj::GearAnimDesc& HatAnim();
const dynamics::Desc& HatDynaL();
const dynamics::Desc& HatDynaR();
}

namespace Needle {
const char* HatPath();
const gobj::GearModelDesc& HatModel();
const gobj::GearAnimDesc& HatAnim();
const char* NeedleBodyPath();
const gobj::GearModelDesc& NeedleBodyModel();
}

namespace Crash {
const char* HatPath();
const gobj::GearModelDesc& HatModel();
}

namespace Bomb {
const char* HatPath();
const gobj::GearModelDesc& HatModel();
const dynamics::Desc& HatDyna();
const char* GuidePath();
const gobj::GearModelDesc& GuideModel();
const gobj::GearAnimDesc& GuideAnim();
}

namespace Stone {
const char* HatPath();
const gobj::GearModelDesc& BodyModel();
const char* HandPath();
}

namespace Ice {
const char* HatPath();
}

namespace Fire {
const char* HatPath();
const gobj::GearModelDesc& HatModel();
}

namespace Sleep {
const char* HatPath();
const gobj::GearModelDesc& HatModel();
const dynamics::Desc& HatDyna();
}

namespace Tornado {
const char* HatPath();
const gobj::GearModelDesc& HatModel();
const gobj::GearAnimDesc& HatAnim();
}

namespace Mike {
const char* HatPath();
const gobj::GearModelDesc& HatModel();
const char* MikePath();
const gobj::GearModelDesc& MikeModel();
const gobj::GearAnimDesc& MikeAnim();
}

namespace Cutter {
const char* HatPath();
const gobj::GearModelDesc& HatModel();
const char* CutterPath();
}

}}}}  // namespace scn::step::hero::modeldesc

#endif
