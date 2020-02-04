#pragma once
class BoxCollider;
class Character;
class Ground : public iGameNode
{
public:
	// �����̴� ������ ���� ���
	bool moving;
	float moveSpeed;
	float minX, maxX;	// �̵� ���� �Ÿ�
	float moveDelta;
	int moveSign = -1;	// �����̴� ���⿡ ������ �ش�(���� �Ǵ� ������)

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

