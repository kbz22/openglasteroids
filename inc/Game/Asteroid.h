#pragma once
#include <Game/GameObject.h>
#include <glm/glm.hpp>

namespace Game {

	class Asteroid : public GameObject {
	private:
		float m_horizontalPos;	
		float m_rollRot;
		float m_yawRot;
		float m_pitchRot;

	public:
		Asteroid();
		void Update(float deltaTime) override;
		void Start();
		void Reset();
	};

}