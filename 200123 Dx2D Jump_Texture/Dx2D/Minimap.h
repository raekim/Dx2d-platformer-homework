#pragma once
class Ground;
class Minimap : public iGameNode
{
public:
	float m_shrinkFactor;	// �� ��ü�� ���� ������ �ٿ��� �̴ϸ����� ��Ÿ�� ������?
	D3DXVECTOR2	m_pos;
	D3DXVECTOR2 m_leftBottomPos;	// �̴ϸ��� ���� �ϴ� ��ǥ
	Rect* m_background;	// �̴ϸ� ���
	Circle* m_player;	// �̴ϸ� ĳ����
	vector<Rect*> m_platforms;
	D3DXVECTOR2 mouseOffset;
	bool clicked;
public:
	Minimap();
	~Minimap();

	virtual void Init(int groundNum);
	virtual void Init() override;
	virtual void Update() override;
	virtual void Update(D3DXVECTOR2 playerPos, vector<Ground*>& grounds);
	virtual void Render() override;
	virtual void Release() override;
};

