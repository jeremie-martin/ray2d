#include "Raytracer.hpp"

namespace Ray2d {
    namespace Computations {
        Raytracer::Raytracer(Graphics::Renderer &renderer, const int batch, const int max_depth) :
        renderer(&renderer), batch(batch), max_depth(max_depth), compute(true), light_nb(0), obstacle_nb(0), ray_ind(0) {
            rayVertice.resize(batch*2 + max_depth*2);
            rayColor.resize(batch*2 + max_depth*2);
        }

        void Raytracer::run(void) {
            obstacle.push_back(new Segment(glm::vec2(0.5f, -0.2f), glm::vec2(0.7, 0.3f)));
            obstacle.push_back(new Segment(glm::vec2(-1.5, 0.7f), glm::vec2(-1.2f, 0.1f)));
            obstacle.push_back(new Segment(glm::vec2(-0.4, -0.4f), glm::vec2(-0.2f, -0.6f)));
            light.push_back(new SegmentLight(glm::vec2(-0.3f, -0.2f), glm::vec2(-0.8f, 0.5f), 1.0f));
            light.push_back(new PointLight(glm::vec2(0.6f, 0.4f), std::vector<int>({450, 550, 650}), 20.0f));
            light.push_back(new PointLight(glm::vec2(-1.0f, 0.8f), std::vector<int>({450, 475, 500}), 5.0f));
            
            obstacle_nb = obstacle.size();
            light_nb = light.size();

            while(true) {
                double compute_start = glfwGetTime();
                
                if(compute)
                    while(ray_ind < batch) {
                        Ray ray = chooseLight()->generateRay();
                        rayTrace(ray);
                    }
   
                if(renderer->update(rayVertice, rayColor, ray_ind, glfwGetTime() - compute_start, compute) == WINDOW_CLOSE)
                    break;
                ray_ind = 0;
            }
        }

        std::vector<float> Raytracer::constructVectorOfLigthIntensity(void) {
            std::vector<float> lightIntensity;
            for(auto &l: light)
                lightIntensity.push_back(l->getIntensity());

            return lightIntensity;
        }

        Light *Raytracer::chooseLight(void) {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            static std::vector<float> ligthIntensity = constructVectorOfLigthIntensity();
            static std::discrete_distribution<> d(ligthIntensity.begin(), ligthIntensity.end());

            return light[d(gen)];
        }

        void Raytracer::addRayToBatch(Ray &ray, float dist) {
            rayVertice[ray_ind] = ray.getOrigin();
            rayColor[ray_ind] = Graphics::wavelengthToRGB(ray.getColor());
            rayVertice[ray_ind + 1] = rayVertice[ray_ind] + ray.dir * dist;
            rayColor[ray_ind + 1] = rayColor[ray_ind];

            ray_ind += 2;
        }

        void Raytracer::rayTrace(Ray &ray) {
            Obstacle *obstacle_nearest = nullptr;
            float distance_nearest = INF;
            for(auto &o: obstacle) {
                float dist = o->rayIntersect(ray);
                if(dist < distance_nearest) {
                    obstacle_nearest = o;
                    distance_nearest = dist;
                }
            }

            addRayToBatch(ray, distance_nearest);
        }
    }
}



