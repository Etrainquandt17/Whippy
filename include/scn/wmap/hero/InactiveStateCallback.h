#ifndef SCN_WMAP_HERO_INACTIVESTATECALLBACK_H
#define SCN_WMAP_HERO_INACTIVESTATECALLBACK_H

#include "types.h"
#include "util/IStateCallback.h"

namespace scn {
namespace wmap {
namespace hero {

class InactiveHero;

class InactiveStateCallback : public util::IStateCallback {
public:
    InactiveStateCallback(InactiveHero& hero);

    virtual void onStateChanged(const util::IStateChanger& changer);

private:
    InactiveHero& mHero;
};

}}}  // namespace scn::wmap::hero

#endif
