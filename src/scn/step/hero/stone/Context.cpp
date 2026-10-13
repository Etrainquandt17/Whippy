#include "scn/step/hero/stone/Context.h"

namespace scn {
namespace step {
namespace hero {
namespace stone {

Context::Context(GearNodeRandomChanger& nodeChanger)
    : mNodeChanger(nodeChanger)
    , mIsScrew(false)
    , mIsRun(false)
    , _6(false)
    , mRotFrame(0)
    , mMaxRotFrame(0)
    , mRotAngle(0.0f)
    , mIsRotEnable(true) {
}

Context::~Context() {
}

void Context::resetFlag() {
    mIsScrew = false;
    mIsRun = false;
    _6 = false;
    mRotFrame = 0;
    mMaxRotFrame = 0;
    mRotAngle = 0.0f;
    mIsRotEnable = true;
}

void Context::setIsScrew(bool isScrew) {
    mIsScrew = isScrew;
}

void Context::setIsRun(bool isRun) {
    mIsRun = isRun;
}

void Context::incRotFrame() {
    mRotFrame++;
}

void Context::setMaxRotFrame(u32 frame) {
    mMaxRotFrame = frame;
}

void Context::setRotAngle(f32 angle) {
    mRotAngle = angle;
}

void Context::setRotEnable(bool isEnable) {
    mIsRotEnable = isEnable;
}

GearNodeRandomChanger& Context::nodeChanger() {
    return mNodeChanger;
}

bool Context::isScrew() const {
    return mIsScrew;
}

bool Context::isRun() const {
    return mIsRun;
}

u32 Context::getRotFrame() const {
    return mRotFrame;
}

u32 Context::getMaxRotFrame() const {
    return mMaxRotFrame;
}

f32 Context::getRotAngle() const {
    return mRotAngle;
}

bool Context::isRotEnable() const {
    return mIsRotEnable;
}

}}}}  // namespace scn::step::hero::stone
