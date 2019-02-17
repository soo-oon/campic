/* Start Header -------------------------------------------------------------
--
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Graphics.cpp
Language: C++
Platform: Visual Studio 2017
Project: sword of souls
Primary : Choi jin hyun
Secondary :
Creation date: 2018/12/14
- End Header ----------------------------------------------------------------
*/
#include "Application.hpp"
#include "Graphics.hpp"
#include "GLSL.hpp"
#include "Animation.hpp"
#include <memory>
#include "Collision.hpp"
#include "Camera.hpp"
#include "State.hpp"
#include <iostream>
#include "Engine.hpp"
#include "Particle_Generator.hpp"
#include "HUD.hpp"

Graphics Graphics_;

vector2 Graphics::camera_center{};
float Graphics::camera_zoom;

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
	bool particle_shaderIsReady = Particleshader.Compile(GLSL::particle_vertex, GLSL::particle_fragment);

    if (!shapes_shaderIsReady)
        return false;

    if (!shaderIsReady)
        return false;

	if (!particle_shaderIsReady)
		return false;

    glGenVertexArrays(NumberOfVertexTypes, vertexAttributes);
    glGenBuffers(NumberOfVertexTypes, vertexBuffer);

    DescribVertexPosition();
    DescribSolidVertexPosition();
	DescribParticlePosition();

    return true;
}

void Graphics::Update(float dt)
{
	if(StateManager_.GetCurrentState()->IsCamera())
	{
		Iscamera = true;
	}
	else
	{
		temp_camera = nullptr;
		Iscamera = false;
	}

	int w, h;

	glfwGetWindowSize(Application_.GetWindow(), &w, &h);
	displaysize.x = static_cast<float>(w);
	displaysize.y = static_cast<float>(h);

	glViewport(0, 0, static_cast<int>(displaysize.x), static_cast<int>(displaysize.y));

	if (temp_camera == nullptr)
	{
		camera_zoom = 1.0f;
		camera_center = 0;
	}
	else
	{
		camera_zoom = temp_camera->GetZoomValue();
		camera_center = temp_camera->GetCenter();
	}

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SetNDC();
}

void Graphics::Draw()
{
	if (!Objectmanager_.GetObjectMap().empty())
	{
		for (auto& obj : Objectmanager_.GetObjectMap())
		{
			if(Iscamera)
			{
				if(auto temp = obj->GetComponentByTemplate<Camera>(); temp != nullptr)
				{
					temp_camera = temp;
				}
			}

			if (auto temp = obj->GetComponentByTemplate<Collision>(); temp != nullptr)
			{
				if (temp->GetCollsionMesh().IsVisible())
				{
					collsionboxes.clear();
					collsionboxes.reserve(temp->GetCollsionMesh().GetCollisionPointsCount());
					for (std::size_t i = 0; i < temp->GetCollsionMesh().GetCollisionPointsCount(); ++i)
					{
						collsionboxes.push_back({
							temp->GetCollsionMesh().GetCollisionCoordinate(i) });
					}
					Draw(temp->GetCollisionTransform(), collsionboxes, temp->GetCollsionMesh().GetPointListType(), temp->GetCollsionMesh().GetColor(0));
				}
			}

			if(auto temp = obj->GetComponentByTemplate<Particle_Generator>(); temp != nullptr)
			{
				if (temp->IsActive())
				{
					for (auto&p : temp->GetParticles())
					{
						particles.clear();
						if (auto sprite_ = p->GetParticleObject()->GetComponentByTemplate<Sprite>(); sprite_ != nullptr)
						{
							particles.reserve(p->GetParticleObject()->GetMesh().GetTexturePointsCount());
							for (std::size_t i = 0; i < p->GetParticleObject()->GetMesh().GetTexturePointsCount(); ++i)
							{
								particles.push_back(
									{ p->GetParticleObject()->GetMesh().GetPoint(i),
										p->GetParticleObject()->GetMesh().GetTextureCoordinate(i, sprite_) });
							}
							Draw(p->GetParticleObject()->GetTransform(), particles,
								p->GetParticleObject()->GetMesh().GetPointListType(), p->GetParticleObject()->GetMesh().GetColor(0), sprite_);
						}
					}
				}
			}

			if(obj->GetMesh().IsVisible())
			{
				if(auto temp_sprite = obj->GetComponentByTemplate<Sprite>(); temp_sprite != nullptr)
				{
					sprite.clear();
					sprite.reserve(obj->GetMesh().GetTexturePointsCount());
					for (std::size_t i = 0; i < obj->GetMesh().GetTexturePointsCount(); ++i)
					{
						sprite.push_back({
							obj->GetMesh().GetPoint(i),
							obj->GetMesh().GetTextureCoordinate(i, temp_sprite)
							});
					}
					Draw(obj->GetTransform(), sprite, obj->GetMesh().GetPointListType(),
						obj->GetMesh().GetColor(0),
						temp_sprite);
				}
				else if (auto temp_animation = obj->GetComponentByTemplate<Animation>(); temp_animation != nullptr)
				{
					animation.clear();
					animation.reserve(obj->GetMesh().GetAnimationPointsCount());
					for (std::size_t i = 0; i < obj->GetMesh().GetAnimationPointsCount(); ++i)
					{
						animation.push_back({
							obj->GetMesh().GetPoint(i),
							obj->GetMesh().GetAnimationCoordinate(i, temp_animation)
							});
					}
					Draw(obj->GetTransform(), animation, obj->GetMesh().GetPointListType(),
						obj->GetMesh().GetColor(0),
						temp_animation->GetCurrentAnimation().sprites);
				}
				else if (obj->GetMesh().GetPointCount())
				{
					shapes.clear();
					shapes.reserve(obj->GetMesh().GetPointCount());
					for (std::size_t i = 0; i < obj->GetMesh().GetPointCount(); ++i)
					{
						shapes.push_back({ obj->GetMesh().GetPoint(i) });
					}
					Draw(obj->GetTransform(), shapes, obj->GetMesh().GetPointListType(), obj->GetMesh().GetColor(0));
				}
			}
		}
	}
    /*if (!Objectmanager_.GetObjectMap().empty())
    {
		for (std::map<std::string, std::unique_ptr<Object>>::iterator it = Objectmanager_.GetObjectMap().begin();
			it != Objectmanager_.GetObjectMap().end(); ++it)
		{
			if (it->second != nullptr)
			{
				Object obj = *(it->second.get());

				if (Iscamera)
				{
					if (obj.GetComponentByTemplate<Camera>() != nullptr)
					{
						temp_camera = obj.GetComponentByTemplate<Camera>();
					}
				}

				if (obj.GetComponentByTemplate<Collision>() != nullptr)
				{
					Collision* temp = obj.GetComponentByTemplate<Collision>();
					if (temp->GetCollsionMesh().IsVisible())
					{
						collsionboxes.clear();
						collsionboxes.reserve(temp->GetCollsionMesh().GetCollisionPointsCount());
						for (std::size_t i = 0; i < temp->GetCollsionMesh().GetCollisionPointsCount(); ++i)
						{
							collsionboxes.push_back({
								temp->GetCollsionMesh().GetCollisionCoordinate(i) });
						}
						Draw(temp->GetCollisionTransform(), collsionboxes, temp->GetCollsionMesh().GetPointListType(), temp->GetCollsionMesh().GetColor(0));
					}
				}

				if (obj.GetComponentByTemplate<Particle>() != nullptr)
				{
					Particle* temp = obj.GetComponentByTemplate<Particle>();

					for (auto&p : temp->GetParticle_Objets())
					{
						particles.clear();
						particles.reserve(p->mesh_.GetTexturePointsCount());
						for (std::size_t i = 0; i < p->mesh_.GetTexturePointsCount(); ++i)
						{
							particles.push_back(
								{ p->mesh_.GetPoint(i), p->mesh_.GetTextureCoordinate(i, p->sprite_) });
						}
						Draw(p->transform_, particles, p->mesh_.GetPointListType(), p->mesh_.GetColor(0), p->sprite_);
					}
				}

				if (obj.GetMesh().IsVisible())
				{
					if (obj.GetComponentByTemplate<Sprite>() != nullptr)
					{
						sprite.clear();
						sprite.reserve(obj.GetMesh().GetTexturePointsCount());
						for (std::size_t i = 0; i < obj.GetMesh().GetTexturePointsCount(); ++i)
						{
							sprite.push_back({
								obj.GetMesh().GetPoint(i),
								obj.GetMesh().GetTextureCoordinate(i, obj.GetComponentByTemplate<Sprite>())
								});
						}
						Draw(obj.GetTransform(), sprite, obj.GetMesh().GetPointListType(),
							obj.GetMesh().GetColor(0),
							obj.GetComponentByTemplate<Sprite>());
					}
					else if (obj.GetComponentByTemplate<Animation>() != nullptr)
					{
						animation.clear();
						animation.reserve(obj.GetMesh().GetAnimationPointsCount());
						for (std::size_t i = 0; i < obj.GetMesh().GetAnimationPointsCount(); ++i)
						{
							animation.push_back({
								obj.GetMesh().GetPoint(i),
								obj.GetMesh().GetAnimationCoordinate(i, obj.GetComponentByTemplate<Animation>())
								});
						}
						Draw(obj.GetTransform(), animation, obj.GetMesh().GetPointListType(),
							obj.GetMesh().GetColor(0),
							obj.GetComponentByTemplate<Animation>()->GetAnimationSprite());
					}
					else if (obj.GetMesh().GetPointCount())
					{
						shapes.clear();
						shapes.reserve(obj.GetMesh().GetPointCount());
						for (std::size_t i = 0; i < obj.GetMesh().GetPointCount(); ++i)
						{
							shapes.push_back({ obj.GetMesh().GetPoint(i) });
						}
						Draw(obj.GetTransform(), shapes, obj.GetMesh().GetPointListType(), obj.GetMesh().GetColor(0));
					}
				}
			}
		}
    }*/
}

void Graphics::HUD_Draw()
{
	if (!HUD_.Get_HUD_Object_Manager().empty())
	{
		for (auto& obj : HUD_.Get_HUD_Object_Manager())
		{
			if (Iscamera)
			{
				if (auto temp = obj->GetComponentByTemplate<Camera>(); temp != nullptr)
				{
					temp_camera = temp;
				}
			}

			if (auto temp = obj->GetComponentByTemplate<Collision>(); temp != nullptr)
			{
				if (temp->GetCollsionMesh().IsVisible())
				{
					collsionboxes.clear();
					collsionboxes.reserve(temp->GetCollsionMesh().GetCollisionPointsCount());
					for (std::size_t i = 0; i < temp->GetCollsionMesh().GetCollisionPointsCount(); ++i)
					{
						collsionboxes.push_back({
							temp->GetCollsionMesh().GetCollisionCoordinate(i) });
					}
					Draw(temp->GetCollisionTransform(), collsionboxes, temp->GetCollsionMesh().GetPointListType(), temp->GetCollsionMesh().GetColor(0));
				}
			}

			if (auto temp = obj->GetComponentByTemplate<Particle_Generator>(); temp != nullptr)
			{
				if (temp->IsActive())
				{
					for (auto&p : temp->GetParticles())
					{
						particles.clear();
						if (auto sprite_ = p->GetParticleObject()->GetComponentByTemplate<Sprite>(); sprite_ != nullptr)
						{
							particles.reserve(p->GetParticleObject()->GetMesh().GetTexturePointsCount());
							for (std::size_t i = 0; i < p->GetParticleObject()->GetMesh().GetTexturePointsCount(); ++i)
							{
								particles.push_back(
									{ p->GetParticleObject()->GetMesh().GetPoint(i),
										p->GetParticleObject()->GetMesh().GetTextureCoordinate(i, sprite_) });
							}
							Draw(p->GetParticleObject()->GetTransform(), particles,
								p->GetParticleObject()->GetMesh().GetPointListType(), p->GetParticleObject()->GetMesh().GetColor(0), sprite_);
						}
					}
				}
			}

			if (obj->GetMesh().IsVisible())
			{
				if (auto temp_sprite = obj->GetComponentByTemplate<Sprite>(); temp_sprite != nullptr)
				{
					sprite.clear();
					sprite.reserve(obj->GetMesh().GetTexturePointsCount());
					for (std::size_t i = 0; i < obj->GetMesh().GetTexturePointsCount(); ++i)
					{
						sprite.push_back({
							obj->GetMesh().GetPoint(i),
							obj->GetMesh().GetTextureCoordinate(i, temp_sprite)
							});
					}
					Draw(obj->GetTransform(), sprite, obj->GetMesh().GetPointListType(),
						obj->GetMesh().GetColor(0),
						temp_sprite);
				}
				else if (auto temp_animation = obj->GetComponentByTemplate<Animation>(); temp_animation != nullptr)
				{
					animation.clear();
					animation.reserve(obj->GetMesh().GetAnimationPointsCount());
					for (std::size_t i = 0; i < obj->GetMesh().GetAnimationPointsCount(); ++i)
					{
						animation.push_back({
							obj->GetMesh().GetPoint(i),
							obj->GetMesh().GetAnimationCoordinate(i, temp_animation)
							});
					}
					Draw(obj->GetTransform(), animation, obj->GetMesh().GetPointListType(),
						obj->GetMesh().GetColor(0),
						temp_animation->GetCurrentAnimation().sprites);
				}
				else if (obj->GetMesh().GetPointCount())
				{
					shapes.clear();
					shapes.reserve(obj->GetMesh().GetPointCount());
					for (std::size_t i = 0; i < obj->GetMesh().GetPointCount(); ++i)
					{
						shapes.push_back({ obj->GetMesh().GetPoint(i) });
					}
					Draw(obj->GetTransform(), shapes, obj->GetMesh().GetPointListType(), obj->GetMesh().GetColor(0));
				}
			}
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
    Solidshader.Delete();
}

void Graphics::SetNDC()
{
	if (temp_camera != nullptr)
	{
		affine2d temp = {
			(2.0f / displaysize.x)*temp_camera->GetZoomValue(), 0.0f, 0.0f,
			0.0f, (2.0f / displaysize.y)*temp_camera->GetZoomValue(), 0.0f,
			0.0f, 0.0f, 1.0f
		};

		projection = temp;
	}
	else
	{
		affine2d temp = {
			(2.0f / displaysize.x), 0.0f, 0.0f,
			0.0f, (2.0f / displaysize.y), 0.0f,
			0.0f, 0.0f, 1.0f
		};

		projection = temp;
	}
}

affine2d Graphics::CalculateModelToNDCTransform(const Transform& transform) const
{
	affine2d myNDC;

	myNDC = transform.GetModelToWorld();

	if (temp_camera != nullptr)
	{
		myNDC = projection * temp_camera->WorldToCamera() * myNDC;
	}
	else
	{
		myNDC = projection * myNDC;
	}

	return myNDC;
}

void Graphics::Draw(const Transform& transform, const std::vector<solidshape>& vertexes, PointListType draw_type,
                    Color color)
{
	affine2d to_ndc;

	if(temp_camera != nullptr)
	{
		to_ndc = CalculateModelToNDCTransform(transform);
	}
	else
	{
		if (transform.GetParent() == nullptr)
			to_ndc = projection * transform.GetModelToWorld();
		else
			to_ndc = projection * transform.GetWorldToModel();
	}

    Solidshader.SendUniformVariable("transform", to_ndc);
    Solidshader.SendUniformVariable("depth", transform.GetDepth());
    Solidshader.SendUniformVariable("color", color);

    glBindVertexArray(vertexAttributes[(int)GraphicsType::solid_obj]);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[(int)GraphicsType::solid_obj]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(solidshape) * vertexes.size(), (const void*)(&vertexes[0]),
                 GL_DYNAMIC_DRAW);

    glDrawArrays(ToGLPrimitiveMode(draw_type), 0, (GLsizei)(vertexes.size()));
}

void Graphics::Draw(const Transform& transform, const std::vector<collsionbox>& vertexes, PointListType draw_type,
    Color color)
{
	affine2d to_ndc;

	if (temp_camera != nullptr)
	{
		to_ndc = CalculateModelToNDCTransform(transform);
	}
	else
	{
		if (transform.GetParent() == nullptr)
			to_ndc = projection * transform.GetModelToWorld();
		else
			to_ndc = projection * transform.GetWorldToModel();
	}

    Solidshader.SendUniformVariable("transform", to_ndc);
    Solidshader.SendUniformVariable("depth", transform.GetDepth());
    Solidshader.SendUniformVariable("color", color);

    glBindVertexArray(vertexAttributes[(int)GraphicsType::solid_obj]);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[(int)GraphicsType::solid_obj]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(collsionbox) * vertexes.size(), (const void*)(&vertexes[0]),
        GL_DYNAMIC_DRAW);

    glDrawArrays(ToGLPrimitiveMode(draw_type), 0, (GLsizei)(vertexes.size()));
}

void Graphics::Draw(const Transform& transform, const std::vector<texture>& vertexes, PointListType draw_type,
                    const Color color, Sprite* sprite)
{
	affine2d to_ndc;

	if (temp_camera != nullptr)
	{
		to_ndc = CalculateModelToNDCTransform(transform);
	}
	else
	{
		if (transform.GetParent() == nullptr)
			to_ndc = projection * transform.GetModelToWorld();
		else
			to_ndc = projection * transform.GetWorldToModel();
	}

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

    glBindVertexArray(vertexAttributes[(int)GraphicsType::sprite]);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[(int)GraphicsType::sprite]);

    glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(texture), &vertexes[0], GL_DYNAMIC_DRAW);

    glDrawArrays(ToGLPrimitiveMode(draw_type), 0, (GLsizei)vertexes.size());
}

void Graphics::Draw(const Transform& transform, const std::vector<animaition>& vertexes, PointListType draw_type,
                    const Color color, Sprite* sprite)
{
	affine2d to_ndc;

	if (temp_camera != nullptr)
	{
		to_ndc = CalculateModelToNDCTransform(transform);
	}
	else
	{
		if(transform.GetParent() == nullptr)
			to_ndc = projection * transform.GetModelToWorld();
		else
			to_ndc = projection * transform.GetWorldToModel();
	}

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

    glBindVertexArray(vertexAttributes[(int)GraphicsType::sprite]);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[(int)GraphicsType::sprite]);

    glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(texture), &vertexes[0], GL_DYNAMIC_DRAW);

    glDrawArrays(ToGLPrimitiveMode(draw_type), 0, (GLsizei)vertexes.size());
}

void Graphics::Draw(const Transform& transform, const std::vector<particle>& vertexes, PointListType draw_type,
	Color color, Sprite* sprite)
{
	affine2d to_ndc;

	if (temp_camera != nullptr)
	{
		to_ndc = CalculateModelToNDCTransform(transform);
	}
	else
	{
		if (transform.GetParent() == nullptr)
			to_ndc = projection * transform.GetModelToWorld();
		else
			to_ndc = projection * transform.GetWorldToModel();
	}

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

	glBindVertexArray(vertexAttributes[(int)GraphicsType::sprite]);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[(int)GraphicsType::sprite]);

	glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(texture), &vertexes[0], GL_DYNAMIC_DRAW);

	glDrawArrays(ToGLPrimitiveMode(draw_type), 0, (GLsizei)vertexes.size());
}

void Graphics::DescribSolidVertexPosition()
{
    glBindVertexArray(vertexAttributes[(int)GraphicsType::solid_obj]);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[(int)GraphicsType::solid_obj]);

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
    glBindVertexArray(vertexAttributes[(int)GraphicsType::sprite]);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[(int)GraphicsType::sprite]);

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

void Graphics::DescribParticlePosition()
{
	glBindVertexArray(vertexAttributes[(int)GraphicsType::particle]);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[(int)GraphicsType::particle]);

	int position_attribute_location = Particleshader.GetVertexAttributeLocation("position");
	int texture_coordinate_attribute_location = Particleshader.GetVertexAttributeLocation("texture_coordinate");

	constexpr int two_components_in_vertex_position = 2;
	constexpr int two_components_in_texture_coordinate = 2;
	constexpr GLenum float_element_type = GL_FLOAT;
	const GLboolean not_fixedpoint = GL_FALSE;
	const void* offset_in_struct = reinterpret_cast<const void*>(offsetof(particle, position));

	glVertexAttribPointer(position_attribute_location, two_components_in_vertex_position,
		float_element_type, not_fixedpoint, sizeof(texture), offset_in_struct);
	glEnableVertexAttribArray(position_attribute_location);

	offset_in_struct = reinterpret_cast<const void*>(offsetof(particle, particleCoordinate));

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
