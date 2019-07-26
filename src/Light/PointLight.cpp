#include "Light/PointLight.hpp"

namespace Ray2d {
    namespace Computations {
        PointLight::PointLight(glm::vec2 pos) : pos(pos), type(RAINBOW) {}
        PointLight::PointLight(glm::vec2 pos, int wavelength) : pos(pos), monochromaticWavelength(wavelength), type(MONOCHROMATIC) {}
        PointLight::PointLight(glm::vec2 pos, std::vector<int> wavelengths) : pos(pos), wavelengths(wavelengths), type(POLYCHROMATIC) {}

        Ray PointLight::generateRay(void) {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            static std::uniform_real_distribution<> dis_1_2(0, PI*2.0);

            float angle = dis_1_2(gen);
            float color;

            switch (type)
            {
            case RAINBOW:
                color = int((angle * (WAVELENGTH_MAX - WAVELENGTH_MIN) / (PI*2.0)) + WAVELENGTH_MIN);
                break;

            case MONOCHROMATIC:
                color = monochromaticWavelength;
                break;

            case POLYCHROMATIC:
                color = wavelengths[rand() % wavelengths.size()];
                break;
            }
            //printf("%d\n", color);
                
            return Ray(pos, glm::vec2(cos(angle), sin(angle)), color);
        }
    }
}