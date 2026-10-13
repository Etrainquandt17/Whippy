#ifndef SCN_STEP_SFX_SUPERFADE_H
#define SCN_STEP_SFX_SUPERFADE_H

namespace scn {
namespace step {
namespace sfx {

// TODO: members unknown; only what scn/step/sfx/MintSuperFade.cpp calls is declared.
class SuperFade {
public:
    SuperFade();
    ~SuperFade();

    void update();
    void setBack(bool back);
    bool isBack() const;
    void setValid(bool isValid);
};

}
}
}

#endif
