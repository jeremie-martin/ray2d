#include "Obstacle/Sphere.hpp"

namespace Ray2d {
    namespace Computations {
        Sphere::Sphere(const glm::vec2 &center, const float &radius, Material material) : center(center), radius(radius), material(material) { }

        float Sphere::rayIntersect(Ray &ray)  {
            glm::vec2 oc = ray.origin - center;
            float b = glm::dot(oc, ray.dir);
            float c = glm::dot(oc, oc) - radius*radius;
            float D = b*b - c;
            
            if(D < 0)
                return NO_INTERSECTION;

            float t0 = -b - std::sqrt(D);
            float t1 = -b + std::sqrt(D);

            if(t1 < 0)
                return NO_INTERSECTION;

            float tHit = t0;
            if(tHit < 0)
                tHit = t1;
                
            return tHit;
        }

        glm::vec2 Sphere::getNormal(glm::vec2 &point) {
            return glm::normalize(point - center);
        }

        Material& Sphere::getMaterial(void) {
            return material;
        }
   
    }
}