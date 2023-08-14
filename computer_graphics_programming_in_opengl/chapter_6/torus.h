#pragma once

#include <cmath>
#include <vector>
#include <glm/glm.hpp>

class Torus
{
public:
    Torus();
    Torus(float innerRadius, float outerRadius, int prec);

    int getNumVertices() { return m_numVertices; }
    int getNumIndices() { return m_numIndices; }
    std::vector<int> getIndices() { return m_indices; }
    std::vector<glm::vec3> getVertices() { return m_vertices; }
    std::vector<glm::vec2> getTexCoords() { return m_texCoords; }
    std::vector<glm::vec3> getNormals() { return m_normals; }
    std::vector<glm::vec3> getStangents() { return m_sTangents; }
    std::vector<glm::vec3> getTtangents() { return m_tTangents; }

private:
    void init();
    float toRadians(float degrees);
private:
    int m_numVertices;
    int m_numIndices;
    int prec;
    float inner;
    float outer;

    std::vector<int> m_indices;
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec2> m_texCoords;
    std::vector<glm::vec3> m_normals;
    std::vector<glm::vec3> m_sTangents;
    std::vector<glm::vec3> m_tTangents;
};
