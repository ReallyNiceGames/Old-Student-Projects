#pragma once
#ifndef __PARTICLE__
#define __PARTICLE__

#include <GLM/glm.hpp>
#include <SDL/SDL.h>
#include "glew.h"
#include <string>
#include "Mesh.h"
#include "Material.h"
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <iostream>
#include <time.h>

class Particle
{
public:
	Particle(glm::quat _orientation, float _x, float _z);
	~Particle();

	glm::vec3 getPosition() const { return m_position; }
	glm::quat getOrientation() const { return m_orientation; }
	glm::vec3 getScale() const { return m_scale; }

	bool Update(float deltaTs);

	void Draw(glm::mat4 &viewMatrix, glm::mat4 &projMatrix);

	void setMaterial(Material *_material) { m_material = _material; }
	void setMesh(Mesh *_mesh) { m_mesh = _mesh; }

private:

	float m_gravityEffect;
	float m_lifeLength;
	float m_gravity;
	float m_timePassed;

	glm::vec3 m_position;
	glm::vec3 m_velocity;

	Mesh *m_mesh;
	Material *m_material;

	glm::mat4 m_modelMatrix;
	glm::mat4 m_invModelMatrix;

	glm::quat m_orientation;

	glm::vec3 m_scale;
	
};



#endif