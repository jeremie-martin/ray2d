#pragma once

#include "Obstacle.hpp"

namespace Ray2d {
    namespace Computations {
        class Segment : public Obstacle {
        private:
            glm::vec2 p1;
            glm::vec2 p2;

        public:
            Segment(glm::vec2 p1, glm::vec2 p2);
            virtual std::optional<glm::vec2> rayIntersect(Ray &ray) override;
        };
    }
}