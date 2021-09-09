#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);//�e,��,�W�� ��^GLFWwindows��H
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



    float vertices[] = {
    -0.5f, -0.5f,  0.0f,
     0.5f, -0.5f,  0.0f,
     0.0f,  0.5f,  0.0f
    };//�T�ӳ��I

    unsigned int VBO;
    glGenBuffers(1, &VBO);//�ͦ�VBO��H
    glBindBuffer(GL_ARRAY_BUFFER, VBO);//�j�w�w�Ĩ�GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//�N�w�q�����I�ƻs�i�w�Ĥ�
    //GL_STATIC_DRAW �G�ƾڴX�G�����ܡC
    // GL_DYNAMIC_DRAW�G�ƾڷ|�Q���ܡC
     //GL_STREAM_DRAW �G�ƾڨC�����Q���ܡC

    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";//���I�ۦ⾹��X
    unsigned int vertexSharder;
    vertexSharder = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexSharder, 1, &vertexShaderSource, NULL);//�N�ۦ⾹��X��i�ۦ⾹��H��
    glCompileShader(vertexSharder);//�sĶ���I�ۦ⾹

    glViewport(150, 100, 800, 600);//���f��m��,���f��m�e,���f��V��,���f��V�e
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//���U�վ㵡�f���
    glfwSetKeyCallback(window, key_callback);//���U��`������

    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(window);//�洫�C��w��
        glfwPollEvents();//�ˬdĲ�o�ƥ� ��p��L�ƹ�
    }

    glfwTerminate();//����and�R�����t�귽
    return 0;
}
