#include <glad/glad.h>  // OpenGL核心头文件（必须放在GLFW之前）
#include <GLFW/glfw3.h>
#include <iostream> // 用于错误输出

// 代码执行顺序的黄金法则
// 1 GLFW初始化 -> 2 创建窗口 -> 3 初始化GLAD -> 4 视口设置 -> 5 注册回调 -> 6 进入循环

// 前置声明窗口尺寸变化回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
    // ---------------------- 1. GLFW初始化 ----------------------
    glfwInit();
    // 配置OpenGL上下文版本（核心模式）
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // MacOS需要额外配置
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // ---------------------- 2. 创建窗口对象 ----------------------
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // 设为当前上下文

    // ---------------------- 3. 初始化GLAD ----------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ---------------------- 4. 视口初始设置 ----------------------
    glViewport(0, 0, 800, 600);
    // 注册窗口尺寸变化回调（必须在循环前设置）
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ---------------------- 5. 渲染循环 ----------------------
    while (!glfwWindowShouldClose(window))
    {
        // 渲染指令（后续可以在此添加绘图代码）

        // 交换颜色缓冲
        glfwSwapBuffers(window);
        // 处理输入事件
        glfwPollEvents();
    }

    // ---------------------- 6. 资源清理 ----------------------
    glfwTerminate();
    return 0;
}

// ---------------------- 回调函数实现 ----------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}