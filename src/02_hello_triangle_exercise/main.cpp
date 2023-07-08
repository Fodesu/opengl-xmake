#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
    "   gl_PointSize = 20.0f;"
    "}\0";

const char* s = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

const char *s2 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\n\0";

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
    
    glEnable(GL_PROGRAM_POINT_SIZE);


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    // 创建 顶点和片段桌色器
    // 
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    // 附加着色器代码
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    
    // 编译
    glCompileShader(vertexShader);
    
    
    // 检测是否编译成功
    int success;
    char infoLog[512];
    // 获取编译的状态 使用  GL_COMPILE_STATUS
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    std::cout << "CHECKING SHARED::VERTEX::COMPILATION--STATUS\n";
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    // 片段着色器创建
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // 附加片段着色器
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // 编译片段着色器
    glCompileShader(fragmentShader);
    // 检测片段着色器的编译状况
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    
    std::cout << "CHECKING SHARED::FRAGMENT::COMPILATION--STATUS\n";
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // fragment shader
    // 片段着色器2创建
    unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    // 附加片段着色器
    glShaderSource(fragmentShader2, 1, &s2, NULL);
    // 编译片段着色器
    glCompileShader(fragmentShader2);
    // 检测片段着色器的编译状况
    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
    
    std::cout << "CHECKING SHARED::FRAGMENT::COMPILATION--STATUS\n";
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    // 创建程序对象用来链接着色器
    unsigned int shaderProgram1 = glCreateProgram();
    unsigned int shaderProgram2 = glCreateProgram();
    // 附加着色器对象
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader);
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    // 链接
    glLinkProgram(shaderProgram1);
    // 检测链接是否成功
    glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
    std::cout << "CHECKING::SHARED::PROGRAM::LINKING--STATUS\n";
    if (!success) {
        glGetProgramInfoLog(shaderProgram1, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glLinkProgram(shaderProgram2);
    // 检测链接是否成功
    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    std::cout << "CHECKING::SHARED::PROGRAM::LINKING--STATUS\n";
    if (!success) {
        glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShader2);
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    //       .
    //       
    //  
    //   .        .
    // 
    float vertices[] = {
        0.5f, 0.8f, 0.0f,
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        -0.5f, 0.8f, 0.0f,
        0.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
    }; 

    unsigned int VAOS[2], VBOS[2];
    glGenVertexArrays(2, VAOS);
    glGenBuffers(2, VBOS);
    // glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAOS[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOS[0]);
    // 绑定 EBO 对象
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 


    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 


    glBindVertexArray(VAOS[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOS[1]);
    // 绑定 EBO 对象
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 


    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(9 * sizeof(float)));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle  
        glUseProgram(shaderProgram1);
        glBindVertexArray(VAOS[0]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);


        glUseProgram(shaderProgram2);
        glBindVertexArray(VAOS[1]); 
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0); // no need to unbind it every time 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(2, VAOS);
    glDeleteBuffers(2, VBOS);
    // glDeleteBuffers(2, EBOS);
    glDeleteProgram(shaderProgram1);
    glDeleteProgram(shaderProgram2);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
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