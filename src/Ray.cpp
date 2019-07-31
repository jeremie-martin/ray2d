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

        void Ray::reflect(glm::vec2 normal)
        {
            //glm::vec2 ray_vec = dir - origin;
            //glm::vec2 new_dir = ray_vec + (normal * (-2 * glm::dot(ray_vec, normal) / glm::dot(normal, normal)));
            //glm::vec2 new_origin = [x2,y2], 0.99999) + arr_mul_const(origin, 0.00001);

            double t = 2.0 * (normal.x * dir.x + normal.y * dir.y) / (normal.x * normal.x + normal.y * normal.y);
            dir.x -= t * normal.x;
            dir.y -= t * normal.y;
            //slope = dir.y / dir.x;
        }

        glm::vec2 Ray::getOrigin(void) { return origin; }
        glm::vec2 Ray::getDir(void) { return dir; }
        int Ray::getColor(void) { return color; }
        void Ray::setOrigin(const glm::vec2 &newOrigin) { origin = newOrigin; }
        void Ray::setDir(const glm::vec2 &newDir) { dir = newDir; }
        void Ray::setColor(const int &newColor) { color = newColor; }
    }
}