#ifndef SCN_STEP_ENEMY_DEGOUT_CUSTOM_H
#define SCN_STEP_ENEMY_DEGOUT_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace degout {

class Custom;

}}}}  // namespace scn::step::enemy::degout

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::degout::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace degout {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual bool onDamaged();

    void setChaseFlag(bool flag);
    bool isChaseFlag() const;
    void setFirstChase(bool flag);
    bool isFirstChase() const;

private:
    bool mIsChaseFlag;
    bool mIsFirstChase;
};

}}}}  // namespace scn::step::enemy::degout

#endif
