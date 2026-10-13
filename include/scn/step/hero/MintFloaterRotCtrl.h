#ifndef SCN_STEP_HERO_MINTFLOATERROTCTRL_H
#define SCN_STEP_HERO_MINTFLOATERROTCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace hero {

namespace MintFloaterRotCtrl {

f32 GetRotV();
void InitRotV(f32 rot);
void SetRotVTarget(f32 rot);
void ResetRotVTarget();
void SetRotVIntpRate(f32 rate);
void ResetRotVIntpRate();

}}}}  // namespace scn::step::hero::MintFloaterRotCtrl

#endif
