#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
using namespace std;

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

class Model
{
public:
    // model ����
    // �洢�Ѽ������������ظ�����
    vector<Texture> textures_loaded;
    vector<Mesh>    meshes;
    string directory;
    bool gammaCorrection;

    Model(string const& path, bool gamma = false);

    // ����ģ��
    void Draw(Shader& shader);

private:
    // ����Assimp֧�ֵ�ģ���ļ����洢��������
    void loadModel(string const& path);

    // �ݹ鴦��Assimp�ڵ�
    void processNode(aiNode* node, const aiScene* scene);
    // ������������
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    // ������������Ƿ��ظ�����
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};

// ��������
unsigned int TextureFromFile(const char* path, const string& directory, bool gamma);
#endif