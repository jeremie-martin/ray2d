#pragma once

#include "Ray.hpp"
#include "Color.hpp"
#include "Utils.hpp"

namespace Ray2d {
    namespace Computations {        
        class Light {
        public:
            virtual ~Light() = default;
            virtual Ray generateRay(void);
        };
    }
}