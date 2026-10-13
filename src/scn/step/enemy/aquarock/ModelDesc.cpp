#include "scn/step/enemy/aquarock/ModelDesc.h"

#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace aquarock {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "TransL",
    "BodyL",
    "FunL",
};

const char* T_NODE_NAMES_SEA[] = {
    "TopL",
    "LotateL",
    "LotateL",
    "LotateL",
};

const gobj::G3DAnimDataReposDesc::Entry* T_ANIM_ENTRIES = 0;

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<71, 0>("step/chara/enemy/AquaRock", "Aquarock", 4, T_NODE_NAMES, 0, T_ANIM_ENTRIES, 7,
                                            T_SCRIPT_ENTRIES);
}

chara::ModelDesc& CreateSea() {
    return ModelDescUtil::CreateTmpl<79, 0>("step/chara/enemy/AquaRockSea", "AquarockSea", 4, T_NODE_NAMES_SEA, 0, T_ANIM_ENTRIES, 7,
                                            T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::aquarock
