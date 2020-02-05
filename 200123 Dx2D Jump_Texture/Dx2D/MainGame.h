#pragma once
#include "background.h"
#include "Coin.h"
#include "Monster.h"
#include "Minimap.h"

class MovingGround;
class Character;
class Ground;
class MainGame : public iGameNode
{
private:
	ID3D11Buffer* m_pViewProjBuffer;	// 뷰, 프로젝션 매트릭스 버퍼
	void SetViewProjectionMatrixes();	// 뷰, 프로젝션 매트릭스 셋팅 및 버퍼 생성

	ID3D11BlendState*	m_pNormalBlendState;	// 기본 블렌드 옵션
	ID3D11BlendState*	m_pAlphaBlendState;		// 반투명 블렌드 옵션
	void SetBlendStates();	// 옵션별 블렌드 상태값 생성

private:
	Animation*			m_pCharacter;
	D3DXVECTOR2			m_vPosition;
	bool				m_isJumping;
	float				m_fJumpPower;
	float				m_fElapsedGravity;

private:
	MovingGround* movGround;
	bool gameStarted;	// 맨 처음 게임 시작(타이틀화면)
	float initTimeScale;
	// 게임 오브젝트들
	Minimap* m_pMiniMap;
	Character* m_pPlayer;	// 플레이어 캐릭터
	vector<Ground*> m_pGround;	// 배경의 platform 땅
	vector<background*> backgrounds;
	vector<Coin*> coins;
	int m_point;
	int m_hp;
	Sprite* heartUI;
	Sprite* gameOverUI;
	Sprite* titleUI;
	vector<Sprite*> m_NumberUI;	// 점수 숫자 이미지
	vector<Monster*> monsters;
	bool gameOver;
public:
	MainGame();
	~MainGame();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

