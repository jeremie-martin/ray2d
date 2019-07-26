#include "Light/PointLight.hpp"

namespace Ray2d {
    namespace Computations {
        PointLight::PointLight(glm::vec2 pos, float intensity) : pos(pos), type(RAINBOW), intensity(intensity) {}
        PointLight::PointLight(glm::vec2 pos, int wavelength, float intensity) : pos(pos), monochromaticWavelength(wavelength), type(MONOCHROMATIC), intensity(intensity) {}
        PointLight::PointLight(glm::vec2 pos, std::vector<int> wavelengths, float intensity) : pos(pos), wavelengths(wavelengths), type(POLYCHROMATIC), intensity(intensity) {}

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

        float PointLight::getIntensity(void) {
            return intensity;
        }
    }
}