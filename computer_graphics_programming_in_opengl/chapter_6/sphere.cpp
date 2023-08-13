#include "sphere.h"

Sphere::Sphere(int prec)
{
    init(prec);
}

void Sphere::init(int prec)
{
    m_numVertices = (prec + 1) * (prec + 1);
    m_numIndices = prec * prec * 6;

    for (int i = 0; i < m_numVertices; i++)
    {
        m_vertices.push_back(glm::vec3());
    }

    for (int i = 0; i < m_numVertices; i++)
    {
        m_texCoords.push_back(glm::vec2());
    }

    for (int i = 0; i < m_numVertices; i++)
    {
        m_normals.push_back(glm::vec3());
    }

    for (int i = 0; i < m_numIndices; i++)
    {
        m_indices.push_back(0);
    }

    for (int i = 0; i <= prec; i++)
    {
        for (int j = 0; j <= prec; j++)
        {
            float y = (float)cos(toRadians(180.0f - i * 180.0f / prec));
            float x = -(float)cos(toRadians(j * 360.0f / prec)) * (float)abs(cos(asin(y)));
            float z = (float)sin(toRadians(j * 360.0f / prec)) * (float)abs(cos(asin(y)));

            m_vertices[i * (prec + 1) + j] = glm::vec3(x, y, z);
            m_texCoords[i * (prec + 1) + j] = glm::vec2(((float)j / prec), ((float)i / prec));
            m_normals[i * (prec + 1) + j] = glm::vec3(x, y, z);
        }
    }

    // 计算三角形索引
    for (int i = 0; i < prec; i++) {
        for (int j = 0; j < prec; j++) {
            m_indices[6 * (i * prec + j) + 0] = i * (prec + 1) + j;
            m_indices[6 * (i * prec + j) + 1] = i * (prec + 1) + j + 1;
            m_indices[6 * (i * prec + j) + 2] = (i + 1) * (prec + 1) + j;
            m_indices[6 * (i * prec + j) + 3] = i * (prec + 1) + j + 1;
            m_indices[6 * (i * prec + j) + 4] = (i + 1) * (prec + 1) + j + 1;
            m_indices[6 * (i * prec + j) + 5] = (i + 1) * (prec + 1) + j;
        }
    }
}

float Sphere::toRadians(float degrees)
{
    return (degrees * 2.0f * 3.14159f) / 360.0f;
}

int Sphere::getNumVertices() { return m_numVertices; }
int Sphere::getNumIndices() { return m_numIndices; }
std::vector<int> Sphere::getIndices() { return m_indices; }
std::vector<glm::vec3> Sphere::getVertices() { return m_vertices; }
std::vector<glm::vec2> Sphere::getTexCoords() { return m_texCoords; }
std::vector<glm::vec3> Sphere::getNormals() { return m_normals; }