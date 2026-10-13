#include "scn/step/hero/MintInvincible.h"

#include "scn/step/hero/Hero.h"
#include "scn/step/hero/MintHero.h"
#include "scn/step/hero/Invincible.h"

namespace scn {
namespace step {
namespace hero {

namespace {

Invincible& t_obj() {
    return MintHero::Obj().invincible();
}

}

namespace MintInvincible {

void Set(int time) {
    t_obj().set(time);
}

void SetPerm() {
    t_obj().setPerm();
}

void UnsetPerm() {
    t_obj().unsetPerm();
}

bool IsMighty() {
    return t_obj().isMighty();
}

}}}}  // namespace scn::step::hero::MintInvincible
