#pragma once

#include "Light/Light.hpp"
#include "Random.hpp"
#include <vector>

using Random = effolkronium::random_static;

namespace Ray2d {
    namespace Computations {
        class PointLight : public Light {
        private:
            std::vector<int> wavelengths;
            glm::vec2 pos;

            int monochromaticWavelength;
            bool is_monochromatic;

        public:
            PointLight(glm::vec2 pos, std::vector<int> wavelengths);
            PointLight(glm::vec2 pos, int wavelength);
            virtual Ray generateRay(void) override;
        };
    }
}