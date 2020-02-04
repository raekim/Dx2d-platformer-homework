#include "stdafx.h"
#include "MovingGround.h"
#include "Ground.h"
#include "Character.h"
#include "BoxCollider.h"
MovingGround::MovingGround()
{
}


MovingGround::~MovingGround()
{
}

void MovingGround::Update(Character* p_character)
{
	if (AABB2D(p_character->m_collider->myRect, this->collider->myRect))
	{
		if (PointInRect(this->collider->myRect->GetPosition(),
			this->collider->myRect->GetSize(), p_character->m_vPosition + D3DXVECTOR2(0, 44)))
		{
			p_character->m_vPosition.x += moveSign * 50 * g_pTimeManager->GetDeltaTime();
		}
		
	}
	m_vBasePosition.x += moveSign * 50 * g_pTimeManager->GetDeltaTime();
	moveRange += moveSign * 50 * g_pTimeManager->GetDeltaTime();
	if (moveRange >= 400)
	{
		moveRange = 0;
		moveSign *= -1;
	}

	Ground::Update();
}
