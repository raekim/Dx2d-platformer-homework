#include "stdafx.h"
#include "Character.h"
#include "BoxCollider.h"
#include "Ground.h"

Character::Character()
{
	m_animation = new Animation;
	m_collider = new BoxCollider;
}


Character::~Character()
{
}

void Character::Init()
{
	grounded = true;
	whileHit = false;
	hitTime = 0;

	m_vPosition = { 110,300 };
	m_animation->SetPosition(m_vPosition);
	m_animation->SetScale(0.5f, 0.5f);
	m_animation->SetAniSpeed(1.0f);
	m_animation->ApplyTransform();
	
	m_isJumping = false;
	m_fMaxJumpPower = 500;
	m_fElapsedGravity = 0.0f;

	m_aniState = AniState::Idle;
	m_animation->Play(m_aniState);

	// collider init
	m_collider->myRect->Init();
	m_collider->myRect->SetPosition(m_vPosition);
	m_collider->myRect->SetSize({ 30,80 });

	if (firstInit)
	{
		facingRight = true;
		firstInit = false;
	}
	else
	{
		if(!facingRight) m_animation->FlipVertical();
		facingRight = true;
	}
}

void Character::Update()
{
	// face right&left
	{
		if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
		{
			if (!facingRight)
			{
				m_animation->FlipVertical();
				facingRight = true;
			}
		}
		else if (g_pKeyManager->isStayKeyDown(VK_LEFT))
		{
			if (facingRight)
			{
				m_animation->FlipVertical();
				facingRight = false;
			}
		}
	}
	
	// Animatino state machine
	switch (m_aniState)
	{
	case AniState::Idle:
	{
		if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
		{
			m_aniState = AniState::Jump;
			m_fJumpPower = 200;
			m_animation->Play(m_aniState);
		}
		else if (g_pKeyManager->isStayKeyDown(VK_RIGHT) || g_pKeyManager->isStayKeyDown(VK_LEFT))
		{
			m_aniState = AniState::Run;
			m_animation->Play(m_aniState);
		}
	}
		break;
	case AniState::Jump:
	{
		// space 누르고 있을 수록 높게 점프
		if (g_pKeyManager->isStayKeyDown(VK_SPACE))
		{
			m_fJumpPower += 600* g_pTimeManager->GetDeltaTime();
  			if (m_fJumpPower > m_fMaxJumpPower) m_fJumpPower = m_fMaxJumpPower;
		}
		if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
		{
			m_vPosition.x += 150 * g_pTimeManager->GetDeltaTime();
		}
		else if (g_pKeyManager->isStayKeyDown(VK_LEFT))
		{
			m_vPosition.x -= 150 * g_pTimeManager->GetDeltaTime();
		}
		float moveY = (m_fJumpPower - m_fElapsedGravity) * g_pTimeManager->GetDeltaTime();
		m_fElapsedGravity += GRAVITY * g_pTimeManager->GetDeltaTime();

		m_vPosition.y += moveY;

		// jump over
		if (m_vPosition.y <= WINSIZEY * 0.5f &&
			m_fElapsedGravity > m_fJumpPower)
		{
			m_vPosition.y = WINSIZEY * 0.5f;
			m_fElapsedGravity = 0.0f;
			m_aniState = AniState::Idle;
			m_animation->Play(m_aniState);
		}
	}
		break;
	case AniState::Run:
	{
		if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
		{
			m_aniState = AniState::Jump;
			m_fJumpPower = 200;
			m_animation->Play(m_aniState);
		}
		else if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
		{
			m_vPosition.x += 200 * g_pTimeManager->GetDeltaTime();
		}
		else if (g_pKeyManager->isStayKeyDown(VK_LEFT))
		{
			m_vPosition.x -= 200 * g_pTimeManager->GetDeltaTime();
		}
		else
		{
			m_aniState = AniState::Idle;
			m_animation->Play(m_aniState);
		}
	}
	break;
	}

	// player position clamp & camera move
	{
		if (m_vPosition.x < 300 && g_cameraPos.x > 0)
		{
			g_cameraPos.x -= 300.0f - m_vPosition.x;
			m_vPosition.x = 300;
			g_cameraPos.x = max(g_cameraPos.x, 0);
		}
		if (m_vPosition.x > 900)
		{
			g_cameraPos.x += m_vPosition.x - 900.0f;
			m_vPosition.x = 900;
		}
		m_vPosition.x = max(0, m_vPosition.x);
	}

	// Update animation
	m_animation->SetPosition(m_vPosition);
	m_animation->ApplyTransform();
	m_animation->Update();

	// update collider
	{
		m_collider->myRect->SetPosition(m_vPosition);
		m_collider->myRect->Update();
	}
}

void Character::Update(vector<Ground*>& grounds)
{
	// face right&left
	{
		if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
		{
			if (!facingRight)
			{
				m_animation->FlipVertical();
				facingRight = true;
			}
		}
		else if (g_pKeyManager->isStayKeyDown(VK_LEFT))
		{
			if (facingRight)
			{
				m_animation->FlipVertical();
				facingRight = false;
			}
		}
	}

	if (whileHit)
	{
		hitTime += g_pTimeManager->GetDeltaTime();
		if (hitTime > 1.1f)
		{
			hitTime = 0;
			m_aniState = AniState::Idle;
			m_animation->Play(m_aniState);
			whileHit = false;
		}
	}

	// Animation state machine
	switch (m_aniState)
	{
	case AniState::Idle:
	{
		if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
		{
			m_aniState = AniState::Jump;
			m_fJumpPower = 350;
			m_animation->Play(m_aniState);
		}
		else if (g_pKeyManager->isStayKeyDown(VK_RIGHT) || g_pKeyManager->isStayKeyDown(VK_LEFT))
		{
			m_aniState = AniState::Run;
			m_animation->Play(m_aniState);
		}
	}
	break;
	case AniState::Jump:
	{
		if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
		{
			m_vPosition.x += 150 * g_pTimeManager->GetDeltaTime();
			m_collider->myRect->SetPosition(m_vPosition);
			m_collider->myRect->Update();
			for (auto& g : grounds)
			{
				if (AABB2D(m_collider->myRect, g->collider->myRect) && m_collider->myRect->GetLeft() <= g->collider->myRect->GetLeft())
				{
					m_vPosition.x = g->collider->myRect->GetLeft() - m_collider->myRect->GetSize().x*0.5f;
				}
			}
		}
		else if (g_pKeyManager->isStayKeyDown(VK_LEFT))
		{
			m_vPosition.x -= 150 * g_pTimeManager->GetDeltaTime();
			m_collider->myRect->SetPosition(m_vPosition);
			m_collider->myRect->Update();
			for (auto& g : grounds)
			{
				if (AABB2D(m_collider->myRect, g->collider->myRect) && m_collider->myRect->GetRight() >= g->collider->myRect->GetRight())
				{
					m_vPosition.x = g->collider->myRect->GetRight() + m_collider->myRect->GetSize().x*0.5f;
				}
			}
		}
		
		m_fJumpPower -= GRAVITY * g_pTimeManager->GetDeltaTime();
		m_vPosition.y += m_fJumpPower * g_pTimeManager->GetDeltaTime();
		m_collider->myRect->SetPosition(m_vPosition);
		m_collider->myRect->Update();

		if (m_fJumpPower < 0)
		{
			m_fJumpPower -= 3.5f * GRAVITY * g_pTimeManager->GetDeltaTime();
			for (auto& g : grounds)
			{
				if (AABB2D(m_collider->myRect, g->collider->myRect) && m_collider->myRect->GetTop() >= g->collider->myRect->GetTop())
				{
					// 발 밑에 있는 발판 위에 서기
					if (PointInRect(g->collider->myRect->GetPosition(), g->collider->myRect->GetSize(), m_vPosition + D3DXVECTOR2(0, -(m_collider->myRect->GetSize().y*0.5f))))
					{
						m_vPosition.y = g->collider->myRect->GetTop() + m_collider->myRect->GetSize().y*0.5f;
						// jump over
						m_fElapsedGravity = 0.0f;
						m_aniState = AniState::Idle;
						m_animation->Play(m_aniState);
					}
				}
			}
			//m_fElapsedGravity += 1.5f*GRAVITY * g_pTimeManager->GetDeltaTime();
			//m_vPosition.y -= 1.5f*GRAVITY * g_pTimeManager->GetDeltaTime();
		}
		else
		{
			for (auto& g : grounds)
			{
				if (AABB2D(m_collider->myRect, g->collider->myRect) && m_collider->myRect->GetBottom() <= g->collider->myRect->GetBottom())
				{
					if (PointInRect(g->collider->myRect->GetPosition(), g->collider->myRect->GetSize(), m_vPosition + D3DXVECTOR2(0, (m_collider->myRect->GetSize().y*0.5f))))
					{
						m_vPosition.y = g->collider->myRect->GetBottom() - m_collider->myRect->GetSize().y*0.5f;
						// jump over
						m_fElapsedGravity = 0.0f;
						m_aniState = AniState::Idle;
						m_animation->Play(m_aniState);
					}
					
				}
			}
			// space 누르고 있을 수록 높게 점프.
			// 즉 spcae 누르고 있지 않는데 점프 위로 올라가는 중이면 가중중력 적용하여 낮게 점프뛰게 한다.
			if (!g_pKeyManager->isStayKeyDown(VK_SPACE))
			{
				m_fJumpPower -= 2*GRAVITY * g_pTimeManager->GetDeltaTime();
			}
		}
	}
	break;
	case AniState::Run:
	{
		if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
		{
			m_aniState = AniState::Jump;
			m_fJumpPower = 350;
			m_animation->Play(m_aniState);
		}
		else if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
		{
			m_vPosition.x += 200 * g_pTimeManager->GetDeltaTime();
			m_collider->myRect->SetPosition(m_vPosition);
			m_collider->myRect->Update();
			for (auto& g : grounds)
			{
				if (AABB2D(m_collider->myRect, g->collider->myRect) && 
					m_collider->myRect->GetLeft() <= g->collider->myRect->GetLeft() &&
					m_collider->myRect->GetBottom() != g->collider->myRect->GetTop())
				{
					m_vPosition.x = g->collider->myRect->GetLeft() - m_collider->myRect->GetSize().x*0.5f;
				}
			}
			
		}
		else if (g_pKeyManager->isStayKeyDown(VK_LEFT))
		{
			m_vPosition.x -= 200 * g_pTimeManager->GetDeltaTime();
			m_collider->myRect->SetPosition(m_vPosition);
			m_collider->myRect->Update();
			for (auto& g : grounds)
			{
				if (AABB2D(m_collider->myRect, g->collider->myRect) && 
					m_collider->myRect->GetRight() >= g->collider->myRect->GetRight() &&
					m_collider->myRect->GetBottom() != g->collider->myRect->GetTop())
				{
					m_vPosition.x = g->collider->myRect->GetRight() + m_collider->myRect->GetSize().x*0.5f;
				}
			}
			
		}
		else
		{
			m_aniState = AniState::Idle;
			m_animation->Play(m_aniState);
		}
		//m_vPosition.y -= GRAVITY * g_pTimeManager->GetDeltaTime();
		//for (auto& g : grounds)
		//{
		//	if (AABB2D(m_collider->myRect, g->collider->myRect) && m_collider->myRect->GetTop() >= g->collider->myRect->GetTop())
		//	{
		//		// 발 밑에 있는 발판 위에 서기
		//		if(PointInRect(g->collider->myRect->GetPosition(), g->collider->myRect->GetSize(), m_vPosition + D3DXVECTOR2(0, -(m_collider->myRect->GetSize().y*0.5f))))
		//			m_vPosition.y = g->collider->myRect->GetTop() + m_collider->myRect->GetSize().y*0.5f;
		//	}
		//}
	}
	break;
	}
	
	// 중력
	if (m_aniState != AniState::Jump)
	{
		m_vPosition.y -= GRAVITY * g_pTimeManager->GetDeltaTime();
		m_collider->myRect->SetPosition(m_vPosition);
		m_collider->myRect->Update();
	}
	
	for (auto& g : grounds)
	{
		if (AABB2D(m_collider->myRect, g->collider->myRect) && m_collider->myRect->GetTop() >= g->collider->myRect->GetTop())
		{
			// 발 밑에 있는 발판 위에 서기
			if (PointInRect(g->collider->myRect->GetPosition(), g->collider->myRect->GetSize(), m_vPosition + D3DXVECTOR2(0, -(m_collider->myRect->GetSize().y*0.5f))))
			{
				m_vPosition.y = g->collider->myRect->GetTop() + m_collider->myRect->GetSize().y*0.5f;
			}
		}
	}

	// player position clamp & camera move
	{
		if (m_vPosition.x < 300 && g_cameraPos.x > 0)
		{
			g_cameraPos.x -= 300.0f - m_vPosition.x;
			m_vPosition.x = 300;
			g_cameraPos.x = max(g_cameraPos.x, 0);
		}
		if (m_vPosition.x > 900)
		{
			g_cameraPos.x += m_vPosition.x - 900.0f;
			if (g_cameraPos.x > 760)
			{
				g_cameraPos.x = 760;
				m_vPosition.x = min(m_vPosition.x, WINSIZEX);
			}
			else
			{
				m_vPosition.x = 900;
			}
		}
		m_vPosition.x = max(0, m_vPosition.x);
		
	}

	// Update animation & collider
	{
		m_animation->SetPosition(m_vPosition);
		m_animation->ApplyTransform();
		m_animation->Update();
		m_collider->myRect->SetPosition(m_vPosition);
		m_collider->myRect->Update();
	}
}

void Character::Hit()
{
	whileHit = true;
	m_aniState = AniState::Hit;
	m_animation->Play(m_aniState);
	hitTime = 0;
}

void Character::Render()
{
	m_animation->Render();

	// render collider
	if(g_isDrawBorder)
	{
		m_collider->myRect->DrawBorder();
	}
}

void Character::Release()
{
}
