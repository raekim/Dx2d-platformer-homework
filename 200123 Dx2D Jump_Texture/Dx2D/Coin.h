#pragma once
enum class COIN_KIND
{
	BRONZE, SILVER, GOLD
};
class BoxCollider;
class Coin : public iGameNode
{
public:
	bool enabled;	// 코인 활성화(게임 리셋용)
	int m_scoreVal;	// 이 코인을 먹으면 증가하는 점수양
	COIN_KIND m_coinKind;
	BoxCollider* collider;
	D3DXVECTOR2	pos;
	Animation* m_animation;
	AniState m_aniState;
	
	Coin(COIN_KIND kind);
	~Coin();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

