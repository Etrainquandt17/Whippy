#ifndef SCN_STEP_OSTOP_REQUESTOR_H
#define SCN_STEP_OSTOP_REQUESTOR_H

#include "ostop/ReqHandle.h"
#include "scn/step/ostop/Flag.h"
#include "types.h"

namespace scn {
namespace step {

class Component;

namespace ostop {

class Requestor {
public:
    Requestor(Component& component);
    ~Requestor();

    bool request(Flag flag);
    void release();
    Requestor(Component& component, const ::ostop::ReqHandle& handle);
    ::ostop::ReqHandle takeHandle();
    bool isActive() const;

private:
    u32 _0[3];
};

}}}  // namespace scn::step::ostop

#endif
