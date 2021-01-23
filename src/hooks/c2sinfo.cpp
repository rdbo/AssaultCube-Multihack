#include <pch.h>
#include <base.h>

void Base::Hooks::c2sinfo(playerent* d)
{
	Hacks::Teleport();
	Hacks::Speedhack();
	Hacks::Triggerbot();
	Hacks::FlyHack();
	Hacks::Bunnyhop();
	Hacks::Aimbot();
	Hacks::InfiniteAmmo();
	Hacks::NoGunWait();
	Hacks::InfiniteArmor();
	Hacks::InfiniteHealth();
	Hacks::AutoGuns();
	Hacks::FullBright();
	Hacks::NameChanger();
	Hacks::RadarHack();
	Hacks::PingChanger();
	Hacks::ChatSpam();

	for (int i = 0; Data::game.players && Data::game.players->inrange(i); i++)
	{
		playerent* ent = Data::game.players->operator[](i);
		if (!ent || ent->state != CS_ALIVE) continue;

		Hacks::TeleportPlayers(ent);
	}

	for (int i = 0; Data::game.ents->inrange(i); i++)
	{
		entity& ent = Data::game.ents->operator[](i);
		Hacks::TeleportItems(ent);
	}

	return Data::o_c2sinfo(d);
}