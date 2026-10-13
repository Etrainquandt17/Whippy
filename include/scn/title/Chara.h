#ifndef SCN_TITLE_CHARA_H
#define SCN_TITLE_CHARA_H

#include "types.h"

namespace g3d {

class StdModel;

}

namespace scn {
namespace title {

class Component;

// TODO: enumerators.
enum CharaKind {
    CHARA_KIND_0,
};

class Chara {
public:
    Chara(Component& component, g3d::StdModel& model, CharaKind kind);
    ~Chara();

    void update();
    void changeAnim(const char* name, f32 frame);
    bool isAnimLooped();
    void effectRequestN(u32 index, const char* name);
    void resetEffect();

private:
    // TODO: size and members.
    u32 _0[1];
};

}}  // namespace scn::title

#endif
