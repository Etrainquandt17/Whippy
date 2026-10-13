#include "util/CurveUtility.h"

namespace util {
namespace CurveUtility {

f32 square(f32 t) {
    return t * t;
}

f32 invSquare(f32 t) {
    return 1.0f - square(1.0f - t);
}

}}  // namespace util::CurveUtility
