#pragma once

#include <glm/glm.hpp>

namespace Ray2d {
    namespace Graphics {
        #define WAVELENGTH_MIN 380
        #define WAVELENGTH_MAX 780
        #define WAVELENGTH_NB (WAVELENGTH_MAX - WAVELENGTH_MIN)

        glm::vec3 wavelengthToRGB(int wavelength);
        float Adjust(float colour, float factor);

    }
}
