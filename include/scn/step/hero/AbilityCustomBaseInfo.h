#ifndef SCN_STEP_HERO_ABILITYCUSTOMBASEINFO_H
#define SCN_STEP_HERO_ABILITYCUSTOMBASEINFO_H

#include "hel/common/RuntimeTypeInfoImpl.h"
#include "scn/step/hero/AbilityCustomBase.h"

// AbilityCustomBase has no info of its own, so it gets the general one. The five super ability units of the
// original (SuperSword, SuperFire, SuperBeam, SuperHammer, SuperIce) hold that instance: the link drops the
// duplicate, but its "no name class" stays at the end of the unit's .data.
// TODO: how the original forces the instance in those units is not known.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::hero::AbilityCustomBase>();

#endif
