#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "imgui.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.cpp"
#include "imgui/backends/imgui_impl_glfw.cpp"


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform float size;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(size * aPos.x, size * aPos.y, size * aPos.z, 1.0);\n"
"}\0";//頂點著色器原碼

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 color;\n"
"void main()\n"
"{\n"
"   FragColor = color;\n"
"}\n";//片段著色器原始碼

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

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);//寬,高,名稱 返回GLFWwindows對象
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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    bool drawTriangle = true;
    float size = 1.0f;
    float color[4] = { 0.8f, 0.2f, 0.03f, 1.0f };

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);//生成VBO對象
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);//生成VAO對象
    glBindVertexArray(VAO);
    //2.把頂點數組複製到緩衝中供OPenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);//綁定緩衝到GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//將定義的頂點複製進緩衝內
    //GL_STATIC_DRAW ：數據幾乎不改變。
    // GL_DYNAMIC_DRAW：數據會被改變。
     //GL_STREAM_DRAW ：數據每次都被改變。

    //3.設置頂點屬性指標
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //創建和編譯著色器
    //------------------------------------
    //vertext shader 頂點渲染器
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//將著色器原碼放進著色器對象內
    glCompileShader(vertexShader);//編譯頂點著色器
    //檢查著色器編譯是否有誤
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //fragment shader 片段著色器
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);//將著色器原碼放進著色器對象內
    glCompileShader(fragmentShader);//編譯頂點著色器
     //檢查著色器編譯是否有誤
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Shader Program著色器程序(link shaders)
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    //檢查著色器編譯是否有誤
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glViewport(0, 0, 800, 600);//窗口位置高,窗口位置寬,窗口渲染高,窗口渲染寬
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//註冊調整窗口函數
    glfwSetKeyCallback(window, key_callback);//註冊手柄控制函數

    glUseProgram(shaderProgram);
    glUniform1f(glGetUniformLocation(shaderProgram, "size"), size);
    glUniform4f(glGetUniformLocation(shaderProgram, "color"), color[0], color[1], color[2], color[3]);

    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清空深度顏色緩衝和深度緩衝

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //繪製三角形
        glUseProgram(shaderProgram);
        glUniform1f(glGetUniformLocation(shaderProgram, "size"), size);
        glUniform4f(glGetUniformLocation(shaderProgram, "color"), color[0], color[1], color[2], color[3]);
        if (drawTriangle)
            glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(VAO);

        ImGui::Begin("My name");
        ImGui::Text("Hello World");
        ImGui::Checkbox("Draw Triangle", &drawTriangle);
        ImGui::SliderFloat("Size", &size, 0.5f, 2.0f);
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


    glDeleteShader(vertexShader);//刪除頂點著色器
    glDeleteShader(fragmentShader);//刪除片段著色器

    glfwTerminate();//釋放and刪除分配資源
    return 0;
}
