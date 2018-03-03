#include "Renderer.h"

Renderer::Renderer(Platform* platform, ResourceManager * rm) : platform(platform), rm(rm)
{
	if (shaderProg.loadProgram("Shaders/VertShader.vert", "Shaders/FragShader.frag"))
	{

		glClearColor(0.3f, 0.3f, 0.3f, 0.0f);

		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);









		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		glEnable(GL_CULL_FACE);

		textureID = glGetUniformLocation(shaderProg.getProgramID(), "textureSampler");

	}
	


}

Renderer::~Renderer()
{

}

void Renderer::render(std::vector<State*> states)
{
	//std::vector<Entity*> entities = em->getEntities();

	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProg.getProgramID());

	for (int j = 0; j < states.size(); j++)
	{
		Camera *c = states[j]->getCamera();

		

		std::vector<Entity*> entities = states[j]->getRenderables();

		glm::mat4 projMat = glm::ortho(0.0f, platform->getWindowSize().x, platform->getWindowSize().y, 0.0f);

		glm::mat4 viewMat = glm::mat4(1);
			
			


		
	/*
		for (int i = 0; i < entities.size(); i++)
		{
			//get model matrix for this specific model
			glm::mat4 modelMat = entities[i]->getModelMatrix();
			//new mvp
			glm::mat4 mvp = projMat * viewMat * modelMat;

			Model* m = entities[i]->getModel();
			//vertices buffer
			GLuint vertexBuffer = m->getVertexBuffer();

			//normal buffer
			GLuint uvBuffer = m->getUVBuffer();


			

			GLsizei indexSize = m->getVertices2D().size();
	
			// Bind our texture in Texture Unit 0
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entities[i]->getTexture()->getTextureID());
			// Set our "myTextureSampler" sampler to use Texture Unit 0
			glUniform1i(textureID, 0);



			//enable vertex position
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);


			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

			// Draw call
			glDrawArrays(GL_TRIANGLES, 0, indexSize);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



			glDisable(GL_BLEND);
		}*/

		for (int i = 0; i < entities.size(); i++)
		{
			Model* m = entities[i]->getModel();
			//vertices buffer
			GLuint vertexBuffer = m->getVertexBuffer2D();

			//normal buffer
			GLuint uvBuffer = m->getUVBuffer();


			GLsizei indexSize = m->getVertices2D().size();

			GLuint tID = entities[i]->getTexture()->getTextureID();

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tID);
			// Set our "myTextureSampler" sampler to use Texture Unit 0
			glUniform1i(textureID, 0);

			// 1rst attribute buffer : vertices
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

			// 2nd attribute buffer : UVs
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			// Draw call
			glDrawArrays(GL_TRIANGLES, 0, indexSize);

			glDisable(GL_BLEND);
		}












	}
	



	//disable vertex position
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);



	//unbind program
	glUseProgram(NULL);





}