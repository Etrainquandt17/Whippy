#ifndef SCN_STEP_HERO_FORMATIONUTIL_H
#define SCN_STEP_HERO_FORMATIONUTIL_H

#include "hel/common/Array.h"
#include "scn/step/hero/Kind.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// TODO: name the four places on a warp star.
enum WarpStarRidePosKind {
    WARP_STAR_RIDE_POS_KIND_NUM = 4,
};

}}}  // namespace scn::step::hero

namespace hel {
namespace common {

// TODO: in the game Array::operator[] is a function of its own (it calls ArrayUtil::RangeCheck), and
// hel/common/Array.h defines it inline. Until that header changes, these instantiations declare it.
template <>
class Array<scn::step::hero::Kind, 4> {
public:
    scn::step::hero::Kind& operator[](u32 index);
    const scn::step::hero::Kind& operator[](u32 index) const;

private:
    scn::step::hero::Kind mArray[4];
};

template <>
class Array<scn::step::hero::WarpStarRidePosKind, 4> {
public:
    Array() : mArray() {}

    scn::step::hero::WarpStarRidePosKind& operator[](u32 index);

private:
    scn::step::hero::WarpStarRidePosKind mArray[4];
};

}}  // namespace hel::common

namespace scn {
namespace step {
namespace hero {

class FormationUtil {
public:
    static WarpStarRidePosKind GetWarpStarRidePosKind(const hel::common::Array<Kind, 4>& kinds, u32 index);
};

}}}  // namespace scn::step::hero

#endif
