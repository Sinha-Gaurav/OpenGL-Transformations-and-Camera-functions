#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include <shader.h>
#include <mesh.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


/**
 * A model class. Used to store the meshes read from a .obj file.
 */
class Model
{
public:

	glm::vec4 color;///< solid color of the model.
	glm::mat4 transform;///< transformation matrix to setup the model in the scene.

	/**
	* Constructor.
	* Constructs a model object.
	* @param[in] path path to the .obj file.
	* @param[in] c vector storing color as rgba.
	* @param[in] t transformation matrix.
	*/
	Model(char* path, glm::vec4 c, glm::mat4 t);

	/*
	* Function used to draw all the meshes in the model.
	* @return void
	*/
	void Draw();
private:
	std::vector<Mesh> meshes;///< array of meshes.
	std::string directory;///< full directory path containing the model.

	/*
	* Function to initialize all the mesh data in the model.
	* @param[in] path path to the .obj file.
	* @return void
	*/
	void loadModel(std::string path);
	/*
	* Function to process each node in the tree structure developed using assimp library.
	* @param[in] node pointer to root node of the tree structure representing a scene.
	* @param[in] scene pointer to assimp scene object.
	* @return void
	*/
	void processNode(aiNode* node, const aiScene* scene);
	/*
	* Function to process a mesh retreived from aiNode structure.
	* @param[in] mesh pointer to assimp mesh object.
	* @param[in] scene pointer to assimp scene object.
	* @return Mesh object.
	*/
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};


#endif
