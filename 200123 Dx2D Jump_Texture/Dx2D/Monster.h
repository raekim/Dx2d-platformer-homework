#pragma once
class BoxCollider;
class Ground;
class Monster : public iGameNode
{
public:
	float speed = 80;
	float moveX = 1;
	Ground* belowGround;	 // 몬스터가 서있는 땅
	bool firstInit;
	bool enabled;
	BoxCollider* m_collider;
	Animation* m_animation;
	AniState m_aniState;
	bool facingRight;
	D3DXVECTOR2	m_vPosition;
public:
	Monster(Ground* belowGround);
	~Monster();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

