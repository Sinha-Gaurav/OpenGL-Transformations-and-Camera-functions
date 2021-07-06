#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shader.h>

/**
 * A vectex struct. Used to store vertex data.
 */
struct Vertex {
	glm::vec3 Position;///< Position vector storing the x,y and z coordinates of the vertex.
};


/**
 * A mesh class. Used as a composite class for Model class. A model is composed of meshes.
 */
class Mesh {
public:
	std::vector<Vertex> vertices;///< array of vertices storing mesh data.
	std::vector<unsigned int> indices;///< array of indices used for indexed drawing.

	/**
	* Constructor.
	* Constructs a mesh object.
	* @param[in] vertices array of vertices of the 3d mesh.
	* @param[in] indices array of indices corresponding to the vertices.
	*/
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

	/**
	* Draw method.
	* Draws the trianglular faces given by the indices.
	* @return void
	*/
	void Draw();
private:
	unsigned int VAO;///< vertex array object
	unsigned int VBO;///< vertex buffer object
	unsigned int EBO;///< element buffer object

	/**
	* Function used to setup the VAO, VBO and EBO.
	* @return void
	*/
	void setupMesh();
};

#endif