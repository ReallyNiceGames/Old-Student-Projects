#include "ParticleRenderer.h"

ParticleRenderer::ParticleRenderer(glm::vec3 _lightPosition)
{
	m_lightPosition = _lightPosition;
	//m_currParticles = 0;
	m_delay = 0;
	m_lastNumX = 0;
	m_lastNumZ = 0;

	//Create material
	m_particleMat = new Material;
	m_particleMat->LoadShaders("VertShader.txt", "FragShader.txt");
	m_particleMat->SetDiffuseColour(glm::vec3(0.8, 0.1, 0.1));
	m_particleMat->SetTexture("FlyingTeapotColour.bmp");
	m_particleMat->SetLightPosition(m_lightPosition);

	//Create mesh
	m_particleMesh = new Mesh;
	m_particleMesh->LoadOBJ("wingedTeapot.obj");
}

ParticleRenderer::~ParticleRenderer()
{
	for (size_t i = 0; i < m_particles.size(); ++i)
	{
		delete m_particles.at(i);
	}

	delete m_particleMat;
	delete m_particleMesh;
}

void ParticleRenderer::DrawParticles(glm::mat4 &_viewMatrix, glm::mat4 &_projMatrix)
{
	for (size_t i = 0; i < m_particles.size(); ++i)
	{
		m_particles.at(i)->Draw(_viewMatrix, _projMatrix);
	}
}

void ParticleRenderer::ChangeAmount()
{
	//Use this function to allow the user to control the amount
	//of particles generated during runtime
}

void ParticleRenderer::UpdateParticles(float deltaTs, glm::quat _cameraOrientation)
{
	bool temp; //Temp var for deleting particles

	if (m_delay == 0)
	{
		if (m_particles.size() < m_maxParticles)
		{
			srand(time(NULL));
			int x;
			int z;

			do
			{
				do
				{
					x = (rand() % 3) - 1; //Randomise x
				} 
				while (x == m_lastNumX);
				m_lastNumX = x;

				do
				{
					z = (rand() % 3) - 1; //Randomise z
				} 
				while (z == m_lastNumZ);
				m_lastNumZ = z;
			} 
			while (x == 0 && z == 0);
			

			//std::cout << "x: " << x << std::endl;
			//std::cout << "z: " << z << std::endl;

			m_particles.push_back(new Particle(_cameraOrientation, x, z)); //Create new particle instance and add to list
			m_particles.at(m_particles.size() - 1)->setMaterial(m_particleMat); //Add material
			m_particles.at(m_particles.size() - 1)->setMesh(m_particleMesh); //Add mesh

			//++m_currParticles;
		}
		m_delay = 10; //Set delay to spread particles
	}
	else
	{
		--m_delay; //Tick down delay
	}

	//Update particles and delete dead ones
	for (size_t i = 0; i < m_particles.size(); ++i)
	{
		temp = m_particles.at(i)->Update(deltaTs);

		if (!temp)
		{
			delete m_particles.at(i);
			m_particles.erase(m_particles.begin() + i);

			//std::cout << "DELETING PARTICLE" << std::endl;
			//--m_currParticles;
		}
	}
}