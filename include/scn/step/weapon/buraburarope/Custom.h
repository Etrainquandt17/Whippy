#ifndef SCN_STEP_WEAPON_BURABURAROPE_CUSTOM_H
#define SCN_STEP_WEAPON_BURABURAROPE_CUSTOM_H

#include "scn/step/weapon/ICustom.h"
#include "scn/step/weapon/buraburarope/ICustomReceiver.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {

class Weapon;

namespace buraburarope {

// TODO: members, the real base class and the overrides.
class Custom : public ICustom {
public:
    Custom(Weapon& weapon);

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual void onDead();
    // TODO: CustomBase's, once that is the base.
    virtual void reqCustomDeadEffect();

    // TODO: name the states.
    enum State {
        STATE_0,
        STATE_1,
        STATE_2,
        STATE_3,
    };

    void setReceiver(ICustomReceiver& receiver);
    void unsetReceiver(ICustomReceiver& receiver);
    void setState(State state);
    State getState() const;
    void setPrevState(State state);
    State getPrevState() const;
    void smallOn();
    bool isSmall() const;

private:
    // TODO: members.
    u32 _4[5];
};

}}}}  // namespace scn::step::weapon::buraburarope

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::buraburarope::Custom>();

}}  // namespace hel::common

#endif
