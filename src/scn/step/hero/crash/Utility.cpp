#include "scn/step/hero/crash/Utility.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"

namespace scn {
namespace step {
namespace hero {
namespace crash {

void Utility::RequestHatEffectNormal(Hero& hero) {
    hero.model().hat().effect().releaseAndVanish();
    hero.model().hat().effect().requestN(static_cast<effect::Kind>(0xBF), 0);
}

void Utility::RequestHatEffectAttack(Hero& hero) {
    hero.model().hat().effect().releaseAndVanish();
    hero.model().hat().effect().requestN(static_cast<effect::Kind>(0xC0), 0);
}

}}}}  // namespace scn::step::hero::crash
