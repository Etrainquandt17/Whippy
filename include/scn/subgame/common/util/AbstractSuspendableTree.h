#ifndef SCN_SUBGAME_COMMON_UTIL_ABSTRACTSUSPENDABLETREE_H
#define SCN_SUBGAME_COMMON_UTIL_ABSTRACTSUSPENDABLETREE_H

#include "hel/common/MutableArray.h"
#include "scn/subgame/common/util/ISuspendable.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace common {
namespace util {

class AbstractSuspendableTree : public ISuspendable {
public:
    AbstractSuspendableTree();
    virtual ~AbstractSuspendableTree() {}
    virtual void suspend();
    virtual void resume();
    virtual bool isExclusivelyResume() const;

    void addSuspendable(ISuspendable& suspendable);

private:
    hel::common::MutableArray<ISuspendable*, 8> mChildren;
};

}}}}  // namespace scn::subgame::common::util

#endif
