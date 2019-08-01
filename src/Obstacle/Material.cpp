#include "Obstacle/Material.hpp"
#include <stdio.h>
namespace Ray2d {
    namespace Computations {
        Material::Material(float absorption, float mirror, float fresnel, float ior) : ior(ior) {
            glm::vec3 v(absorption, mirror, fresnel);
            v = glm::normalize(v);
            this->absorption = v.x;
            this->mirror = v.y;
            this->fresnel = v.z;
        }
    }
}