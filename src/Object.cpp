#include "Object.h"

Object::Object(Shader* shader, const std::string file) {
    this->shader = shader;
	MODEL_FILE_PATH = file;
	size = { 1.0f, 1.0f, 1.0f };
    position = {3.0f, 0.0f, 0.25f};
    rotationAxis = {1.0f, 0.0f, 0.0f};
	angle = 90.0f;

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), rotationAxis);
	modelMatrix = glm::scale(modelMatrix, size);
}

Object::~Object() {
	for (auto g : geometry)
		delete g;

	delete shader;
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
			shader->useProgram();

			shader->setMatrices(modelMatrix, viewMatrix, projectionMatrix);
			shader->setMaterial(g->diffuse, g->ambient, g->specular, g->shininess);

			g->VAO->Bind();
			glDrawElements(GL_TRIANGLES, g->numTriangles * 3, GL_UNSIGNED_INT, 0);
			g->VAO->Unbind();

			shader->notUseProgram();
		} else {
			std::cerr << "Object::draw(): Can't draw, mesh is not initialized properly!" << std::endl;
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

	//(*geometry)->texture = 0;
	//if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
	//	aiString path;

	//	mat->GetTexture(aiTextureType_DIFFUSE, 0, &path);
	//	std::string name = path.data;

	//	size_t found = MODEL_FILE_NAME.find_last_of("/\\");
	//	if (found != std::string::npos) {
	//		name.insert(0, MODEL_FILE_NAME.substr(0, found + 1));
	//	}

	//	std::cout << "Loading texture file: " << name << std::endl;
	//	(*geometry)->texture = pgr::createTexture(name);
	//}

	(*geometry)->VAO = new VertexArrayObject();
	(*geometry)->VAO->Bind();

	(*geometry)->EBO->Bind();

	bool validInit = false;

	if (shader != nullptr) {

		(*geometry)->VBO->Bind();
		(*geometry)->VAO->LinkAttributes(shader->locations.position, 3, GL_FLOAT, 0, (void*)0);
		(*geometry)->VAO->LinkAttributes(shader->locations.normal, 3, GL_FLOAT, 0, (void*)(3 * sizeof(float) * mesh->mNumVertices));
		//(*geometry)->VAO->LinkAttributes(shader->locations.textureCoord, 2, GL_FLOAT, 0, (void*)(6 * sizeof(float) * mesh->mNumVertices));
		(*geometry)->VBO->Unbind();

		validInit = true;
	}

	(*geometry)->VAO->Unbind();;

	(*geometry)->numTriangles = mesh->mNumFaces;

	return validInit;
}