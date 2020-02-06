#include "stdafx.h"
#include "Minimap.h"
#include "Ground.h"
#include "BoxCollider.h"

Minimap::Minimap()
{
	m_background = new Rect;
	m_background->Init();
	m_background->SetColor({ 34 / 255.0f, 55 / 255.0f, 110 / 255.0f, 0.5f });

	m_player = new Circle;
	m_player->Init();
	m_player->SetColor({ 1,0,0,0.7f });
}


Minimap::~Minimap()
{
}
void Minimap::Init()
{
}

void Minimap::Init(int groundNum)
{
	m_background->SetSize({ MAP_LENGTH*m_shrinkFactor, WINSIZEY*m_shrinkFactor });
	m_background->SetPosition(m_pos);

	m_player->SetRadius(5);

	m_leftBottomPos = { m_pos.x - m_background->GetSize().x*0.5f , m_pos.y - m_background->GetSize().y*0.5f };

	m_platforms.clear();
	for (int i = 0; i < groundNum; ++i)
	{
		m_platforms.push_back(new Rect);
		m_platforms[i]->Init();
		m_platforms[i]->SetColor({ 23 / 255.0f, 27 / 255.0f, 84 / 255.0f, 0.8f });
	}

	clicked = false;
}

void Minimap::Update()
{

}

void Minimap::Update(D3DXVECTOR2 playerPos, vector<Ground*>& grounds)
{
	// minimap mouse drag & move
	{
		if (g_mouseLButtonDown)
		{
			// clicking inside minimap
			if (PointInRect(m_background->GetPosition(), m_background->GetSize(), D3DXVECTOR2(g_ptMouse.x, g_ptMouse.y)))
			{
				if (!clicked)
				{
					mouseOffset = m_pos - D3DXVECTOR2(g_ptMouse.x, g_ptMouse.y);
					clicked = true;
				}
			}
			if (clicked)
			{
				m_pos = D3DXVECTOR2(g_ptMouse.x, g_ptMouse.y) + mouseOffset;
			}
		}
		else
		{
			clicked = false;
		}
	}

	m_leftBottomPos = { m_pos.x - m_background->GetSize().x*0.5f , m_pos.y - m_background->GetSize().y*0.5f };
	m_background->SetPosition(m_pos);
	m_background->Update();

	// player icon
	{
		D3DXVECTOR2 playerIconPos = m_leftBottomPos + (playerPos + g_cameraPos)* m_shrinkFactor;
		// clamp inside minimap
		playerIconPos.y = max(playerIconPos.y, m_background->GetBottom());
		playerIconPos.y = min(playerIconPos.y, m_background->GetTop());
		playerIconPos.x = min(playerIconPos.x, m_background->GetRight());
		playerIconPos.x = max(playerIconPos.x, m_background->GetLeft());
		m_player->SetPosition(playerIconPos);
		m_player->Update();
	}
	
	// ground blocks
	{
		D3DXVECTOR2 groundIconPos;
		for (int i = 0; i < m_platforms.size(); ++i)
		{
			auto& g = grounds[i];
			auto groundIcon = m_platforms[i];

			//groundIconPos = m_leftBottomPos + (g->m_vCenterPosition + g_cameraPos)* m_shrinkFactor;
			// 발판은 collider 기준으로 사이즈와 위치를 정해 미니맵에 그린다
			groundIconPos = m_leftBottomPos + (g->collider->myRect->GetPosition() + g_cameraPos)* m_shrinkFactor;
			groundIcon->SetPosition(groundIconPos);
			groundIcon->SetSize(g->collider->myRect->GetSize()*m_shrinkFactor);

			groundIcon->Update();
		}
	}
}

void Minimap::Render()
{
	// 미니맵 배경 그리기
	m_background->Render();

	// 발판 그리기
	for (auto p : m_platforms)
	{
		p->Render();
	}

	// 캐릭터 그리기
	m_player->Render();
}

void Minimap::Release()
{
}
