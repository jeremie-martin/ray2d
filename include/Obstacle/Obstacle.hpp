#pragma once

#include "Ray.hpp"
#include "Color.hpp"
#include "Utils.hpp"

namespace Ray2d {
    namespace Computations {        
        class Obstacle {
        public:
            virtual ~Obstacle() = default;
            virtual glm::vec2 intersect(void);
        };
    }
}