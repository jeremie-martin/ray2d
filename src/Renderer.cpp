#include "Renderer.hpp"

namespace Ray2d {
    namespace Graphics {
        Renderer::Renderer(WindowWrapper &wrap, const int MSAA) : win_wrapper(&wrap), MSAA(MSAA), brightness(0.5f), contrast(0.5f), gamma(0.5f),
                                                                  denoise(false), imgui_show_window(true), space_is_released(false), compute_time(0.0f), draw_time(0.0f) {
            window = this->win_wrapper->getWindow();
            camera = this->win_wrapper->getCamera();

            width = this->win_wrapper->getWidth();
            height = this->win_wrapper->getHeight();

            shader_ray = new Shader(std::move(shader_ray_frag_src), shader_ray_vertex_src);
            shader_post = new Shader(shader_post_frag_src, shader_post_vertex_src);

            // vertex attributes for a screen that fills the entire screen in Normalized Device Coordinates.
            const float screenVertices[] = {
                // positions   // texCoords
                -1.0f,  1.0f,  0.0f, 1.0f,
                -1.0f, -1.0f,  0.0f, 0.0f,
                1.0f, -1.0f,  1.0f, 0.0f,

                -1.0f,  1.0f,  0.0f, 1.0f,
                1.0f, -1.0f,  1.0f, 0.0f,
                1.0f,  1.0f,  1.0f, 1.0f
            };

            glGenBuffers(1, &rayVBO_points);
            glGenBuffers(1, &rayVBO_colors);

            glGenVertexArrays(1, &rayVAO);
            glBindVertexArray(rayVAO);
            glBindBuffer(GL_ARRAY_BUFFER, rayVBO_points);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
            glBindBuffer(GL_ARRAY_BUFFER, rayVBO_colors);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);

            // setup screen VAO
            glGenVertexArrays(1, &screenVAO);
            glGenBuffers(1, &screenVBO);
            glBindVertexArray(screenVAO);
            glBindBuffer(GL_ARRAY_BUFFER, screenVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(screenVertices), &screenVertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

            // configure MSAA framebuffer
            glGenFramebuffers(1, &framebuffer_MSAA);
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_MSAA);
            
            // create a multisampled color attachment texture
            unsigned int textureColorBufferMultiSampled;
            glGenTextures(1, &textureColorBufferMultiSampled);
            glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, textureColorBufferMultiSampled);
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, MSAA, GL_RGB32F, width, height, GL_TRUE);
            glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, textureColorBufferMultiSampled, 0);
            unsigned int rbo;
            glGenRenderbuffers(1, &rbo);
            glBindRenderbuffer(GL_RENDERBUFFER, rbo);
            glRenderbufferStorageMultisample(GL_RENDERBUFFER, MSAA, GL_DEPTH24_STENCIL8, width, height);
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            // configure second post-processing framebuffer
            glGenFramebuffers(1, &intermediateFBO);
            glBindFramebuffer(GL_FRAMEBUFFER, intermediateFBO);
            
            // create a color attachment texture
            glGenTextures(1, &screenTexture);
            glBindTexture(GL_TEXTURE_2D, screenTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glGenerateMipmap(GL_TEXTURE_2D);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture, 0);	// we only need a color buffer

            GLfloat param;
            glGetTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, &param);
            glGetTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, &param);
            glGetTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, &param);

            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                std::cout << "ERROR::FRAMEBUFFER:: Intermediate framebuffer is not complete!" << std::endl;
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            shader_ray->use();
            shader_post->setInt("screenTexture", 0);
        }

        int Renderer::update(std::vector<glm::vec2> &rayVertices, std::vector<glm::vec3> &rayColor, double compute_time, bool &compute) {
            this->compute = &compute;

            this->ray_nb = double(rayVertices.size() / 2);
            this->compute_time = compute_time;
            glfwPollEvents();
            win_wrapper->processInput();

            if(glfwWindowShouldClose(window))
                return WINDOW_CLOSE;
            static bool first = true;
            if((rand()%10) == 0 || first) {
            imgui_update();
            first = false;
            }

            if(compute)
                draw(rayVertices, rayColor);
            
            imgui_render();

            glfwSwapBuffers(window);

            return WINDOW_OPEN;
        }

        void Renderer::draw(std::vector<glm::vec2> &rayVertices, std::vector<glm::vec3> &rayColor) {
            double start_draw = glfwGetTime();
            
            glBindBuffer(GL_ARRAY_BUFFER, rayVBO_points);
            glBufferData(GL_ARRAY_BUFFER, sizeof(rayVertices[0]) * rayVertices.size(), rayVertices.data(), GL_DYNAMIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, rayVBO_colors);
            glBufferData(GL_ARRAY_BUFFER, sizeof(rayColor[0]) * rayColor.size(), rayColor.data(), GL_DYNAMIC_DRAW);

            // Draw scene as normal in multisampled buffers
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_MSAA);

            // Set transformation matrices		
            shader_ray->use();
            glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)width / (float)height, 0.1f, 1000.0f);
            shader_ray->setMat4("projection", projection);
            shader_ray->setMat4("view", camera->GetViewMatrix());
            shader_ray->setMat4("model", glm::mat4(1.0f));
            glBindVertexArray(rayVAO);
            glDrawArrays(GL_LINES, 0, rayVertices.size());

            // Blit multisampled buffer to normal colorbuffer of intermediate FBO
            glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer_MSAA);
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, intermediateFBO);
            glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

            // Render screen with scene's visuals as its texture image
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glDisable(GL_DEPTH_TEST);

            shader_post->use();
            shader_post->setFloat("brightness", (brightness - 0.5f) * 2.0f);
            shader_post->setFloat("contrast", contrast * 2.0f);
            shader_post->setFloat("gamma", gamma*3);
            glBindVertexArray(screenVAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, screenTexture); // Use the now resolved color attachment as the screen's texture
            
            // Update the texture (TODO: without recreating it from scratch)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glGenerateMipmap(GL_TEXTURE_2D);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            draw_time = glfwGetTime() - start_draw;
        }

        void Renderer::imgui_update(void) {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if(imgui_show_window == false) {
                if(ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter))) {
                    brightness = 0.5f;
                    contrast = 0.5f;
                    gamma = 0.5f;
                }

                if(ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Space))) {
                    imgui_show_window = true;
                    space_is_released = false;
                }
                else {
                    ImGui::EndFrame();
                    return;
                }
            }

            if(ImGui::IsKeyReleased(ImGui::GetKeyIndex(ImGuiKey_Space)))
                space_is_released = true;

            ImGui::Begin("Post processing", 0, ImGuiWindowFlags_AlwaysAutoResize);

            if(*compute) {
                char compute_time_str[100];
                sprintf(compute_time_str, "Compute: %dK/s", int((ray_nb / compute_time) / 1000.0));
                ImGui::Text(compute_time_str);

                char draw_time_str[100];
                sprintf(draw_time_str, "Draw:    %dK/s", int((ray_nb / draw_time) / 1000.0));
                ImGui::Text(draw_time_str);
            }
 
            ImGui::Checkbox("Compute", compute);

            ImGui::Checkbox("Denoise (not yet implemented)", &denoise);

            ImGui::SliderFloat("Brightness", &brightness, 0.0f, 1.0f);
            ImGui::SliderFloat("Contrast", &contrast, 0.0f, 1.0f);     
            ImGui::SliderFloat("Gamma", &gamma, 0.0f, 1.0f);

            if(ImGui::Button("Reset") || ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter))) {
                brightness = 0.5f;
                contrast = 0.5f;
                gamma = 0.5f;
            }

            ImGui::SameLine();
            ImGui::Text("Press 'enter' to reset the parameters");

            if(ImGui::Button("Hide") || (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Space)) && space_is_released)) {
                imgui_show_window = false;
                ImGui::End();
                ImGui::EndFrame();
                return;
            }

            ImGui::SameLine();
            ImGui::Text("Press 'space' to hide/show this window");

            ImGui::Button("Screenshot");
            ImGui::SameLine();
            ImGui::Text("(not yet implemented)");

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        void Renderer::imgui_render(void) {
            if(imgui_show_window) {
                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            }
        }
    }
}