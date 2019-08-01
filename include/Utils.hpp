#pragma once

#include <random>

#define PI 3.14159265358979323846

extern std::random_device rd;
extern std::mt19937 gen;
static std::uniform_real_distribution<> dis_0_2pi(0, PI*2.0);
static std::uniform_real_distribution<> dis_0_1(0, 1.0f);
