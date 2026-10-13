#ifndef OCOLL_ATTACK_H
#define OCOLL_ATTACK_H

#include "hel/math/Vector2.h"
#include "types.h"

namespace ocoll {

class Manager;
class NodeDesc;
class Owner;

class Attack {
public:
    Attack(Manager& manager, Owner& owner, u32);
    ~Attack();

    void clearNode();
    void setType(u32, u32 type);
    void addNode(u32 id, const NodeDesc& desc);
    bool isCollide() const;
    bool isCollideGimmick() const;
    hel::math::Vector2 getCollidedHitPos() const;
    u32 getCollidedHitResistLv() const;
    u32 getCollidedHitStopFrame() const;
    void setPause(bool isPause);
    void setValid(bool valid);

private:
    // TODO: the members. The size is from hero::parasol::Custom, which holds one.
    u32 _0[0x270 / 4];
};

}

#endif
