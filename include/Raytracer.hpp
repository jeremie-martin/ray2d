#pragma once

#include <random>

#include "Light/Light.hpp"
#include "Light/PointLight.hpp"
#include "Light/SegmentLight.hpp"
#include "Obstacle/Obstacle.hpp"
#include "Obstacle/Segment.hpp"
#include "Obstacle/Sphere.hpp"
#include "Renderer.hpp"
#include "Ray.hpp"
#include "Utils.hpp"
#include <algorithm>
#include <vector>


namespace Ray2d {
    namespace Computations {
        #define INF 10000000000.0f

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
            
            Light *chooseLight(void);
            std::vector<float> constructVectorOfLigthIntensity(void);
            void rayTrace(Ray &ray, int depth = 0);
            void mirror(Ray &ray, Obstacle &obstacle_nearest, glm::vec2 &intersection);
            void fresnel(Ray &ray, Obstacle &obstacle_nearest, Material &mat, glm::vec2 &intersection);
            void addRayToBatch(glm::vec2 &p1, glm::vec2 &p2, int color);

        public:
            Raytracer(Graphics::Renderer &renderer, std::vector<Obstacle*> &obstacle, std::vector<Light*> &light, const int batch, const int max_depth);
            void run(void);
        };
    }
}