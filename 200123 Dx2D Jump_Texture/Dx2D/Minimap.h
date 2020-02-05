#pragma once
class Minimap : public iGameNode
{
public:
	float m_shrinkFactor;	// �� ��ü�� ���� ������ �ٿ��� �̴ϸ����� ��Ÿ�� ������?
	D3DXVECTOR2	m_pos;
	Rect* m_background;	// �̴ϸ� ���
	Circle* m_player;	// �̴ϸ� ĳ����
public:
	Minimap();
	~Minimap();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Update(D3DXVECTOR2 playerPos);
	virtual void Render() override;
	virtual void Release() override;
};

