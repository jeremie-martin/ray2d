#pragma once

#include "Ray.hpp"
#include "Color.hpp"
#include "Utils.hpp"

namespace Ray2d {
    namespace Computations {        
        class Light {
        public:
            virtual Ray generateRay(void) = 0;
            virtual float getIntensity(void) = 0;
        };
    }
}