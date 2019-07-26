#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GL/gl3w.h>    // Initialize with gl3wInit()
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "camera.h"

namespace Ray2d {
    namespace Graphics {
        class WindowWrapper {
        private:
            GLFWwindow *window;

            std::string title;
            std::string aaa;
            Camera *camera;

            //ImGuiIO *io;

            int width;
            int height;

            bool is_visible;

            float deltaTime;
            float lastFrame;


            static void framebuffer_size_callback(GLFWwindow* window, int new_width, int new_height);
            static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

        public:
        
            float lastX;
            float lastY;
            bool firstMouse;
            
            WindowWrapper(const int width, const int height, const bool is_visible=true, const std::string &title=std::string("Ray2d"));
            ~WindowWrapper() {};

            void processInput(void);

            GLFWwindow* getWindow(void);
            void setWindow(GLFWwindow* window);

            Camera* getCamera(void);
            void setCamera(Camera* camera);

            int getWidth(void);
            void setWidth(int width);
            
            int getHeight(void);
            void setHeight(int height);
        };
    }
}