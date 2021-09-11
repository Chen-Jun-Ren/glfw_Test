#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader/shader.h"
#include "ext/glm/glm.hpp"
#include "ext/glm/gtc/matrix_transform.hpp"
#include "ext/glm/gtc/type_ptr.hpp"

#include "imgui.h"
#include "ext/imgui/backends/imgui_impl_opengl3.h"
#include "ext/imgui/backends/imgui_impl_glfw.h"
#include "ext/imgui/backends/imgui_impl_opengl3.cpp"
#include "ext/imgui/backends/imgui_impl_glfw.cpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);//註冊回調函數動態調整窗口大小
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);//關閉窗口

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
};

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//按下esc關閉
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
    glfwInit();//初始化
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);//寬,高,名稱 返回GLFWwindows對象
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) { //初始化GLAD
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
    glm::mat4 trans;
    trans = glm::rotate(trans, glm::radians(rotate), glm::vec3(0.0, 0.0, 1.0));

    Shader ourShader("D:/GitHub/glfw_Test/Shader/3.3.shader.vs", "D:/GitHub/glfw_Test/Shader/3.3.shader.fs");

    //生成Buffer Object
    unsigned int VBO;
    glGenBuffers(1, &VBO);//生成VBO對象
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);//生成VAO對象
    glBindVertexArray(VAO);

    // 2.把頂點數組複製到緩衝中供OPenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);// 綁定緩衝到GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//將定義的頂點複製進緩衝內
    // GL_STATIC_DRAW ：數據幾乎不改變。
    // GL_DYNAMIC_DRAW：數據會被改變。
    // GL_STREAM_DRAW ：數據每次都被改變。

    //3.設置頂點屬性指標
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//註冊調整窗口函數
    glfwSetKeyCallback(window, key_callback);//註冊手柄控制函數

    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清空深度顏色緩衝和深度緩衝

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // create transformations
        glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        transform = glm::rotate(transform, rotate, glm::vec3(0.0f, 0.0f, 1.0f));

        //繪製三角形
        ourShader.use();
        ourShader.setFloat("size", size);
        ourShader.setVec4("color", color[0], color[1], color[2], color[3]);
        ourShader.setMat4("transform", transform);
        if (drawTriangle)
            glDrawArrays(GL_TRIANGLES, 0, 3);

        //繪製imgui介面
        ImGui::Begin("My name");
        ImGui::Text("Hello World");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Checkbox("Draw Triangle", &drawTriangle);
        ImGui::SliderFloat("Size", &size, 0.5f, 2.0f);
        ImGui::SliderFloat("Rotate", &rotate, 0.0f, 10.0f);
        ImGui::ColorEdit4("Color", color);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        glfwSwapBuffers(window);//交換顏色緩衝
        glfwPollEvents();//檢查觸發事件 比如鍵盤滑鼠
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();


    //glDeleteShader(vertexShader);//刪除頂點著色器
    //glDeleteShader(fragmentShader);//刪除片段著色器

    glfwTerminate();//釋放and刪除分配資源
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)//註冊回調函數動態調整窗口大小
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    {
        if (mods & GLFW_MOD_CONTROL) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);//關閉窗口
        }
    }
}
