#ifndef SCN_SUBGAME_COMMON_PAUSE_PAUSELOCKREQUESTOR_H
#define SCN_SUBGAME_COMMON_PAUSE_PAUSELOCKREQUESTOR_H

#include "scn/subgame/common/pause/Manager.h"
#include "scn/subgame/common/util/AccessProtectedSingleton.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace common {
namespace pause {

class PauseLockRequestor : public util::AccessProtectedSingletonAccessor<Manager> {
public:
    PauseLockRequestor();
    virtual ~PauseLockRequestor();

    void request();
    void cancel();
    void requestSELock();
    void cancelSELock();

private:
    bool mIsLocked;
    bool mIsSELocked;
};

}}}}  // namespace scn::subgame::common::pause

#endif
