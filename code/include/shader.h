#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

/**
 * A shader class. Used to store the compiled shader file.
 */
class Shader
{
public:
	unsigned int ID;///< id representing the shader program.

	/**
	* Constructor.
	* Constructs shader object.
	* @param[in] vertexPath path to vertex shader file.
	* @param[in] fragmentPath path to fragment shader file.
	*/
	Shader(const char* vertexPath, const char* fragmentPath);

	/**
	* Function to activate the shader program.
	* @return void
	*/
	void use();

	/**
	* Function to set mat4 uniforms.
	* @param[in] name name of the uniform.
	* @param[in] mat a mat4
	* @return void
	*/
	void setMat4(const std::string& name, const glm::mat4& mat) const;

	/**
	* Function to set vec4 uniforms.
	* @param[in] name name of the uniform.
	* @param[in] vec a vec4
	* @return void
	*/
	void setVec4(const std::string& name, const glm::vec4& vec) const;
};

#endif