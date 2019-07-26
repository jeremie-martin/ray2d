#include <Ray.hpp>

namespace Ray2d {
    namespace Computations {
        Ray::Ray(glm::vec2 origin, glm::vec2 dir) : origin(origin), dir(dir), color(480) { }
        Ray::Ray(glm::vec2 origin, glm::vec2 dir, int color) : origin(origin), dir(dir), color(color) { }

        Ray::Ray(const Ray& ray) {
            this->origin = ray.origin;
            this->dir = ray.dir;
            this->color = ray.color;
        }

        glm::vec2 Ray::getPoint(float dist) {
            return origin + dir * dist;
        }

        glm::vec2 Ray::getOrigin(void) { return origin; }
        glm::vec2 Ray::getDir(void) { return dir; }
        int Ray::getColor(void) { return color; }
        void Ray::setOrigin(const glm::vec2 &newOrigin) { origin = newOrigin; }
        void Ray::setDir(const glm::vec2 &newDir) { dir = newDir; }
        void Ray::setColor(const int &newColor) { color = newColor; }
    }
}