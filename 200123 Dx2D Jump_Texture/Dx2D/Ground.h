#pragma once
class BoxCollider;
class Ground : public iGameNode
{
public:
	BoxCollider* collider;
	vector<Sprite*> m_vSprites;
	D3DXVECTOR2	m_vBasePosition;
	D3DXVECTOR2	m_vCenterPosition;
public:
	Ground();
	~Ground();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

