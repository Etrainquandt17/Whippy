#ifndef SCN_TITLE_COMMANDER_H
#define SCN_TITLE_COMMANDER_H

#include "types.h"

namespace scn {
namespace title {

class Chara;
class Component;

class Commander {
public:
    static int CurrentFrame();
    static void SetFrame(int frame);
    // TODO: a pointer or a reference; the binding stores the address either way.
    static scn::title::Chara* Chara(u32 kind);
    static void CompanyLogoAppear();
    static void TitleInfoAppear();
    static void TitleInfoEffect(u32 index);
    static void TitleInfoEffectBG(u32 index);
    static void CinemaScopeOut();
    static void CinemaScopeHide();
    static void BGMStart();
    static void SceneAnimStart();
    static void SceneAnimStop();
    static void LocatorAnim(const char* name);
    static void SEStart(int id);
    static void SEStop();
    static void BGSetFrameRate(f32 rate);

    Commander(Component& component);

    void start();
    void update();
    bool isEnd() const;
    void execScript();

private:
    // TODO: size and members.
    u32 _0[1];
};

}}  // namespace scn::title

#endif
