#include "WindowWrapper.hpp"

namespace Ray2d {
    namespace Graphics {
        WindowWrapper::WindowWrapper(const int width, const int height, const bool is_visible, const std::string &title)
            : width(width), height(height), is_visible(is_visible), title(title), deltaTime(0.0f), lastFrame(0.0f), lastX(10.0f), lastY(0.0f), firstMouse(true) {

            glfwInit();

            const char* glsl_version = "#version 430";
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
            if(is_visible == false)
                glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
                
            // Create window with graphics context
            window = glfwCreateWindow(width, height, "Ray2d", NULL, NULL);
            glfwMakeContextCurrent(window);
            glfwSwapInterval(1); // Enable vsync

            gl3wInit();

            // Setup Dear ImGui context
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

            // Setup Dear ImGui style
            ImGui::StyleColorsDark();
            //ImGui::StyleColorsClassic();

            // Setup Platform/Renderer bindings
            ImGui_ImplGlfw_InitForOpenGL(window, true);
            ImGui_ImplOpenGL3_Init(glsl_version);

            glfwSetWindowUserPointer(window, this);
            glfwSetFramebufferSizeCallback(window, this->framebuffer_size_callback);
            glfwSetCursorPosCallback(window, this->mouse_callback);

            //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            // Configure global opengl state
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Additive blending
            glDisable(GL_DEPTH_TEST);

            // load all OpenGL function pointers

            this->camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
        }

        void WindowWrapper::framebuffer_size_callback(GLFWwindow* window, int new_width, int new_height) {
            glViewport(0, 0, new_width, new_height);
        }

        void WindowWrapper::mouse_callback(GLFWwindow* windo, double xpos, double ypos) {
            void *data = glfwGetWindowUserPointer(windo);
            WindowWrapper *wrapper = static_cast<WindowWrapper *>(data);

            if (wrapper->firstMouse)
            {
                wrapper->lastX = xpos;
                wrapper->lastY = ypos;
                wrapper->firstMouse = false;
            }

            float xoffset = xpos - wrapper->lastX;
            float yoffset = wrapper->lastY - ypos; // reversed since y-coordinates go from bottom to top

            wrapper->lastX = xpos;
            wrapper->lastY = ypos;
        }

        void WindowWrapper::processInput(void) {
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, true);

            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                camera->ProcessKeyboard(FORWARD, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                camera->ProcessKeyboard(BACKWARD, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                camera->ProcessKeyboard(LEFT, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                camera->ProcessKeyboard(RIGHT, deltaTime);
        }

        GLFWwindow* WindowWrapper::getWindow() {
            return this->window;
        }

        void WindowWrapper::setWindow(GLFWwindow* window) {
            this->window = window;
        }

        Camera* WindowWrapper::getCamera(void) {
            return this->camera;
        }

        void WindowWrapper::setCamera(Camera* camera) {
            this->camera = camera;
        }

        int WindowWrapper::getWidth() {
            return this->width;
        }

        void WindowWrapper::setWidth(int width) {
            this->width = width;
        }

        int WindowWrapper::getHeight() {
            return this->height;
        }

        void WindowWrapper::setHeight(int height) {
            this->height = height;
        }
    }
}