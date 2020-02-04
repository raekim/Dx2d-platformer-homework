#include "stdafx.h"
#include "Monster.h"
#include "BoxCollider.h"
#include "Ground.h"

Monster::Monster(Ground* belowGround)
{
	this->belowGround = belowGround;
	facingRight = false;
	firstInit = true;
	m_collider = new BoxCollider;

	// static animation clip 초기화
	if (true)
	{
		m_animation = new Animation;

		Clip* clip;
		Sprite* sprite;
		// Idle Animation
		clip = new Clip(PlayMode::Loop, 1.0f);
		sprite = new Sprite(L"small-snail", 9, 4, 0);
		clip->AddFrame(sprite, 1.0f / 12.0f);
		m_animation->AddClip(AniState::Idle, clip);

		// Run Animation
		clip = new Clip(PlayMode::Loop, 1.0f);
		for (int i = 0; i < 5; i++)
		{
			sprite = new Sprite(L"small-snail", 9, 4, 9 + i);
			clip->AddFrame(sprite, 1.0f / 6.0f);
		}
		m_animation->AddClip(AniState::Run, clip);

		// Hit Animation
		clip = new Clip(PlayMode::Once, 1.0f);
		sprite = new Sprite(L"small-snail", 9, 4, 18);
		clip->AddFrame(sprite, 1.0f / 12.0f);
		m_animation->AddClip(AniState::Hit, clip);

		// Die Animation
		clip = new Clip(PlayMode::Once, 1.0f);
		for (int i = 0; i < 9; i++)
		{
			sprite = new Sprite(L"small-snail", 9, 4, 27 + i);
			clip->AddFrame(sprite, 1.0f / 12.0f);
		}
		m_animation->AddClip(AniState::Die, clip);
	}
}


Monster::~Monster()
{
}

void Monster::Init()
{
	enabled = true;
	m_animation->SetPosition(m_vPosition);
	m_animation->SetScale(1.2f, 1.2f);
	m_animation->SetAniSpeed(1.0f);
	m_animation->ApplyTransform();

	m_aniState = AniState::Run;
	m_animation->Play(m_aniState);

	// collider init
	m_collider->myRect->Init();
	m_collider->myRect->SetPosition(m_vPosition);
	m_collider->myRect->SetSize({ 33,30 });

}

void Monster::Update()
{
	// moving left/right
	{


		if(m_collider->myRect->GetLeft() < belowGround->collider->myRect->GetLeft())
		{
			// 오른쪽으로 기어가기
			if (!facingRight)
			{
				m_animation->FlipVertical();
				facingRight = true;
			}
			moveX = 1;
		}
		else if (m_collider->myRect->GetRight() > belowGround->collider->myRect->GetRight())
		{
			// 왼쪽으로 기어가기
			if (facingRight)
			{
				m_animation->FlipVertical();
				facingRight = false;
			}
			moveX = -1;
		}
		m_vPosition.x += moveX * speed * g_pTimeManager->GetDeltaTime();
	}

	// Update collider
	{
		m_collider->myRect->SetPosition(m_vPosition - g_cameraPos);
		m_collider->myRect->Update();

		
	}
}

void Monster::Render()
{
	m_animation->SetPosition(m_vPosition - g_cameraPos);
	m_animation->ApplyTransform();
	m_animation->Update();
	m_animation->Render();

	// render collider
	if (g_isDrawBorder)
	{
		m_collider->myRect->DrawBorder();
	}
}

void Monster::Release()
{
}
