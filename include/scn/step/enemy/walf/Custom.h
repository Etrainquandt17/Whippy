#ifndef SCN_STEP_ENEMY_WALF_CUSTOM_H
#define SCN_STEP_ENEMY_WALF_CUSTOM_H

#include "hel/math/Vector2.h"
#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace walf {

class Custom;

}}}}  // namespace scn::step::enemy::walf

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::walf::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace walf {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onDamaged();
    virtual bool onInWater();
    virtual bool onOutWater();

    bool isInWater();
    bool isFloating(hel::math::Vector2 offset);
    bool isFloating();
    bool checkTurn(bool isRight);
    bool checkJump();
    void setDirBeforeJump(bool isRight);
    bool checkTurnAfterJump();

private:
    bool mDirBeforeJump;
    bool mIsDamaged;
    int mTurnStep;
    u32 mJumpCount;
    s32 mJumpRand;
};

}}}}  // namespace scn::step::enemy::walf

#endif
