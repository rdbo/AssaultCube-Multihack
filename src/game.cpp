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