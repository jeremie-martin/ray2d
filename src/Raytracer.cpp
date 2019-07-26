#include "Raytracer.hpp"

namespace Ray2d {
    namespace Computations {
        Raytracer::Raytracer(Graphics::Renderer &renderer, const int batch) : renderer(&renderer), batch(batch), compute(false) {
            rayVertice.resize(batch);
            rayColor.resize(batch);
        }

        void Raytracer::run(void) {
            PointLight l(glm::vec2(-0.5f, 0.5f), 480);

            while(true) {
                double compute_start = glfwGetTime();
                if(compute)
                    for(int i = 0; i < batch; i += 2) {
                        Ray ray = l.generateRay();
                        rayVertice[i] = ray.getOrigin();
                        rayColor[i] = Graphics::wavelengthToRGB(ray.getColor());
                        rayVertice[i+1] = rayVertice[i] + ray.getDir()*4.0f;
                        rayColor[i+1] = rayColor[i];
                    }
   
                if(renderer->update(rayVertice, rayColor, glfwGetTime() - compute_start, compute) == WINDOW_CLOSE)
                    break;
            }
        }

        void Raytracer::rayTrace(Ray &ray) {

        }
    }
}



