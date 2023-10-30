#pragma once

#include "primitive.h"

namespace KCore::Shape
{

class KTriangle : public KPrimitive
{
public:
    KTriangle() : KPrimitive() { }
    virtual void SetupShape() override;
};

}