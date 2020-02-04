#include "stdafx.h"
#include "MainGame.h"
#include "Character.h"
#include "Ground.h"
#include "BoxCollider.h"
#include "MovingGround.h"

/* 런 or 아케이드 게임
맵 이동
캐릭터 애니메이션

오브젝트
코인, 아이템, 장애물, 몬스터, 발판지형
*/

MainGame::MainGame()
{
	initTimeScale = g_pTimeManager->GetTimeScale();
	srand(time(NULL));

	SetViewProjectionMatrixes();
	SetBlendStates();

	// Player load
	{
		// 리소스 로드
		g_pTextureManager->AddTexture(L"Player-Idle", L"Player-Dog/idle.png");
		g_pTextureManager->AddTexture(L"Player-Jump", L"Player-Dog/jump.png");
		g_pTextureManager->AddTexture(L"Player-Run", L"Player-Dog/run.png");
		g_pTextureManager->AddTexture(L"Player-Hit", L"Player-Dog/hurt.png");
		
		m_pPlayer = new Character;
		Animation*& playerAnim = m_pPlayer->m_animation;
		Clip* clip;
		Sprite* sprite;

		// Idle Animation
		clip = new Clip(PlayMode::Loop, 1.0f);
		for (int i = 0; i < 10; i++)
		{
			sprite = new Sprite(L"Player-Idle", 10, 1, i);
			clip->AddFrame(sprite, 1.0f / 12.0f);
		}
		playerAnim->AddClip(AniState::Idle, clip);

		// Jump Animation
		clip = new Clip(PlayMode::Once, 1.0f);
		for (int i = 0; i < 8; i++)
		{
			sprite = new Sprite(L"Player-Jump", 8, 1, i);
			clip->AddFrame(sprite, 1.0f / 12.0f);
		}
		playerAnim->AddClip(AniState::Jump, clip);

		// Run Animation
		clip = new Clip(PlayMode::Loop, 1.0f);
		for (int i = 0; i < 8; i++)
		{
			sprite = new Sprite(L"Player-Run", 8, 1, i);
			clip->AddFrame(sprite, 1.0f / 12.0f);
		}
		playerAnim->AddClip(AniState::Run, clip);

		// Hit Animation
		clip = new Clip(PlayMode::Once, 1.0f);
		for (int i = 0; i < 10; i++)
		{
			sprite = new Sprite(L"Player-Hit", 10, 1, i);
			clip->AddFrame(sprite, 1.0f / 12.0f);
		}
		playerAnim->AddClip(AniState::Hit, clip);
	}

	// map load (platform)
	{
		g_pTextureManager->AddTexture(L"bg-ground-grass-left", L"bg/grassLeft.png");
		g_pTextureManager->AddTexture(L"bg-ground-grass-mid", L"bg/grassMid.png");
		g_pTextureManager->AddTexture(L"bg-ground-grass-right", L"bg/grassRight.png");

		Ground* ground;
		Sprite* sprite;


		// moving ground
		movGround = new MovingGround;
		sprite = new Sprite(L"bg-ground-grass-left", 1, 1, 0);
		movGround->m_vSprites.push_back(sprite);
		sprite = new Sprite(L"bg-ground-grass-mid", 1, 1, 0);
		movGround->m_vSprites.push_back(sprite);
		sprite = new Sprite(L"bg-ground-grass-right", 1, 1, 0);
		movGround->collider = new BoxCollider;
		movGround->m_vBasePosition = { WINSIZEX + 476,444 };


		ground = new Ground;
		sprite = new Sprite(L"bg-ground-grass-left", 1, 1, 0);
		ground->m_vSprites.push_back(sprite);
		sprite = new Sprite(L"bg-ground-grass-mid", 1, 1, 0);
		ground->m_vSprites.push_back(sprite);
		sprite = new Sprite(L"bg-ground-grass-right", 1, 1, 0);
		ground->m_vSprites.push_back(sprite);
		ground->collider = new BoxCollider;
		ground->m_vBasePosition = { WINSIZEX*0.5f,WINSIZEY*0.5f };
		m_pGround.push_back(ground);

		ground = new Ground;
		sprite = new Sprite(L"bg-ground-grass-left", 1, 1, 0);
		ground->m_vSprites.push_back(sprite);
		for (int i = 0; i < 15; ++i)
		{
			sprite = new Sprite(L"bg-ground-grass-mid", 1, 1, 0);
			ground->m_vSprites.push_back(sprite);
		}
		sprite = new Sprite(L"bg-ground-grass-right", 1, 1, 0);
		ground->m_vSprites.push_back(sprite);
		ground->collider = new BoxCollider;
		ground->m_vBasePosition = { 0, 195 };
		m_pGround.push_back(ground);

		ground = new Ground;
		sprite = new Sprite(L"bg-ground-grass-left", 1, 1, 0);
		ground->m_vSprites.push_back(sprite);
		for (int i = 0; i < 15; ++i)
		{
			sprite = new Sprite(L"bg-ground-grass-mid", 1, 1, 0);
			ground->m_vSprites.push_back(sprite);
		}
		sprite = new Sprite(L"bg-ground-grass-right", 1, 1, 0);
		ground->m_vSprites.push_back(sprite);
		ground->collider = new BoxCollider;
		ground->m_vBasePosition = { 1042, 284 };
		m_pGround.push_back(ground);

		ground = new Ground;
		sprite = new Sprite(L"bg-ground-grass-left", 1, 1, 0);
		ground->m_vSprites.push_back(sprite);

		sprite = new Sprite(L"bg-ground-grass-right", 1, 1, 0);
		ground->m_vSprites.push_back(sprite);
		ground->collider = new BoxCollider;
		ground->m_vBasePosition = { 1020, 520 };
		m_pGround.push_back(ground);
	}

	// monsters load
	{
		g_pTextureManager->AddTexture(L"small-snail", L"snail-trans.png");
		monsters.push_back(new Monster(m_pGround[0]));
		monsters.push_back(new Monster(m_pGround[1]));
		monsters.push_back(new Monster(m_pGround[2]));
		monsters.push_back(new Monster(m_pGround[2]));
		monsters.push_back(new Monster(m_pGround[2]));
		monsters[1]->speed = 60;
		monsters[3]->speed = 40;
		monsters[4]->speed = 77;
	}

	// map load (background)
	{
		g_pTextureManager->AddTexture(L"bg-forest1", L"bg/forest1.png");
		background* bg;
		bg = new background;
		bg->m_Sprite = new Sprite(L"bg-forest1", 1, 1, 0);
		bg->m_Sprite->SetSize( 2,2 );
		bg->camRatio = 0.5f;
		bg->pos = { WINSIZEX*0.5f, WINSIZEY*0.5f };

		backgrounds.push_back(bg);
	}

	// coin load
	{
		g_pTextureManager->AddTexture(L"coin-gold", L"etc/CoinGold.png");
		g_pTextureManager->AddTexture(L"coin-bronze", L"etc/CoinBronze.png");
		g_pTextureManager->AddTexture(L"coin-silver", L"etc/CoinSilver.png");

		coins.push_back(new Coin(COIN_KIND::GOLD));
		coins.push_back(new Coin(COIN_KIND::GOLD));
		coins.push_back(new Coin(COIN_KIND::BRONZE));
		coins.push_back(new Coin(COIN_KIND::BRONZE));
		coins.push_back(new Coin(COIN_KIND::BRONZE));
		coins.push_back(new Coin(COIN_KIND::GOLD));
		coins.push_back(new Coin(COIN_KIND::GOLD));
		coins.push_back(new Coin(COIN_KIND::SILVER));
		coins.push_back(new Coin(COIN_KIND::SILVER));
		coins.push_back(new Coin(COIN_KIND::SILVER));
		coins.push_back(new Coin(COIN_KIND::SILVER));
	}

	// UI load
	{
		// score
		g_pTextureManager->AddTexture(L"point-number", L"etc/Number.png");
		Sprite* sprite;
		for (int i = 0; i < 10; i++)
		{
			sprite = new Sprite(L"point-number", 10, 1, i);
			m_NumberUI.push_back(sprite);
			sprite->SetSize(0.5f, 0.5f);
		}

		// heart
		g_pTextureManager->AddTexture(L"hp-UI", L"etc/Heart.png");
		heartUI = new Sprite(L"hp-UI", 1, 1, 0);
		heartUI->SetSize(0.1f, 0.1f);

		// game over
		g_pTextureManager->AddTexture(L"game-over", L"game-over.png");
		gameOverUI = new Sprite(L"game-over", 1, 1, 0);
		gameOverUI->SetPosition(WINSIZEX*0.5f, WINSIZEY*0.5f);
		gameOverUI->Update();

		// title screen
		g_pTextureManager->AddTexture(L"title-screen", L"title-screen.png");
		titleUI = new Sprite(L"title-screen", 1, 1, 0);
		titleUI->Init();
		titleUI->SetPosition(WINSIZEX*0.5f, WINSIZEY*0.5f);
		titleUI->Update();
	}
	g_pTimeManager->SetTimeScale(0);
	gameStarted = false;
}

void MainGame::SetViewProjectionMatrixes()
{
	ViewProjectionDesc VPDesc;

	// 뷰 매트릭스 셋팅
	D3DXVECTOR3 eye(0, 0, -1);
	D3DXVECTOR3 lookAt(0, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXMatrixLookAtLH(&VPDesc.View, &eye, &lookAt, &up);
	D3DXMatrixTranspose(&VPDesc.View, &VPDesc.View);
	// 셰이더에서 매트릭스의 행과 열의 방향이 바껴있기 때문에 트랜스포즈를 해주어야 한다.

	// 프로젝션 매트릭스 셋팅
	D3DXMatrixOrthoOffCenterLH(&VPDesc.Projection, 0, (float)WINSIZEX, 0, (float)WINSIZEY, -1, 1);
	D3DXMatrixTranspose(&VPDesc.Projection, &VPDesc.Projection);

	// 버퍼 생성
	D3D11_BUFFER_DESC desc = { 0, };
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(ViewProjectionDesc);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// 버퍼에 담을 데이터
	D3D11_SUBRESOURCE_DATA data = { 0, };
	data.pSysMem = &VPDesc;

	HRESULT hr = Device->CreateBuffer(&desc, &data, &m_pViewProjBuffer);
}

void MainGame::SetBlendStates()
{
	D3D11_BLEND_DESC desc = { 0, };

	desc.RenderTarget[0].BlendEnable = false;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	Device->CreateBlendState(&desc, &m_pNormalBlendState);

	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	Device->CreateBlendState(&desc, &m_pAlphaBlendState);
}

MainGame::~MainGame()
{
	this->Release();

	SAFE_RELEASE(m_pNormalBlendState);
	SAFE_RELEASE(m_pAlphaBlendState);

	SAFE_RELEASE(m_pViewProjBuffer);

	SAFE_RELEASE(m_pPlayer);
	for (auto& g : m_pGround)
	{
		SAFE_RELEASE(g);
	}
	for (auto& bg : backgrounds)
	{
		SAFE_RELEASE(bg);
	}
}

void MainGame::Init()
{
	gameStarted = true;
	gameOver = false;
	g_pTimeManager->SetTimeScale(initTimeScale);
	m_point = 0;
	m_hp = 3;
	g_cameraPos = { 0,0 };

	for (int i = 0; i < m_pGround.size(); ++i)
	{
		m_pGround[i]->Init();
	}

	// coins Init
	{
		coins[0]->pos = { 1010,580 };
		coins[1]->pos = { 1060,580 };
		coins[2]->pos = { 768, 431 };
		coins[3]->pos = { 831, 491 };
		coins[4]->pos = { 904, 557 };
		coins[5]->pos = { 1010,630 };
		coins[6]->pos = { 1060,630 };

		coins[7]->pos = {1042 + 495,444 };
		coins[8]->pos = {1042 + 595,430 };
		coins[9]->pos = {1042 + 695,444 };
		coins[10]->pos = {1042 + 795,430 };
		for (auto& c : coins)
		{
			c->Init();
		}
	}

	
	movGround->m_vBasePosition = { WINSIZEX + 476,444 };
	movGround->Init();
	
	m_pPlayer->Init();

	// monsters Init
	{
		monsters[0]->m_vPosition = { 670,404 };
		monsters[1]->m_vPosition = { 500,240 };
		monsters[2]->m_vPosition = { 1042 + 559,332 };
		monsters[3]->m_vPosition = { 1042 + 844,332 };
		monsters[4]->m_vPosition = { 1042 + 1135,332 };

		for (auto& m : monsters)
		{
			m->Init();
		}
	}
}

void MainGame::Update()
{
	float bgSize[2] = { backgrounds[0]->m_Sprite->GetSize().x, backgrounds[0]->m_Sprite->GetSize().y };
	int mouseXY[2] = { g_ptMouse.x, g_ptMouse.y };
	ImGui::InputFloat2("bgSize", bgSize);
	ImGui::InputInt2("MouseXY", mouseXY);
	ImGui::InputFloat("CameraX", &g_cameraPos.x);
	ImGui::Checkbox("BorderLine", &g_isDrawBorder);
	ImGui::InputInt("HP", &m_hp);

	if (g_pKeyManager->isOnceKeyDown(VK_F9)) // 게임 초기화
	{
		this->Release();
		this->Init();
	}

	for (auto& g : m_pGround)
	{
		g->Update();
	}

	m_pPlayer->Update(m_pGround);

	//movGround->Update(m_pPlayer);

	for (auto& bg : backgrounds)
	{
		bg->Update();
	}

	for (int i = 0; i < coins.size(); ++i)
	{
		auto coin = coins[i];
		coin->Update();
		// 코인 먹었나 확인
		if (coin->enabled && AABB2D(coin->collider->myRect, m_pPlayer->m_collider->myRect))
		{
			m_point += coin->m_scoreVal;
			coin->enabled = false;	// 먹힌 코인은 비활성화. update와 render에서 제외된다.
		}
	}

	// 몬스터 충돌 처리
	{
		for (auto& m : monsters)
		{
			if (AABB2D(m->m_collider->myRect, m_pPlayer->m_collider->myRect))
			{
				if (!m_pPlayer->whileHit)
				{
					m_hp--;
					if (m_hp <= 0)
					{
						m_hp = 0;
						g_pTimeManager->SetTimeScale(0.0f); // freeze game
						gameOver = true;
					}
					m_pPlayer->Hit();
				}
				break;
			}
		}
	}

	for (auto& m : monsters)
	{
		m->Update();
	}
}

void MainGame::Render()
{
	D3DXCOLOR background = D3DXCOLOR(0, 0, 0, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)background);
	DeviceContext->VSSetConstantBuffers(0, 1, &m_pViewProjBuffer);

	DeviceContext->OMSetBlendState(m_pAlphaBlendState, NULL, 0xFF);	// 반투명 사용 설정

	// Render
	
	for (auto& bg : backgrounds)
	{
		bg->Render();
	}

	for (auto& g : m_pGround)
	{
		g->Render();
	}

	//movGround->Render();

	for (auto& m : monsters)
	{
		m->Render();
	}

	m_pPlayer->Render();

	for (auto& c : coins)
	{
		c->Render();
	}

	// UI 렌더
	{
		string score = to_string(m_point);
		for (int i = 0; i < score.length(); ++i)
		{
			auto num = m_NumberUI[score[i] - '0'];
			num->SetPosition(num->GetWidth()*0.5f*0.5f + i*num->GetWidth()*0.5f, WINSIZEY - num->GetHeight()*0.5f*0.5f);
			num->Update();
			num->Render();
		}
		for (int i = 0; i < m_hp; ++i)
		{
			heartUI->SetPosition(24 + i * heartUI->GetWidth()*0.1f, 626);
			heartUI->Update();
			heartUI->Render();
		}

		if (gameOver)
		{
			gameOverUI->Render();
		}

		if (!gameStarted)
		{
			titleUI->Render();
		}
	}

	DeviceContext->OMSetBlendState(m_pNormalBlendState, NULL, 0xFF); // 반투명 미사용(기본값) 설정

	ImGui::Render();

	SwapChain->Present(0, 0);
}

void MainGame::Release()
{
}