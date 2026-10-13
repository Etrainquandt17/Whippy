#ifndef SCN_ARENA_SCENEARENA_H
#define SCN_ARENA_SCENEARENA_H

#include "hel/common/ScopedPtr.h"
#include "scn/arena/Component.h"
#include "scn/arena/ContextArena.h"
#include "types.h"

// TODO: hel/common/ScopedPtr.h gives no access to the pointer yet, which
// SceneArena::result tests inline. Until it does, it is specialized here.
namespace hel {
namespace common {

template <>
class ScopedPtr<scn::arena::Component> {
public:
    explicit ScopedPtr(scn::arena::Component* ptr = 0);
    ~ScopedPtr();

    scn::arena::Component* operator->() const;
    scn::arena::Component* get() const { return mPtr; }

private:
    scn::arena::Component* mPtr;
};

}}  // namespace hel::common

namespace scn {
namespace arena {

class SceneArena {
public:
    struct Result {
        ContextArena context;
        int next;
    };

    Result result();

private:
    u8 _0[0x254];
    int _254;
    u8 _258[0x8];
    hel::common::ScopedPtr<Component> mComponent;
};

}}  // namespace scn::arena

#endif
