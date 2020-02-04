#pragma once

class Animation;
class BoxCollider;
class Ground;
class Character : public iGameNode
{
public:
	float hitTime;
	BoxCollider* m_collider;
	bool grounded;	// 플레이어가 땅에 닿았는가?
	bool firstInit = true;
	Animation* m_animation;
	D3DXVECTOR2	m_vPosition;
	bool m_isJumping;
	float m_fMaxJumpPower;
	float m_fJumpPower;
	float m_fElapsedGravity;
	AniState m_aniState;
	bool facingRight;
	bool whileHit;
public:
	Character();
	~Character();

	virtual void Init() override;
	virtual void Update() override;
	void Update(vector<Ground*>& grounds);
	void Hit();
	virtual void Render() override;
	virtual void Release() override;
};

