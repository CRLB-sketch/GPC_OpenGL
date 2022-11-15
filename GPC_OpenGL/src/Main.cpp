
/*
* Universidad del Valle de Guatemala
* Graficas por Computadora
* C++ - Open GL
* 
* @author Cristian Laynez
* @status Student Of Computer Science
* 
* ! Main : Clase Principal De Open GL
*/
// Referencias: https://learnopengl.com/
#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Shaderm.h"
#include "Camera.h"
#include "Model.h"

#include <iostream>
#include <fstream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void allInputs(GLFWwindow* window);

// Resolucion de la pantalla
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Preparar Camara 
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// Tiempo de Control
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Texturas
const char* nameTexture1 = "resources/textures/container.jpg";

int main()
{
    // glfw: Inicializar y Configurar
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creacion de la Ventana : GLFW
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "C++ Open GL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Error al crear GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Para obtener Cursor

    // Cargar todas las funciones de punteros OpenGL : glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Fallo al inicializar GLAD" << std::endl;
        return -1;
    }

    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);
        
    Shader ourShader(
        "shaders/vertexShaders/color.vs",
        "shaders/fragmentShaders/color.fs"
    );

    // Shaderm ourShader("shaders/vertexShaders/color.vs", "shaders/fragmentShaders/color.fs");

    //Model mainModel;
    //mainModel.loadFromFile("resources/models/model.obj");   
    //std::vector<float> vertices = mainModel.getVertexData();
    //int vertexCount = mainModel.getVertexCount();
    //
    //// ! ---------------------------------------------------------
   
    //unsigned int VAO, VBO, EBO;

    //glGenVertexArrays(1, &VAO);
    //glBindVertexArray(VAO);

    //glGenBuffers(1, &VBO);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)12);
    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)24);
    //glEnableVertexAttribArray(2);



    // ! ---------------------------------------------------------

    // Empezar a Renderizar los Objetos en Escena +++++++++++++++++++++++++++++++++++++
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        allInputs(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        //// Renderizar modelo
        //glm::mat4 model = glm::mat4(1.0f);
        //model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        //float angle = 20.0f;
        //model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        //ourShader.setMat4("model", model);

        //glDrawArrays(GL_TRIANGLES, 0, vertexCount);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

   /* glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);*/

    glfwTerminate();
    return 0;
}

void allInputs(GLFWwindow* window)
{
    // ! --------------------------------------------------------------------
    // Terminar el programa
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    // ! --------------------------------------------------------------------

    // ! --------------------------------------------------------------------
    // Zoom In --------------------------------------------------------------
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);

    // Zoom Out -------------------------------------------------------------
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    // ! --------------------------------------------------------------------

    // ! --------------------------------------------------------------------
    // Movimiento Izquierda -------------------------------------------------
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);

    // Movimiento Derecha ---------------------------------------------------
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    // Movimiento Arriba ----------------------------------------------------
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);

    // Movimiento Abajo -----------------------------------------------------
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
    // ! --------------------------------------------------------------------
    
    // ! --------------------------------------------------------------------
    // Control de modelos ---------------------------------------------------
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {

    }

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {

    }
    // ! --------------------------------------------------------------------

    // ! --------------------------------------------------------------------
    // Control de Shaders ---------------------------------------------------
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {

    }
    // ! --------------------------------------------------------------------
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
