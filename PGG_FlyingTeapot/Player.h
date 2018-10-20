#ifndef __PLAYER__
#define __PLAYER__

#include <GLM/gtc/quaternion.hpp>
#include "GameObject.h"


class Player : public GameObject
{
public:
	Player();
	~Player();
	
	virtual void Update( float deltaTs );
	
	void ChangeThrust(float value) {_thrust += value;}
	void ChangeRoll( float value ) {_roll = value;}
	void ChangePitch( float value ) {_pitch = value;}
	
	glm::quat GetOrientation() {return _orientation;}
	
protected:

	glm::vec3 _velocity;
	glm::quat _orientation;
	glm::vec3 _originalFacingDir, _originalUpDir, _originalLeftDir;

	float _thrust;
	float _pitch, _roll;


};





#endif
