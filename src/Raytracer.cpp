#include "Raytracer.hpp"

namespace Ray2d {
    namespace Computations {
        Raytracer::Raytracer(Graphics::Renderer &renderer, const int batch, const int max_depth) :
        renderer(&renderer), batch(batch), max_depth(max_depth), compute(true), light_nb(0), obstacle_nb(0), ray_ind(0) {
            rayVertice.resize(batch*2 + max_depth*2);
            rayColor.resize(batch*2 + max_depth*2);
        }

        void Raytracer::run(void) {
            //obstacle.push_back(new Segment(glm::vec2(0.5f, -0.2f), glm::vec2(0.7, 0.3f)));
            //obstacle.push_back(new Segment(glm::vec2(0.1, 0.7f), glm::vec2(0.2, 0.1f)));
            light.push_back(new PointLight(glm::vec2(0.0f, 0.0f)));
            
            obstacle_nb = obstacle.size();
            light_nb = light.size();

            while(true) {
                double compute_start = glfwGetTime();
                
                if(compute)
                    while(ray_ind < batch) {
                        Ray ray = light[rand() % light_nb]->generateRay();
                        rayTrace(ray);
                    }
   
                if(renderer->update(rayVertice, rayColor, ray_ind, glfwGetTime() - compute_start, compute) == WINDOW_CLOSE)
                    break;
                ray_ind = 0;
            }
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



