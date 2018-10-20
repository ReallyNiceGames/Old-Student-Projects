
#include "Scene.h"

#include <iostream>
#include <SDL/SDL.h>
#include <stdlib.h>


Scene::Scene()
{
	_cameraAngleX = 0.3f, _cameraAngleY = 1.5f;

	// Set up the viewing matrix
	// This represents the camera's orientation and position
	_viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,-3.5f) );
	

	// Set up a projection matrix
	_projMatrix = glm::perspective(45.0f, 1.0f, 0.1f, 10000.0f);

	// Set up your scene here

	// Position of the light, in world-space
	_lightPosition = glm::vec3(10,10,0);

	// Create a game object
	// This needs a material and a mesh
	_model = new GameObject();

	//-------------------------------------------------------------
	volcano = new GameObject();

	Material *volcanoMaterial = new Material();
	volcanoMaterial->LoadShaders("VertShader.txt", "FragShader.txt");
	volcanoMaterial->SetDiffuseColour(glm::vec3(0.5, 0.5, 0.5));
	volcanoMaterial->SetTexture("volcano.bmp");
	volcanoMaterial->SetLightPosition(_lightPosition);
	volcano->SetMaterial(volcanoMaterial);

	Mesh *volcanoMesh = new Mesh();
	volcanoMesh->LoadOBJ("VolcanoTiny.obj");
	volcano->SetMesh(volcanoMesh);

	volcano->setScale(1.0f, 1.0f, 1.0f);
	volcano->SetPosition(0.0f, -100.0f, 0.0f);
	//-------------------------------------------------------------

	// Create the material for the game object
	Material *modelMaterial = new Material();
	// Shaders are now in files
	modelMaterial->LoadShaders("VertShader.txt","FragShader.txt");
	// You can set some simple material properties, these values are passed to the shader
	// This colour modulates the texture colour
	modelMaterial->SetDiffuseColour( glm::vec3(0.8,0.1,0.1) );
	// The material currently supports one texture
	// This is multiplied by all the light components (ambient, diffuse, specular)
	// Note that the diffuse colour set with the line above will be multiplied by the texture colour
	// If you want just the texture colour, use modelMaterial->SetDiffuseColour( glm::vec3(1,1,1) );
	modelMaterial->SetTexture("Image1.bmp");
	// Need to tell the material the light's position
	// If you change the light's position you need to call this again
	modelMaterial->SetLightPosition(_lightPosition);
	// Tell the game object to use this material
	_model->SetMaterial(modelMaterial);



	// Create the material for the game object
	Material *teapotMaterial = new Material();
	// Shaders are now in files
	teapotMaterial->LoadShaders( "VertShader.txt", "FragShader.txt" );
	// You can set some simple material properties, these values are passed to the shader
	// This colour modulates the texture colour
	teapotMaterial->SetDiffuseColour( glm::vec3( 1.0, 1.0, 1.0 ) );
	// The material currently supports one texture
	// This is multiplied by all the light components (ambient, diffuse, specular)
	// Note that the diffuse colour set with the line above will be multiplied by the texture colour
	// If you want just the texture colour, use modelMaterial->SetDiffuseColour( glm::vec3(1,1,1) );
	teapotMaterial->SetTexture( "FlyingTeapotColour.bmp" );
	// Need to tell the material the light's position
	// If you change the light's position you need to call this again
	teapotMaterial->SetLightPosition( _lightPosition );



	// The mesh is the geometry for the object
	Mesh *modelMesh = new Mesh();
	// Load from OBJ file. This must have triangulated geometry
	modelMesh->LoadOBJ("wingedTeapot.obj");
	// Tell the game object to use this mesh
	//_model->SetMesh(modelMesh);
	

	// The mesh is the geometry for the object
	Mesh *groundMesh = new Mesh();
	// Load from OBJ file. This must have triangulated geometry
	groundMesh->LoadOBJ("ground.obj");
	// Tell the game object to use this mesh
	_model->SetMesh(groundMesh);


	_player = new Player();
	_player->SetMaterial(volcanoMaterial);
	_player->SetMesh(volcanoMesh);

	_player->SetPosition(10.0f,0.0f,0.0f);

	particleRenderer = new ParticleRenderer(_lightPosition);
}

Scene::~Scene()
{
	// You should neatly clean everything up here
	delete _model;
	delete _player;
	delete volcano;
	delete particleRenderer;
}

void Scene::Update( float deltaTs )
{
	// Update the game object (this is currently hard-coded to rotate)
	//_model->Update(deltaTs);

	//volcano->Update(deltaTs);

	_player->Update(deltaTs);

	particleRenderer->UpdateParticles(deltaTs, _cameraOrientation);

	glm::vec3 playerPos = _player->GetPosition();
	glm::quat playerOrientation = _player->GetOrientation();


	// This updates the camera's position and orientation based on those of the player


	// We change the camera's orientation to be part-way between its previous orientation and the player's orientation
	// deltaTs is very small, so the multiplier needs to be >1 if you want it to quickly snap
	_cameraOrientation = glm::slerp(_cameraOrientation,-playerOrientation,0.8f*deltaTs);

	// Build the viewing matrix:
	_viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, -1.0f, -10.0f)); // Provides offset away from player object
	_viewMatrix = glm::rotate(_viewMatrix,_cameraAngleX,glm::vec3(1,0,0)); // Allows player to rotate camera using player object as pivot
	_viewMatrix = glm::rotate(_viewMatrix,_cameraAngleY,glm::vec3(0,1,0));
	_viewMatrix = _viewMatrix * glm::mat4_cast(glm::inverse(_cameraOrientation)); // Orient towards player direction
	_viewMatrix = glm::translate( _viewMatrix, -playerPos ); // Move to player's position
	// done :)


	// This commented-out version just tracks the player, without orienting to their direction of movement:
	//_viewMatrix = glm::translate( glm::rotate( glm::rotate( glm::translate(glm::mat4(1.0f), glm::vec3(0,0,-3.5)), _cameraAngleX, glm::vec3(1,0,0) ), _cameraAngleY, glm::vec3(0,1,0) ), -playerPos );
}

void Scene::Draw()
{
	// Draw that model, giving it the camera's position and projection
	//_model->Draw(_viewMatrix,_projMatrix);
	
	_player->Draw(_viewMatrix,_projMatrix);

	particleRenderer->DrawParticles(_viewMatrix, _projMatrix);

	//volcano->Draw(_viewMatrix, _projMatrix);

}



