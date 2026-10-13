#ifndef SCN_STEP_ENEMY_STARMAN_CUSTOM_H
#define SCN_STEP_ENEMY_STARMAN_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace starman {

class Custom;

}}}}  // namespace scn::step::enemy::starman

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::starman::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace starman {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();

    void setHighJumpMode(bool isHighJump);
    bool isHighJumpMode();

private:
    bool mIsHighJumpMode;
};

}}}}  // namespace scn::step::enemy::starman

#endif
