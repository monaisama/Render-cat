#include "camera.h"

namespace KMath
{

KCamera KCamera::Ortho(KVec3f location, KRotatorf rotation, float near, float far, float width, float height)
{
    KCamera camera(MakeTranslateMatrix(location)); // todo rotation

    return camera;
}

}