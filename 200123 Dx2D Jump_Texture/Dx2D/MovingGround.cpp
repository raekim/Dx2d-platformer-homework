#include "stdafx.h"
#include "MovingGround.h"
#include "Ground.h"
#include "Character.h"
#include "BoxCollider.h"
MovingGround::MovingGround()
{
	moveSpeed = 500;
}


MovingGround::~MovingGround()
{
}

void MovingGround::Update(Character* p_character)
{
	// 캐릭터가 플랫폼 위에 올라와있다면
	// 가만히 있어도 플랫폼과 같은 속도와 방향으로 이동해야 한다
	if (AABB2D(p_character->m_collider->myRect, this->collider->myRect))
	{
		if (PointInRect(this->collider->myRect->GetPosition(),
			this->collider->myRect->GetSize(), p_character->m_vPosition + D3DXVECTOR2(0, -(p_character->m_collider->myRect->GetSize().y*0.5f))))
		{
			p_character->m_vPosition.x += moveSign * moveSpeed * g_pTimeManager->GetDeltaTime();
		}
		
	}
	m_vBasePosition.x += moveSign * moveSpeed * g_pTimeManager->GetDeltaTime();
	moveRange += moveSpeed * g_pTimeManager->GetDeltaTime();
	// 왼쪽 오른쪽 왔다갔다 하면서 움직임
	if (moveRange >= 300)
	{
		moveRange = 0;
		moveSign *= -1;
	}

	// sprite position update
	for (int i = 0; i < m_vSprites.size(); ++i)
	{
		m_vSprites[i]->SetPosition(m_vBasePosition + D3DXVECTOR2(m_vSprites[0]->GetWidth() * i*0.5f, 0) - g_cameraPos);
		m_vSprites[i]->Update();
	}

	// collider update
	float leftX = m_vSprites[0]->GetPosition().x - m_vSprites[0]->GetSize().x*0.5f;
	float rightX = m_vSprites[m_vSprites.size() - 1]->GetPosition().x + m_vSprites[m_vSprites.size() - 1]->GetSize().x*0.5f;
	m_vCenterPosition = { leftX + (rightX - leftX)*0.5f, m_vSprites[0]->GetPosition().y };
	collider->myRect->SetPosition(m_vCenterPosition);
	collider->Update();
}
