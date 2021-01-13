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
typedef void(* drawcrosshair_t)(playerent* p, int n, struct color* c, float size);
typedef void(* midfunction_t)(void);
typedef midfunction_t attackphysics_t;

bool WorldToScreen(vec pos3D, vec* pos2D);

class AC_Client
{
public:
	bool Updated = false;
	mem::module_t* mod = nullptr;
	playerent* player1 = nullptr;
	vector<playerent*>* players = nullptr;
	glmatrixf* mvpmatrix = nullptr;
	getclient_t getclient = nullptr;
	servertoclient_t servertoclient = nullptr;
	updateworld_t updateworld = nullptr;
	c2sinfo_t c2sinfo = nullptr;
	movelocalplayer_t movelocalplayer = nullptr;
	drawcrosshair_t drawcrosshair = nullptr;
	attackphysics_t attackphysics = nullptr;
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
		this->mvpmatrix = (glmatrixf*)              GAME_OFFSET(0x101AE8);
		this->getclient = (getclient_t)             GAME_OFFSET(0x27320);
		this->servertoclient = (servertoclient_t)   GAME_OFFSET(0x2E830);
		this->updateworld = (updateworld_t)         GAME_OFFSET(0x25EB0);
		this->c2sinfo     = (c2sinfo_t)             GAME_OFFSET(0x20720);
		this->movelocalplayer = (movelocalplayer_t) GAME_OFFSET(0x25770);
		this->drawcrosshair = (drawcrosshair_t)     GAME_OFFSET(0x8660);
		this->attackphysics = (attackphysics_t)     GAME_OFFSET(0x63786);
		this->Updated = true;
	}
};

class playerinfo_t
{
public:
	bool is_valid = false;
	playerent* ent = nullptr;
	vec pos2D = {};
	vec headpos3D = {};
	vec headpos2D = {};

	playerinfo_t()
	{

	}

	playerinfo_t(playerent* p_ent)
	{
		bool check = true;
		this->ent = p_ent;
		check &= this->ent != nullptr;

		if (check)
		{
			check &= this->ent->state == CS_ALIVE;
			this->headpos3D = this->ent->head;
			if (this->headpos3D.x == -1.0f || this->headpos3D.y == -1.0f || this->headpos2D.z == -1)
				this->headpos3D = this->ent->o;
			check &= WorldToScreen(this->ent->newpos, &this->pos2D);
			check &= WorldToScreen(this->headpos3D, &this->headpos2D);
		}

		this->is_valid = check;
		
	}
};

#endif