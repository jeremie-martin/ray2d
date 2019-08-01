#include "Obstacle/Material.hpp"
#include <stdio.h>
namespace Ray2d {
    namespace Computations {
        Material::Material(void) : absorption(0.0f), mirror(0.0f), fresnel(0.0f), ior(0.0f) { }
        Material::Material(float absorption, float mirror, float fresnel, float ior) : ior(ior) {
            float tot = absorption + mirror + fresnel;
            this->absorption = absorption / tot ;
            this->mirror = mirror / tot;
            this->fresnel = fresnel / tot;
        }
    }
}