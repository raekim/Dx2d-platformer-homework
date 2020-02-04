#include "stdafx.h"
#include "Coin.h"
#include "BoxCollider.h"

Coin::Coin(COIN_KIND kind)
{
	m_coinKind = kind;
	m_animation = new Animation;
	collider = new BoxCollider;

	Clip* clip;
	Sprite* sprite;
	switch (m_coinKind)
	{
	case COIN_KIND::BRONZE:
		// Idle Animation
		clip = new Clip(PlayMode::Loop, 1.0f);
		for (int i = 0; i < 12; i++)
		{
			sprite = new Sprite(L"coin-bronze", 12, 1, i);
			clip->AddFrame(sprite, 1.0f / 12.0f);
		}
		m_animation->AddClip(AniState::Idle, clip);
		// coin value
		m_scoreVal = 50;
		break;
	case COIN_KIND::SILVER:
		// Idle Animation
		clip = new Clip(PlayMode::Loop, 1.0f);
		for (int i = 0; i < 12; i++)
		{
			sprite = new Sprite(L"coin-silver", 12, 1, i);
			clip->AddFrame(sprite, 1.0f / 12.0f);
		}
		m_animation->AddClip(AniState::Idle, clip);
		m_scoreVal = 100;
		break;
	case COIN_KIND::GOLD:
		// Idle Animation
		clip = new Clip(PlayMode::Loop, 1.0f);
		for (int i = 0; i < 12; i++)
		{
			sprite = new Sprite(L"coin-gold", 12, 1, i);
			clip->AddFrame(sprite, 1.0f / 12.0f);
		}
		m_animation->AddClip(AniState::Idle, clip);
		m_scoreVal = 500;
		break;
	}
}


Coin::~Coin()
{
}

void Coin::Init()
{
	enabled = true;

	// collider init
	collider->myRect->Init();
	collider->myRect->SetPosition(pos);
	collider->myRect->SetSize({ 50,50 });
	//collider->myRect->SetSize();

	// animation init
	m_animation->SetPosition(pos);
	m_animation->SetScale(1, 1);
	m_animation->SetAniSpeed(1.0f);
	m_animation->ApplyTransform();
	m_aniState = AniState::Idle;
	m_animation->Play(m_aniState);
}

void Coin::Update()
{
	if (enabled)
	{
		// collider update
		collider->myRect->SetPosition(pos - g_cameraPos);
		collider->Update();

		// Update animation
		m_animation->SetPosition(pos - g_cameraPos);
		m_animation->ApplyTransform();
		m_animation->Update();
	}
}

void Coin::Render()
{
	if (enabled)
	{
		m_animation->Render();

		if (g_isDrawBorder)
		{
			collider->Render();
		}
	}
}

void Coin::Release()
{
}
