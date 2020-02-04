#pragma once
/* Utility */

inline bool AABB2D(D3DXVECTOR2 p1, D3DXVECTOR2 s1, D3DXVECTOR2 p2, D3DXVECTOR2 s2)
{
	float L1 = p1.x - s1.x * 0.5f;
	float R1 = L1 + s1.x; // R1 = p1.x + s1.x * 0.5f;
	float T1 = p1.y + s1.y * 0.5f;
	float B1 = T1 - s1.y;

	float L2 = p2.x - s2.x * 0.5f;
	float R2 = L2 + s2.x;
	float T2 = p2.y + s2.y * 0.5f;
	float B2 = T2 - s2.y;

	if (R1 < L2 || L1 > R2)
		return false;

	if (B1 > T2 || T1 < B2)
		return false;

	return true;
}

inline bool AABB2D(Rect* r1, Rect* r2)
{
	return AABB2D(r1->GetPosition(), r1->GetSize(), r2->GetPosition(), r2->GetSize());
}

inline bool CircleCollision(D3DXVECTOR2 p1, float r1, D3DXVECTOR2 p2, float r2)
{
	/*
	원 충돌 : 두 점 사이의 거리가 두 원의 반지름을 더한 값보다 작다면 두 원은 충돌 상태
	*/

	float distX = p1.x - p2.x;
	float distY = p1.y - p2.y;

	float distance = sqrtf(distX * distX + distY * distY);

	if (r1 + r2 < distance)
		return false;

	return true;
}

inline float GetAngle(D3DXVECTOR2 p1, D3DXVECTOR2 p2) // p1 -> p2
{
	/*
	p1 에서 p2 방향의 각도 값 = theta
	cos(theta) = (x2 - x1) / 대각선 길이
	theta = cos^-1( (x2 - x1) / 대각선 길이 )
	theta = acos( (x2 - x1) / 대각선 길이 )
	*/

	float distX = p2.x - p1.x;
	float distY = p2.y - p1.y;

	float distance = sqrtf(distX * distX + distY * distY);

	float result = acosf(distX / distance);

	if (p2.y < p1.y)
		result = D3DX_PI * 2 - result;

	// 서클 클래스가 사용하는 앵글값은 Degree 값이고
	// cos, sin 함수들이 사용하는 값은 Radian 값이다.
	return D3DXToDegree(result);
}

inline bool PointInRect(D3DXVECTOR2 p1, D3DXVECTOR2 s1, D3DXVECTOR2 point)
{
	float L1 = p1.x - s1.x * 0.5f;
	float R1 = L1 + s1.x; // R1 = p1.x + s1.x * 0.5f;
	float T1 = p1.y + s1.y * 0.5f;
	float B1 = T1 - s1.y;

	if (point.x < L1 || point.x > R1 ||
		point.y < B1 || point.y > T1)
		return false;

	return true;
}

inline bool PointInCircle(D3DXVECTOR2 p1, float r1, D3DXVECTOR2 point)
{
	float distX = p1.x - point.x;
	float distY = p1.y - point.y;

	float dist = sqrtf(distX * distX + distY * distY);

	if (dist > r1)
		return false;

	return true;
}