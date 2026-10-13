#ifndef SCN_SUBGAME_COMMON_UTIL_ISUSPENDABLE_H
#define SCN_SUBGAME_COMMON_UTIL_ISUSPENDABLE_H

namespace scn {
namespace subgame {
namespace common {
namespace util {

class ISuspendable {
public:
    virtual ~ISuspendable();
    virtual bool isSuspend() const = 0;
    virtual void suspend() = 0;
    virtual void resume() = 0;
    virtual bool isExclusivelyResume() const = 0;
};

}}}}  // namespace scn::subgame::common::util

#endif
