#pragma once

struct Dimensions
{
	float width;
	float height;
	float length;

	Dimensions(float t_width, float t_height, float t_length)
	{
		this->width = t_width;
		this->height = t_height;
		this->length = t_length;
	}
};