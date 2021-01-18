#include <pch.h>
#include <base.h>

void Base::Hacks::Aimbot()
{
	if (Data::Settings::EnableAimbot && (Data::WMKeys[Data::Keys::Aimbot] && !Data::Settings::AimbotToggle || Data::Settings::AimbotToggle && Data::Settings::AimbotToggleState))
	{
		playerent* p_target = nullptr;
		switch (Data::Settings::AimbotTargetPreference)
		{
		case 0:
			p_target = GetClosestTarget();
			break;
		case 1:
			p_target = GetCrosshairClosestTarget();
			break;
		default:
			Data::Settings::AimbotTargetPreference = 0;
			break;
		}

		if (!p_target) return;

		vec head = p_target->head;

		if (head.x == -1.0f && head.x == -1.0f && head.z == -1.0f)
			head = p_target->o;

		vec Angles = CalcAngles(Data::game.player1->o, head);

		if (Data::Settings::AimbotSmooth)
		{
			vec SmoothAngles = {};
			SmoothAngles.x = Angles.x - Data::game.player1->yaw;
			SmoothAngles.y = Angles.y - Data::game.player1->pitch;
			Data::game.player1->yaw += SmoothAngles.x / Data::Settings::AimbotSmoothValue;
			Data::game.player1->pitch += SmoothAngles.y / Data::Settings::AimbotSmoothValue;
		}

		else
		{
			Data::game.player1->yaw = Angles.x;
			Data::game.player1->pitch = Angles.y;
		}
	}
}