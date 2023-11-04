#pragma once

#include "core.h"
#include "memory"

namespace KCore
{

class KAsset : public KObject, public std::enable_shared_from_this<KAsset>
{
public:
    virtual const IMeta* GetMeta() const override { return nullptr; }

    virtual ~KAsset() { }
};

}