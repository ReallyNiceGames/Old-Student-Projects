
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtx/rotate_vector.hpp>
#include <GLM/gtc/quaternion.hpp>
#include <GLM/gtx/quaternion.hpp>
#include "Player.h"
#include <cmath>


Player::Player()
{
	_thrust = 0.5f;
	_pitch = 0.0f;
	_roll = 0.0f;


	// Initialise with direction object is facing
	_originalFacingDir = glm::vec3(1,0,0);
	_originalUpDir = glm::vec3(0,1,0);
	_originalLeftDir = glm::vec3(0,0,-1);

	// Give it an initial velocity, otherwise it falls out the sky
	_velocity = glm::vec3(15.0f,0,0);

}

Player::~Player()
{

}



void Player::Update( float deltaTs )
{
	// _roll and _pitch are like 'commands'
	// Need to work out the current requested change in roll and pitch, based on these
	// The magic numbers at the end are the maximum rates of turn
	float currentRoll = _roll * deltaTs * 1.2f;
	float currentPitch = _pitch * deltaTs * 1.2f;

	_thrust = glm::clamp(_thrust,0.0f,1.0f);



	// Compute current facing direction vector by rotating the original facing direction by the orientation
	glm::vec3 currentFacingDir;// = glm::rotate( something );

	// Now, add a roll rotation by rotating about the facing direction axis
	_orientation = glm::angleAxis( currentRoll, currentFacingDir) * _orientation;

	// Using the new orientation, compute the current left direction (literally the world-space direction that is 'left' for the player)
	glm::vec3 currentLeftDir = glm::rotate(_orientation,_originalLeftDir);
	
	// Add pitch rotation by rotating around the left direction axis
	//_orientation = something;
	
	// Update the current facing direction based on the new rotation
	//currentFacingDir = glm::rotate(_orientation,    something    );

	
	//_position +=   something using Forward Euler ;

	// Set the modelling matrix based on the current position and orientation
	_modelMatrix = glm::translate( glm::mat4(1), _position ) * glm::mat4_cast(_orientation);
	
	_invModelMatrix = glm::inverse(_modelMatrix);
	

}
