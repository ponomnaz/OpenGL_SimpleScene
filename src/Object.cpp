#include "Object.h"
#include <string>
#include <locale>
#include <codecvt>

Object::Object(Shader* shader, const std::string file) {
    this->shader = shader;
	MODEL_FILE_PATH = file;
	size = { 1.0f, 1.0f, 1.0f };
    position = {5.0f, 0.0f, 0.0f};
    rotationAxis = {1.0f, 0.0f, 0.0f};
	angle = 0.0f;

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), rotationAxis);
	modelMatrix = glm::scale(modelMatrix, size);
}

Object::~Object() {
	for (auto g : geometry)
		delete g;
}

void Object::update(const double dt) {
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), rotationAxis);
	modelMatrix = glm::scale(modelMatrix, size);
}

void Object::render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
	glUniformMatrix4fv(shader->locations.model, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	for (const auto g : geometry) {
		if (shader != nullptr) {
			shader->useProgram(true);

			shader->setMatrices(modelMatrix, viewMatrix, projectionMatrix);
			shader->setMaterial(g->diffuse, g->ambient, g->specular, g->shininess, g->texture);


			g->VAO->bind();
			glDrawElements(GL_TRIANGLES, g->numTriangles * 3, GL_UNSIGNED_INT, 0);
			g->VAO->unbind();

			shader->useProgram(false);
		} else {
			std::cerr << "Object::render(): Can't draw, mesh is not initialized properly!" << std::endl;
		}
	}
}

bool Object::loadModel() {
    Assimp::Importer importer;

    // unitize object in size (scale the model to fit into (-1..1)^3)
    importer.SetPropertyInteger(AI_CONFIG_PP_PTV_NORMALIZE, 1);

    // load asset from the file - you can play with various processing steps
    const aiScene* scn = importer.ReadFile(MODEL_FILE_PATH.c_str(), 0
        | aiProcess_Triangulate             // triangulate polygons (if any)
        | aiProcess_PreTransformVertices    // transforms scene hierarchy into one root with geometry-leafs only, for more see Doc
        | aiProcess_GenSmoothNormals        // calculate normals per vertex
        | aiProcess_JoinIdenticalVertices);

    // abort if the loader fails
    if (scn == NULL) {
        std::cerr << "Object::loadModel(): assimp error - " << importer.GetErrorString() << std::endl;
        return false;
    }

    if (scn->mNumMeshes == 0) {
        std::cerr << "Object::loadModel(): no meshes" << std::endl;
        return false;
    }

    for (unsigned int i = 0; i < scn->mNumMeshes; i++) {
        ObjectGeometry* g;
        if (!loadSingleMesh(&g, scn->mMeshes[i], scn->mMaterials[scn->mMeshes[i]->mMaterialIndex]))
            return false;
        geometry.push_back(g);
    }

    return true;
}

bool Object::loadSingleMesh(ObjectGeometry** geometry, aiMesh* mesh, aiMaterial* mat) {

	*geometry = new ObjectGeometry;

	(*geometry)->VBO = new VertexBufferObject(8 * sizeof(float) * mesh->mNumVertices, 0);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * sizeof(float) * mesh->mNumVertices, mesh->mVertices);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * sizeof(float) * mesh->mNumVertices, 3 * sizeof(float) * mesh->mNumVertices, mesh->mNormals);

	float* textureCoords = new float[2 * mesh->mNumVertices];
	float* currentTC = textureCoords;
	if (mesh->HasTextureCoords(0)) {
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			aiVector3D vect = (mesh->mTextureCoords[0])[i];
			*currentTC++ = vect.x;
			*currentTC++ = vect.y;
		}
	}
	glBufferSubData(GL_ARRAY_BUFFER, 6 * sizeof(float) * mesh->mNumVertices, 2 * sizeof(float) * mesh->mNumVertices, textureCoords);

	unsigned int* indices = new unsigned int[mesh->mNumFaces * 3];
	for (unsigned int f = 0; f < mesh->mNumFaces; ++f) {
		indices[f * 3 + 0] = mesh->mFaces[f].mIndices[0];
		indices[f * 3 + 1] = mesh->mFaces[f].mIndices[1];
		indices[f * 3 + 2] = mesh->mFaces[f].mIndices[2];
	}

	(*geometry)->EBO = new ElementBufferObject(3 * sizeof(unsigned int) * mesh->mNumFaces, indices);
	delete[] indices;

	aiColor4D color;
	aiString name;
	aiReturn retValue = AI_SUCCESS;

	mat->Get(AI_MATKEY_NAME, name);

	if ((retValue = aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &color)) != AI_SUCCESS)
		color = aiColor4D(0.0f, 0.0f, 0.0f, 0.0f);

	(*geometry)->diffuse = glm::vec3(color.r, color.g, color.b);

	if ((retValue = aiGetMaterialColor(mat, AI_MATKEY_COLOR_AMBIENT, &color)) != AI_SUCCESS)
		color = aiColor4D(0.0f, 0.0f, 0.0f, 0.0f);
	(*geometry)->ambient = glm::vec3(color.r, color.g, color.b);

	if ((retValue = aiGetMaterialColor(mat, AI_MATKEY_COLOR_SPECULAR, &color)) != AI_SUCCESS)
		color = aiColor4D(0.0f, 0.0f, 0.0f, 0.0f);
	(*geometry)->specular = glm::vec3(color.r, color.g, color.b);

	ai_real shininess, opacity;
	if ((retValue = aiGetMaterialFloatArray(mat, AI_MATKEY_SHININESS, &shininess, NULL)) != AI_SUCCESS)
		shininess = 1.0f;
	if ((retValue = aiGetMaterialFloatArray(mat, AI_MATKEY_SHININESS_STRENGTH, &opacity, NULL)) != AI_SUCCESS)
		opacity = 1.0f;
	(*geometry)->shininess = shininess * opacity;

	(*geometry)->texture = 0;
	if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
		aiString path;

		mat->GetTexture(aiTextureType_DIFFUSE, 0, &path);
		std::string name = path.data;

		size_t found = MODEL_FILE_PATH.find_last_of("/\\");
		if (found != std::string::npos) {
			name.insert(0, MODEL_FILE_PATH.substr(0, found + 1));
		}

		std::cout << "Loading texture file: " << name << std::endl;
		(*geometry)->texture = createTexture(name, false);
	}

	(*geometry)->VAO = new VertexArrayObject();
	(*geometry)->VAO->bind();

	(*geometry)->EBO->bind();

	bool validInit = false;

	if (shader != nullptr) {

		(*geometry)->VBO->bind();
		(*geometry)->VAO->linkAttributes(shader->locations.position, 3, GL_FLOAT, 0, (void*)0);
		(*geometry)->VAO->linkAttributes(shader->locations.normal, 3, GL_FLOAT, 0, (void*)(3 * sizeof(float) * mesh->mNumVertices));
		(*geometry)->VAO->linkAttributes(shader->locations.textureCoord, 2, GL_FLOAT, 0, (void*)(6 * sizeof(float) * mesh->mNumVertices));
		(*geometry)->VBO->unbind();

		validInit = true;
	}

	(*geometry)->VAO->unbind();;

	(*geometry)->numTriangles = mesh->mNumFaces;

	return validInit;
}

GLuint Object::createTexture(const std::string& fileName, bool mipmap) {
	// generate and bind one texture
	GLuint tex = 0;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	// set linear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mipmap ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// upload our image data to OpenGL
	if (!loadTexImage2D(fileName, GL_TEXTURE_2D)) {
		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteTextures(1, &tex);
		return 0;
	}
	// create mipmaps
	if (mipmap)
		glGenerateMipmap(GL_TEXTURE_2D);
	// unbind the texture (just in case someone will mess up with texture calls later)
	glBindTexture(GL_TEXTURE_2D, 0);
	return tex;
}

bool Object::loadTexImage2D(const std::string& fileName, GLenum target) {
	// DevIL library has to be initialized (ilInit() must be called)

	// DevIL uses mechanism similar to OpenGL, each image has its ID (name)
	ILuint img_id;
	ilGenImages(1, &img_id); // generate one image ID (name)
	ilBindImage(img_id); // bind that generated id

	// set origin to LOWER LEFT corner (the orientation which OpenGL uses)
	ilEnable(IL_ORIGIN_SET);
	ilSetInteger(IL_ORIGIN_MODE, IL_ORIGIN_LOWER_LEFT);

	// this will load image data to the currently bound image
	if (ilLoadImage(stringToWString(fileName).c_str()) == IL_FALSE) {
		ilDeleteImages(1, &img_id);
		std::cerr << __FUNCTION__ << " cannot load image " << fileName << std::endl;
		std::cerr << "Error: " << ilGetError() << std::endl;
		return false;
	}

	// if the image was correctly loaded, we can obtain some informatins about our image
	ILint width = ilGetInteger(IL_IMAGE_WIDTH);
	ILint height = ilGetInteger(IL_IMAGE_HEIGHT);
	ILenum format = ilGetInteger(IL_IMAGE_FORMAT);
	// there are many possible image formats and data types
	// we will convert all image types to RGB or RGBA format, with one byte per channel
	unsigned Bpp = ((format == IL_RGBA || format == IL_BGRA) ? 4 : 3);
	char* data = new char[width * height * Bpp];
	// this will convert image to RGB or RGBA, one byte per channel and store data to our array
	ilCopyPixels(0, 0, 0, width, height, 1, Bpp == 4 ? IL_RGBA : IL_RGB, IL_UNSIGNED_BYTE, data);
	// image data has been copied, we dont need the DevIL object anymore
	ilDeleteImages(1, &img_id);

	// bogus ATI drivers may require this call to work with mipmaps
	//glEnable(GL_TEXTURE_2D);

	glTexImage2D(target, 0, Bpp == 4 ? GL_RGBA : GL_RGB, width, height, 0, Bpp == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);

	// free our data (they were copied to OpenGL)
	delete[] data;
	return true;
}

std::wstring Object::stringToWString(const std::string& str) {
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(str);
}