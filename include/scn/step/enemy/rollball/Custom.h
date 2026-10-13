#ifndef SCN_STEP_ENEMY_ROLLBALL_CUSTOM_H
#define SCN_STEP_ENEMY_ROLLBALL_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace rollball {

class Custom;

}}}}  // namespace scn::step::enemy::rollball

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::rollball::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace rollball {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual bool onInWater();

    f32 getRadius();
    void addAttack();
    int getSize();
    bool isBallIron();
    bool isPlayingSound();
    void setPlayingSound(bool isPlayingSound);

private:
    bool mIsBallIron;
    int mSize;
    bool mIsPlayingSound;
};

}}}}  // namespace scn::step::enemy::rollball

#endif
