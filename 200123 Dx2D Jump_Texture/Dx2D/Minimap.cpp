#include "stdafx.h"
#include "Minimap.h"

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
	m_background->SetSize({ MAP_LENGTH*m_shrinkFactor, WINSIZEY*m_shrinkFactor });
	m_background->SetPosition(m_pos);

	m_player->SetRadius(5);
}

void Minimap::Update()
{

}

void Minimap::Update(D3DXVECTOR2 playerPos)
{
	m_background->Update();
	m_player->SetPosition(m_pos);
	m_player->Update();
}

void Minimap::Render()
{
	// 미니맵 배경 그리기
	m_background->Render();

	// 발판 그리기

	// 캐릭터 그리기
	m_player->Render();
}

void Minimap::Release()
{
}
