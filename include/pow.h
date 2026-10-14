#ifndef POW_H
#define POW_H

// The original evaluates the argument once per factor, as these macros do. An inline function would evaluate it once:
// POW4(1.0f - Math::SinDegF(x)) is four calls of SinDegF, as in the game.
#define POW2(x) ((x) * (x))
#define POW3(x) ((x) * POW2(x))
#define POW4(x) ((x) * POW3(x))

#endif
