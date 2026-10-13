#ifndef SCN_STEP_ENEMY_ICUSTOMINFO_H
#define SCN_STEP_ENEMY_ICUSTOMINFO_H

#include "hel/common/RuntimeTypeInfoImpl.h"
#include "scn/step/enemy/ICustom.h"

// ICustom has no info of its own, so it gets the general one. Each enemy AddOnMint unit of the original holds
// that instance: the link drops the duplicate, but its "no name class" stays at the end of the unit's .data.
// TODO: this belongs in ICustom.h (see RuntimeTypeInfoImpl.h). How the original forces the instance is not known.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::enemy::ICustom>();

#endif
