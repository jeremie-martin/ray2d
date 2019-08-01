#pragma once

#include "Obstacle/Obstacle.hpp"

namespace Ray2d {
    namespace Computations {
        class Sphere : public Obstacle {
        private:

        public:
            glm::vec2 center;
            float radius;
            Material material;

            Sphere(const glm::vec2 &center, const float &radius, Material material);
            virtual float rayIntersect(Ray &ray) override;
            virtual glm::vec2 getNormal(glm::vec2 &point) override;
            virtual Material& getMaterial(void) override;
        };
    }
}