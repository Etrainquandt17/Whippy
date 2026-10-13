#ifndef MCOLL_DETAIL_SHAPEDIAMONDCONTEXT_H
#define MCOLL_DETAIL_SHAPEDIAMONDCONTEXT_H

#include "hel/math/Vector2.h"
#include "types.h"

namespace mcoll {
namespace detail {

// TODO: members (a base position and six distances, as its constructor takes them) and the other functions.
class ShapeDiamondContext {
public:
    ShapeDiamondContext(const hel::math::Vector2& base, f32, f32, f32, f32, f32, f32);

    static ShapeDiamondContext CreateBaseBottom(f32 width, f32 height, f32 slant);
    static ShapeDiamondContext CreateBaseCenter(f32 width, f32 height, f32 slant);

private:
    u32 _0[8];
};

}}  // namespace mcoll::detail

#endif
