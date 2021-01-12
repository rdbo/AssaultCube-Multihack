#pragma once
#ifndef GAME_H
#define GAME_H

#include <pch.h>
#define GAME_OFFSET(offset) (&((char*)this->mod->base)[offset])
typedef playerent*(* getclient_t)(int cn);
typedef void(* servertoclient_t)(int chan, uchar* buf, int len, bool demo);
typedef void(* updateworld_t)(int curtime, int lastmillis);
typedef void(* c2sinfo_t)(playerent* d);
typedef void(* movelocalplayer_t)(void);

class AC_Client
{
public:
	bool Updated = false;
	mem::module_t* mod = nullptr;
	playerent* player1 = nullptr;
	vector<playerent*>* players = nullptr;
	getclient_t getclient = nullptr;
	servertoclient_t servertoclient = nullptr;
	updateworld_t updateworld = nullptr;
	c2sinfo_t c2sinfo = nullptr;
	movelocalplayer_t movelocalplayer = nullptr;
public:
	inline AC_Client()
	{

	}

	inline AC_Client(mem::module_t* p_m_ac_client)
	{
		this->mod = p_m_ac_client;
		this->Update();
	}

	inline void Update()
	{
		if (!this->mod || !this->mod->is_valid())
		{
			this->Updated = false;
			return;
		}
		
		this->player1   = *(playerent**)            GAME_OFFSET(0x10F4F4);
		this->players   = (vector<playerent*>*)     GAME_OFFSET(0x10F4F8);
		this->getclient = (getclient_t)             GAME_OFFSET(0x27320);
		this->servertoclient = (servertoclient_t)   GAME_OFFSET(0x2E830);
		this->updateworld = (updateworld_t)         GAME_OFFSET(0x25EB0);
		this->c2sinfo     = (c2sinfo_t)             GAME_OFFSET(0x20720);
		this->movelocalplayer = (movelocalplayer_t) GAME_OFFSET(0x25770);
		this->Updated = true;
	}
};

#endif