#ifndef SCN_STEP_ENEMY_SIRKIBBLE_CUSTOM_H
#define SCN_STEP_ENEMY_SIRKIBBLE_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace sirkibble {

class Custom;

}}}}  // namespace scn::step::enemy::sirkibble

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::sirkibble::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace sirkibble {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onDamaged();
    virtual void onProcFixPos();

    void reqWeapon();
    void chkPlayerPos();
    void chkNextTurnJump();
    bool isPlayerUpPos();
    bool isChangeDirType();
    bool isNextTurnJump();
    void setNextTurnJumpInvalid();

private:
    bool mIsPlayerUpPos;
    bool mIsChangeDirType;
    bool mIsNextTurnJump;
    bool mJumpLog0;
    bool mJumpLog1;
    bool mJumpLog2;
};

}}}}  // namespace scn::step::enemy::sirkibble

#endif
