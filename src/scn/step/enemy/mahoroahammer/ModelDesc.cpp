#include "scn/step/enemy/mahoroahammer/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroahammer {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "MahoroaHammer.AnimScript.Main.Exec", 0, 0, 0, 0 },
    { "MahoroaHammer.AnimScript.Main.Exec", 0, 0, 0, 0 },
    { "MahoroaHammer.AnimScript.NoAnim.Exec", 0, 0, 0, 0 },
    { "MahoroaHammer.AnimScript.Main.Exec", 0, 0, 0, 0 },
    { "MahoroaHammer.AnimScript.Main.Exec", 0, 0, 0, 0 },
    { "MahoroaHammer.AnimScript.Damage.Exec", 0, 0, 0, 0 },
    { "MahoroaHammer.AnimScript.Damage.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<144, 0>("step/chara/hero/kirby/hammer/Hammer", "MahoroaHammer", 1, T_NODE_NAMES, 0, 0, 7, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::mahoroahammer
