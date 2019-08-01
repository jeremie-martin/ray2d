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

std::random_device rd;
std::mt19937 gen;

int main(int argc, char *argv[])
{
    glm::vec3 a;
    gen = std::mt19937(rd());

    Ray2d::Graphics::WindowWrapper winWrap(1270, 720);
    Ray2d::Graphics::Renderer renderer(winWrap, 4);
    Ray2d::Computations::Raytracer raytracer(renderer, 100000, 6);
    
    raytracer.run();

    return 0;
}
