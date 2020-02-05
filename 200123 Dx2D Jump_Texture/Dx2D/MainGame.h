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
	ID3D11Buffer* m_pViewProjBuffer;	// ��, �������� ��Ʈ���� ����
	void SetViewProjectionMatrixes();	// ��, �������� ��Ʈ���� ���� �� ���� ����

	ID3D11BlendState*	m_pNormalBlendState;	// �⺻ ���� �ɼ�
	ID3D11BlendState*	m_pAlphaBlendState;		// ������ ���� �ɼ�
	void SetBlendStates();	// �ɼǺ� ���� ���°� ����

private:
	Animation*			m_pCharacter;
	D3DXVECTOR2			m_vPosition;
	bool				m_isJumping;
	float				m_fJumpPower;
	float				m_fElapsedGravity;

private:
	MovingGround* movGround;
	bool gameStarted;	// �� ó�� ���� ����(Ÿ��Ʋȭ��)
	float initTimeScale;
	// ���� ������Ʈ��
	Minimap* m_pMiniMap;
	Character* m_pPlayer;	// �÷��̾� ĳ����
	vector<Ground*> m_pGround;	// ����� platform ��
	vector<background*> backgrounds;
	vector<Coin*> coins;
	int m_point;
	int m_hp;
	Sprite* heartUI;
	Sprite* gameOverUI;
	Sprite* titleUI;
	vector<Sprite*> m_NumberUI;	// ���� ���� �̹���
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

