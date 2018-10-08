/******************************************************************************/
/*!
\file   Mesh.hpp
\author Choi Jin Hyun
\par    email: jinhyun175@gmail.com
\par    DigiPen login: jinhyun.choi
\par    Course: CS230
\par    Assignment #7
\date   6/16/2018
*/
/******************************************************************************/
#pragma once

#include "vector2.hpp"
#include <vector>
#include "Color.hpp"


class Animation;

enum class PointListType
{
    Lines,
    LineStrip,
    Triangles,
    TriangleStrip,
    TriangleFan
};

class Mesh
{
public:
    Mesh() = default;
    ~Mesh();

    size_t GetPointCount() const;
    vector2 GetPoint(size_t index) const;
    Color GetColor(size_t index) const;
    vector2 GetTextureCoordinate(size_t index) const;
    vector2 GetAnimationCoordinate(size_t index, Animation* animation);

    PointListType GetPointListType() const;
    void SetPointListType(PointListType list_type);

    void AddColor(Color color);
    void AddPoint(vector2 point);
    void AddTextureCoordinate(vector2 texture_coordinate);
    void AddAnimationCoordinate(vector2 animation_coordinate);

    void ClearColors();
    void ClearTextureCoordinates();
    void ClearPoints();

    void Clear();

private:
    int Animation_frame;
    std::vector<vector2> points{};
    std::vector<Color> colors{};
    std::vector<vector2> textureCoordinates{};
    std::vector<vector2> animationCoordinates{};
    PointListType point_type = PointListType::Lines;
};

namespace mesh
{
    Mesh CreateCircle(float radius = 1, Color color = {255, 255, 255}, size_t points_number = 30);
    Mesh CreateLineCircle(float radius = 1, Color color = {255, 255, 255}, size_t points_number = 30);
    Mesh CreateBox(float dimension = 1, Color color = {255, 255, 255});
    Mesh CreateLineBox(float dimension = 1, Color color = {255, 255, 255});
    Mesh CrateLine(vector2 point_a = {0, 0}, vector2 point_b = {1, 0}, Color color = {255, 255, 255});
}
