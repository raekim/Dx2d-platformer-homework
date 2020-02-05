#pragma once
class background : public iGameNode
{
public:
	float offset;
	D3DXVECTOR2 pos;
	float camRatio;
	Sprite* m_Sprite;
public:
	background();
	~background();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

