#ifndef G3D_MODELBUFFEROPTION_H
#define G3D_MODELBUFFEROPTION_H

#include "types.h"

namespace g3d {

class ModelBufferOption {
public:
    ModelBufferOption();

    void addAnimMatColor();
    void addAnimTexPattern();
    void addAnimTexSRT();
    void addAnimVisible();
    u32 value() const;

    bool _0;
    bool _1;
    bool _2;
    bool _3;
    bool _4;
    bool _5;
    bool _6;
    bool _7;
    bool _8;
    bool _9;
    bool _A;
    bool _B;
    bool _C;
    bool _D;
    bool _E;
    bool _F;
};

}

#endif
