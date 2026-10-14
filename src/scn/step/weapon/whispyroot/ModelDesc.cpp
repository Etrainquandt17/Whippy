#include "scn/step/weapon/whispyroot/ModelDesc.h"

#include "scn/step/weapon/ModelDescUtil.h"

using hel::common::FixedString;

namespace scn {
namespace step {
namespace weapon {
namespace whispyroot {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<86>("step/weapon/whispy/Root", "WhispyRoot", 1, T_NODE_NAMES, 0, 0, 0, 0);
    desc.mModel._18 = FixedString<40>("TopL");
    return desc;
}

}

}}}}  // namespace scn::step::weapon::whispyroot
