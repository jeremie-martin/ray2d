#include "Obstacle/Segment.hpp"

namespace Ray2d {
    namespace Computations {
        Segment::Segment(glm::vec2 p1, glm::vec2 p2) : p1(p1), p2(p2) {}

        std::optional<glm::vec2> Segment::rayIntersect(Ray &ray) {
            glm::vec2 v1 = ray.origin - p1;
            glm::vec2 v2 = p2 - p1;
            glm::vec2 v3 = glm::vec2(-ray.dir.y, ray.dir.x);
            float dot_tmp = glm::dot(v2, v3);

            float t1 = Computations::cross(v2, v1) / dot_tmp;
            if (t1 < 0.0)
                return std::nullopt;

            float t2 = glm::dot(v1, v3) / dot_tmp;
            if (t2 < 0.0 || t2 > 1.0)
                return std::nullopt;

            return ray.origin + ray.dir * t1;
        }
    }
}