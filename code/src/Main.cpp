#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader.h>
#include <camera.h>
#include <model.h>

#include <iostream>



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 800;

Camera camera(glm::vec3(0.0f, 5.0f, 10.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Simple Scene", NULL, NULL);
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

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Unable to initialize glew" << std::endl;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	glEnable(GL_DEPTH_TEST);

	Shader myShader("C:/Dev/graphics_a2/Project1/Project1/src/vertex_shader.vs", "C:/Dev/graphics_a2/Project1/Project1/src/fragment_shader.fs");

	//calculate transformation matrices for each model
	glm::mat4 model_table = glm::mat4(1.0f);
	model_table = glm::translate(model_table, glm::vec3(0.0f, 0.1f, 0.0f));
	model_table = glm::scale(model_table, glm::vec3(1.0f, 1.0f, 1.0f));

	glm::mat4 model_teaset = glm::mat4(1.0f);
	model_teaset = glm::translate(model_teaset, glm::vec3(0.0f, 3.225f, 2.0f));
	model_teaset = glm::scale(model_teaset, glm::vec3(0.2f, 0.2f, 0.2f));

	glm::mat4 model_mario = glm::mat4(1.0f);
	model_mario = glm::translate(model_mario, glm::vec3(-2.0f, 3.1f, 0.0f));
	model_mario = glm::rotate(model_mario, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model_mario = glm::scale(model_mario, glm::vec3(0.02f, 0.02f, 0.02f));

	glm::mat4 model_plantpot = glm::mat4(1.0f);
	model_plantpot = glm::translate(model_plantpot, glm::vec3(1.0f, 3.2f, -2.5f));
	model_plantpot = glm::scale(model_plantpot, glm::vec3(0.02f, 0.02f, 0.02f));

	glm::mat4 model_car = glm::mat4(1.0f);
	model_car = glm::translate(model_car, glm::vec3(18.0f, 0.0f, -18.0f));
	model_car = glm::rotate(model_car, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model_car = glm::scale(model_car, glm::vec3(3.5f, 3.5f, 3.5f));

	glm::mat4 model_chair = glm::mat4(1.0f);
	model_chair = glm::translate(model_chair, glm::vec3(1.0f, -0.2f, 0.0f));
	model_chair = glm::scale(model_chair, glm::vec3(1.0f, 1.0f, 1.0f));

	glm::mat4 model_platform = glm::mat4(1.0f);
	model_platform = glm::translate(model_platform, glm::vec3(0.0f, 0.0f, 0.0f));
	model_platform = glm::scale(model_platform, glm::vec3(1.0f, 1.0f, 1.0f));

	// load models
	Model table((char*)"C:/Users/Syed Jamaluddin/Documents/blender_models/table.obj", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), model_table);
	Model teaset((char*)"C:/Users/Syed Jamaluddin/Documents/blender_models/teapot_n_glass.obj", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), model_teaset);
	Model mario((char*)"C:/Users/Syed Jamaluddin/Documents/blender_models/mario-sculpture.obj", glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), model_mario);
	Model plantpot((char*)"C:/Users/Syed Jamaluddin/Documents/blender_models/FlowerPot.obj", glm::vec4(0.0f, 1.0f, 1.0f, 1.0f), model_plantpot);
	Model car((char*)"C:/Users/Syed Jamaluddin/Documents/blender_models/Car.obj", glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), model_car);
	Model chair((char*)"C:/Users/Syed Jamaluddin/Documents/blender_models/chair.obj", glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), model_chair);
	Model platform((char*)"C:/Users/Syed Jamaluddin/Documents/blender_models/platform.obj", glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), model_platform);



	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		myShader.use();

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		myShader.setMat4("projection", projection);
		myShader.setMat4("view", view);

		// render the loaded models
		myShader.setMat4("model", table.transform);
		myShader.setVec4("color", table.color);
		table.Draw();


		myShader.setMat4("model", teaset.transform);
		myShader.setVec4("color", teaset.color);
		teaset.Draw();

		myShader.setMat4("model", car.transform);
		myShader.setVec4("color", car.color);
		car.Draw();

		myShader.setMat4("model", mario.transform);
		myShader.setVec4("color", mario.color);
		mario.Draw();

		myShader.setMat4("model", plantpot.transform);
		myShader.setVec4("color", plantpot.color);
		plantpot.Draw();

		myShader.setMat4("model", chair.transform);
		myShader.setVec4("color", chair.color);
		chair.Draw();

		myShader.setMat4("model", platform.transform);
		myShader.setVec4("color", platform.color);
		platform.Draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

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
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		camera.ProcessKeyboard(YAW_CCLKW, deltaTime);	
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		camera.ProcessKeyboard(YAW_CLKW, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
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

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}