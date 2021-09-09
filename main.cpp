#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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



    float vertices[] = {
    -0.5f, -0.5f,  0.0f,
     0.5f, -0.5f,  0.0f,
     0.0f,  0.5f,  0.0f
    };//三個頂點

    unsigned int VBO;
    glGenBuffers(1, &VBO);//生成VBO對象
    glBindBuffer(GL_ARRAY_BUFFER, VBO);//綁定緩衝到GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//將定義的頂點複製進緩衝內
    //GL_STATIC_DRAW ：數據幾乎不改變。
    // GL_DYNAMIC_DRAW：數據會被改變。
     //GL_STREAM_DRAW ：數據每次都被改變。

    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";//頂點著色器原碼
    unsigned int vertexSharder;
    vertexSharder = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexSharder, 1, &vertexShaderSource, NULL);//將著色器原碼放進著色器對象內
    glCompileShader(vertexSharder);//編譯頂點著色器

    glViewport(150, 100, 800, 600);//窗口位置高,窗口位置寬,窗口渲染高,窗口渲染寬
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//註冊調整窗口函數
    glfwSetKeyCallback(window, key_callback);//註冊手柄控制函數

    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(window);//交換顏色緩衝
        glfwPollEvents();//檢查觸發事件 比如鍵盤滑鼠
    }

    glfwTerminate();//釋放and刪除分配資源
    return 0;
}
