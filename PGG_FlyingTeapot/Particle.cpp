#include "Particle.h"

Particle::Particle(glm::quat _orientation, float _x, float _z)
{
	m_orientation = _orientation;
	m_gravity = 3.5;
	m_gravityEffect = 0;
	m_lifeLength = 200;
	m_scale = glm::vec3(0.2f, 0.2f, 0.2f);
	srand(time(NULL));
	//m_position = glm::vec3((rand() % 30), 50.0f, (rand() % 30)); //Trying to randomise it this way didn't work out so well
	m_position = glm::vec3(10.0f, 2.5f, 0.0f);
	m_velocity.y = 0;
	m_velocity.x = _x;
	m_velocity.z = _z;
	m_timePassed = 0;
}

Particle::~Particle()
{
}

bool Particle::Update(float deltaTs)
{
	if (m_position.y > 0)
	{
		m_velocity.y += (m_gravity + m_gravityEffect) * deltaTs; //POTENTIAL ISSUE WITH USING DELTATS HERE (Actually no this works fine, who knew)
		//m_velocity.y -= 0.1; //A default velocity changer if the calculation isn't working correctly
		m_gravityEffect += -0.1;
	}
	else
	{
		m_velocity.y = 0;
		m_velocity.x = 0;
		m_velocity.z = 0;
	}

	glm::vec3 change = m_velocity;
	change *= deltaTs;
	m_position += change;
	//m_timePassed += deltaTs;
	++m_timePassed;


	//std::cout << m_gravityEffect << std::endl;
	//std::cout << "Time passed: " << m_timePassed << std::endl;
	
	if (m_position.y <= 0) //The particle is eating the non-existent dirt
	{
		m_position.y = 0; //Stops particle from falling any further
		m_timePassed = m_lifeLength; //End the life of the particle if it hit the ground or "putting it out of its misery"
	}

	/*
	while (m_orientation.y > (3.14159265358979323846 * 2.0))
	{
		m_orientation.y -= (float)(3.14159265358979323846 * 2.0);
	}
	*/

	m_orientation.y = (rand() % 361); //SPIN! SPIN! SPIN!

	m_modelMatrix = glm::translate(glm::mat4(1.0f), m_position);
	m_modelMatrix = glm::rotate(m_modelMatrix, m_orientation.y, glm::vec3(0, 1, 0));
	m_modelMatrix = glm::scale(m_modelMatrix, m_scale);
	m_invModelMatrix = glm::rotate(glm::mat4(1.0f), -m_orientation.y, glm::vec3(0, 1, 0));
	
	if (m_timePassed < m_lifeLength)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Particle::Draw(glm::mat4 &_viewMatrix, glm::mat4 &_projMatrix)
{
	if (m_mesh != NULL)
	{
		if (m_material != NULL)
		{
			m_material->SetMatrices(m_modelMatrix, m_invModelMatrix, _viewMatrix, _projMatrix);
			m_material->Apply();
		}

		m_mesh->Draw();

	}
}