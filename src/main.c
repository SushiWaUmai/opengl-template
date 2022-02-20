#include <stdio.h>
#include <stdlib.h>

#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

#include <glad/glad.h>

#include "file_loader.h"

int main(void)
{
    if (!glfwInit())
    {
        printf("Could not initialize glfw.");
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
        printf("Could not initialize glad.\n");
        return -1;
    }

    float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.0f,  0.5f,
    };

    // Create vertex buffers
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create vertex arrays
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create vertex shader
    const char *vertSrc = load_file("./assets/vert.glsl");
    unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vertSrc, NULL);
    glCompileShader(vertShader);

    // Create fragment shader
    const char *fragSrc = load_file("./assets/frag.glsl");
    unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragSrc, NULL);
    glCompileShader(fragShader);

    // Create shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);

    // Clean up
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    free((char *)vertSrc);
    free((char *)fragSrc);

    // Use shader program
    glUseProgram(shaderProgram);

    // Add vertex attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
