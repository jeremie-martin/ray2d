#include "Light/SegmentLight.hpp"

namespace Ray2d {
    namespace Computations {
        SegmentLight::SegmentLight(glm::vec2 p1, glm::vec2 p2, float intensity) : p1(p1), p2(p2), intensity(intensity), type(RAINBOW) {
            glm::vec2 vec_p1_p2 = p2 - p1;
            normal = glm::vec2(-vec_p1_p2[1], vec_p1_p2[0]);
        }

        SegmentLight::SegmentLight(glm::vec2 p1, glm::vec2 p2, int wavelength, float intensity) : p1(p1), p2(p2), monochromaticWavelength(wavelength), intensity(intensity), type(MONOCHROMATIC) {
            glm::vec2 vec_p1_p2 = p2 - p1;
            normal = glm::vec2(-vec_p1_p2[1], vec_p1_p2[0]);
        }
        SegmentLight::SegmentLight(glm::vec2 p1, glm::vec2 p2, std::vector<int> wavelengths, float intensity) : p1(p1), p2(p2), wavelengths(wavelengths), intensity(intensity), type(POLYCHROMATIC) {
            glm::vec2 vec_p1_p2 = p2 - p1;
            normal = glm::vec2(-vec_p1_p2[1], vec_p1_p2[0]);
        }
        Ray SegmentLight::generateRay(void) {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            static std::uniform_real_distribution<> dis_1_2(0.0f, 1.0f);

            float interpol = dis_1_2(gen);
            float color;

            switch (type)
            {
            case RAINBOW:
                color = int(interpol * (WAVELENGTH_MAX-WAVELENGTH_MIN)) + WAVELENGTH_MIN;
                break;

            case MONOCHROMATIC:
                color = monochromaticWavelength;
                break;

            case POLYCHROMATIC:
                color = wavelengths[rand() % wavelengths.size()];
                break;
            }
            //printf("%d\n", color);
                
            return Ray((interpol * p1) + ((1-interpol) * p2), normal, color);
        }

        float SegmentLight::getIntensity(void) {
            return intensity;
        }
    }
}