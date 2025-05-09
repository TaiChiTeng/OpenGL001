#include <glad/glad.h>
//Glad是一个开源库，可以大大节省我们关于获取OpenGL各种函数的地址的代码量。
//因为OpenGL驱动有多种不同的版本，其大部分函数在编译时无法确定位置，需要在运行时动态查询。因此，开发者需要自行获取所需函数的地址，并将其存储在函数指针中供后续调用。
//注意，GLAD 它采用了独特的配置方式——提供一个在线服务，让我们可以指定需要的 OpenGL 版本，然后自动生成并加载该版本对应的所有相关函数。
#include <GLFW/glfw3.h>
//GLFW:专门针对OpenGL的库。它省去了我们处理操作系统特定工作的麻烦，并为我们提供了一个窗口和OpenGL上下文来进行渲染。
//GLFW 是一个用 C 语言编写的库，专门针对 OpenGL 设计。它提供了将图形渲染到屏幕上所需的基本功能，包括创建 OpenGL 上下文、定义窗口参数以及处理用户输入。

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <learnopengl/shader_s.h>

#include <iostream>
//是 C++ 中的一个预处理指令，用于包含标准输入/输出流库（I/O Stream Library）。  
// 提供基本的输入/输出功能  
//- `cin`（标准输入，如键盘输入）
//- `cout`（标准输出，如屏幕打印）
//- `cerr`（标准错误输出）
//- `clog`（日志输出）
//在 OpenGL 程序中的常见用途
//- 检查 OpenGL 版本、显卡支持情况
//- 输出错误信息（如 `glGetError()` 的返回值）
//- 调试着色器（Shader）编译 / 链接日志

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//这是一个 回调函数（Callback Function），用于在 窗口大小改变时（如用户拖动窗口边框）自动调整 OpenGL 的视口（Viewport）。
//GLFW 会在窗口尺寸变化时调用此函数，并传入新的  width  和  height 。
//如果不处理窗口大小变化，渲染的内容可能会被拉伸或压缩。
//通过  glViewport()  确保 OpenGL 正确映射坐标到新的窗口尺寸。

void processInput(GLFWwindow* window);
//这是一个 自定义函数，用于 处理用户输入（如键盘、鼠标操作）。
//通常在主循环（ while  循环）中每帧调用，检测按键状态并执行相应操作（如移动摄像机、关闭窗口等）。
//让程序能够响应用户交互（如 WASD 移动、退出程序等）。

// settings
const unsigned int SCR_WIDTH = 768;
const unsigned int SCR_HEIGHT = 768;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("2.1.shader.vs", "2.1.shader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top 
    };
    float secondTriangle[] = {
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top 
    };
    unsigned int VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs); // we can also generate multiple VAOs or buffers at the same time
    glGenBuffers(2, VBOs);
    // first triangle setup
    // --------------------
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    // glBindVertexArray(0); // no need to unbind at all as we directly bind a different VAO the next few lines
    // second triangle setup
    // ---------------------
    glBindVertexArray(VAOs[1]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);
    // glBindVertexArray(0); // not really necessary as well, but beware of calls that could affect VAOs while this one is bound (like binding element buffer objects, or enabling/disabling vertex attributes)

    // 只画线框
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // 画整个面(默认)
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.718f, 0.318f, 0.114f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        ourShader.use();

        // draw first triangle using the data from the first VAO
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // then we draw the second triangle using the data from the second VAO
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    //glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}