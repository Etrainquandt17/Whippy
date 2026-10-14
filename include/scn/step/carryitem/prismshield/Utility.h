#ifndef SCN_STEP_CARRYITEM_PRISMSHIELD_UTILITY_H
#define SCN_STEP_CARRYITEM_PRISMSHIELD_UTILITY_H

#include "scn/step/carryitem/CarryItem.h"

namespace scn {
namespace step {
namespace carryitem {
namespace prismshield {

enum AnimKind {
    ANIM_KIND_WAIT,
    ANIM_KIND_ATTACK_START,
    ANIM_KIND_ATTACK,
    ANIM_KIND_BLUE,
    ANIM_KIND_YELLOW,
    ANIM_KIND_RED,
};

class Utility {
public:
    static bool IsWarn(CarryItem& carryItem);
    static bool IsDanger(CarryItem& carryItem);
    static void StartAnim(CarryItem& carryItem, AnimKind kind);
    static void StartFlash(CarryItem& carryItem);
    static void UpdateFlash(CarryItem& carryItem);
    static f32 UpdateFlash(CarryItem& carryItem, f32 angle);
};

}}}}  // namespace scn::step::carryitem::prismshield

#endif
