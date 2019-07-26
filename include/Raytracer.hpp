#pragma once

#include <random>

#include "Light/Light.hpp"
#include "Light/PointLight.hpp"
#include "Obstacle/Obstacle.hpp"
#include "Obstacle/Segment.hpp"
#include "Renderer.hpp"
#include "Ray.hpp"
#include "Utils.hpp"

namespace Ray2d {
    namespace Computations {
        #define INF 100000000000.0

        class Raytracer {
        private:
            Graphics::Renderer *renderer;
            std::vector<glm::vec2> rayVertice;
            std::vector<glm::vec3> rayColor;
            int ray_ind;

            std::vector<Obstacle*> obstacle;
            std::vector<Light*> light;

            int light_nb;
            int obstacle_nb;

            int batch;
            int max_depth;
            bool compute;
    
            void rayTrace(Ray &ray);
            void addRayToBatch(Ray &ray, float dist);

        public:
            Raytracer(Graphics::Renderer &renderer, const int batch, const int max_depth);
            void run(void);
        };
    }
}