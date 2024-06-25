#include "AABB.h"

namespace GameDev2D
{
	AABB::AABB(const Vector2& lower, const Vector2& upper) :
		lower(lower),
		upper(upper)
	{}

	AABB::AABB() : 
		lower(0.0f, 0.0f), 
		upper(1.0f, 1.0f)
	{}

	Vector2 AABB::Center() const
	{
		return lower + GetHalfDimensions();
	}

	Vector2 AABB::GetDimensions() const
	{
		return upper - lower;
	}

	Vector2 AABB::GetHalfDimensions() const
	{
		return GetDimensions() * 0.5f;
	}

	bool AABB::Intersects(const AABB& other) const
	{
		if (upper.x < other.lower.x)
			return false;

		if (upper.y < other.lower.y)
			return false;

		if (lower.x > other.upper.x)
			return false;

		if (lower.y > other.upper.y)
			return false;

		return true;
	}

	bool AABB::Contains(const AABB& other) const
	{
		if (other.lower.x >= lower.x &&
			other.upper.x <= upper.x &&
			other.lower.y >= lower.y &&
			other.upper.y <= upper.y)
			return true;

		return false;
	}
}