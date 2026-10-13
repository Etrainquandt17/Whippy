#ifndef EFFECT_STDREQUESTOR_H
#define EFFECT_STDREQUESTOR_H

#include "types.h"

namespace hel {
namespace math {
class Vector3;
}}  // namespace hel::math

namespace g3d {
class NodeAccessor;
}

namespace effect {

class Group;
class Manager;

class StdRequestor {
public:
    StdRequestor(Manager& manager);
    ~StdRequestor();

    void changeGroup(Group& group);
    void release();
    void releaseAndVanish();
    void requestP(u32 id, const hel::math::Vector3& pos);
    void requestN(u32 id, const g3d::NodeAccessor& node);

private:
    u32 _0[7];
};

}  // namespace effect

#endif
