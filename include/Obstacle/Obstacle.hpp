#pragma once

#include <optional>
#include "Ray.hpp"
#include "Color.hpp"
#include "Material.hpp"

namespace Ray2d {
    namespace Computations {
        #define NO_INTERSECTION 10000000000.0f

        float cross(const glm::vec2 &lhs, const glm::vec2 &rhs);

        class Obstacle {
        public:
            virtual float rayIntersect(Ray &ray) = 0;
            virtual glm::vec2 getNormal(glm::vec2 &point) = 0;
            virtual Material& getMaterial(void) = 0;
        };

    }
}