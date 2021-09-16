#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader/shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);//���U�^�ը�ưʺA�վ㵡�f�j�p
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);//�������f

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

float vertices[] = {
         0.5f,  0.5f, 0.0f,    1.0f, 0.0f, 0.0f,      // top right
         0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,     // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,     // bottom left
        -0.5f,  0.5f, 0.0f    ,1.0f, 0.0f, 1.0f  // top left    
};

unsigned int indices[] = {  
    0, 2, 6, 
    2, 4, 6  
};

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//���Uesc����
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
    glfwInit();//��l��
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);//�e,��,�W�� ��^GLFWwindows��H
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) { //��l��GLAD
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //----ImGui init ----
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    //----ImGUi contrule block----
    bool drawTriangle = true;
    float size = 1.0f;
    float color[4] = { 0.8f, 0.2f, 0.03f, 1.0f };
    float rotate = 0.0f;

    Shader ourShader("3.3.shader.vs", "3.3.shader.fs");

    //�ͦ�Buffer Object
    unsigned int VBO;
    glGenBuffers(1, &VBO);//�ͦ�VBO��H
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);//�ͦ�VAO��H
    glBindVertexArray(VAO);
    unsigned int EBO;
    glGenBuffers(1, &EBO);//�ͦ�EBO��H


    // 2.�⳻�I�Ʋսƻs��w�Ĥ���OPenGL�ϥ�
    glBindBuffer(GL_ARRAY_BUFFER, VBO);// �j�w�w�Ĩ�GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//�N�w�q�����I�ƻs�i�w�Ĥ�
    // GL_STATIC_DRAW �G�ƾڴX�G�����ܡC
    // GL_DYNAMIC_DRAW�G�ƾڷ|�Q���ܡC
    // GL_STREAM_DRAW �G�ƾڨC�����Q���ܡC
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //3.�]�m���I�ݩʫ���
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //�C��
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//���U�վ㵡�f���
    glfwSetKeyCallback(window, key_callback);//���U��`������

    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�M�Ų`���C��w�ĩM�`�׽w��

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // create transformations
        float rad = (3.14159265358 / 180) * rotate;
        glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        transform = glm::rotate(transform, rad, glm::vec3(0.0f, 0.0f, 1.0f));

        //ø�s�T����
        ourShader.use();
        ourShader.setFloat("size", size);
        ourShader.setVec4("color", color[0], color[1], color[2], color[3]);
        ourShader.setMat4("transform", transform);
        if (drawTriangle)
        {
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        //ø�simgui����
        ImGui::Begin("My name");
        ImGui::Text("Hello World");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Checkbox("Draw Triangle", &drawTriangle);
        ImGui::SliderFloat("Size", &size, 0.5f, 2.0f);
        ImGui::SliderFloat("Rotate", &rotate, 0.0f, 270.0f);
        ImGui::ColorEdit4("Color", color);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        glfwSwapBuffers(window);//�洫�C��w��
        glfwPollEvents();//�ˬdĲ�o�ƥ� ��p��L�ƹ�
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();//����and�R�����t�귽
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)//���U�^�ը�ưʺA�վ㵡�f�j�p
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    {
        if (mods & GLFW_MOD_CONTROL) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);//�������f
        }
    }
}