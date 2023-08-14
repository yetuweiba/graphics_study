#include "torus.h"

#include <glm/gtc/matrix_transform.hpp>

Torus::Torus()
{
    prec = 48;
    inner = 0.5f;
    outer = 0.2f;

    init();
}

Torus::Torus(float in, float out, int precIn) {
    prec = precIn;
    inner = in;
    outer = out;
    init();
}

float Torus::toRadians(float degrees)
{
    return (degrees * 2.0f * 3.14159f) / 360.0f;
}

void Torus::init()
{
    m_numVertices = (prec + 1) * (prec + 1);
    m_numIndices = prec * prec * 6;

    for (int i = 0; i < m_numVertices; i++) { m_vertices.push_back(glm::vec3()); }
    for (int i = 0; i < m_numVertices; i++) { m_texCoords.push_back(glm::vec2()); }
    for (int i = 0; i < m_numVertices; i++) { m_normals.push_back(glm::vec3()); }
    for (int i = 0; i < m_numVertices; i++) { m_sTangents.push_back(glm::vec3()); }
    for (int i = 0; i < m_numVertices; i++) { m_tTangents.push_back(glm::vec3()); }
    for (int i = 0; i < m_numIndices; i++) { m_indices.push_back(0); }

    for (int i = 0; i < prec + 1; i++)
    {
        float amt = toRadians(i * 360.0f / prec);

        glm::mat4 rmat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 0.0f, 1.0f));
        glm::vec3 initPos(rmat * glm::vec4(outer, 0.0f, 0.0f, 1.0f));
        m_vertices[i] = glm::vec3(initPos + glm::vec3(inner, 0.0f, 0.0f));

        m_texCoords[i] = glm::vec2(0.0f, ((float)i) / (float)prec);

        rmat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 0.0f, 1.0f));
        m_tTangents[i] = glm::vec3(rmat * glm::vec4(0.0f, -1.0f, 0.0f, 1.0f));
        m_sTangents[i] = glm::vec3(glm::vec3(0.0f, 0.0f, -1.0f));
        m_normals[i] = glm::cross(m_tTangents[i], m_sTangents[i]);
    }

    for (int ring = 1; ring < prec + 1; ring++)
    {
        for (int i = 0; i < prec + 1; i++)
        {
            // 绕 y 轴旋转最初那个环的顶点坐标
            float amt = (float)(toRadians(ring * 360.0f / prec));
            glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));
            m_vertices[ring * (prec + 1) + i] = glm::vec3(rMat * glm::vec4(m_vertices[i], 1.0f));
            // 计算新环顶点的纹理坐标
            m_texCoords[ring * (prec + 1) + i] = glm::vec2((float)ring * 2.0f / (float)prec, m_texCoords
                [i].t);
            if (m_texCoords[ring * (prec + 1) + i].s > 1.0) m_texCoords[ring * (prec + 1) + i].s -= 1.0f;
            // 绕 y 轴旋转切向量和副切向量
            rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));
            m_sTangents[ring * (prec + 1) + i] = glm::vec3(rMat * glm::vec4(m_sTangents[i], 1.0f));
            rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));
            m_tTangents[ring * (prec + 1) + i] = glm::vec3(rMat * glm::vec4(m_tTangents[i], 1.0f));
            // 绕 y 轴旋转法向量
            rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));
            m_normals[ring * (prec + 1) + i] = glm::vec3(rMat * glm::vec4(m_normals[i], 1.0f));
        }
    }

    for (int ring = 0; ring < prec; ring++) {
        for (int i = 0; i < prec; i++) {
            m_indices[((ring * prec + i) * 2) * 3 + 0] = ring * (prec + 1) + i;
            m_indices[((ring * prec + i) * 2) * 3 + 1] = (ring + 1) * (prec + 1) + i;
            m_indices[((ring * prec + i) * 2) * 3 + 2] = ring * (prec + 1) + i + 1;
            m_indices[((ring * prec + i) * 2 + 1) * 3 + 0] = ring * (prec + 1) + i + 1;
            m_indices[((ring * prec + i) * 2 + 1) * 3 + 1] = (ring + 1) * (prec + 1) + i;
            m_indices[((ring * prec + i) * 2 + 1) * 3 + 2] = (ring + 1) * (prec + 1) + i + 1;
        }
    }
}