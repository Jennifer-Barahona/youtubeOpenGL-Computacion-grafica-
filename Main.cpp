


#include <iostream>
#include <vector>
#include <fstream>
#include <direct.h>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Model.h"
#include "Bezier.h"

// ================= VERTEX SHADER =================

const char* vertexShaderSource = "#version 330 core\n"

"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aNormal;\n"
"layout (location = 2) in vec2 aTexCoord;\n"

"out vec3 Normal;\n"
"out vec3 FragPos;\n"
"out vec2 TexCoord;\n"

"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"

"void main()\n"
"{\n"
"   vec4 worldPosition = model * vec4(aPos, 1.0);\n"

"   FragPos = vec3(worldPosition);\n"
"   Normal = mat3(transpose(inverse(model))) * aNormal;\n"
"   TexCoord = aTexCoord;\n"

"   gl_Position = projection * view * worldPosition;\n"
"}\n\0";

// ================= FRAGMENT SHADER =================

const char* fragmentShaderSource = "#version 330 core\n"

"in vec3 Normal;\n"
"in vec3 FragPos;\n"
"in vec2 TexCoord;\n"

"out vec4 FragColor;\n"

"uniform sampler2D texture_diffuse1;\n"

"uniform vec3 lightPos;\n"
"uniform vec3 lightColor;\n"

"void main()\n"
"{\n"
"   vec3 objectColor = texture(texture_diffuse1, TexCoord).rgb;\n"

"   vec3 norm = normalize(Normal);\n"
"   vec3 lightDir = normalize(lightPos - FragPos);\n"

"   float diff = max(dot(norm, lightDir), 0.0);\n"

"   vec3 ambient = 0.2 * lightColor;\n"
"   vec3 diffuse = diff * lightColor;\n"

"   vec3 result = (ambient + diffuse) * objectColor;\n"

"   FragColor = vec4(result, 1.0);\n"
"}\n\0";

// ================= CAMARA =================

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

float lastX = 400.0f;
float lastY = 400.0f;

bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

// ================= MOUSE =================

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset);
}

// ================= TECLADO =================

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(FORWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(BACKWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(LEFT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(RIGHT, deltaTime);
}

// ================= MAIN =================

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(
        800, 800,
        "OpenGL - Modelo 3D",
        NULL, NULL
    );

    if (!window)
    {
        std::cout << "Error al crear la ventana" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGL())
    {
        std::cout << "Error al inicializar GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 800);
    glEnable(GL_DEPTH_TEST);

    // COMPROBAR RUTA DEL ARCHIVO

    char ruta[1024];

    _getcwd(ruta, sizeof(ruta));

    std::cout << "\nDirectorio de ejecucion: "
        << ruta << std::endl;

    std::ifstream archivo("models/DamagedHelmet.glb");

    if (archivo.good())
        std::cout << "ARCHIVO ENCONTRADO" << std::endl;
    else
        std::cout << "ARCHIVO NO ENCONTRADO" << std::endl;

    archivo.close();

    // CREAR SHADER

    Shader shader(vertexShaderSource, fragmentShaderSource);

    // CARGAR MODELO

    Model helmet("models/DamagedHelmet.glb");
    Bezier trayectoria(
        glm::vec3(-2.0f, 0.0f, 0.0f),  // P0
        glm::vec3(-1.0f, 2.0f, 0.0f),  // P1
        glm::vec3(1.0f, -2.0f, 0.0f),  // P2
        glm::vec3(2.0f, 0.0f, 0.0f)    // P3
    );

    // CICLO PRINCIPAL

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());

        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        // CONFIGURAR ILUMINACION

        shader.setVec3(
            "lightPos",
            glm::vec3(2.0f, 3.0f, 3.0f)
        );

        shader.setVec3(
            "lightColor",
            glm::vec3(1.0f, 1.0f, 1.0f)
        );

        // UNIDAD DE TEXTURA

        shader.setInt("texture_diffuse1", 0);

        // MATRIZ MODELO

        float tiempo = (sin(glfwGetTime() * 0.5f) + 1.0f) / 2.0f;

        glm::vec3 posicion = trayectoria.getPoint(tiempo);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, posicion);

        model = glm::scale(
            model,
            glm::vec3(1.0f, 1.0f, 1.0f)
        );

        // MATRIZ VISTA

        glm::mat4 view = camera.getViewMatrix();

        // MATRIZ PROYECCION

        glm::mat4 projection = glm::perspective(
            glm::radians(45.0f),
            800.0f / 800.0f,
            0.1f,
            100.0f
        );

        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        // DIBUJAR MODELO

        helmet.draw();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

