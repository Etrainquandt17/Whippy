#ifndef SCN_STEP_HERO_MINTABILITYMANAGER_H
#define SCN_STEP_HERO_MINTABILITYMANAGER_H

#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace MintAbilityManager {

bool IsSuper();
int AbilityKind();
void SuperBGMRequest();
void SuperBGMUnrequest();
bool CanSuperBGMRequest();
int GetUseCount();
bool IsOnGrandLowperBattle();

}}}}  // namespace scn::step::hero::MintAbilityManager

#endif
