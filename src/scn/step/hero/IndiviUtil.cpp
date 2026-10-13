#include "scn/step/hero/IndiviUtil.h"

#include "mintglue/VectorInline.h"
#include "param/JITParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/NodeAttach.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/modeldesc/ModelDesc.h"

// TODO: inline in the original; they belong in xdata/XData.h, which declares them out of line for the
// units that call them.
namespace xdata {

inline bool XData::isValidData() const {
    return isValidEndian() && static_cast<const u32*>(mData)[2] >= 0x10;
}

inline const void* XData::dataHeadAddress() const {
    return isValidData() ? static_cast<const u8*>(mData) + 0x10 : 0;
}

}

namespace scn {
namespace step {
namespace hero {

const IndiviParam& IndiviUtil::Param(const Hero& hero) {
    switch (hero.kind()) {
    case KIND_KIRBY_0:
    case KIND_KIRBY_1:
    case KIND_KIRBY_2:
    case KIND_KIRBY_3:
        return hero.param().indiviKirby();
    case KIND_META:
        return hero.param().indiviMeta();
    case KIND_DEDEDE:
        return hero.param().indiviDedede();
    case KIND_DEE:
        return hero.param().indiviDee();
    default:
        return hero.param().indiviKirby();
    }
}

f32 IndiviUtil::Height(Kind kind) {
    switch (kind) {
    case KIND_KIRBY_0:
    case KIND_KIRBY_1:
    case KIND_KIRBY_2:
    case KIND_KIRBY_3:
        return 1.0f;
    case KIND_META:
        return 1.0f;
    case KIND_DEDEDE:
        return 1.7f;
    case KIND_DEE:
        return 1.0f;
    default:
        return 1.0f;
    }
}

f32 IndiviUtil::CenterOffset(Kind kind) {
    switch (kind) {
    case KIND_KIRBY_0:
    case KIND_KIRBY_1:
    case KIND_KIRBY_2:
    case KIND_KIRBY_3:
        return 0.5f;
    case KIND_META:
        return 0.5f;
    case KIND_DEDEDE:
        return 0.75f;
    case KIND_DEE:
        return 0.5f;
    default:
        return 0.5f;
    }
}

hel::math::Vector2 IndiviUtil::VacuumAttackerOffset() {
    return hel::math::Vector2(0.0f, 0.75f);
}

void IndiviUtil::InitNodeAttach(NodeAttach& nodeAttach, Kind kind) {
    switch (kind) {
    case KIND_META: {
        param::JITParam param("step/hero/nodeattach/Meta");
        const NodeAttachParam& data = param.data<NodeAttachParam>();
        nodeAttach.setOffset(hel::math::Vector3(data.mOffsetX, data.mOffsetY, data.mOffsetZ));
        nodeAttach.setRotate(hel::math::Vector3(data.mRotateX, data.mRotateY, data.mRotateZ));
        nodeAttach.setScale(data.mScale);
        break;
    }
    case KIND_DEDEDE: {
        param::JITParam param("step/hero/nodeattach/Dedede");
        const NodeAttachParam& data = param.data<NodeAttachParam>();
        nodeAttach.setOffset(hel::math::Vector3(data.mOffsetX, data.mOffsetY, data.mOffsetZ));
        nodeAttach.setRotate(hel::math::Vector3(data.mRotateX, data.mRotateY, data.mRotateZ));
        nodeAttach.setScale(data.mScale);
        break;
    }
    case KIND_DEE: {
        param::JITParam param("step/hero/nodeattach/Dee");
        const NodeAttachParam& data = param.data<NodeAttachParam>();
        nodeAttach.setOffset(hel::math::Vector3(data.mOffsetX, data.mOffsetY, data.mOffsetZ));
        nodeAttach.setRotate(hel::math::Vector3(data.mRotateX, data.mRotateY, data.mRotateZ));
        nodeAttach.setScale(data.mScale);
        break;
    }
    default:
        break;
    }
}

const char* IndiviUtil::NodeNameHaveWeapon(Kind kind) {
    switch (kind) {
    case KIND_META:
        return modeldesc::Meta::Model().mNodeNames[modeldesc::NODE_HAVE_WEAPON];
    case KIND_DEDEDE:
        return modeldesc::Dedede::Model().mNodeNames[modeldesc::NODE_HAVE_WEAPON];
    case KIND_DEE:
        return modeldesc::Dee::Model().mNodeNames[modeldesc::NODE_HAVE_WEAPON];
    default:
        return "";
    }
}

const char* IndiviUtil::NodeNameHaveWeaponParent(Kind kind) {
    switch (kind) {
    case KIND_META:
        return modeldesc::Meta::Model().mNodeNames[modeldesc::NODE_HAVE_WEAPON_PARENT];
    case KIND_DEDEDE:
        return modeldesc::Dedede::Model().mNodeNames[modeldesc::NODE_HAVE_WEAPON_PARENT];
    case KIND_DEE:
        return modeldesc::Dee::Model().mNodeNames[modeldesc::NODE_HAVE_WEAPON_PARENT];
    default:
        return "";
    }
}

const char* IndiviUtil::NodeNameHaveWeaponWearBack(Kind kind) {
    switch (kind) {
    case KIND_META:
        return modeldesc::Meta::Model().mNodeNames[modeldesc::NODE_HAVE_WEAPON_WEAR_BACK];
    case KIND_DEDEDE:
        return modeldesc::Dedede::Model().mNodeNames[modeldesc::NODE_HAVE_WEAPON_WEAR_BACK];
    case KIND_DEE:
        return modeldesc::Dee::Model().mNodeNames[modeldesc::NODE_HAVE_WEAPON_WEAR_BACK];
    default:
        return "";
    }
}

bool IndiviUtil::IsKirby(Kind kind) {
    return static_cast<u32>(kind) <= KIND_KIRBY_3;
}

bool IndiviUtil::IsMeta(Kind kind) {
    return kind == KIND_META;
}

bool IndiviUtil::IsDedede(Kind kind) {
    return kind == KIND_DEDEDE;
}

bool IndiviUtil::IsDee(Kind kind) {
    return kind == KIND_DEE;
}

// TODO: the original calls both functions here although each has this one caller in the unit; why it does
// not expand them is not known.
#pragma dont_inline on
bool IndiviUtil::CanHover(Kind kind) {
    if (IsKirby(kind)) {
        return true;
    }
    return IsDedede(kind);
}
#pragma dont_inline reset

}}}  // namespace scn::step::hero
