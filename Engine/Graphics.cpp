#include "Graphics.hpp"
#include "GLSL.hpp"
#include "Animation.hpp"
#include <memory>

namespace
{
    GLenum ToGLPrimitiveMode(PointListType primitive);
}


bool Graphics::Initialize()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	bool shapes_shaderIsReady = Solidshader.Compile(GLSL::shapes_vertex, GLSL::shapes_fragment);
    bool shaderIsReady = Spriteshader.Compile(GLSL::vertex, GLSL::fragment);

	if (!shapes_shaderIsReady)
		return false;

    if (!shaderIsReady)
        return false;

    glGenVertexArrays(NumberOfVertexTypes, vertexAttributes);
    glGenBuffers(NumberOfVertexTypes, vertexBuffer);

    DescribVertexPosition();
	DescribSolidVertexPosition();

    return true;
}

void Graphics::Update(float dt)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    SetNDC();
}

void Graphics::Draw(Objectmanager* objects)
{
    for (std::map<std::string, std::unique_ptr<Object>>::iterator it = objects->GetObjectMap().begin(); it != objects
                                                                                              ->GetObjectMap().end(); ++it)
    {
        if (it->second->GetComponentByTemplate<Sprite>() != nullptr)
        {
            sprite.clear();
            sprite.reserve(it->second->GetMesh().GetTexturePointsCount());
            for (std::size_t i = 0; i < it->second->GetMesh().GetTexturePointsCount(); ++i)
            {
                sprite.push_back({
                    it->second->GetMesh().GetPoint(i),
                    it->second->GetMesh().GetTextureCoordinate(i)
                });
            }
            Draw(it->second->GetTransform(), sprite, it->second->GetMesh().GetPointListType(),
                 it->second->GetMesh().GetColor(0),
                 dynamic_cast<Sprite*>(it->second->GetComponent(ComponentType::sprite)));
        }
        else if (it->second->GetComponentByTemplate<Animation>() != nullptr)
        {
            animation.clear();
            animation.reserve(it->second->GetMesh().GetAnimationPointsCount());
            for (std::size_t i = 0; i < it->second->GetMesh().GetAnimationPointsCount(); ++i)
            {
                animation.push_back({
                    it->second->GetMesh().GetPoint(i),
                    it->second->GetMesh().GetAnimationCoordinate(i, it->second->GetComponentByTemplate<Animation>())
                });
            }
            Draw(it->second->GetTransform(), animation, it->second->GetMesh().GetPointListType(),
                 it->second->GetMesh().GetColor(0),
                 it->second->GetComponentByTemplate<Animation>()->GetAnimationSprite());
        }
		else
		{
			shapes.clear();
			shapes.reserve(it->second->GetMesh().GetPointCount());
			for (std::size_t i = 0; i<it->second->GetMesh().GetPointCount(); ++i)
			{
				vector2 temp = it->second->GetMesh().GetPoint(i);
				shapes.push_back({ it->second->GetMesh().GetPoint(i) });
			}
			Draw(it->second->GetTransform(), shapes, it->second->GetMesh().GetPointListType(), it->second->GetMesh().GetColor(0));
		}
    }
}


void Graphics::EndDraw()
{
    glFinish();
}

void Graphics::Quit()
{
    glDeleteVertexArrays(NumberOfVertexTypes, vertexAttributes);
    glDeleteBuffers(NumberOfVertexTypes, vertexBuffer);

	Spriteshader.Delete();
}

void Graphics::SetNDC()
{
    affine2d temp = {
        (2.0f / displaysize.x), 0.0f, 0.0f,
        0.0f, (2.0f / displaysize.y), 0.0f,
        0.0f, 0.0f, 1.0f
    };

    projection = temp;

    glViewport(0, 0, static_cast<GLsizei>(displaysize.x), static_cast<GLsizei>(displaysize.y));
}

void Graphics::Draw(const Transform& transform, const std::vector<solidshape>& vertexes, PointListType draw_type,
	Color color)
{
	affine2d to_ndc = projection * transform.GetModelToWorld();

	Solidshader.SendUniformVariable("transform", to_ndc);
	Solidshader.SendUniformVariable("depth", transform.GetDepth());
	Solidshader.SendUniformVariable("color", color);

	glBindVertexArray(vertexAttributes[(int)Type::solid_obj]);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[(int)Type::solid_obj]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(solidshape) * vertexes.size(), (const void*)(&vertexes[0]),
		GL_DYNAMIC_DRAW);

	glDrawArrays(ToGLPrimitiveMode(draw_type), 0, (GLsizei)(vertexes.size()));
}

void Graphics::Draw(const Transform& transform, const std::vector<texture>& vertexes, PointListType draw_type,
                    const Color color, Sprite* sprite)
{
    affine2d to_ndc = projection * transform.GetModelToWorld();

    const int texture_slot = 0;
    if (lastBoundTexture != sprite->GetTextureHandler())
    {
        sprite->Bind(texture_slot);
        lastBoundTexture = sprite->GetTextureHandler();
    }

	Spriteshader.SendUniformVariable("transform", to_ndc);
	Spriteshader.SendUniformVariable("depth", transform.GetDepth());
	Spriteshader.SendUniformVariable("color", color);
	Spriteshader.SendUniformVariable("texture_to_sample", texture_slot);

    glBindVertexArray(vertexAttributes[(int)Type::sprite]);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[(int)Type::sprite]);

    glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(texture), &vertexes[0], GL_DYNAMIC_DRAW);

    glDrawArrays(ToGLPrimitiveMode(draw_type), 0, (GLsizei)vertexes.size());
}

void Graphics::Draw(const Transform& transform, const std::vector<animaition>& vertexes, PointListType draw_type,
                    const Color color, Sprite* sprite)
{
    affine2d to_ndc = projection * transform.GetModelToWorld();

    const int texture_slot = 0;
    if (lastBoundTexture != sprite->GetTextureHandler())
    {
        sprite->Bind(texture_slot);
        lastBoundTexture = sprite->GetTextureHandler();
    }

	Spriteshader.SendUniformVariable("transform", to_ndc);
	Spriteshader.SendUniformVariable("depth", transform.GetDepth());
	Spriteshader.SendUniformVariable("color", color);
	Spriteshader.SendUniformVariable("texture_to_sample", texture_slot);

    glBindVertexArray(vertexAttributes[(int)Type::sprite]);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[(int)Type::sprite]);

    glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(texture), &vertexes[0], GL_DYNAMIC_DRAW);

    glDrawArrays(ToGLPrimitiveMode(draw_type), 0, (GLsizei)vertexes.size());
}

void Graphics::DescribSolidVertexPosition()
{
	glBindVertexArray(vertexAttributes[(int)Type::solid_obj]);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[(int)Type::solid_obj]);

	int position_attribute_location = Solidshader.GetVertexAttributeLocation("position");

	constexpr int two_components_in_vertex_position = 2;
	constexpr GLenum float_element_type = GL_FLOAT;
	constexpr GLboolean not_fixedpoint = GL_FALSE;
	const void* offset_in_struct = (const void*)offsetof(solidshape, position);

	glVertexAttribPointer(position_attribute_location, two_components_in_vertex_position, float_element_type,
		not_fixedpoint, sizeof(solidshape), offset_in_struct);

	glEnableVertexAttribArray(position_attribute_location);
}

void Graphics::DescribVertexPosition()
{
    glBindVertexArray(vertexAttributes[(int)Type::sprite]);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[(int)Type::sprite]);

    int position_attribute_location = Spriteshader.GetVertexAttributeLocation("position");
    int texture_coordinate_attribute_location = Spriteshader.GetVertexAttributeLocation("texture_coordinate");

    constexpr int two_components_in_vertex_position = 2;
    constexpr int two_components_in_texture_coordinate = 2;
    constexpr GLenum float_element_type = GL_FLOAT;
    constexpr GLboolean not_fixedpoint = GL_FALSE;
    const void* offset_in_struct = reinterpret_cast<const void*>(offsetof(texture, position));

    glVertexAttribPointer(position_attribute_location, two_components_in_vertex_position,
                          float_element_type, not_fixedpoint, sizeof(texture), offset_in_struct);
    glEnableVertexAttribArray(position_attribute_location);

    offset_in_struct = reinterpret_cast<const void*>(offsetof(texture, textureCoordinate));

    glVertexAttribPointer(texture_coordinate_attribute_location, two_components_in_texture_coordinate,
                          float_element_type, not_fixedpoint, sizeof(texture), offset_in_struct);
    glEnableVertexAttribArray(texture_coordinate_attribute_location);
}

namespace
{
    GLenum ToGLPrimitiveMode(PointListType primitive)
    {
        switch (primitive)
        {
        case PointListType::Lines:
            return GL_LINES;

        case PointListType::LineStrip:
            return GL_LINE_STRIP;

        case PointListType::Triangles:
            return GL_TRIANGLES;

        case PointListType::TriangleStrip:
            return GL_TRIANGLE_STRIP;

        case PointListType::TriangleFan:
            return GL_TRIANGLE_FAN;

        default:
            return GL_POINTS;
        }
    }
}
