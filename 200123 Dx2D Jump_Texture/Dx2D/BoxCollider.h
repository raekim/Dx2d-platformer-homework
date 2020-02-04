#pragma once
class BoxCollider : iGameNode
{
public:
	Rect* myRect;
public:
	BoxCollider();
	~BoxCollider();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

