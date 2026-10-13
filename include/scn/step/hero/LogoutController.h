#ifndef SCN_STEP_HERO_LOGOUTCONTROLLER_H
#define SCN_STEP_HERO_LOGOUTCONTROLLER_H

namespace scn {
namespace step {
namespace hero {

// TODO: members.
class LogoutController {
public:
    bool canLogout() const;
    void returnRestPlayer();
    bool isLogoutForce() const;
};

}
}
}

#endif
