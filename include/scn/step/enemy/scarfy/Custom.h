#ifndef SCN_STEP_ENEMY_SCARFY_CUSTOM_H
#define SCN_STEP_ENEMY_SCARFY_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace scarfy {

class Custom;

}}}}  // namespace scn::step::enemy::scarfy

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::scarfy::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace scarfy {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onHitPointIsZero();
    virtual bool onVacuumResist();
    virtual bool onDamaged();

    bool scarfyDamage();
    void onAngerFlag();
    bool isAngerFlag() const;

private:
    bool mIsAnger;
    bool mIsFaceChanged;
};

}}}}  // namespace scn::step::enemy::scarfy

#endif
