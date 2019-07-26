#pragma once

#include <optional>
#include "Ray.hpp"
#include "Color.hpp"
#include "Utils.hpp"

namespace Ray2d {
    namespace Computations {
        float cross(const glm::vec2 &lhs, const glm::vec2 &rhs);

        class Obstacle {
        public:
            virtual std::optional<glm::vec2> rayIntersect(Ray &ray) = 0;
        };

    }
}