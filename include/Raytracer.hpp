#pragma once

#include <random>

#include "Light/PointLight.hpp"
#include "Renderer.hpp"
#include "Ray.hpp"
#include "Utils.hpp"

namespace Ray2d {
    namespace Computations {
        class Raytracer {
        private:
            Graphics::Renderer *renderer;
            std::vector<glm::vec2> rayVertice;
            std::vector<glm::vec3> rayColor;

            int batch;
            bool compute;
    
            void rayTrace(Ray &ray);

        public:
            Raytracer(Graphics::Renderer &renderer, const int batch);
            void run(void);
        };
    }
}