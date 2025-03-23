#pragma once

#include <fstream>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
class Map{ 
public:

    Map(const std::string& filename);
    std::vector<glm::vec3> GetPoints() const;
    int GetWidth() const;
    int GetHeight() const;
    float GetMaxHeight() const;
private:
    void LoadFromFile(const std::string& filename);

private:
    int width = 1;
    int height = 1;
    std::vector<glm::vec3> m_points;
};