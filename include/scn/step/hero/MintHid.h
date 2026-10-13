#ifndef SCN_STEP_HERO_MINTHID_H
#define SCN_STEP_HERO_MINTHID_H

#include "types.h"

namespace scn {
namespace step {
namespace hero {

namespace MintHid {

bool IsHold(u32 mask);
bool IsTrigger(u32 mask);
void SetAutoInputHold(u32 mask);

}}}}  // namespace scn::step::hero::MintHid

#endif
