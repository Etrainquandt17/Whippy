#ifndef SCN_STEP_GIMMICK_CUTROPESTEP_CUTROPESTEP_H
#define SCN_STEP_GIMMICK_CUTROPESTEP_CUTROPESTEP_H

#include "g3d/ResFileAccessor.h"
#include "g3d/StdModel.h"
#include "hel/math/Vector2.h"
#include "scn/step/gimmick/ParamAccessor.h"
#include "types.h"
#include "util/FrameCounter.h"

namespace scn {
namespace step {

class Component;

namespace gimmick {
namespace cutropestep {

struct Param {
    f32 _0;
    u32 _4;
};

class CutRopeStep {
public:
    class RestRope {
    public:
        RestRope(CutRopeStep& owner, u32 index);

    private:
        CutRopeStep& mOwner;
        u32 _4;
        hel::math::Vector2 _8;
        g3d::StdModel _10;
        util::FrameCounter _1BC;
    };

    hel::math::Vector2 pos() const;
    Component& comp() { return mComponent; }
    u32 ropeLength() const { return mRopeLength; }
    // TODO: name. Only seen inlined.
    const g3d::ResFileAccessor& resFile() const { return _28; }

private:
    friend class RestRope;

    ParamAccessor<Param> mParam;
    Component& mComponent;
    hel::math::Vector2 mPos;
    u32 mRopeLength;
    u8 _18[0x28 - 0x18];
    g3d::ResFileAccessor _28;
};

}}}}  // namespace scn::step::gimmick::cutropestep

#endif
