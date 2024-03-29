#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace Ray2d {
    namespace Computations {
        class Ray {
        private:
        public:
            glm::vec2 origin;
            glm::vec2 dir;
            int color;

            Ray(glm::vec2 origin, glm::vec2 dir);
            Ray(glm::vec2 origin, glm::vec2 dir, int color);
            Ray(const Ray& ray);

            glm::vec2 getPoint(float dist);
            glm::vec2 getOrigin(void);
            glm::vec2 getDir(void);

            int getColor(void);
            void setOrigin(const glm::vec2 &newOrigin);
            void setDir(const glm::vec2 &newDir);
            void setColor(const int &newColor);
            void reflect(glm::vec2 normal);
        };
    }
}

