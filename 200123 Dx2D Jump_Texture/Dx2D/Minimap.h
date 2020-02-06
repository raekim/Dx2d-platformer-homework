#pragma once
class Ground;
class Minimap : public iGameNode
{
public:
	float m_shrinkFactor;	// 맵 전체를 얼마의 비율로 줄여서 미니맵으로 나타낼 것인지?
	D3DXVECTOR2	m_pos;
	D3DXVECTOR2 m_leftBottomPos;	// 미니맵의 왼쪽 하단 좌표
	Rect* m_background;	// 미니맵 배경
	Circle* m_player;	// 미니맵 캐릭터
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

