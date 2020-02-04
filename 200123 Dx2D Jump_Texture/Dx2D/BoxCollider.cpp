#include "stdafx.h"
#include "BoxCollider.h"

BoxCollider::BoxCollider()
{
	myRect = new Rect;
}


BoxCollider::~BoxCollider()
{
}

void BoxCollider::Init()
{
	myRect->Init();
}

void BoxCollider::Update()
{
	myRect->Update();
}

void BoxCollider::Render()
{
	myRect->Render();
	if (g_isDrawBorder)
	{
		myRect->DrawBorder();
	}
}

void BoxCollider::Release()
{
}
