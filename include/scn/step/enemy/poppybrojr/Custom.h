#ifndef SCN_STEP_ENEMY_POPPYBROJR_CUSTOM_H
#define SCN_STEP_ENEMY_POPPYBROJR_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace enemy {
namespace poppybrojr {

class Custom;

}}}}  // namespace scn::step::enemy::poppybrojr

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::poppybrojr::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace poppybrojr {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onDamaged();
    virtual void onCaptured();

    void requestBomb();
    void changeBombState();
    void requestBombDead();
    int setWaitTime();
    void setIsThrowValid(bool isThrowValid);
    bool isThrowValid();

private:
    util::ObjRefHandle<Enemy> mBomb;
    bool mIsThrowValid;
};

}}}}  // namespace scn::step::enemy::poppybrojr

#endif
