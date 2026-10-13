#ifndef SCN_STEP_CHARA_LANDCONSTRAINT_H
#define SCN_STEP_CHARA_LANDCONSTRAINT_H

#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace chara {

class MapCollResult;

// TODO: members, the constructor and the other functions.
class LandConstraint {
public:
    // TODO: name the modes.
    enum Mode {
        MODE_0,
        MODE_1,
        MODE_2,
        MODE_3,
        MODE_4,
    };

    void resetMode();
    void setMode(Mode mode);
    void update(const MapCollResult& result);
    void update(const MapCollResult& result, f32);
    bool isConstraintFloor() const;
    bool isConstraintWallFront() const;
    bool isConstraintRoof() const;
    hel::math::Vector2 prevVelocity() const;
};

}}}  // namespace scn::step::chara

#endif
