#include "Light/PointLight.hpp"

namespace Ray2d {
    namespace Computations {
        PointLight::PointLight(glm::vec2 pos, int wavelength) : pos(pos), monochromaticWavelength(wavelength), is_monochromatic(true) {}
        PointLight::PointLight(glm::vec2 pos, std::vector<int> wavelengths) : pos(pos), wavelengths(wavelengths), is_monochromatic(false) {}

        Ray PointLight::generateRay(void) {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            static std::uniform_real_distribution<> dis_1_2(0, PI*2.0);

            float angle = dis_1_2(gen);
            float color;

            if(is_monochromatic)
                color = monochromaticWavelength;
            else
                color = wavelengths[rand() % wavelengths.size()];
                
            return Ray(pos, glm::vec2(cos(angle), sin(angle)), color);
        }
    }
}