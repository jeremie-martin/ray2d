#pragma once

#include "Obstacle/Obstacle.hpp"

namespace Ray2d {
    namespace Computations {
        class Segment : public Obstacle {
        private:

        public:
            glm::vec2 p1;
            glm::vec2 p2;
            glm::vec2 normal;
            Material material;

            Segment(glm::vec2 p1, glm::vec2 p2, Material material);
            virtual float rayIntersect(Ray &ray) override;
            virtual glm::vec2 getNormal(glm::vec2 &point) override;
            virtual Material& getMaterial(void) override;
        };
    }
}