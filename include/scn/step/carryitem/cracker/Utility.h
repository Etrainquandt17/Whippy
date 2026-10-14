#ifndef SCN_STEP_CARRYITEM_CRACKER_UTILITY_H
#define SCN_STEP_CARRYITEM_CRACKER_UTILITY_H

#include "scn/step/carryitem/CarryItem.h"

namespace scn {
namespace step {
namespace carryitem {
namespace cracker {

enum AnimKind {
    ANIM_KIND_SHOOT,
    ANIM_KIND_CRASH,
    ANIM_KIND_BLUE,
    ANIM_KIND_YELLOW,
    ANIM_KIND_RED,
};

class Utility {
public:
    static bool IsWarn(CarryItem& carryItem);
    static bool IsDanger(CarryItem& carryItem);
    static bool IsBroken(CarryItem& carryItem);
    static f32 UpdateFlash(CarryItem& carryItem, f32 angle);
    static void StartSubAnim(CarryItem& carryItem, AnimKind kind);
    static void ClearSubAnim(CarryItem& carryItem);
    static void StartFlashAnim(CarryItem& carryItem);
    static void UpdateFlashAnim(CarryItem& carryItem);
};

}}}}  // namespace scn::step::carryitem::cracker

#endif
