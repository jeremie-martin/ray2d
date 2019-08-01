#include <benchmark/benchmark.h>
#include "WindowWrapper.hpp"
#include "Renderer.hpp"
#include <random>
#include <glm/gtc/random.hpp>

#include <iostream>
#include "WindowWrapper.hpp"
#include "Renderer.hpp"
#include "Raytracer.hpp"
#include "Color.hpp"

#include "Light/Light.hpp"
#include "Light/PointLight.hpp"
#include "Light/SegmentLight.hpp"
#include "Obstacle/Obstacle.hpp"
#include "Obstacle/Segment.hpp"
#include "Obstacle/Sphere.hpp"

std::random_device rd;
std::mt19937 gen;

namespace RC = Ray2d::Computations;

int main(int argc, char *argv[])
{
    glm::vec3 a;
    gen = std::mt19937(rd());

    std::vector<RC::Obstacle*> obstacle;
    std::vector<RC::Light*> light;
    
    obstacle.push_back(new RC::Segment(glm::vec2(-1.5, 0.7f), glm::vec2(-1.2f, 0.1f), RC::Material(1.0, 0.0, 1.0, 1.0)));
    //obstacle.push_back(new RC::Sphere(glm::vec2(0.3f, -0.4f), 0.4f, RC::Material(1.0, 0.5, 0.2, 1.5)));
    //light.push_back(new SegmentLight(glm::vec2(-0.3f, -0.2f), glm::vec2(-0.8f, 0.5f), 1.0f));
    light.push_back(new RC::PointLight(glm::vec2(1.4f, 0.3f), std::vector<int>({550}), 3.0f));
    //light.push_back(new PointLight(glm::vec2(-1.0f, 0.8f), std::vector<int>({425, 450, 475, 500, 525, 550}), 5.0f));
    std::vector<int> wavelengths(WAVELENGTH_NB);
    std::generate(wavelengths.begin(), wavelengths.end(), [n = WAVELENGTH_MIN] () mutable { return n++; });
    light.push_back(new RC::PointLight(glm::vec2(-1.0f, 0.8f), wavelengths, 20.0f));

    Ray2d::Graphics::WindowWrapper winWrap(1270, 720);
    Ray2d::Graphics::Renderer renderer(winWrap, 4);
    RC::Raytracer raytracer(renderer, obstacle, light, 100000, 6);
    
    raytracer.run();

    return 0;
}
