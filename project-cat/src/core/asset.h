#pragma once

#include "core.h"
#include "memory"

namespace KCore
{

// ����meta��Ϣ�Ļ���
struct IMeta
{};

class KAsset : public KObject, public std::enable_shared_from_this<KAsset>
{
public:
    virtual const IMeta* GetMeta() const { return nullptr; }

    virtual ~KAsset() { }
};

}