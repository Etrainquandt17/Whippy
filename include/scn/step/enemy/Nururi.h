#ifndef SCN_STEP_ENEMY_NURURI_H
#define SCN_STEP_ENEMY_NURURI_H

#include "hel/math/Vector2.h"
#include "nururi/Mode.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

// TODO: members.
class Nururi {
public:
    Nururi(Enemy& enemy);

    void setupInfo();
    void update();
    hel::math::Vector2 getNururiDir() const;
    void setValid(bool isValid);
    void setCanNururi(bool canNururi);
    void changeSetting(const hel::math::Vector2& offset, f32 width, f32 height, nururi::Mode mode);
    void changeSetting(nururi::Mode mode);
};

}
}
}

#endif
