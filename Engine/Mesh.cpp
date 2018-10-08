/******************************************************************************/
/*!
\file   Mesh.cpp
\author Choi Jin Hyun
\par    email: jinhyun175@gmail.com
\par    DigiPen login: jinhyun.choi
\par    Course: CS230
\par    Assignment #7
\date   6/16/2018
*/
/******************************************************************************/
#include "Mesh.hpp"
#include "Animation.hpp"

Mesh::~Mesh()
{
    Clear();
}

size_t Mesh::GetPointCount() const
{
    return points.size();
}

vector2 Mesh::GetPoint(size_t index) const
{
    return points.at(index);
}

Color Mesh::GetColor(size_t index) const
{
    if (index >= colors.size())
    {
        if (!colors.empty())
            return colors.back();

        return {0, 0, 0};
    }
    return colors[index];
}


vector2 Mesh::GetTextureCoordinate(size_t index) const
{
    return textureCoordinates.at(index);
}

vector2 Mesh::GetAnimationCoordinate(size_t index, Animation* animation)
{
    switch (index)
    {
    case 0:
        animationCoordinates.at(index).x = animation->GetAnimationPosition().x;
        animationCoordinates.at(index).y = 1;
        break;
    case 1:
        animationCoordinates.at(index).x = animation->GetAnimationPosition().y;
        animationCoordinates.at(index).y = 1;
        break;
    case 2:
        animationCoordinates.at(index).x = animation->GetAnimationPosition().x;
        animationCoordinates.at(index).y = 0;
        break;
    case 3:
        animationCoordinates.at(index).x = animation->GetAnimationPosition().y;
        animationCoordinates.at(index).y = 0;
        break;
    default:
        break;
    }
    return animationCoordinates.at(index);
}

PointListType Mesh::GetPointListType() const
{
    return point_type;
}

void Mesh::SetPointListType(PointListType list_type)
{
    point_type = list_type;
}

void Mesh::AddColor(Color color)
{
    colors.push_back(color);
}

void Mesh::AddPoint(vector2 point)
{
    points.push_back(point);
}

void Mesh::AddTextureCoordinate(vector2 texture_coordinate)
{
    textureCoordinates.push_back(texture_coordinate);
}

void Mesh::AddAnimationCoordinate(vector2 animation_coordinate)
{
    animationCoordinates.push_back(animation_coordinate);
}


void Mesh::ClearColors()
{
    colors.clear();
}

void Mesh::ClearTextureCoordinates()
{
    textureCoordinates.clear();
}

void Mesh::ClearPoints()
{
    points.clear();
}

void Mesh::Clear()
{
    ClearColors();
    ClearPoints();
    ClearTextureCoordinates();
}

namespace
{
    const float PI = 4.0f * std::atan(1.0f);
}

namespace mesh
{
    Mesh CreateCircle(float radius, Color color, size_t points_number)
    {
        Mesh mesh;

        mesh.AddPoint({0, 0});
        mesh.AddTextureCoordinate({0.5f, 0.5f});

        for (int i = 0; i <= (int)points_number; ++i)
        {
            float angle = i * (360.0f / points_number) * PI / 180.0f;
            mesh.AddPoint({radius * cos(angle), radius * sin(angle)});
            mesh.AddTextureCoordinate({cos(angle), sin(angle)});
            mesh.AddColor(color);
        }

        mesh.SetPointListType(PointListType::TriangleFan);

        return mesh;
    }

    Mesh CreateLineCircle(float radius, Color color, size_t points_number)
    {
        Mesh mesh;

        for (int i = 0; i <= (int)points_number; ++i)
        {
            float angle = i * (360.0f / points_number) * PI / 180.0f;
            mesh.AddPoint({radius * cos(angle), radius * sin(angle)});
            mesh.AddColor(color);
        }

        mesh.SetPointListType(PointListType::LineStrip);

        return mesh;
    }

    Mesh CreateBox(float dimension, Color color)
    {
        Mesh mesh;

        mesh.AddPoint({-0.5f * dimension, -0.5f * dimension});
        mesh.AddPoint({0.5f * dimension, -0.5f * dimension});
        mesh.AddPoint({-0.5f * dimension, 0.5f * dimension});
        mesh.AddPoint({0.5f * dimension, 0.5f * dimension});

        mesh.AddTextureCoordinate({0, 1});
        mesh.AddTextureCoordinate({1, 1});
        mesh.AddTextureCoordinate({0, 0});
        mesh.AddTextureCoordinate({1, 0});

        mesh.AddAnimationCoordinate({0, 1});
        mesh.AddAnimationCoordinate({1, 1});
        mesh.AddAnimationCoordinate({0, 0});
        mesh.AddAnimationCoordinate({1, 0});


        mesh.SetPointListType(PointListType::TriangleStrip);

        mesh.AddColor(color);

        return mesh;
    }

    Mesh CreateLineBox(float dimension, Color color)
    {
        Mesh mesh;

        mesh.AddPoint(dimension * vector2{-0.5f, -0.5f});
        mesh.AddPoint(dimension * vector2{0.5f, -0.5f});
        mesh.AddPoint(dimension * vector2{0.5f, 0.5f});
        mesh.AddPoint(dimension * vector2{-0.5f, 0.5f});
        mesh.AddPoint(dimension * vector2{-0.5f, -0.5f});

        mesh.SetPointListType(PointListType::LineStrip);

        mesh.AddColor(color);

        return mesh;
    }

    Mesh CrateLine(vector2 point_a, vector2 point_b, Color color)
    {
        Mesh mesh;

        mesh.AddPoint(point_a);
        mesh.AddPoint(point_b);

        mesh.SetPointListType(PointListType::Lines);

        mesh.AddColor(color);

        return mesh;
    }
}
