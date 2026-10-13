#ifndef APP_ALERTMINT_H
#define APP_ALERTMINT_H

#include "hel/math/Vector3.h"
#include "types.h"

namespace app {

// Debug output for scripts. Every function is empty in the retail game.
class AlertMint {
public:
    static void Print(const char* text);
    static void PrintIndex(int index, const char* text);
    static void Print(int value);
    static void Print(const char* text, int value);
    static void Print(const char* text, int value0, int value1);
    static void Print(const char* text, int value0, int value1, int value2);
    static void PrintIndex(int index, int value);
    static void PrintIndex(int index, const char* text, int value);
    static void PrintIndex(int index, const char* text, int value0, int value1);
    static void PrintIndex(int index, const char* text, int value0, int value1, int value2);
    static void Print(f32 value);
    static void Print(const char* text, f32 value);
    static void Print(const char* text, f32 value0, f32 value1);
    static void Print(const char* text, f32 value0, f32 value1, f32 value2);
    static void PrintIndex(int index, f32 value);
    static void PrintIndex(int index, const char* text, f32 value);
    static void PrintIndex(int index, const char* text, f32 value0, f32 value1);
    static void PrintIndex(int index, const char* text, f32 value0, f32 value1, f32 value2);
    static void Print(const hel::math::Vector3& value);
    static void PrintIndex(int index, const hel::math::Vector3& value);
};

}  // namespace app

#endif
