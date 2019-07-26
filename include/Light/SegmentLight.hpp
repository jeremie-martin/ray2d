#pragma once

#include "Light/Light.hpp"
#include "Random.hpp"
#include <vector>

using Random = effolkronium::random_static;

namespace Ray2d {
    namespace Computations {
        class SegmentLight : public Light {
        typedef enum {MONOCHROMATIC, POLYCHROMATIC, RAINBOW} Type;

        private:
            std::vector<int> wavelengths;
            glm::vec2 p1;
            glm::vec2 p2;
            glm::vec2 normal;
            
            Type type;
            int monochromaticWavelength;
            float intensity;

        public:
            SegmentLight(glm::vec2 p1, glm::vec2 p2, std::vector<int> wavelengths, float intensity = 1.0f);
            SegmentLight(glm::vec2 p1, glm::vec2 p2, int wavelength, float intensity = 1.0f);
            SegmentLight(glm::vec2 p1, glm::vec2 p2, float intensity = 1.0f);
            virtual Ray generateRay(void) override;
            virtual float getIntensity(void) override;
        };
    }
}