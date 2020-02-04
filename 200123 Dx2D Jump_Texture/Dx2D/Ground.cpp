#include "stdafx.h"
#include "Ground.h"
#include "BoxCollider.h"
#include "Character.h"

Ground::Ground()
{
	// 발판은 기본적으로 움직이지 않는 발판이다.
	moving = false;
}

Ground::~Ground()
{
}

void Ground::Init()
{
	m_vBasePosition = initBasePosition;
	moveDelta = 0;
	for (int i = 0; i < m_vSprites.size(); ++i)
	{
		m_vSprites[i]->SetSize(0.5f, 0.5f);
		m_vSprites[i]->SetPosition(m_vBasePosition + D3DXVECTOR2(m_vSprites[0]->GetWidth() * i*0.5f, 0));
	}

	float leftX = m_vSprites[0]->GetPosition().x - m_vSprites[0]->GetSize().x*0.5f;
	float rightX = m_vSprites[m_vSprites.size() - 1]->GetPosition().x + m_vSprites[m_vSprites.size() - 1]->GetSize().x*0.5f;
	m_vCenterPosition = { leftX + (rightX - leftX)*0.5f, m_vSprites[0]->GetPosition().y };
	
	// collider init
	collider->myRect->SetPosition(m_vCenterPosition);
	collider->myRect->SetSize({ m_vSprites[0]->GetWidth() * m_vSprites.size()*0.5f, m_vSprites[0]->GetHeight()*0.5f });
}

void Ground::Update()
{
}

void Ground::Update(Character* p_character)
{
	for (int i = 0; i < m_vSprites.size(); ++i)
	{
		m_vSprites[i]->SetPosition(m_vBasePosition + D3DXVECTOR2(m_vSprites[0]->GetWidth() * i*0.5f, 0) - g_cameraPos);
		m_vSprites[i]->Update();
	}
	
	// 움직이는 발판의 경우
	if (moving)
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

		// 왼쪽 오른쪽 왔다갔다 하면서 움직임
		if (m_vBasePosition.x <= minX)
		{
			moveSign = 1;
		}
		else if (m_vBasePosition.x >= maxX)
		{
			moveSign = -1;
		}

		// collider update
		float leftX = m_vSprites[0]->GetPosition().x - m_vSprites[0]->GetSize().x*0.5f;
		float rightX = m_vSprites[m_vSprites.size() - 1]->GetPosition().x + m_vSprites[m_vSprites.size() - 1]->GetSize().x*0.5f;
		m_vCenterPosition = { leftX + (rightX - leftX)*0.5f, m_vSprites[0]->GetPosition().y };
		collider->myRect->SetPosition(m_vCenterPosition);
		collider->Update();
	}
	else
	{
		// collider update
		collider->myRect->SetPosition(m_vCenterPosition - g_cameraPos);
		collider->Update();
	}
}

void Ground::Render()
{
	for (auto& s : m_vSprites)
	{
		s->Render();
	}
	if (g_isDrawBorder)
	{
		collider->Render();
	}
}

void Ground::Release()
{
}
