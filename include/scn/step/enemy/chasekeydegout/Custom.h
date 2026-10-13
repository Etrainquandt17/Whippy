#ifndef SCN_STEP_ENEMY_CHASEKEYDEGOUT_CUSTOM_H
#define SCN_STEP_ENEMY_CHASEKEYDEGOUT_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace chasekeydegout {

class Custom;

}}}}  // namespace scn::step::enemy::chasekeydegout

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::chasekeydegout::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace chasekeydegout {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onHitPointIsZero();
    virtual bool onDamaged();
    virtual void onProcFixPos();

    void setFirstChase(bool isFirstChase);
    bool isFirstChase() const;

private:
    bool mIsFirstChase;
};

}}}}  // namespace scn::step::enemy::chasekeydegout

#endif
