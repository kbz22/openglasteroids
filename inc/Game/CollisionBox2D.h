#pragma once

namespace Game {

	enum CollisionBox2DType {		
		Square,
		Circle
	};

	class CollisionBox2D {

	private:
		struct {
			float x = 0.0f;
			float y = 0.0f;
		} m_center;
		float m_sideLength = 0.0f;
		CollisionBox2DType m_type;

	public:
		CollisionBox2D(float x, float y, float sideLength, CollisionBox2DType type = CollisionBox2DType::Square);
		bool Collides(CollisionBox2D other);
		void Get(float& x, float& y, float& side);
		void Get(float& x, float& y, float& side, CollisionBox2DType &type);
		void Set(float x, float y);		
	};

}