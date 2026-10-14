#include "mintglue/App__Alert.h"

#include "app/AlertMint.h"
#include "mintglue/WrapNative.h"

using app::AlertMint;
using hel::math::Vector3;

namespace mintglue {
namespace App__Alert {

void AddOn(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void Print(string)", Print, static_cast<void (*)(const char*)>(&AlertMint::Print));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void PrintIndex(int,string)", PrintIndex, static_cast<void (*)(int, const char*)>(&AlertMint::PrintIndex));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void Print(int)", Print, static_cast<void (*)(int)>(&AlertMint::Print));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void Print(string,int)", Print, static_cast<void (*)(const char*, int)>(&AlertMint::Print));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void Print(string,int,int)", Print, static_cast<void (*)(const char*, int, int)>(&AlertMint::Print));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void Print(string,int,int,int)", Print, static_cast<void (*)(const char*, int, int, int)>(&AlertMint::Print));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void PrintIndex(int,int)", PrintIndex, static_cast<void (*)(int, int)>(&AlertMint::PrintIndex));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void PrintIndex(int,string,int)", PrintIndex, static_cast<void (*)(int, const char*, int)>(&AlertMint::PrintIndex));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void PrintIndex(int,string,int,int)", PrintIndex, static_cast<void (*)(int, const char*, int, int)>(&AlertMint::PrintIndex));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void PrintIndex(int,string,int,int,int)", PrintIndex, static_cast<void (*)(int, const char*, int, int, int)>(&AlertMint::PrintIndex));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void Print(float)", Print, static_cast<void (*)(f32)>(&AlertMint::Print));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void Print(string,float)", Print, static_cast<void (*)(const char*, f32)>(&AlertMint::Print));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void Print(string,float,float)", Print, static_cast<void (*)(const char*, f32, f32)>(&AlertMint::Print));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void Print(string,float,float,float)", Print, static_cast<void (*)(const char*, f32, f32, f32)>(&AlertMint::Print));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void PrintIndex(int,float)", PrintIndex, static_cast<void (*)(int, f32)>(&AlertMint::PrintIndex));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void PrintIndex(int,string,float)", PrintIndex, static_cast<void (*)(int, const char*, f32)>(&AlertMint::PrintIndex));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void PrintIndex(int,string,float,float)", PrintIndex, static_cast<void (*)(int, const char*, f32, f32)>(&AlertMint::PrintIndex));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void PrintIndex(int,string,float,float,float)", PrintIndex, static_cast<void (*)(int, const char*, f32, f32, f32)>(&AlertMint::PrintIndex));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void Print(const ref HEL.Math.Vector3)", Print, static_cast<void (*)(const Vector3&)>(&AlertMint::Print));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void PrintIndex(int,const ref HEL.Math.Vector3)", PrintIndex, static_cast<void (*)(int, const Vector3&)>(&AlertMint::PrintIndex));
}

}}  // namespace mintglue::App__Alert
