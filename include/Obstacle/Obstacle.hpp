#pragma once

#include <optional>
#include "Ray.hpp"
#include "Color.hpp"

namespace Ray2d {
    namespace Computations {
        #define NO_INTERSECTION 10000000000

        float cross(const glm::vec2 &lhs, const glm::vec2 &rhs);

        class Obstacle {
        public:
            virtual float rayIntersect(Ray &ray) = 0;
        };

    }
}