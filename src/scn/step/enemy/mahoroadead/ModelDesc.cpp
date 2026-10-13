#include "scn/step/enemy/mahoroadead/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroadead {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "HeadJ",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Wait2", 0 },
    { "TalkRegretStart", 0 },
    { "TalkRegret", 0 },
    { "TalkRegretEnd", 0 },
    { "TalkPointing", 0 },
    { "Death", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "MahoroaDead.AnimScript.Wait.Exec", 0, 0, 0, 0 },
    { "MahoroaDead.AnimScript.Fall.Exec", 0, 0, 0, 0 },
    { "MahoroaDead.AnimScript.Landing.Exec", 0, 0, 0, 0 },
    { "MahoroaDead.AnimScript.Walk.Exec", 0, 0, 0, 0 },
    { "MahoroaDead.AnimScript.Fly.Exec", 0, 0, 0, 0 },
    { "MahoroaDead.AnimScript.Damage.Exec", 0, 0, 0, 0 },
    { "MahoroaDead.AnimScript.DamageEtc.Exec", 0, 0, 0, 0 },
    { "MahoroaDead.AnimScript.Dead.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<145, 0>("step/chara/enemy/Mahoroa", "MahoroaDead", 2, T_NODE_NAMES, 7, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::mahoroadead
