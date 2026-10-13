#include "scn/step/weapon/shotzobullet/ModelDesc.h"

#include "scn/step/weapon/ModelDescUtil.h"

namespace scn {
namespace step {
namespace weapon {
namespace shotzobullet {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "ShotzoWeaponM",
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<15>("step/weapon/Shotzo/Shot", "ShotzoBullet", 2, T_NODE_NAMES, 0, 0, 0, 0);
    desc.mModel._18 = hel::common::FixedString<40>("Model");
    return desc;
}

}

}}}}  // namespace scn::step::weapon::shotzobullet
