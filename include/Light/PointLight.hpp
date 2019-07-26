#pragma once

#include "Light/Light.hpp"
#include "Random.hpp"
#include <vector>

using Random = effolkronium::random_static;

namespace Ray2d {
    namespace Computations {
        class PointLight : public Light {
        typedef enum {MONOCHROMATIC, POLYCHROMATIC, RAINBOW} Type;

        private:
            std::vector<int> wavelengths;
            glm::vec2 pos;
            
            Type type;
            int monochromaticWavelength;
            
        public:
            PointLight(glm::vec2 pos, std::vector<int> wavelengths);
            PointLight(glm::vec2 pos, int wavelength);
            PointLight(glm::vec2 pos);
            virtual Ray generateRay(void) override;
        };
    }
}