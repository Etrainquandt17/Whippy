#include "hel/geo/Rect.h"

#include "hel/math/Math.h"
#include "hel/math/Vector2.h"

using hel::math::Vector2;

namespace hel {
namespace geo {

// _0 is the upper edge, _4 the lower, _8 the left and _C the right; y grows upward.
Rect::Rect()
    : _0(0.0f)
    , _4(0.0f)
    , _8(0.0f)
    , _C(0.0f) {
    set(0.0f, 0.0f, 0.0f, 0.0f);
}

Rect::Rect(f32 minY, f32 maxY, f32 minX, f32 maxX)
    : _0(0.0f)
    , _4(0.0f)
    , _8(0.0f)
    , _C(0.0f) {
    set(minY, maxY, minX, maxX);
}

Rect::Rect(const Rect& other)
    : _0(0.0f)
    , _4(0.0f)
    , _8(0.0f)
    , _C(0.0f) {
    set(other._0, other._4, other._8, other._C);
}

Rect::~Rect() {}

void Rect::set(f32 minY, f32 maxY, f32 minX, f32 maxX) {
    _0 = minY;
    _4 = maxY;
    _8 = minX;
    _C = maxX;
}

void Rect::trans(f32 x, f32 y) {
    _0 += y;
    _4 += y;
    _8 += x;
    _C += x;
}

const Vector2 Rect::getCenter() const {
    return Vector2(0.5f * (_8 + _C), 0.5f * (_0 + _4));
}

f32 Rect::getWidth() const {
    return math::Math::Abs<f32>(_C - _8);
}

f32 Rect::getHeight() const {
    return math::Math::Abs<f32>(_4 - _0);
}

bool Rect::isInclude(f32 x, f32 y) const {
    bool include = false;
    if (_8 <= x && x <= _C && _4 <= y && y <= _0) {
        include = true;
    }
    return include;
}

bool Rect::isIntersect(const Rect& other) const {
    if (_8 > other._C) {
        return false;
    }
    if (_C < other._8) {
        return false;
    }
    if (_0 < other._4) {
        return false;
    }
    if (_4 > other._0) {
        return false;
    }
    return true;
}

void Rect::adjustAspectShrink(f32 aspect) {
    Vector2 center = getCenter();
    f32 width = getWidth();
    f32 height = getHeight();
    height *= aspect;
    if (height > width) {
        width *= 1.0f / aspect;
        _4 = -(0.5f * width - center.y);
        _0 = 0.5f * width + center.y;
    } else {
        _8 = -(0.5f * height - center.x);
        _C = 0.5f * height + center.x;
    }
}

void Rect::transInternal(const Rect& other) {
    if (getWidth() > other.getWidth()) {
        _8 = other._8;
        _C = other._C;
    }
    if (getHeight() > other.getHeight()) {
        _0 = other._0;
        _4 = other._4;
    }
    f32 diff = _0 - other._0;
    if (diff > 0.0f) {
        _0 -= diff;
        _4 -= diff;
    }
    diff = _4 - other._4;
    if (diff < 0.0f) {
        _0 -= diff;
        _4 -= diff;
    }
    diff = _8 - other._8;
    if (diff < 0.0f) {
        _8 -= diff;
        _C -= diff;
    }
    diff = _C - other._C;
    if (diff > 0.0f) {
        _8 -= diff;
        _C -= diff;
    }
}

void Rect::margeUnion(const Rect& other) {
    if (other._8 < _8) {
        _8 = other._8;
    }
    if (other._C > _C) {
        _C = other._C;
    }
    if (other._4 < _4) {
        _4 = other._4;
    }
    if (other._0 > _0) {
        _0 = other._0;
    }
}

}
}
