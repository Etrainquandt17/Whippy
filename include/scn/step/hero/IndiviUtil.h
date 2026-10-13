#ifndef SCN_STEP_HERO_INDIVIUTIL_H
#define SCN_STEP_HERO_INDIVIUTIL_H

#include "hel/math/Vector2.h"
#include "scn/step/hero/Kind.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

class Hero;
class NodeAttach;
struct IndiviParam;

struct NodeAttachParam {
    f32 mOffsetX;
    f32 mOffsetY;
    f32 mOffsetZ;
    f32 mRotateX;
    f32 mRotateY;
    f32 mRotateZ;
    f32 mScale;
};

class IndiviUtil {
public:
    static const IndiviParam& Param(const Hero& hero);
    static f32 Height(Kind kind);
    static f32 CenterOffset(Kind kind);
    static hel::math::Vector2 VacuumAttackerOffset();
    static void InitNodeAttach(NodeAttach& nodeAttach, Kind kind);
    static const char* NodeNameHaveWeapon(Kind kind);
    static const char* NodeNameHaveWeaponParent(Kind kind);
    static const char* NodeNameHaveWeaponWearBack(Kind kind);
    static bool IsKirby(Kind kind);
    static bool IsMeta(Kind kind);
    static bool IsDedede(Kind kind);
    static bool IsDee(Kind kind);
    static bool CanHover(Kind kind);
};

}}}  // namespace scn::step::hero

#endif
