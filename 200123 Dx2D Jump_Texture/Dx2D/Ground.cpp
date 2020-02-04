#include "stdafx.h"
#include "Ground.h"
#include "BoxCollider.h"

Ground::Ground()
{
}

Ground::~Ground()
{
}

void Ground::Init()
{
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
	for (int i = 0; i < m_vSprites.size(); ++i)
	{
		m_vSprites[i]->SetPosition(m_vBasePosition + D3DXVECTOR2(m_vSprites[0]->GetWidth() * i*0.5f, 0) - g_cameraPos);
		m_vSprites[i]->Update();
	}
	// collider update
	collider->myRect->SetPosition(m_vCenterPosition - g_cameraPos);
	collider->Update();
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
