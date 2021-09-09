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

    glViewport(150, 100, 800, 600);//���f��m��,���f��m�e,���f��V��,���f��V�e
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//���U�վ㵡�f���
    glfwSetKeyCallback(window, key_callback);//���U��`������

    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(window);//�洫�C��w��
        glfwPollEvents();//�ˬdĲ�o�ƥ� ��p��L�ƹ�
    }

    glfwTerminate();//����and�R�����t�귽
    return 0;
}
