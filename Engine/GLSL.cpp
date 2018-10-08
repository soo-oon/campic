#include "GLSL.hpp"

namespace GLSL
{
    const std::string vertex =
        R"(
	#version 330

	layout (location = 0) in vec2 position;
	layout (location = 1) in vec2 texture_coordinate;

	uniform mat3 transform;
	uniform float depth;

	out vec2 interpolated_texture_coordinate;

	void main()
	{
		vec3 position = transform * vec3(position, 1.0f);
		gl_Position = vec4(position.xy, depth, 1.0);
		interpolated_texture_coordinate = texture_coordinate;
	}
	)";

    const std::string fragment =
        R"(
	#version 330
	
	in vec2 interpolated_texture_coordinate;

	uniform vec4 color;
	uniform sampler2D texture_to_sample;

	out vec4 output_color;

	void main()
	{
		vec4 texel = texture(texture_to_sample, interpolated_texture_coordinate);
		vec4 new_color = color * texel;
		if(new_color.a <= 0.0f)
			discard;
		output_color = new_color;
	}
	)";
}
