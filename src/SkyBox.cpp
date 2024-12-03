#include "SkyBox.h"

SkyBox::SkyBox(SkyBoxShader* shader, const std::string file)
{
	this->shader = shader;
	MODEL_FILE_PATH = file;
}

SkyBox::~SkyBox()
{
	delete geometry;
}

void SkyBox::render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const float sunIntensity) {

	shader->useProgram(true);
	glm::mat4 viewRotation = viewMatrix;
	viewRotation[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 inversePV = glm::inverse(projectionMatrix * viewRotation);

	shader->setUniforms(inversePV, sunIntensity);

	geometry->VAO->bind();
	glBindTexture(GL_TEXTURE_CUBE_MAP, geometry->texture);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, geometry->numTriangles + 2);
	geometry->VAO->unbind();
	shader->useProgram(false);
}

bool SkyBox::loadModel() {

	geometry = new ObjectGeometry();

	static const float screenCoords[] = {
		-1.0f, -1.0f,
		 1.0f, -1.0f,
		-1.0f,  1.0f,
		 1.0f,  1.0f,
	};

	geometry->VAO = new VertexArrayObject();
	geometry->VAO->bind();

	geometry->VBO = new VertexBufferObject(sizeof(screenCoords), screenCoords);
	geometry->VAO->linkAttributes(shader->locations.coord, 2, GL_FLOAT, 0, (void*)0);
	geometry->VAO->unbind();

	geometry->numTriangles = 2;

	glActiveTexture(GL_TEXTURE0);

	glGenTextures(1, &(geometry->texture));
	glBindTexture(GL_TEXTURE_CUBE_MAP, geometry->texture);

	const char* cor[] = { "+x", "-x", "+y", "-y", "+z", "-z" };
	GLuint targets[] = {
	  GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	  GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	  GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};

	for (size_t i = 0; i < 6; i++) {
		std::string txt = std::string(MODEL_FILE_PATH) + cor[i] + ".bmp";
		std::cout << "Loading skybox: " << txt << std::endl;
		if (!Object::loadTexImage2D(txt, targets[i])) {
			std::cerr << "SkyBox::loadModel(): Can't load texture image 2D!" << std::endl;
			return false;
		}
	}

	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return true;
}