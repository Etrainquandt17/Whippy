#include "app/Random.h"

#include "app/Application.h"
#include "hel/math/Random.h"

using hel::common::ExplicitSingleton;

namespace app {

bool Random::RandBool(f32 rate) {
    return Obj().randBool(rate);
}

int Random::Rand(int max) {
    return Obj().rand(max);
}

int Random::Rand(int min, int max) {
    return Obj().rand(min, max);
}

f32 Random::RandF(f32 min, f32 max) {
    return Obj().randF(min, max);
}

u32 Random::RandU32(u32 max) {
    return Obj().randU32(max);
}

u32 Random::RandU32(u32 min, u32 max) {
    return Obj().randU32(min, max);
}

f32 Random::RandF32(f32 min, f32 max) {
    return Obj().randF32(min, max);
}

f32 Random::RandNF() {
    return Obj().randNF();
}

f32 Random::RandAF() {
    return Obj().randAF();
}

void Random::Reset() {
    Obj() = hel::math::Random(hel::math::Random::Seed::Default());
}

hel::math::Random& Random::Obj() {
    return ExplicitSingleton<Application>::object_->random();
}

}  // namespace app
