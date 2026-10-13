#ifndef SCN_STEP_SFX_MINTSUPERBACKPICTURE_H
#define SCN_STEP_SFX_MINTSUPERBACKPICTURE_H

#include "scn/step/effect/Kind.h"

namespace scn {
namespace step {
namespace sfx {

class SuperBackPicture;

namespace MintSuperBackPicture {

void Register(SuperBackPicture& obj);
void Unregister(SuperBackPicture& obj);
void RequestEffect(effect::Kind kind);
void RequestEffectN(effect::Kind kind);
void ReleaseEffect();
void RequestEffect2(effect::Kind kind);
void RequestEffect2N(effect::Kind kind);
void ReleaseEffect2();
void RequestEffectNonStop(effect::Kind kind);
void RequestEffectNonStopN(effect::Kind kind);
void ReleaseEffectNonStop();
void RequestEffectNonStop2(effect::Kind kind);
void RequestEffectNonStop2N(effect::Kind kind);
void ReleaseEffectNonStop2();

}}}}  // namespace scn::step::sfx::MintSuperBackPicture

#endif
