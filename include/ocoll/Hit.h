#ifndef OCOLL_HIT_H
#define OCOLL_HIT_H

#include "types.h"

namespace ocoll {

class Manager;
class NodeDesc;
class Owner;

class Hit {
public:
    Hit(Manager& manager, Owner& owner);
    ~Hit();

    void setValid(bool valid);
    void update();
    void addNode(const NodeDesc& desc);
    void clearNode();
    bool isCollide() const;
    bool getCollidedAttackTargetGimmick() const;
    u32 getCollidedAttackType() const;
    void setResistLv(u32 level);
    void setFlagXlu(u32 flag);
    void setElementXlu(u32 element);
    void setTeamXlu(u32 team);
    u32 getCollidedAttackElement() const;

private:
    u32 _0[0x448 / 4];
};

}  // namespace ocoll

#endif
