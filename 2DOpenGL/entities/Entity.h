#pragma once
#include "../Model.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../Texture.h"
#include "../BoundingBox.h"
#include <math.h> 

class Entity {
public:

	/**
	@brief Entity constructor with texture, position, dimensions and the uvsize of an individual element
	*/

	Entity(Texture* entTexture, glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0));

	/**
	@brief Entity constructor with  position, dimensions, uvsize of an individual element and whether or not it is a container
	*/
	Entity(glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0), glm::vec3 offPos = glm::vec3(0), bool container = false);



	virtual ~Entity();

	void init();

	virtual void update(float dt);

	void updateModelMatrix();

	void updateBoundingBoxMatrix();

	void setVelocity(glm::vec3 v, bool add = false);
	glm::vec3 getVelocity() { return velocity; }

	void setAcceleration(glm::vec3 a, bool add = false);
	glm::vec3 getAcceleration() { return acceleration; }


	void setModel(Model *m);

	Model* getModel();

	std::vector<Model*> getModels() { return entModels; }

	void setPosition(glm::vec3 p, bool add = false);

	GLuint getTextureUVBuffer();

	virtual glm::vec2 getTextureUVOffset();


	glm::vec3 getPosition();

	glm::vec3 getCentrePosition();

	glm::vec3 getDimensions();


	void setTexture(Texture* t);
	virtual Texture* getTexture();

	Texture* getTexture(int index) { return entTextures[index]; }

	virtual std::vector<Texture*> getTextures() { return entTextures; }
	





	///rotate across x axis
	void setYaw(float rot, bool add);
	///rotate across y axis
	void setPitch(float rot, bool add);
	///rotate across z axis
	void setRoll(float rot, bool add);

	float getRoll();


	

	void setScale(glm::vec3 s);



	glm::mat4 getModelMatrix();




	std::vector<glm::vec2> getEntityVertices();
	virtual std::vector<glm::vec2> getEntityUVs() { return UVs; }


	void setBlendColour(glm::vec4 bc) { blendColour = bc; }



	glm::vec4 getBlendColour() { return blendColour; }

	BoundingBox *getBoundingBox();


	void setShouldRender(bool r) { shouldRender = r; }

	bool getShouldRender() { return shouldRender; }


	
	
	


protected:

	void setQuadVertices(std::vector<glm::vec2> &vertices);
	void setQuadUVs(std::vector<glm::vec2> &UVs);

	//void setVec3(glm::vec3 &v, glm::vec3 changeV, bool add);

	bool modelMatChanged;

	std::vector<Model*> entModels;
	std::vector<Texture*> entTextures;


	///The model for this entity
	Model *model;

	///The model matrix
	glm::mat4 modelMatrix;

	glm::mat4 bbMatrix;

	///The rotation matrix
	glm::mat4 rotMatrix;

	///The scale beyond sprite size
	glm::vec3 modScale;

	//scale for the sprite size
	glm::vec3 dimensScale;

	//rotation
	///x axis rotation
	float rotPitch;
	///y axis rotation
	float rotYaw;
	///z-axis rotation
	float rotRoll;

	///If entity is container or not
	bool container;

	///speed of the entity
	float speed;

	///position of the entity
	glm::vec3 pos;

	///The dimensions of the entity
	glm::vec3 dimens;

	///the offset of position - half width and height
	glm::vec3 offsetPos;


	Texture * entTexture;

	
	///The entity's bounding box - used for collision
	BoundingBox *bb;


	glm::vec2 uvSize;


	std::vector<glm::vec2> UVs;
	std::vector<glm::vec2> vertices;


	glm::vec4 blendColour;


	bool shouldRender;

	glm::vec3 velocity;
	glm::vec3 offsetVal;


	float maxXVel;

	glm::vec3 acceleration;
};