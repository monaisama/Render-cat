#include "render.h"

namespace KCore
{

KRender::KRender(const KMath::KCamera& camera)
    : context { camera }
{ }

}