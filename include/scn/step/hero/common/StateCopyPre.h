#ifndef SCN_STEP_HERO_COMMON_STATECOPYPRE_H
#define SCN_STEP_HERO_COMMON_STATECOPYPRE_H

#include "ostop/ReqHandle.h"
#include "scn/step/hero/StateBase.h"
#include "scn/step/ostop/Requestor.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateCopyPre : public StateBase {
public:
    StateCopyPre(Hero* hero);
    StateCopyPre(Hero* hero, const ::ostop::ReqHandle& handle);
    virtual ~StateCopyPre();
    virtual void procAnim();

private:
    void construct();

    ostop::Requestor mRequestor;
    bool mIsChanged;
};

}}}}  // namespace scn::step::hero::common

#endif
