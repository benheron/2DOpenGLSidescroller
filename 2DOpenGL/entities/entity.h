#pragma once
#include "../Model.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../Texture.h"
#include "../BoundingBox.h"


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

	void strafeLeft(float dt);
	void strafeRight(float dt);

	void moveForward(float dt);

	void moveBackward(float dt);


	std::vector<glm::vec2> getEntityVertices() { return vertices; }
	virtual std::vector<glm::vec2> getEntityUVs() { return UVs; }




	BoundingBox *getBoundingBox();

	//hacky player code
	void moveRight(float dt);
	void moveLeft(float dt);

	void moveDown(float dt);
	void moveUp(float dt);

	


protected:

	void setQuadVertices(std::vector<glm::vec2> &vertices);
	void setQuadUVs(std::vector<glm::vec2> &UVs);




	bool modelMatChanged;

	std::vector<Model*> entModels;
	std::vector<Texture*> entTextures;

	Model *model;
	glm::mat4 modelMatrix;
	glm::mat4 rotMatrix;
	glm::vec3 modScale;
	//rotation
	//x axis
	float rotPitch;
	//y axis
	float rotYaw;
	//z-axis
	float rotRoll;


	bool container;

	float speed;

	///position of the entity
	glm::vec3 pos;

	///the offset of position - half width and height
	glm::vec3 offsetPos;


	Texture * entTexture;

	glm::vec3 dimens;
	
	BoundingBox *bb;


	glm::vec2 uvSize;


	std::vector<glm::vec2> UVs;
	std::vector<glm::vec2> vertices;
};