#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION 
#include <learnopengl/stb_image.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 1000;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _APPLE_
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Exercise 16 Task 3", NULL, NULL);
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

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    //stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    Shader ourShader("shaders/ExamenBimestral2-Grupo04.vs", "shaders/ExamenBimestral2-Grupo04.fs");

    // load models
    // -----------
     Model ourModel1("C:/Users/claud/OneDrive/Documentos/Visual Studio 2022/OpenGL/OpenGL/model/model01/model01.obj");
     Model ourModel2("C:/Users/claud/OneDrive/Documentos/Visual Studio 2022/OpenGL/OpenGL/model/model02/model02.obj");
     Model ourModel3("C:/Users/claud/OneDrive/Documentos/Visual Studio 2022/OpenGL/OpenGL/model/model04/model04.obj");
	 Model ourModel5("C:/Users/claud/OneDrive/Documentos/Visual Studio 2022/OpenGL/OpenGL/model/model05/model05.obj");
     Model ourModel4("C:/Users/claud/OneDrive/Documentos/Visual Studio 2022/OpenGL/OpenGL/model/model06/model06.obj");
     Model ourModel6("C:/Users/claud/OneDrive/Documentos/Visual Studio 2022/OpenGL/OpenGL/model/model07/model07.obj");


    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    camera.MovementSpeed = 10; //Optional. Modify the speed of the camera

    
    // render loop
    while (!glfwWindowShouldClose(window))

    {
        // per-frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(window);

        // render
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // don't forget to enable shader before setting uniforms
        ourShader.use();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // render the first model
        glm::mat4 model1 = glm::mat4(1.0f);
        model1 = glm::translate(model1, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it to the center
        model1 = glm::scale(model1, glm::vec3(0.88f, 0.88f, 0.88f));  // scale it down
        ourShader.setMat4("model", model1);
        ourModel1.Draw(ourShader);

        // render the second model
        glm::mat4 model2 = glm::mat4(1.0f);
        model2 = glm::translate(model2, glm::vec3(5.0f, 6.0f, 0.0f)); // translate it to the right
        model2 = glm::scale(model2, glm::vec3(0.3f, 0.3f, 0.3f));  // scale it down
        model2 = glm::rotate(model2, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        ourShader.setMat4("model", model2);
        ourModel2.Draw(ourShader);

        // render the third model
        glm::mat4 model3 = glm::mat4(1.0f);
        model3 = glm::translate(model3, glm::vec3(7.0f, 0.0f, 1.0f)); // translate it to the left
        model3 = glm::scale(model3, glm::vec3(0.2f, 0.2f, 0.2f));  // scale it down
        ourShader.setMat4("model", model3);
        ourModel3.Draw(ourShader);

        // render the fourth model
        glm::mat4 model4 = glm::mat4(1.0f);
        model4 = glm::translate(model4, glm::vec3(-5.0f, 0.0f, 8.0f)); // translate it to a new position
        model5 = glm::rotate(model5, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model4 = glm::scale(model4, glm::vec3(0.1f, 0.1f, 0.1f));  // scale it down
        ourShader.setMat4("model", model4);
        ourModel4.Draw(ourShader);

        // render the fifth model
        glm::mat4 model5 = glm::mat4(1.0f);
        model5 = glm::translate(model5, glm::vec3(10.0f, 0.0f, 0.0f)); // translate it to a new posit   ion
        model5 = glm::rotate(model5, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // rotate it 90 degrees around the Y axis
        model5 = glm::scale(model5, glm::vec3(0.9f, 0.9f, 0.9f));  // scale it down
        ourShader.setMat4("model", model5);
        ourModel5.Draw(ourShader);


	// render the sixth model in a grid pattern
	int gridSize = 5; // Define the size of the grid
	float modelSize = 5.0f; // Define the size of each model
	float spacing = modelSize; // Define the spacing between models

	// Calculate the initial position to center the grid
	float startX = -(gridSize - 1) * spacing / 2.0f;
	float startZ = -(gridSize - 1) * spacing / 2.0f;
	float startY = -0.05f; // Position it below the other models

	for (int i = 0; i < gridSize; ++i) {
    	for (int j = 0; j < gridSize; ++j) {
        glm::mat4 model6 = glm::mat4(1.0f);
        model6 = glm::translate(model6, glm::vec3(startX + i * spacing, startY, startZ + j * spacing)); // translate it to a new position
        model6 = glm::scale(model6, glm::vec3(3.0f, 3.0f, 3.0f));  // scale it to its original size
        ourShader.setMat4("model", model6);
        ourModel6.Draw(ourShader);
    		}
	}
	    




        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }





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

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
