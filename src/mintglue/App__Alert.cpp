#include "mintglue/App__Alert.h"

#include "app/AlertMint.h"
#include "mintglue/WrapNative.h"

namespace mintglue {
namespace App__Alert {

void AddOn(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void Print(string)", Print, static_cast<void (*)(const char*)>(&app::AlertMint::Print));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void PrintIndex(int,string)", PrintIndex, static_cast<void (*)(int, const char*)>(&app::AlertMint::PrintIndex));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void Print(int)", Print, static_cast<void (*)(int)>(&app::AlertMint::Print));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void Print(string,int)", Print, static_cast<void (*)(const char*, int)>(&app::AlertMint::Print));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void Print(string,int,int)", Print, static_cast<void (*)(const char*, int, int)>(&app::AlertMint::Print));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void Print(string,int,int,int)", Print, static_cast<void (*)(const char*, int, int, int)>(&app::AlertMint::Print));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void PrintIndex(int,int)", PrintIndex, static_cast<void (*)(int, int)>(&app::AlertMint::PrintIndex));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void PrintIndex(int,string,int)", PrintIndex, static_cast<void (*)(int, const char*, int)>(&app::AlertMint::PrintIndex));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void PrintIndex(int,string,int,int)", PrintIndex, static_cast<void (*)(int, const char*, int, int)>(&app::AlertMint::PrintIndex));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void PrintIndex(int,string,int,int,int)", PrintIndex, static_cast<void (*)(int, const char*, int, int, int)>(&app::AlertMint::PrintIndex));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void Print(float)", Print, static_cast<void (*)(f32)>(&app::AlertMint::Print));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void Print(string,float)", Print, static_cast<void (*)(const char*, f32)>(&app::AlertMint::Print));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void Print(string,float,float)", Print, static_cast<void (*)(const char*, f32, f32)>(&app::AlertMint::Print));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void Print(string,float,float,float)", Print, static_cast<void (*)(const char*, f32, f32, f32)>(&app::AlertMint::Print));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void PrintIndex(int,float)", PrintIndex, static_cast<void (*)(int, f32)>(&app::AlertMint::PrintIndex));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void PrintIndex(int,string,float)", PrintIndex, static_cast<void (*)(int, const char*, f32)>(&app::AlertMint::PrintIndex));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void PrintIndex(int,string,float,float)", PrintIndex, static_cast<void (*)(int, const char*, f32, f32)>(&app::AlertMint::PrintIndex));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void PrintIndex(int,string,float,float,float)", PrintIndex, static_cast<void (*)(int, const char*, f32, f32, f32)>(&app::AlertMint::PrintIndex));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void Print(const ref HEL.Math.Vector3)", Print, static_cast<void (*)(const hel::math::Vector3&)>(&app::AlertMint::Print));
    MINT_NATIVE_FUNCTION(core, "App.Alert", "void PrintIndex(int,const ref HEL.Math.Vector3)", PrintIndex, static_cast<void (*)(int, const hel::math::Vector3&)>(&app::AlertMint::PrintIndex));
}

}}  // namespace mintglue::App__Alert
