#ifndef HEL_MINT_ADDONMATHVECTOR3_H
#define HEL_MINT_ADDONMATHVECTOR3_H

#include "hel/math/Vector3.h"

namespace hel {
namespace mint {
namespace AddOnMathVector3 {

const hel::math::Vector3 Get();
float GetX();
float GetY();
float GetZ();
void SetXYZ(float x, float y, float z);
void Set(const hel::math::Vector3& value);
void SetX(float x);
void SetY(float y);
void SetZ(float z);
void Mul(float scale);
void Div(float scale);
void SlotLoad(unsigned long index);
void SlotSave(unsigned long index);
void SlotAdd(unsigned long index);
void SlotSub(unsigned long index);
const hel::math::Vector3 Create(float x, float y, float z);

}
}
}

#endif
