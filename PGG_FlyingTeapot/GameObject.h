#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include "Mesh.h"
#include "Material.h"

// The GameObject contains a mesh, a material and position / orientation information
class GameObject
{
public:

	GameObject();
	~GameObject();

	void SetMesh(Mesh *input) {_mesh = input;}
	void SetMaterial(Material *input) {_material = input;}
	
	void SetPosition( float posX, float posY, float posZ ) {_position.x = posX; _position.y = posY; _position.z = posZ;}
	void SetPosition( glm::vec3 value) {_position = value;}

	void SetRotation( float rotX, float rotY, float rotZ ) {_rotation.x = rotX; _rotation.y = rotY; _rotation.z = rotZ;}
	void setScale(float _scaleX, float _scaleY, float _scaleZ) { scale.x = _scaleX; scale.y = _scaleY; scale.z = _scaleZ; }

	glm::vec3 GetPosition() {return _position;}
	
	// Game object is current hard-coded to rotate
	virtual void Update( float deltaTs );

	// Need to give it the camera's orientation and projection
	virtual void Draw(glm::mat4 &viewMatrix, glm::mat4 &projMatrix);

protected:

	// The actual model geometry
	Mesh *_mesh;
	// The material contains the shader
	Material *_material;

	// Matrix for the position and orientation of the game object
	glm::mat4 _modelMatrix;
	glm::mat4 _invModelMatrix;
	
	// Position of the model
	// The model matrix must be built from this and the _rotation
	glm::vec3 _position;
	
	// Orientation of the model
	// The model matrix must be built from this and the _position
	glm::vec3 _rotation;
	
	glm::vec3 scale;


};



#endif
