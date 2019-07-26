#pragma once

#include "WindowWrapper.hpp"

#include <vector>

#include <boost/preprocessor/stringize.hpp>

#include "shader.h"
#include "stb_image.h"
#include <stdlib.h>

#define WINDOW_CLOSE -1
#define WINDOW_OPEN 0

#define SHADER_RAY_FRAG_PATH shader/ray.fs
#define SHADER_RAY_VERTEX_PATH shader/ray.vs
#define SHADER_POST_FRAG_PATH shader/postprocessing.fs
#define SHADER_POST_VERTEX_PATH shader/postprocessing.vs

#define INCLUDE_FILE(path) BOOST_PP_STRINGIZE(path)

// Include shaders source files
static const char *shader_ray_frag_src =
#include INCLUDE_FILE(SHADER_RAY_FRAG_PATH)
;

static const char *shader_ray_vertex_src =
#include INCLUDE_FILE(SHADER_RAY_VERTEX_PATH)
;

static const char *shader_post_frag_src =
#include INCLUDE_FILE(SHADER_POST_FRAG_PATH)
;

static const char *shader_post_vertex_src =
#include INCLUDE_FILE(SHADER_POST_VERTEX_PATH)
;

namespace Ray2d {
    namespace Graphics {
        class Renderer {
        private:
            WindowWrapper *win_wrapper;
            Camera *camera;
            GLFWwindow *window;

            Shader *shader_ray;
            Shader *shader_post;

            GLuint rayVBO_points;
            GLuint rayVBO_colors;
            GLuint rayVAO;

            GLuint screenVAO;
            GLuint screenVBO;

            GLuint framebuffer_MSAA;
            GLuint intermediateFBO;
            GLuint screenTexture;
            GLuint colorTexture;

            int MSAA;
            int width;
            int height;

            float brightness;
            float contrast;
            float gamma;
            bool denoise;

            bool imgui_show_window;
            bool space_is_released;

            double compute_time;
            double draw_time;
            double ray_nb;

            bool *compute;

            void imgui_update(void);
            void imgui_render(void);
            void draw(std::vector<glm::vec2> &rayVertices, std::vector<glm::vec3> &rayColor);

        public:
            Renderer(WindowWrapper &wrap, const int MSAA=1);
            ~Renderer() {};

            int update(std::vector<glm::vec2> &rayVertices, std::vector<glm::vec3> &rayColor, double compute_time, bool &compute);
        };
    }
}