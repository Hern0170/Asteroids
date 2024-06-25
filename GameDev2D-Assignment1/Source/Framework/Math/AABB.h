#pragma once

#include "Vector2.h"


namespace GameDev2D
{
	struct AABB
	{
		AABB(const Vector2& lower, const Vector2& upper);
		AABB();
		~AABB() = delete;

		Vector2 Center() const;
		Vector2 GetDimensions() const;
		Vector2 GetHalfDimensions() const;

		bool Intersects(const AABB& other) const;
		bool Contains(const AABB& other) const;

		Vector2 lower;
		Vector2 upper;
	};
}