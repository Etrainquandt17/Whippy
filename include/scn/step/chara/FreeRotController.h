#ifndef SCN_STEP_CHARA_FREEROTCONTROLLER_H
#define SCN_STEP_CHARA_FREEROTCONTROLLER_H

#include "hel/math/Direction3.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace chara {

// TODO: the size and the members behind the first two are not known.
class FreeRotController {
public:
    FreeRotController();

    void update(const hel::math::Vector3& dir);
    hel::math::Matrix34 getRotMtx() const;

private:
    hel::math::Direction3 mDir;
    f32 _24;
};

}}}  // namespace scn::step::chara

#endif
