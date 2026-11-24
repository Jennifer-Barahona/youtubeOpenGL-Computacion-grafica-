
#pragma once

#include <glm/glm.hpp>

class Bezier
{
public:

    glm::vec3 P0;
    glm::vec3 P1;
    glm::vec3 P2;
    glm::vec3 P3;

    Bezier(
        glm::vec3 p0,
        glm::vec3 p1,
        glm::vec3 p2,
        glm::vec3 p3
    )
    {
        P0 = p0;
        P1 = p1;
        P2 = p2;
        P3 = p3;
    }

    glm::vec3 getPoint(float t)
    {
        float u = 1.0f - t;

        glm::vec3 point =
            (u * u * u) * P0 +
            (3.0f * u * u * t) * P1 +
            (3.0f * u * t * t) * P2 +
            (t * t * t) * P3;

        return point;
    }
};
#pragma once
