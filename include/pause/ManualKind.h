#ifndef PAUSE_MANUALKIND_H
#define PAUSE_MANUALKIND_H

namespace pause {

// Named after the ability each stands for in scn::step::hero::AbilityKindUtil's T_MANUAL_KIND_TABLE.
enum ManualKind {
    MANUAL_KIND_NORMAL,
    // TODO: what AbilityKindUtil::ToManualKind gives for no ability when either of its flags is set.
    MANUAL_KIND_1,
    MANUAL_KIND_SWORD,
    MANUAL_KIND_CUTTER,
    MANUAL_KIND_LEAF,
    MANUAL_KIND_WHIP,
    MANUAL_KIND_FIRE,
    MANUAL_KIND_NEEDLE,
    MANUAL_KIND_BEAM,
    MANUAL_KIND_SPARK,
    MANUAL_KIND_STONE,
    MANUAL_KIND_SLEEP,
    MANUAL_KIND_PARASOL,
    MANUAL_KIND_WATER,
    MANUAL_KIND_HIGHJUMP,
    MANUAL_KIND_TORNADO,
    MANUAL_KIND_BOMB,
    MANUAL_KIND_SPEAR,
    MANUAL_KIND_HAMMER,
    MANUAL_KIND_ICE,
    MANUAL_KIND_WING,
    MANUAL_KIND_NINJA,
    MANUAL_KIND_FIGHTER,
    MANUAL_KIND_CRASH,
    MANUAL_KIND_MIKE,
    MANUAL_KIND_LANDIA,
    MANUAL_KIND_SUPER_SWORD,
    MANUAL_KIND_SUPER_FIRE,
    MANUAL_KIND_SUPER_BEAM,
    MANUAL_KIND_SUPER_HAMMER,
    MANUAL_KIND_SUPER_ICE,
    MANUAL_KIND_META,
    MANUAL_KIND_DEDEDE,
    MANUAL_KIND_DEE,
    MANUAL_KIND_34,
    // TODO: stands for no manual; the pause frame then gets no ability icon.
    MANUAL_KIND_35,
};

}  // namespace pause

#endif
