#include "stdafx.h"
#include "background.h"


background::background()
{
}


background::~background()
{
	
}

void background::Init()
{
}

void background::Update()
{
	m_Sprite->SetPosition({ pos.x - g_cameraPos.x * camRatio + offset, pos.y });
	m_Sprite->Update();
}

void background::Render()
{
	m_Sprite->Render();
}

void background::Release()
{
}
