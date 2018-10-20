#pragma once
#ifndef __PARTICLERENDERER__
#define __PARTICLERENDERER__

#include <GLM/glm.hpp>
#include <SDL/SDL.h>
#include "glew.h"
#include <string>
#include "GameObject.h"
#include "Mesh.h"
#include "Material.h"
#include <vector>
#include "Particle.h"
#include <GLM/gtc/quaternion.hpp>

class ParticleRenderer
{
public:
	ParticleRenderer(glm::vec3 _lightPosition);
	~ParticleRenderer();

	void DrawParticles(glm::mat4 &viewMatrix, glm::mat4 &projMatrix);

	void ChangeAmount();

	//int getCurrParticles() { return currParticles; }

	void UpdateParticles(float deltaTs, glm::quat _cameraOrientation);

private:

	//Particle *m_particle;
	Mesh *m_particleMesh;
	Material *m_particleMat;

	glm::vec3 m_lightPosition;

	//int m_currParticles;
	const int m_maxParticles = 30;
	std::vector<Particle*> m_particles;

	int m_delay;
	int m_lastNumX;
	int m_lastNumZ;

};

#endif