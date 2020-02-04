#pragma once
#include "Ground.h"
class Character;
class MovingGround : public Ground
{
public:
	float moveSpeed;
	float moveRange = 0;	// �̵��Ÿ�
	float moveDelta = 0;
	int moveSign = -1;
public:
	MovingGround();
	~MovingGround();

	virtual void Update(Character* p_character);
};

