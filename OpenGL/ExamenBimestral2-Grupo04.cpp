#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

#define STB_IMAGE_IMPLEMENTATION 
#include <learnopengl/stb_image.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

//Exercise 14 Task 2
unsigned int loadTexture(const char* path);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//Exercise 13
//lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef APPLE
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Exercise 14 Task 4", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // ------------------------------------
    glEnable(GL_DEPTH_TEST);

    // ------------------------------------
    Shader lightingShader("shaders/shader_exercise14t4_materials.vs", "shaders/shader_exercise14t4_materials.fs");
    Shader lightCubeShader("shaders/shader_exercise14_lightcube.vs", "shaders/shader_exercise14_lightcube.fs");
    //-------------------------------------
    Shader ourShader("shaders/ExamenBimestral2-Grupo04.vs", "shaders/ExamenBimestral2-Grupo04.fs");

    // ------------------------------------
    Model ourModel1("C:/Users/Usuario/Documents/Visual Studio 2022/OpenGL/OpenGL/model/model01/model01.obj");
    Model ourModel2("C:/Users/Usuario/Documents/Visual Studio 2022/OpenGL/OpenGL/model/model02/model02.obj");
    // antorcha      
    Model ourModel3("C:/Users/Usuario/Documents/Visual Studio 2022/OpenGL/OpenGL/model/model04/model04.obj");
    // personaje     
    Model ourModel5("C:/Users/Usuario/Documents/Visual Studio 2022/OpenGL/OpenGL/model/model05/model05.obj");
    //fogata        
    Model ourModel4("C:/Users/Usuario/Documents/Visual Studio 2022/OpenGL/OpenGL/model/model06/model06.obj");
    // piso          
    Model ourModel6("C:/Users/Usuario/Documents/Visual Studio 2022/OpenGL/OpenGL/model/model07/model07.obj");
    Model ourModel7("C:/Users/Usuario/Documents/Visual Studio 2022/OpenGL/OpenGL/model/inglesia/inglesia.obj");
    Model ourModel8("C:/Users/Usuario/Documents/Visual Studio 2022/OpenGL/OpenGL/model/ruined/ruined.obj");
    Model ourModel9("C:/Users/Usuario/Documents/Visual Studio 2022/OpenGL/OpenGL/model/demon/demon.obj");

    // ------------------------------------------------------------------
 //Exercise 14 Task 2
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };



    // first, configure the cube's VAO (and VBO)
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Exerice 14 Task 2
   //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //Exercise 14 Task 2
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // -----------------------------------------------------------------------------
    unsigned int diffuseMap = loadTexture("textures/container2.png");
    unsigned int specularMap = loadTexture("textures/container2_specular.png");
    unsigned int emissionMap = loadTexture("textures/matrix2.jpg");
    // shader configuration
    // --------------------
    lightingShader.use();
    lightingShader.setInt("material.diffuse", 0);
    lightingShader.setInt("material.specular", 1);
    lightingShader.setInt("material.emission", 2);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("light.position", lightPos);
        lightingShader.setVec3("viewPos", camera.Position);

        // light properties
        lightingShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        lightingShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
        lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        // material properties
        //lightingShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
        lightingShader.setFloat("material.shininess", 64.0f);

        // don't forget to enable shader before setting uniforms
        ourShader.use();


        // render the first model
        glm::mat4 model1 = glm::mat4(1.0f);
        model1 = glm::translate(model1, glm::vec3(-23.0f, 0.0f, -17.0f));
        model1 = glm::scale(model1, glm::vec3(1.5f, 1.5f, 1.5f));
        ourShader.setMat4("model", model1);
        ourModel1.Draw(ourShader);

        // render the second model
        glm::mat4 model2 = glm::mat4(1.0f);
        model2 = glm::translate(model2, glm::vec3(-3.0f, 16.0f, 5.0f));
        model2 = glm::scale(model2, glm::vec3(0.8f, 0.8f, 0.8f));
        model2 = glm::rotate(model2, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        ourShader.setMat4("model", model2);
        ourModel2.Draw(ourShader);

        // render the third model
        glm::mat4 model3 = glm::mat4(1.0f);
        model3 = glm::translate(model3, glm::vec3(7.0f, 0.0f, -5.0f));
        model3 = glm::scale(model3, glm::vec3(0.2f, 0.2f, 0.2f));
        ourShader.setMat4("model", model3);
        ourModel3.Draw(ourShader);

        // render the fourth model
        glm::mat4 model4 = glm::mat4(1.0f);
        model4 = glm::translate(model4, glm::vec3(5.0f, -0.3f, 5.0f));
        model4 = glm::rotate(model4, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model4 = glm::scale(model4, glm::vec3(0.15f, 0.15f, 0.15f));
        ourShader.setMat4("model", model4);
        ourModel4.Draw(ourShader);

        // render the fifth model
        glm::mat4 model5 = glm::mat4(1.0f);
        model5 = glm::translate(model5, glm::vec3(10.0f, 0.0f, -3.0f));
        model5 = glm::rotate(model5, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model5 = glm::scale(model5, glm::vec3(1.0f, 1.0f, 1.0f));
        ourShader.setMat4("model", model5);
        ourModel5.Draw(ourShader);

        // render the seventh model
        glm::mat4 model7 = glm::mat4(1.0f);
        model7 = glm::translate(model7, glm::vec3(-20.0f, 0.0f, 0.0f));
        model7 = glm::rotate(model7, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model7 = glm::scale(model7, glm::vec3(0.01f, 0.01f, 0.01f));
        ourShader.setMat4("model", model7);
        ourModel7.Draw(ourShader);

        // render the eighth model
        glm::mat4 model8 = glm::mat4(1.0f);
        model8 = glm::translate(model8, glm::vec3(-20.0f, 0.0f, 20.0f));
        model8 = glm::rotate(model8, glm::radians(120.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model8 = glm::scale(model8, glm::vec3(3.0f, 3.0f, 3.0f));
        ourShader.setMat4("model", model8);
        ourModel8.Draw(ourShader);

        // render the ninth model
        glm::mat4 model9 = glm::mat4(1.0f);
        model9 = glm::translate(model9, glm::vec3(-40.0f, -70.0f, 0.0f)); // translate it to a new position
        model9 = glm::rotate(model9, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // rotate it 180 degrees around the Y axis
        model9 = glm::scale(model9, glm::vec3(40.0f, 40.0f, 40.0f));  // scale it down
        ourShader.setMat4("model", model9);
        ourModel9.Draw(ourShader);



        // render the sixth model in a grid pattern
        int gridSize = 20;
        float modelSize = 5.0f;
        float spacing = modelSize;

        // Calculate the initial position to center the grid
        float startX = -(gridSize - 1) * spacing / 2.0f;
        float startZ = -(gridSize - 1) * spacing / 2.0f;
        float startY = -0.05f;

        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                glm::mat4 model6 = glm::mat4(1.0f);
                model6 = glm::translate(model6, glm::vec3(startX + i * spacing, startY, startZ + j * spacing)); // translate it to a new position
                model6 = glm::scale(model6, glm::vec3(3.0f, 3.0f, 3.0f));
                ourShader.setMat4("model", model6);
                ourModel6.Draw(ourShader);
            }
        }



        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);


        // bind diffuse map
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);


        // bind specular map
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);

        // bind emission map
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, emissionMap);

        // render the cube
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        // also draw the lamp object
        lightCubeShader.use();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightCubeShader.setMat4("model", model);

        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    // Si se presiona la tecla Escape, cierra la ventana
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Si se presiona la tecla 'W', mueve la cámara hacia adelante
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    // Si se presiona la tecla 'S', mueve la cámara hacia atrás
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    // Si se presiona la tecla 'A', mueve la cámara hacia la izquierda
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    // Si se presiona la tecla 'D', mueve la cámara hacia la derecha
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: siempre que el tamaño de la ventana cambie (por el sistema operativo o el redimensionamiento del usuario), se ejecuta esta función de devolución de llamada
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Asegura que la vista se ajuste a las nuevas dimensiones de la ventana; observa que el ancho y la altura serán significativamente mayores en pantallas Retina
    glViewport(0, 0, width, height);
}

// glfw: siempre que el ratón se mueva, se llama a esta función de devolución de llamada
// -------------------------------------------------------
// 
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    // Si es la primera vez que el ratón se mueve, guarda la posición inicial
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false; // Asegura que no se ejecute esta sección más de una vez
    }

    // Calcula el desplazamiento del ratón en las direcciones X y Y
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // Y está invertido ya que las coordenadas Y aumentan hacia abajo en la ventana

    // Actualiza las últimas posiciones del ratón
    lastX = xpos;
    lastY = ypos;

    // Procesa el movimiento del ratón para actualizar la orientación de la cámara
    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: cada vez que la rueda del ratón se desplaza, se llama a esta función de devolución de llamada
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    // Procesa el desplazamiento del ratón para hacer zoom en la cámara
    camera.ProcessMouseScroll(yoffset);
}

// Ejercicio 14 Tarea 2
// Función de utilidad para cargar una textura 2D desde un archivo
// ---------------------------------------------------
unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID); // Genera un identificador único para la textura

    int width, height, nrComponents;
    // Carga la imagen utilizando la biblioteca STB Image
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);

    if (data) // Si la imagen se carga correctamente
    {
        GLenum format;
        // Determina el formato según el número de componentes de la imagen
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        // Vincula la textura a GL_TEXTURE_2D y carga la imagen en OpenGL
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D); // Genera mipmaps para la textura

        // Configura los parámetros de la textura
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Establece el envolvimiento horizontal
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Establece el envolvimiento vertical
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Establece el filtro de minificación
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Establece el filtro de magnificación

        stbi_image_free(data); // Libera la memoria de la imagen cargada
    }
    else // Si la imagen no se carga correctamente
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data); // Libera la memoria de la imagen, aunque haya fallado
    }

    return textureID; // Devuelve el identificador de la textura cargada
}
