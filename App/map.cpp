#include "map.h"

Map::Map(const std::string &filename): width(0), height(0) 
{
    LoadFromFile(filename);
}

std::vector<glm::vec3> Map::GetPoints() const
{
    return m_points;
}

int Map::GetWidth() const
{
    return width;
}

int Map::GetHeight() const
{
    return height;
}

float Map::GetMaxHeight() const
{
    auto maxElementIt = std::max_element(m_points.begin(), m_points.end(), [](const glm::vec3& v1, const glm::vec3& v2) {return v1.y < v2.y;});
    return maxElementIt->y;
}

void Map::LoadFromFile(const std::string &filename)
{
    std::ifstream is(filename);
    if(!is) {
        std::cerr << "Couldn't find file " << filename << std::endl;
        return;
    }
 height = 0;
    width = 0;
    std::string line;
       while (std::getline(is, line)) {
        std::istringstream iss(line);
        glm::vec3 point;
        int currentWidth = 0; // Текущая ширина для этой строки

        while (iss >> point.y) {
            point.x = currentWidth; // Устанавливаем x как текущую ширину
            point.z = height; // Устанавливаем z как высоту
            m_points.emplace_back(point);
            currentWidth++;
        }

        // Обновляем ширину, если текущая ширина больше
        if (currentWidth > width) {
            width = currentWidth;
        }

        height++; // Увеличиваем высоту после обработки строки
    }
}