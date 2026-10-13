#ifndef GOBJ_FOOTSTATE_H
#define GOBJ_FOOTSTATE_H

namespace gobj {

class FootState {
public:
    FootState();

    bool isGround() const;
    bool isAir() const;
    void setGround();
    void setAir();

private:
    bool mIsGround;
};

}

#endif
