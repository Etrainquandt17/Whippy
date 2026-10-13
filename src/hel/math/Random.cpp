#include "hel/math/Random.h"

namespace hel {
namespace math {

Random::Seed Random::Seed::Default() {
    Seed seed;
    seed._0 = 0x75BCD15;
    seed._4 = 0x159A55E5;
    seed._8 = 0x1F123BB5;
    seed._C = 0x5491333;
    return seed;
}

Random::Random(const Seed& seed)
    : mSeed(seed) {}

bool Random::randBool(f32 rate) {
    if (rate == 0.0f) {
        return false;
    }
    return randCoreF32() <= rate;
}

int Random::rand(int max) {
    return randS32(max);
}

int Random::rand(int min, int max) {
    return randS32(min, max);
}

f32 Random::randF(f32 min, f32 max) {
    return randF32(min, max);
}

s32 Random::randS32(s32 max) {
    s32 value = randCoreU32() & 0x7FFFFFFF;
    return value % max;
}

s32 Random::randS32(s32 min, s32 max) {
    return min + randS32(max - min);
}

u32 Random::randU32(u32 max) {
    return randCoreU32() % max;
}

u32 Random::randU32(u32 min, u32 max) {
    return min + randCoreU32() % (max - min);
}

f32 Random::randF32(f32 min, f32 max) {
    return (max - min) * randCoreF32() + min;
}

f32 Random::randNF() {
    return randCoreF32();
}

f32 Random::randAF() {
    return 2.0f * randCoreF32() + -1.0f;
}

int Random::operator()(int max) {
    return randS32(max);
}

u32 Random::randCoreU32() {
    u32 t = mSeed._0 ^ (mSeed._0 << 11);
    mSeed._0 = mSeed._4;
    mSeed._4 = mSeed._8;
    mSeed._8 = mSeed._C;
    mSeed._C = (mSeed._C ^ (mSeed._C >> 19)) ^ (t ^ (t >> 8));
    return mSeed._C;
}

f32 Random::randCoreF32() {
    return static_cast<f32>(randCoreU32() & 0xFFFF) / 65536.0f;
}

}}  // namespace hel::math
