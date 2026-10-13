#ifndef SCN_STEP_CHARA_MOVEALGORITHMVACUUMRECEIVE_H
#define SCN_STEP_CHARA_MOVEALGORITHMVACUUMRECEIVE_H

#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "types.h"

namespace scn {
namespace step {
namespace chara {

// TODO: members.
class MoveAlgorithmVacuumReceive {
public:
    MoveAlgorithmVacuumReceive();

    void init(const hel::math::Vector2& offset, const hel::math::Vector2& dir, f32, u32 time);
    void update();
    bool isEnd() const;
    f32 getScale() const;
    hel::math::Vector2 getNextOffs() const;
    hel::math::Matrix34 getRotMtx() const;

private:
    u32 _0[0x1D];
};

}
}
}

#endif
