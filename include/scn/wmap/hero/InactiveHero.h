#ifndef SCN_WMAP_HERO_INACTIVEHERO_H
#define SCN_WMAP_HERO_INACTIVEHERO_H

#include "hid/RumbleRequestor.h"
#include "mem/ExplicitScopedPtr.h"
#include "mem/HeapExpArrayUser.h"
#include "scn/step/ContextHeroIndivi.h"
#include "scn/step/hero/Kind.h"
#include "scn/wmap/hero/InactiveStateCallback.h"
#include "snd/SERequestor.h"
#include "types.h"
#include "util/StateChanger.h"

namespace mem {
class HeapExpArray;
}

namespace scn {
namespace wmap {

class Component;

namespace info {
class HeroPanel;
}

namespace hero {

class IInactiveState;

namespace inactive {
class StateInit;
class StateSelect;
}

class InactiveHero {
public:
    InactiveHero(Component& component, mem::HeapExpArray& heapArray, u32 index, const step::ContextHeroIndivi& context);
    ~InactiveHero();

    void proc();
    void createHero();
    step::ContextHeroIndivi createContext() const;
    info::HeroPanel& infoHeroPanel();
    void setIsConnected(bool isConnected);
    bool isConnected() const;
    void setIsDecided(bool isDecided);
    bool isDecided() const;
    bool isForbidSelect();
    void setKind(step::hero::Kind kind);
    step::hero::Kind kind() const;

private:
    Component& mComponent;
    mem::HeapExpArrayUser mHeapUser;
    mem::ExplicitScopedPtr<hid::RumbleRequestor> mRumble;
    mem::ExplicitScopedPtr<snd::SERequestor> mSE;
    mem::ExplicitScopedPtr<InactiveStateCallback> mStateCallback;
    mem::ExplicitScopedPtr<util::StateChanger<IInactiveState, 256> > mStateChanger;
    step::ContextHeroIndivi::Unk38 _2C;
    u32 mIndex;
    int _38;
    bool _3C;
    bool _3D;
    bool _3E;
};

}}}  // namespace scn::wmap::hero

#endif
