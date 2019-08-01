#pragma once

#include "Color.hpp"

namespace Ray2d {
    namespace Computations {
        class Material {

        public:
            float absorption;
            float mirror;
            float fresnel;
            float ior;
            Material(float absorption, float mirror, float fresnel, float ior);
        };

    }
}