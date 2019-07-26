#include "Obstacle/Obstacle.hpp"

namespace Ray2d {
    namespace Computations {
        float cross(const glm::vec2 &lhs, const glm::vec2 &rhs) {
            return lhs[0] * rhs[1] - lhs[1] * rhs[0];
        }
    }
}