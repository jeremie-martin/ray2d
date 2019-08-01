#include "Raytracer.hpp"

namespace Ray2d {
    namespace Computations {
        Raytracer::Raytracer(Graphics::Renderer &renderer, const int batch, const int max_depth) :
        renderer(&renderer), batch(batch), max_depth(max_depth), compute(true), light_nb(0), obstacle_nb(0), ray_ind(0) {
            rayVertice.resize(batch*2 + max_depth*2);
            rayColor.resize(batch*2 + max_depth*2);
        }

        void Raytracer::run(void) {
            //obstacle.push_back(new Segment(glm::vec2(1.2f, -0.4f), glm::vec2(1.4, 0.3f)));
            //obstacle.push_back(new Segment(glm::vec2(-1.5, 0.7f), glm::vec2(-1.2f, 0.1f)));
            //obstacle.push_back(new Segment(glm::vec2(-0.4, -0.6f), glm::vec2(-0.2f, -0.8f)));
            obstacle.push_back(new Sphere(glm::vec2(0.3f, -0.4f), 0.4f, Material(0.0, 0.5, 0.0, 1.5)));
            //light.push_back(new SegmentLight(glm::vec2(-0.3f, -0.2f), glm::vec2(-0.8f, 0.5f), 1.0f));
            light.push_back(new PointLight(glm::vec2(1.4f, 0.3f), std::vector<int>({550}), 3.0f));
            //light.push_back(new PointLight(glm::vec2(-1.0f, 0.8f), std::vector<int>({425, 450, 475, 500, 525, 550}), 5.0f));
            std::vector<int> wavelengths(WAVELENGTH_NB);
            std::generate(wavelengths.begin(), wavelengths.end(), [n = WAVELENGTH_MIN] () mutable { return n++; });
            light.push_back(new PointLight(glm::vec2(-1.0f, 0.8f), wavelengths, 20.0f));
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
            static std::vector<float> ligthIntensity = constructVectorOfLigthIntensity();
            static std::discrete_distribution<> d(ligthIntensity.begin(), ligthIntensity.end());
            return light[d(gen)];
        }

        void Raytracer::addRayToBatch(glm::vec2 &p1, glm::vec2 &p2, int color) {
            rayVertice[ray_ind] = p1;
            rayColor[ray_ind] = Graphics::wavelengthToRGB(color);
            rayVertice[ray_ind + 1] = p2;
            rayColor[ray_ind + 1] = rayColor[ray_ind];

            ray_ind += 2;
        }

        void Raytracer::rayTrace(Ray &ray, int depth) {
            if(depth >= max_depth)
                return;

            Obstacle *obstacle_nearest = nullptr;
            float distance_nearest = INF;
            for(auto &o: obstacle) {
                float dist = o->rayIntersect(ray);
                if(dist < distance_nearest) {
                    obstacle_nearest = o;
                    distance_nearest = dist;
                }
            }

            glm::vec2 intersection = ray.getPoint(distance_nearest);
            addRayToBatch(ray.origin, intersection, ray.color);

            if(obstacle_nearest != nullptr) { // An obstacle was hit
                Material &mat = obstacle_nearest->getMaterial();
                float r = dis_0_1(gen);

                if(r < mat.absorption)
                    return;
                else if(r < mat.absorption + mat.mirror)
                    this->mirror(ray, *obstacle_nearest, intersection);
                else
                    this->fresnel(ray, *obstacle_nearest, mat, intersection);

                rayTrace(ray, depth + 1);
            }
        }

        void Raytracer::mirror(Ray &ray, Obstacle &obstacle_nearest, glm::vec2 &intersection) {
            ray.origin = intersection;
            glm::vec2 normal = obstacle_nearest.getNormal(intersection);
            
            ray.origin += normal * 0.00001f;
            ray.reflect(normal);
        }

        void Raytracer::fresnel(Ray &ray, Obstacle &obstacle_nearest, Material &mat, glm::vec2 &intersection) {
            ray.origin = intersection;
            glm::vec2 normal = obstacle_nearest.getNormal(intersection);

            float cosI = glm::dot(ray.dir, normal);
            float n1, n2;
            if (cosI > 0) { // Ray is inside
                n1 = mat.ior;
                n2 = 1.0f;
                normal = - normal;
            }
            
            else { // Ray is outside
                n2 = mat.ior;
                n1 = 1.0f;
                cosI = -cosI;
            }

            float n1_n2 = n1 / n2;
            float cosT = 1.0f - pow(n1_n2, 2.0f) * (1.0f - pow(cosI, 2.0f));

            if (cosT < 0.0f) { // Total internal reflection
                ray.origin += normal * 0.00001f;
                ray.reflect(normal);
            }

            else {
                cosT = sqrt(cosT);

                // Fresnel coefficient
                float R = (pow((n1 * cosI - n2 * cosT) / (n1 * cosI + n2 * cosT), 2.0f) + pow((n2 * cosI - n1 * cosT) / (n1 * cosT + n2 * cosI), 2.0f)) * 0.5f;

                if (dis_0_1(gen) < R) { // Reflexion
                    ray.origin += normal * 0.00001f;
                    ray.reflect(normal);
                }
                else { //Refraction
                    ray.origin -= normal * 0.00001f;
                    ray.dir = glm::normalize(ray.dir * n1_n2 + normal * (n1_n2 * cosI - cosT));
                }
            }
        }
    }
}



