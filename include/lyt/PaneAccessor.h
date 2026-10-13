#ifndef LYT_PANEACCESSOR_H
#define LYT_PANEACCESSOR_H

#include "types.h"
#include "util/ObjRefHandle.h"

namespace hel {
namespace math {
class Matrix34;
class Vector2;
class Vector3;
}}  // namespace hel::math

namespace nw4r {
namespace lyt {
class TextBox;
}}  // namespace nw4r::lyt

namespace lyt {

class Layout;

class PaneAccessor {
public:
    PaneAccessor();

    bool isValid() const;
    void setScale(const hel::math::Vector2& scale) const;
    void setTrans(const hel::math::Vector3& trans) const;
    bool isVisible() const;
    void setVisibility(bool visible) const;
    void show() const;
    void hide() const;
    void setAlpha(u8 alpha) const;
    void setSize(const hel::math::Vector2& size) const;
    hel::math::Vector2 size() const;
    hel::math::Vector3 pos() const;
    hel::math::Matrix34 globalMtx() const;
    nw4r::lyt::TextBox* textBox() const;
    void setText(const wchar_t* text) const;
    void setText(const char* text) const;
    void setTextSmart(const wchar_t* text) const;
    void setTextDirect(const wchar_t* text) const;

private:
    util::ObjRefHandle<Layout> mLayout;
    void* mPane;
};

}  // namespace lyt

#endif
