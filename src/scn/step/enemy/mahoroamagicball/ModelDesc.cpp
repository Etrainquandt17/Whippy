#include "scn/step/enemy/mahoroamagicball/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "MahoroaMagicBall.AnimScript.Main.Exec", 0, 0, 0, 0 },
    { "MahoroaMagicBall.AnimScript.Main.Exec", 0, 0, 0, 0 },
    { "MahoroaMagicBall.AnimScript.NoAnim.Exec", 0, 0, 0, 0 },
    { "MahoroaMagicBall.AnimScript.Main.Exec", 0, 0, 0, 0 },
    { "MahoroaMagicBall.AnimScript.Main.Exec", 0, 0, 0, 0 },
    { "MahoroaMagicBall.AnimScript.Damage.Exec", 0, 0, 0, 0 },
    { "MahoroaMagicBall.AnimScript.Damage.Exec", 0, 0, 0, 0 },
    { "MahoroaMagicBall.AnimScript.Start.Exec", 0, 0, 0, 0 },
    { "MahoroaMagicBall.AnimScript.Main.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<134, 0>("step/weapon/common/EffectLocator", "MahoroaMagicBall", 1, T_NODE_NAMES, 0, 0, 9, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::mahoroamagicball
