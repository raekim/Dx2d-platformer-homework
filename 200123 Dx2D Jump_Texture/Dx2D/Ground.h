#pragma once
class BoxCollider;
class Character;
class Ground : public iGameNode
{
public:
	// 움직이는 발판을 위한 멤버
	bool moving;
	float moveSpeed;
	float minX, maxX;	// 이동 제한 거리
	float moveDelta;
	int moveSign = -1;	// 움직이는 방향에 영향을 준다(왼쪽 또는 오른쪽)

	BoxCollider* collider;
	vector<Sprite*> m_vSprites;
	D3DXVECTOR2	m_vBasePosition;
	D3DXVECTOR2	m_vCenterPosition;
public:
	Ground();
	~Ground();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Update(Character* p_character);
	virtual void Render() override;
	virtual void Release() override;
};

