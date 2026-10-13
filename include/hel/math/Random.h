#ifndef HEL_MATH_RANDOM_H
#define HEL_MATH_RANDOM_H

#include "types.h"

namespace hel {
namespace math {

class Random {
public:
    class Seed {
    public:
        static Seed Default();

        u32 _0;
        u32 _4;
        u32 _8;
        u32 _C;
    };

    Random(const Seed& seed);

    int operator()(int max);

    bool randBool(f32 rate);
    int rand(int max);
    int rand(int min, int max);
    f32 randF(f32 min, f32 max);
    s32 randS32(s32 max);
    s32 randS32(s32 min, s32 max);
    u32 randU32(u32 max);
    u32 randU32(u32 min, u32 max);
    f32 randF32(f32 min, f32 max);
    f32 randNF();
    f32 randAF();

private:
    u32 randCoreU32();
    f32 randCoreF32();

    Seed mSeed;
};

}
}

#endif
