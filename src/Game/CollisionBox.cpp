#include <Game/CollisionBox2D.h>
#include <cmath>

#if _DEBUG
#include <iostream>
#endif

Game::CollisionBox2D::CollisionBox2D(float x, float y, float sideLength, CollisionBox2DType type)
	:
	m_center{.x = x, .y = y},
	m_sideLength{fabs(sideLength)},
	m_type{type}
{}

bool Game::CollisionBox2D::Collides(CollisionBox2D other)
{
	float ox, oy, oside;
	CollisionBox2DType otype;
	other.Get(ox,oy,oside,otype);

	if (otype == CollisionBox2DType::Circle || this->m_type == CollisionBox2DType::Circle){
		if (otype == CollisionBox2DType::Circle && this->m_type == CollisionBox2DType::Circle)
			return false; //! not implemented
		else
			goto _CHECK_TYPE_SQUARE_CIRCLE;			
	}

	_CHECK_TYPE_SQUARE_SQUARE:
	{
		bool yCheck = false;
		bool xCheck = false;

		if ((oy + oside / 2 > m_center.y - m_sideLength / 2)
			&& (oy - oside / 2 < m_center.y + m_sideLength / 2))
			yCheck = true;

		if ((ox + oside / 2 > m_center.x - m_sideLength / 2)
			&& (ox - oside / 2 < m_center.x + m_sideLength / 2))
			xCheck = true;
#if _DEBUG
		if (yCheck && xCheck)
			std::cout << "Collision" << std::endl;
		else
			std::cout << "No collision" << std::endl;
#endif
		return yCheck && xCheck;
	}

	_CHECK_TYPE_SQUARE_CIRCLE:
	{
		float cx, cy, cr;
		float rx, ry, rs;

		if (otype == CollisionBox2DType::Circle) {
			cx = ox;
			cy = oy;
			cr = oside/2;
			rx = m_center.x;
			ry = m_center.y;
			rs = m_sideLength;
		}
		else {
			cx = m_center.x; 
			cy = m_center.y;
			cr = m_sideLength/2; 
			rx = ox;
			ry = oy;
			rs = oside;
		}

		float disx = cx - rx;
		float disy = cy - ry;

		return sqrt((disx * disx) + (disy * disy)) <= cr;
	}

}

void Game::CollisionBox2D::Get(float& x, float& y, float& side)
{
	x = m_center.x;
	y = m_center.y;
	side = m_sideLength;
}

void Game::CollisionBox2D::Set(float x, float y)
{
	m_center.x = x;
	m_center.y = y;
}

void Game::CollisionBox2D::Get(float& x, float& y, float& side, Game::CollisionBox2DType& type)
{
	Get(x, y, side);
	type = m_type;
}


