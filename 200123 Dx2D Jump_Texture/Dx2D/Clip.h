#pragma once

enum class PlayMode
{
	Once,
	Loop,
	ReverseOnce,
	ReverseLoop
};

struct Frame
{
	Sprite*		pSprite;
	float		fPlayTime;

	Frame(Sprite* p, float t) : pSprite(p), fPlayTime(t) { }
};

class Clip
{
private:
	vector<Frame*>	m_vecFrame;
	PlayMode		m_ePlayMode;
	bool			m_isPlaying;
	int				m_nCurrFrame;
	int				m_nStartFrame;
	float			m_fElapsedTime;
	float			m_fSpeed;
	D3DXVECTOR2		m_vPosition;

public:
	Clip(PlayMode mode = PlayMode::Loop, float speed = 1.0f);
	~Clip();

	void AddFrame(Sprite* p, float t);
	void SetStartFrame(int n) { m_nStartFrame = n; }

	void SetSpeed(float s) { m_fSpeed = s; }

	void SetPosition(float x, float y);
	void SetPosition(D3DXVECTOR2 v);

	void SetScale(float x, float y);
	void SetScale(D3DXVECTOR2 s);

	void FlipVertical();

	void SetConstantScale(float x, float y);
	void SetConstantScale(D3DXVECTOR2 s);

	void ApplyTransform();

	void Play();
	void Play(UINT startFrame);
	void PlayReverse();
	void Stop();
	void Pause();
	void Resume();

	void Update();
	void Render();
};

