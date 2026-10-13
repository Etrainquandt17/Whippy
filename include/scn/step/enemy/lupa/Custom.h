#ifndef SCN_STEP_ENEMY_LUPA_CUSTOM_H
#define SCN_STEP_ENEMY_LUPA_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace lupa {

class CliffChecker;

// TODO: members and the other functions.
class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();

    bool checkExistLand();
    void approachMap();
    void reqShot();
    CliffChecker& cliffChecker();

private:
    // TODO: members.
    u32 _8[7];
};

}}}}  // namespace scn::step::enemy::lupa

namespace hel {
namespace common {

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::lupa::Custom>();

}}  // namespace hel::common

#endif
