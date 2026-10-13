#ifndef SCN_SUBGAME_COMMON_BOXMENU_SELECTUNIT_H
#define SCN_SUBGAME_COMMON_BOXMENU_SELECTUNIT_H

#include "scn/subgame/common/util/AbstractSuspendableTree.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace common {
namespace boxmenu {

class SelectUnit : public util::AbstractSuspendableTree {
public:
    SelectUnit();
    virtual ~SelectUnit();
    virtual bool isSuspend() const;
    virtual void suspend();
    virtual void resume();
    virtual bool isExclusivelyResume() const;

    u32 selectedIndex() const;

private:
    void suspendImpl();
    void resumeImpl();

    u8 _28[0x18];
    bool _40;
    bool mIsSuspend;
    bool _42;
};

}}}}  // namespace scn::subgame::common::boxmenu

#endif
