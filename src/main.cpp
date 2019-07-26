#include <benchmark/benchmark.h>
#include "WindowWrapper.hpp"
#include "Renderer.hpp"
#include <random>
#include <glm/gtc/random.hpp>

#define BATCH 100000

/*     std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis_pos(0, 3.14159265*2.0);
    std::uniform_real_distribution<> dis_col(0, 1.0);

    // Define another benchmark
static void Array1(benchmark::State& state) {
    for (auto _ : state) {
        glm::vec2 aaa[BATCH];
        for(int i = 0; i < BATCH; i+=2) {
            double angle = dis_pos(gen);
            aaa[i] = glm::vec2(-0.5f, 0.5f);
            aaa[i+1] = 3.0f * glm::vec2(cos(angle), sin(angle));
        }
    }
}
BENCHMARK(Array1)->Unit(benchmark::kMillisecond);

static void Vector1(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<glm::vec2> rayVertices(BATCH);
        for(int i = 0; i < BATCH; i+=2) {
            double angle = dis_pos(gen);
            rayVertices[i] = glm::vec2(-0.5f, 0.5f);
            rayVertices[i+1] = 3.0f * glm::vec2(cos(angle), sin(angle));
        }
    }
}
BENCHMARK(Vector1)->Unit(benchmark::kMillisecond);

static void Vector2(benchmark::State& state) {
    std::vector<glm::vec2> rayVertices(BATCH);
    std::vector<int> angle(BATCH); 

    for (auto _ : state) {
        std::generate(angle.begin(), angle.end(), [&](){ return dis_pos(gen); });
        for(int i = 0; i < BATCH; i+=2) {
            rayVertices[i] = glm::vec2(-0.5f, 0.5f);
            rayVertices[i+1] = 3.0f * glm::vec2(cos(angle[i]), sin(angle[i]));
        }
    }
}
BENCHMARK(Vector2)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();

*/

#include <iostream>
#include "WindowWrapper.hpp"
#include "Renderer.hpp"
#include "Raytracer.hpp"
#include "Color.hpp"
#define BATCH 50000

int main(int argc, char *argv[])
{
    glm::vec3 a;

    Ray2d::Graphics::WindowWrapper winWrap(1270, 720);
    Ray2d::Graphics::Renderer renderer(winWrap, 1);
    Ray2d::Computations::Raytracer raytracer(renderer, 100000, 4);
    
    raytracer.run();

    return 0;
}
