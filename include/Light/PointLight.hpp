#pragma once

#include "Light/Light.hpp"
#include <vector>

namespace Ray2d {
    namespace Computations {
        class PointLight : public Light {
        typedef enum {MONOCHROMATIC, POLYCHROMATIC, RAINBOW} Type;

        private:
            std::vector<int> wavelengths;
            glm::vec2 pos;
            float intensity;
            
            Type type;
            int monochromaticWavelength;

        public:
            PointLight(glm::vec2 pos, std::vector<int> wavelengths, float intensity = 1.0f);
            PointLight(glm::vec2 pos, int wavelength, float intensity = 1.0f);
            PointLight(glm::vec2 pos, float intensity = 1.0f);
            virtual Ray generateRay(void) override;
            virtual float getIntensity(void) override;
        };
    }
}