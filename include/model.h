#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <map>
#include <vector>
#include <glm/glm.hpp>
#include "glbuffer.h"
#include "glvertexarray.h"
#include "glprogram.h"
#include "material.h"

/**
* A basic model that can be drawn, the model will specify
* the VAO, the ambient, diffuse and specular colors and/or textures
* in the form of the associated Materials along with
* its model transformation matrix, however the program
* to use won't be associated with the model
* maybe I will associate the program, it'll be easier
*/
class Model {
public:
	/**
	* Create a model using the vertices and indices from the vectors
	* passed in, this basic mode will simply draw a gray model
	* @param verts The model vertices interleaved like: vec3(pos), vec3(normal), vec3(texCoord)
	* @param indices The indices for the element buffer
	* @param mats The materials for the model to use
	*/
	Model(const std::string &file);
	/**
	* Add a material for usage by the model
	* @param name Name to associate with the material
	* @param mat The material
	*/
	void addMaterial(const std::string &name, Material &mat);
	/**
	* Assign the shader program to be used for drawing
	* @param prog The program to use
	*/
	void useProgram(GL::Program &prog);
	/**
	* Specify which material should be used when drawing the model
	* The texture stuff is super lazy again
	* @param name Name of material to use
	*/
	void useMaterial(const std::string &name);
	/**
	* Translate the model by some amount from its current position
	* @param vect The vector describing the amount to translate by
	*/
	void translate(const glm::vec3 &vect);
	/**
	* Rotate the model by some amount from its current rotation along
	* some axis
	* @param angle Angle in degrees to rotate by
	* @param axis Axis to rotate around
	*/
	void rotate(float angle, const glm::vec3 &axis);
	/**
	* Scale the model by some amount from its current scaling
	* @param scale The scale vector to use containg the x, y, z scale information
	*/
	void scale(const glm::vec3 &scale);
	///Draw the model, textured specifies if we want to pass textures
	///This is really awful, come up with something better when it's not just a test
	void draw(bool textured);

public:
	/**
	* A utility function, I'm not sure how I want model to look in the end b/c it's complicated
	* but I want to be able to load obj files for testing and such just into a simple
	* vbo + vao w/ elems
	* it also won't handle materials.
	*/
	static void loadObj(const std::string &file, GL::VertexArray &vao, GL::VertexBuffer &vbo);

private:
	///Update the material color properties being sent to the shader
	void updateColors();
	///Load the model from an obj file
	void loadObj(const std::string &file);

//Temporarily public while I work on stuff
public:
	///The model transformation matrix
	glm::mat4 mModel;
	///Model's VBO
	GL::VertexBuffer mVbo;
	///The model's VAO
	GL::VertexArray mVao;
	///The shader program we're using
	GL::Program mProg;
	///Materials associated with the model
	std::map<std::string, Material> mMaterials;
	///The active material
	Material *mActiveMat;
};

#endif
