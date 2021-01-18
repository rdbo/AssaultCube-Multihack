#include <pch.h>
#include <base.h>
#include "game.h"

bool WorldToScreen(vec pos3D, vec* pos2D)
{
	float mX = (float)Base::Data::WindowWidth / 2.0f;
	float mY = (float)Base::Data::WindowHeight / 2.0f;

	float x = Base::Data::game.mvpmatrix->transformx(pos3D);
	float y = Base::Data::game.mvpmatrix->transformy(pos3D);
	float z = Base::Data::game.mvpmatrix->transformz(pos3D);
	float w = Base::Data::game.mvpmatrix->transformw(pos3D);

	if (w < 0.01F)
		return false;

	pos2D->x = mX + (mX * x / w);
	pos2D->y = mY - (mY * y / w);
	pos2D->z = 0;

	return true;
}

bool IsVisible(playerent* p_ent)
{
	traceresult_s tr = {};
	tr.collided = false;
	playerent* LocalPlayer = Base::Data::game.player1;
	mem::voidptr_t fnTraceLine = (mem::voidptr_t)Base::Data::game.TraceLine;
	vec from = Base::Data::game.player1->o;
	vec to = p_ent->o;

	__asm
	{
		push 0
		push 0
		push LocalPlayer
		push to.z
		push to.y
		push to.x
		push from.z
		push from.y
		push from.x
		lea eax, [tr]
		call fnTraceLine;
		add esp, 36
	}

	return !tr.collided;
}

float GetDistance(vec src, vec dst)
{
	return sqrtf(
		powf(dst.x - src.x, 2.0f) +
		powf(dst.y - src.y, 2.0f) +
		powf(dst.z - src.z, 2.0f)
	);
}

float GetDistance2D(vec src, vec dst)
{
	return sqrtf(
		powf(dst.x - src.x, 2.0f) +
		powf(dst.y - src.y, 2.0f)
	);
}

playerent* GetClosestTarget()
{
	playerent* current = nullptr;
	float last_dist = -1.0f;

	for (int i = 0; Base::Data::game.players->inrange(i); i++)
	{
		playerent* p_ent = Base::Data::game.players->operator[](i);
		if (!(p_ent && p_ent->state == CS_ALIVE && (p_ent->team != Base::Data::game.player1->team || (!m_teammode && !m_coop)))) continue;

		if (!current)
		{
			current = p_ent;
			last_dist = GetDistance(p_ent->o, Base::Data::game.player1->o);
			continue;
		}

		float dist = GetDistance(p_ent->o, Base::Data::game.player1->o);
		if (dist < last_dist)
		{
			current = p_ent;
			last_dist = dist;
		}
	}

	return current;
}

playerent* GetCrosshairClosestTarget()
{
	playerent* current = nullptr;
	float last_dist = -1.0f;
	vec CrosshairPos = { (float)Base::Data::WindowWidth / 2.0f, (float)Base::Data::WindowHeight / 2.0f, 0.0f };

	for (int i = 0; Base::Data::game.players->inrange(i); i++)
	{
		playerent* p_ent = Base::Data::game.players->operator[](i);
		if (!(p_ent && p_ent->state == CS_ALIVE && (p_ent->team != Base::Data::game.player1->team || (!m_teammode && !m_coop)))) continue;

		vec pos2D = {};
		if (!WorldToScreen(p_ent->o, &pos2D)) continue;

		if (!current)
		{
			current = p_ent;
			last_dist = GetDistance2D(pos2D, CrosshairPos);
			continue;
		}

		float dist = GetDistance2D(pos2D, CrosshairPos);
		if (dist < last_dist)
		{
			current = p_ent;
			last_dist = dist;
		}
	}

	return current;
}

vec CalcAngles(vec src, vec dst)
{
	vec angles = {};
	angles.x = -atan2f(dst.x - src.x, dst.y - src.y) / PI * 180.0f + 180.0f;
	angles.y = asinf((dst.z - src.z) / GetDistance(src, dst)) * 180.0f / PI;
	angles.z = 0.0f;

	return angles;
}