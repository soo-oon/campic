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
#include "Particle_Generator.hpp"
#include "HUD.hpp"
#include "Mesh.hpp"
#include "Tile_Map.hpp"

Graphics Graphics_;

vector2 Graphics::camera_center{};

namespace
{
    GLenum ToGLPrimitiveMode(PointListType primitive);
}


bool Graphics::Initialize()
{
	std::clog << "OpenGL Rendere: " << glGetString(GL_RENDERER) << '\n';
	std::clog << "OpenGL Version: " << glGetString(GL_VERSION) << "\n\n";

    glClearColor(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);


    bool shapes_shaderIsReady = Solidshader.Compile(GLSL::shapes_vertex, GLSL::shapes_fragment);
    bool shaderIsReady = Spriteshader.Compile(GLSL::vertex, GLSL::fragment);
    bool particle_shaderIsReady = Particleshader.Compile(GLSL::particle_vertex, GLSL::particle_fragment);
    bool font_shaderIsReady = Fontshader.Compile(GLSL::font_vertex, GLSL::font_fragment);

	if (!shapes_shaderIsReady)
	{
		std::cout << "ERROR" << std::endl;
		return false;
	}

    if (!shaderIsReady)
	{
		std::cout << "ERROR" << std::endl;
		return false;
	}

    if (!particle_shaderIsReady)
	{
		std::cout << "ERROR" << std::endl;
		return false;
	}

    if (!font_shaderIsReady)
	{
		std::cout << "ERROR" << std::endl;
		return false;
	}

    glGenVertexArrays(NumberOfVertexTypes, vertexAttributes);
    glGenBuffers(NumberOfVertexTypes, vertexBuffer);

    DescribSolidVertexPosition();
    DescribVertexPosition();
    DescribParticlePosition();
    DescribFontPosition();

    return true;
}

void Graphics::Update(float dt)
{
    if (StateManager_.GetCurrentState()->IsCamera())
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
        camera_center = 0;
    }
    else
    {
        camera_center = temp_camera->GetCenter();
    }

    SetNDC();
}

void Graphics::Draw()
{
    if (!Objectmanager_.GetObjectMap().empty())
    {
        for (auto& obj : Objectmanager_.GetObjectMap())
        {
			if (obj->GetMesh().IsVisible())
			{
				if (Iscamera)
				{
					if (auto temp = obj->GetComponentByTemplate<Camera>(); temp != nullptr)
					{
						temp_camera = temp;
					}
				}

				if (auto temp = obj->GetComponentByTemplate<Collision>(); 
					temp != nullptr)
				{
					DrawCollisionBox(obj.get(), temp);
				}

				if (auto temp_sprite = obj->GetComponentByTemplate<Sprite>(); temp_sprite != nullptr)
				{
					DrawSprite(obj.get(), temp_sprite);
				}
				else if (auto temp_animation = obj->GetComponentByTemplate<Animation>(); temp_animation != nullptr)
				{
					DrawAnimation(obj.get(), temp_animation);
				}
				else if (obj->GetMesh().GetPointCount())
				{
					DrawSolidShape(obj.get());
				}

				if (auto temp = obj->GetComponentByTemplate<Particle_Generator>(); temp != nullptr)
				{
					DrawParticle(temp);
				}

				if (auto temp = obj->GetComponentByTemplate<Font>(); temp != nullptr)
				{
					DrawFont(obj.get(), temp);
				}

			}
        }
    }
}

void Graphics::HUD_Draw()
{
	if (!HUD_.Get_HUD_Object_Manager().empty())
	{
		for (auto& obj : HUD_.Get_HUD_Object_Manager())
		{
			if (obj->GetMesh().IsVisible())
			{
				if (auto temp = obj->GetComponentByTemplate<Collision>();
					temp != nullptr)
				{
					DrawCollisionBox(obj.get(), temp);
				}

				if (auto temp_sprite = obj->GetComponentByTemplate<Sprite>(); temp_sprite != nullptr)
				{
					DrawSprite(obj.get(), temp_sprite);
				}
				else if (auto temp_animation = obj->GetComponentByTemplate<Animation>(); temp_animation != nullptr)
				{
					DrawAnimation(obj.get(), temp_animation);
				}
				else if (obj->GetMesh().GetPointCount())
				{
					DrawSolidShape(obj.get());
				}

				if (auto temp = obj->GetComponentByTemplate<Particle_Generator>(); temp != nullptr)
				{
					DrawParticle(temp);
				}

				if (auto temp = obj->GetComponentByTemplate<Font>(); temp != nullptr)
				{
					DrawFont(obj.get(), temp);
				}

			}
		}
	}
}

void Graphics::Tile_Draw()
{
	if(!Tile_Map_.GetGraphicsTiles().empty())
	{	
		for (auto it = Tile_Map_.GetGraphicsTiles().begin(); it != Tile_Map_.GetGraphicsTiles().end(); ++it)
		{
			if(auto temp_sprite = it->second->GetComponentByTemplate<Sprite>(); 
				temp_sprite != nullptr)
			{
				DrawSprite(it->second, temp_sprite);
			}
			else if (auto temp_animation = it->second->GetComponentByTemplate<Animation>(); 
				temp_animation != nullptr)
			{
				DrawAnimation(it->second, temp_animation);
			}
		}
    }


	if (!Tile_Map_.GetPhysicalTiles().empty())
	{
		for (auto it = Tile_Map_.GetPhysicalTiles().begin(); it != Tile_Map_.GetPhysicalTiles().end(); ++it)
		{
			if (auto temp = it->second->GetComponentByTemplate<Collision>();
				temp != nullptr)
			{
				DrawCollisionBox(it->second, temp);
			}	

			if (auto temp_sprite = it->second->GetComponentByTemplate<Sprite>();
				temp_sprite != nullptr)
			{
				DrawSprite(it->second, temp_sprite);
			}
			else if (auto temp_animation = it->second->GetComponentByTemplate<Animation>();
				temp_animation != nullptr)
			{
				DrawAnimation(it->second, temp_animation);
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

void Graphics::BeginDraw()
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Graphics::SetNDC()
{
    if (temp_camera != nullptr)
    {
        affine2d temp = {
            (2.0f / displaysize.x) * temp_camera->GetZoomValue(), 0.0f, 0.0f,
            0.0f, (2.0f / displaysize.y) * temp_camera->GetZoomValue(), 0.0f,
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
	affine2d complex_matrix = transform.GetModelToWorld();

	complex_matrix = projection * temp_camera->WorldToCamera() * complex_matrix;
    return complex_matrix;
}

void Graphics::DrawSolidShape(Object* obj)
{
	shapes.clear();
	shapes.reserve(obj->GetMesh().GetPointCount());
	for (std::size_t i = 0; i < obj->GetMesh().GetPointCount(); ++i)
	{
		shapes.push_back({ obj->GetMesh().GetPoint(i) });
	}

	affine2d to_ndc;

	Shader::UseShader(Solidshader);

	if (temp_camera != nullptr)
	{
		to_ndc = CalculateModelToNDCTransform(obj->GetTransform());
	}
	else
	{
		to_ndc = projection * obj->GetTransform().GetModelToWorld();
	}

	Solidshader.SendUniformVariable("transform", to_ndc);
	Solidshader.SendUniformVariable("depth", obj->GetTransform().GetDepth());
	Solidshader.SendUniformVariable("color", obj->GetMesh().GetColor(0));

	glBindVertexArray(vertexAttributes[(int)GraphicsType::solid_obj]);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[(int)GraphicsType::solid_obj]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(solidshape) * shapes.size(), (const void*)(&shapes[0]),
		GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawArrays(ToGLPrimitiveMode(obj->GetMesh().GetPointListType()), 0, (GLsizei)(shapes.size()));
}

void Graphics::DrawSprite(Object* obj, Sprite* sprite_)
{
	sprite.clear();
	sprite.reserve(obj->GetMesh().GetTexturePointsCount());
	for (std::size_t i = 0; i < obj->GetMesh().GetTexturePointsCount(); ++i)
	{
		sprite.push_back({
			obj->GetMesh().GetPoint(i),
			obj->GetMesh().GetTextureCoordinate(i, sprite_)});
	}

	affine2d to_ndc;

	Shader::UseShader(Spriteshader);

	if (temp_camera != nullptr)
	{
		to_ndc = CalculateModelToNDCTransform(obj->GetTransform());
	}
	else
	{
		to_ndc = projection * obj->GetTransform().GetModelToWorld();
	}

	const int texture_slot = 0;
	if (lastBoundTexture != sprite_->GetTextureHandler())
	{
		sprite_->Bind(texture_slot);
		lastBoundTexture = sprite_->GetTextureHandler();
	}

	Spriteshader.SendUniformVariable("transform", to_ndc);
	Spriteshader.SendUniformVariable("depth", obj->GetTransform().GetDepth());
	Spriteshader.SendUniformVariable("color", obj->GetMesh().GetColor(0));
	Spriteshader.SendUniformVariable("texture_to_sample", 0);

	glBindVertexArray(vertexAttributes[(int)GraphicsType::sprite]);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[(int)GraphicsType::sprite]);

	glBufferData(GL_ARRAY_BUFFER, sprite.size() * sizeof(texture), (const void*)&sprite[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glDrawArrays(ToGLPrimitiveMode(obj->GetMesh().GetPointListType()), 0, (GLsizei)sprite.size());
}

void Graphics::DrawCollisionBox(Object* obj, Collision* collision)
{
	if (collision->GetCollsionMesh().IsVisible())
	{
		collsionboxes.clear();
		collsionboxes.reserve(collision->GetCollsionMesh().GetCollisionPointsCount());
		for (std::size_t i = 0; i < collision->GetCollsionMesh().GetCollisionPointsCount(); ++i)
		{
			collsionboxes.push_back({
				collision->GetCollsionMesh().GetCollisionCoordinate(i)
				});
		}

		affine2d to_ndc;

		Shader::UseShader(Solidshader);

		if (temp_camera != nullptr)
		{
			to_ndc = CalculateModelToNDCTransform(collision->GetCollisionTransform());
		}
		else
		{
			to_ndc = projection * collision->GetCollisionTransform().GetModelToWorld();
		}

		Solidshader.SendUniformVariable("transform", to_ndc);
		Solidshader.SendUniformVariable("depth", collision->GetCollisionTransform().GetDepth());
		Solidshader.SendUniformVariable("color", collision->GetCollsionMesh().GetColor(0));

		glBindVertexArray(vertexAttributes[(int)GraphicsType::solid_obj]);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[(int)GraphicsType::solid_obj]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(collsionbox) * collsionboxes.size(),
			(const void*)(&collsionboxes[0]),GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(ToGLPrimitiveMode(collision->GetCollsionMesh().GetPointListType()), 
			0, (GLsizei)(collsionboxes.size()));
	}
}

void Graphics::DrawAnimation(Object* obj, Animation* animation_)
{
	animation.clear();
	animation.reserve(obj->GetMesh().GetAnimationPointsCount());
	for (std::size_t i = 0; i < obj->GetMesh().GetAnimationPointsCount(); ++i)
	{
		animation.push_back({
			obj->GetMesh().GetPoint(i),
			obj->GetMesh().GetAnimationCoordinate(i, animation_)});
	}

	affine2d to_ndc;

	Shader::UseShader(Spriteshader);

	if (temp_camera != nullptr)
	{
		to_ndc = CalculateModelToNDCTransform(obj->GetTransform());
	}
	else
	{
		to_ndc = projection * obj->GetTransform().GetModelToWorld();
	}

	const int texture_slot = 0;
	if (lastBoundTexture != animation_->GetCurrentAnimation().sprites->GetTextureHandler())
	{
		animation_->GetCurrentAnimation().sprites->Bind(texture_slot);
		lastBoundTexture = animation_->GetCurrentAnimation().sprites->GetTextureHandler();
	}

	Spriteshader.SendUniformVariable("transform", to_ndc);
	Spriteshader.SendUniformVariable("depth", obj->GetTransform().GetDepth());
	Spriteshader.SendUniformVariable("color", obj->GetMesh().GetColor(0));
	Spriteshader.SendUniformVariable("texture_to_sample", texture_slot);

	glBindVertexArray(vertexAttributes[(int)GraphicsType::sprite]);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[(int)GraphicsType::sprite]);

	glBufferData(GL_ARRAY_BUFFER, animation.size() * sizeof(font), (const void*)&animation[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawArrays(ToGLPrimitiveMode(obj->GetMesh().GetPointListType()), 0, (GLsizei)animation.size());
}

void Graphics::DrawParticle(Particle_Generator* particles_)
{
	if (particles_->IsActive())
	{
		for (auto& p : particles_->GetParticles())
		{
			particles.clear();
			if (auto sprite_ = p->GetParticleObject()->GetComponentByTemplate<Sprite>(); sprite_ !=
				nullptr)
			{
				particles.reserve(p->GetParticleObject()->GetMesh().GetTexturePointsCount());
				for (std::size_t i = 0; i < p->GetParticleObject()->GetMesh().GetTexturePointsCount();
					++i)
				{
					particles.push_back({p->GetParticleObject()->GetMesh().GetPoint(i),
			p->GetParticleObject()->GetMesh().GetTextureCoordinate(i, sprite_)});
				}

				affine2d to_ndc;

				Shader::UseShader(Particleshader);

				if (temp_camera != nullptr)
				{
					to_ndc = CalculateModelToNDCTransform(p->GetParticleObject()->GetTransform());
				}
				else
				{
					to_ndc = projection * p->GetParticleObject()->GetTransform().GetModelToWorld();
				}

				const int texture_slot = 0;
				if (lastBoundTexture != sprite_->GetTextureHandler())
				{
					sprite_->Bind(texture_slot);
					lastBoundTexture = sprite_->GetTextureHandler();
				}

				Particleshader.SendUniformVariable("transform", to_ndc);
				Particleshader.SendUniformVariable("depth", p->GetParticleObject()->GetTransform().GetDepth());
				Particleshader.SendUniformVariable("color", p->GetParticleObject()->GetMesh().GetColor(0));
				Particleshader.SendUniformVariable("texture_to_sample", texture_slot);

				glBindVertexArray(vertexAttributes[(int)GraphicsType::particle]);
				glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[(int)GraphicsType::particle]);

				glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(texture), 
					(const void*)&particles[0], GL_DYNAMIC_DRAW);

				glBindBuffer(GL_ARRAY_BUFFER, 0);

				glDrawArrays(ToGLPrimitiveMode(p->GetParticleObject()->GetMesh().GetPointListType()), 0, 
					(GLsizei)particles.size());
			}
		}
	}
}

void Graphics::DrawFont(Object* obj, Font* font_)
{
	int index = 0;
	for (auto temp_mesh : font_->GetFontMeshes())
	{
		fontes.clear();
		for (std::size_t i = 0; i < temp_mesh.GetPointCount(); ++i)
		{
			fontes.push_back({ temp_mesh.GetPoint(i), temp_mesh.GetTextureCoordinate(i) });
		}

		affine2d to_ndc;

		Shader::UseShader(Fontshader);

		if (temp_camera != nullptr)
		{
			to_ndc = CalculateModelToNDCTransform(obj->GetTransform());
		}
		else
		{
			to_ndc = projection * obj->GetTransform().GetModelToWorld();
		}

		const int texture_slot = 0;

		font_->BindTexture(index);

		Fontshader.SendUniformVariable("transform", to_ndc);
		Fontshader.SendUniformVariable("depth", obj->GetTransform().GetDepth());
		Fontshader.SendUniformVariable("color", temp_mesh.GetColor(0));
		Fontshader.SendUniformVariable("text", texture_slot);

		glBindVertexArray(vertexAttributes[(int)GraphicsType::font]);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[(int)GraphicsType::font]);

		glBufferData(GL_ARRAY_BUFFER, fontes.size() * sizeof(font), (const void*)& fontes[0], GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(ToGLPrimitiveMode(temp_mesh.GetPointListType()), 0, (GLsizei)fontes.size());

		index++;
	}
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
                          float_element_type, not_fixedpoint, sizeof(particle), offset_in_struct);
    glEnableVertexAttribArray(position_attribute_location);

    offset_in_struct = reinterpret_cast<const void*>(offsetof(particle, particleCoordinate));

    glVertexAttribPointer(texture_coordinate_attribute_location, two_components_in_texture_coordinate,
                          float_element_type, not_fixedpoint, sizeof(particle), offset_in_struct);
    glEnableVertexAttribArray(texture_coordinate_attribute_location);
}

void Graphics::DescribFontPosition()
{
    glBindVertexArray(vertexAttributes[(int)GraphicsType::font]);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[(int)GraphicsType::font]);

    int position_attribute_location = Fontshader.GetVertexAttributeLocation("position");
    int texture_coordinate_attribute_location = Fontshader.GetVertexAttributeLocation("texture_coordinate");

    constexpr int two_components_in_vertex_position = 2;
    constexpr int two_components_in_texture_coordinate = 2;
    constexpr GLenum float_element_type = GL_FLOAT;
    constexpr GLboolean not_fixedpoint = GL_FALSE;
    const void* offset_in_struct = reinterpret_cast<const void*>(offsetof(font, position));

    glVertexAttribPointer(position_attribute_location, two_components_in_vertex_position,
                          float_element_type, not_fixedpoint, sizeof(font), offset_in_struct);
    glEnableVertexAttribArray(position_attribute_location);

    offset_in_struct = reinterpret_cast<const void*>(offsetof(font, fontCoordinate));

    glVertexAttribPointer(texture_coordinate_attribute_location, two_components_in_texture_coordinate,
                          float_element_type, not_fixedpoint, sizeof(font), offset_in_struct);
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
