#include <glad/glad.h>  // OpenGL����ͷ�ļ����������GLFW֮ǰ��
#include <GLFW/glfw3.h>
#include <iostream> // ���ڴ������

// ����ִ��˳��Ļƽ���
// 1 GLFW��ʼ�� -> 2 �������� -> 3 ��ʼ��GLAD -> 4 �ӿ����� -> 5 ע��ص� -> 6 ����ѭ��

// ǰ���������ڳߴ�仯�ص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
    // ---------------------- 1. GLFW��ʼ�� ----------------------
    glfwInit();
    // ����OpenGL�����İ汾������ģʽ��
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // MacOS��Ҫ��������
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // ---------------------- 2. �������ڶ��� ----------------------
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // ��Ϊ��ǰ������

    // ---------------------- 3. ��ʼ��GLAD ----------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ---------------------- 4. �ӿڳ�ʼ���� ----------------------
    glViewport(0, 0, 800, 600);
    // ע�ᴰ�ڳߴ�仯�ص���������ѭ��ǰ���ã�
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ---------------------- 5. ��Ⱦѭ�� ----------------------
    while (!glfwWindowShouldClose(window))
    {
        // ��Ⱦָ����������ڴ���ӻ�ͼ���룩

        // ������ɫ����
        glfwSwapBuffers(window);
        // ���������¼�
        glfwPollEvents();
    }

    // ---------------------- 6. ��Դ���� ----------------------
    glfwTerminate();
    return 0;
}

// ---------------------- �ص�����ʵ�� ----------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}