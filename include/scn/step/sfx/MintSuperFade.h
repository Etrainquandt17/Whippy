#ifndef SCN_STEP_SFX_MINTSUPERFADE_H
#define SCN_STEP_SFX_MINTSUPERFADE_H

namespace scn {
namespace step {
namespace sfx {

class SuperFade;

namespace MintSuperFade {

void Register(SuperFade& obj);
void Unregister(SuperFade& obj);
void SetBack(bool back);

}}}}  // namespace scn::step::sfx::MintSuperFade

#endif
