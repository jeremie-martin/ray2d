#pragma once


#include "Obstacle/Obstacle.hpp"

namespace Ray2d {
    namespace Computations {
        class Segment : public Obstacle {
        private:
            glm::vec2 p1;
            glm::vec2 p2;

        public:
            Segment(glm::vec2 p1, glm::vec2 p2);
            virtual float rayIntersect(Ray &ray) override;
        };
    }
}