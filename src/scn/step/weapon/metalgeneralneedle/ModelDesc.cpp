#include "scn/step/weapon/metalgeneralneedle/ModelDesc.h"

#include "scn/step/weapon/ModelDescUtil.h"

namespace scn {
namespace step {
namespace weapon {
namespace metalgeneralneedle {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

const gobj::G3DAnimDataReposDesc::Entry* T_ANIM_ENTRIES = 0;

const gobj::ScriptDesc::Entry* T_SCRIPT_ENTRIES = 0;

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<62>("step/weapon/metalgeneral/Needle", "MetalGeneralNeedle", 1, T_NODE_NAMES, 0, T_ANIM_ENTRIES, 0, T_SCRIPT_ENTRIES);
    desc.mModel._18 = hel::common::FixedString<40>("TopL");
    return desc;
}

}

}
}
}
}
