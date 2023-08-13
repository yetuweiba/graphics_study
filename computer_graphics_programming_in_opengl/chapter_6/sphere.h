#pragma once

#include <cmath>
#include <vector>
#include <glm/glm.hpp>

class Sphere
{
public:
    Sphere(int prec);
    int getNumVertices();
    int getNumIndices();

    std::vector<int> getIndices();
    std::vector<glm::vec3> getVertices();
    std::vector<glm::vec2> getTexCoords();
    std::vector<glm::vec3> getNormals();

private:
    void init(int);
    float toRadians(float degrees);
private:
    int m_numVertices;
    int m_numIndices;

    std::vector<int> m_indices;
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec2> m_texCoords;
    std::vector<glm::vec3> m_normals;
};