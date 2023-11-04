#pragma once

#include "primitive.h"

namespace KCore
{

class KTriangle : public KPrimitive
{
public:
    KTriangle() : KPrimitive() { }
    virtual void SetupShape() override;
};

}