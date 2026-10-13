#ifndef APP_RANDOM_H
#define APP_RANDOM_H

#include "types.h"

namespace hel {
namespace math {
class Random;
}}  // namespace hel::math

namespace app {

class Random {
public:
    static bool RandBool(f32 rate);
    static int Rand(int max);
    static int Rand(int min, int max);
    static f32 RandF(f32 min, f32 max);
    static u32 RandU32(u32 max);
    static u32 RandU32(u32 min, u32 max);
    static f32 RandF32(f32 min, f32 max);
    static f32 RandNF();
    static f32 RandAF();
    static void Reset();
    static hel::math::Random& Obj();
};

}  // namespace app

#endif
