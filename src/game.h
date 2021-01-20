#pragma once
#ifndef GAME_H
#define GAME_H

#include <pch.h>
#define GAME_OFFSET(offset) (&((char*)this->mod->base)[offset])
#define m_teammode    (*Base::Data::game.gamemode==0 || *Base::Data::game.gamemode==4 || *Base::Data::game.gamemode==5 || *Base::Data::game.gamemode==7 || *Base::Data::game.gamemode==11 || *Base::Data::game.gamemode==13 || *Base::Data::game.gamemode==14 || *Base::Data::game.gamemode==16 || *Base::Data::game.gamemode==17 || *Base::Data::game.gamemode==20 || *Base::Data::game.gamemode==21)
#define m_botmode     (*Base::Data::game.gamemode==7 || *Base::Data::game.gamemode == 8 || *Base::Data::game.gamemode==12 || (*Base::Data::game.gamemode>=18 && *Base::Data::game.gamemode<=21))
#define m_demo        (*Base::Data::game.gamemode==-1)
#define m_coop        (*Base::Data::game.gamemode==1)

typedef playerent*(* getclient_t)(int cn);
typedef void(* servertoclient_t)(int chan, uchar* buf, int len, bool demo);
typedef void(* updateworld_t)(int curtime, int lastmillis);
typedef void(* c2sinfo_t)(playerent* d);
typedef void(* movelocalplayer_t)(void);
typedef void(* drawcrosshair_t)(playerent* p, int n, struct color* c, float size);
typedef playerent*(* playerincrosshair_t)();
typedef void(* midfunction_t)(void);
typedef midfunction_t attackphysics_t;
typedef void(* drawscope_t)(bool preload);
typedef void(__stdcall* glDrawRangeElements_t)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices);
typedef void(* TraceLine_t)(vec from, vec to, dynent* pTracer, bool CheckPlayers, traceresult_s* tr, bool SkipTags);
typedef bool(* IsVisible_t)(vec v1, vec v2, dynent* tracer, bool SkipTags);
typedef int(* dodamage_t)(int damage, int gun);
typedef midfunction_t dodamage2_t;
typedef void(__stdcall* calclight_t)(void);
typedef void(__stdcall* fullbrightlight_t)(void);

bool WorldToScreen(vec pos3D, vec* pos2D);
bool IsVisible(playerent* p_ent);
float GetDistance(vec src, vec dst);
playerent* GetClosestTarget();
playerent* GetCrosshairClosestTarget();
vec CalcAngles(vec src, vec dst);

class AC_Client
{
public:
	mem::module_t* mod = nullptr;
	playerent* player1 = nullptr;
	vector<playerent*>* players = nullptr;
	glmatrixf* mvpmatrix = nullptr;
	int* gamemode = nullptr;
	bool* fullbright = nullptr;
	getclient_t getclient = nullptr;
	servertoclient_t servertoclient = nullptr;
	updateworld_t updateworld = nullptr;
	c2sinfo_t c2sinfo = nullptr;
	movelocalplayer_t movelocalplayer = nullptr;
	drawcrosshair_t drawcrosshair = nullptr;
	attackphysics_t attackphysics = nullptr;
	playerincrosshair_t playerincrosshair = nullptr;
	drawscope_t drawscope = nullptr;
	glDrawRangeElements_t* p_glDrawRangeElements = nullptr;
	TraceLine_t TraceLine = nullptr;
	IsVisible_t IsVisible = nullptr;
	dodamage_t dodamage = nullptr;
	dodamage2_t dodamage2 = nullptr;
	midfunction_t checkheadshot = nullptr;
	midfunction_t doheadshot = nullptr;
	calclight_t calclight = nullptr;
	fullbrightlight_t fullbrightlight = nullptr;
public:
	inline AC_Client()
	{

	}

	inline AC_Client(mem::module_t* p_m_ac_client)
	{
		this->mod = p_m_ac_client;
		this->Update();
	}

	inline bool Update()
	{
		if (!this->mod || !this->mod->is_valid())
			return false;
		
		this->player1   = *(playerent**)                       GAME_OFFSET(0x10F4F4);
		this->players   = (vector<playerent*>*)                GAME_OFFSET(0x10F4F8);
		this->mvpmatrix = (glmatrixf*)                         GAME_OFFSET(0x101AE8);
		this->gamemode = (int*)                                GAME_OFFSET(0x10F49C);
		this->fullbright = (bool*)                             GAME_OFFSET(0x1100A0);
		this->getclient = (getclient_t)                        GAME_OFFSET(0x27320);
		this->servertoclient = (servertoclient_t)              GAME_OFFSET(0x2E830);
		this->updateworld = (updateworld_t)                    GAME_OFFSET(0x25EB0);
		this->c2sinfo     = (c2sinfo_t)                        GAME_OFFSET(0x20720);
		this->movelocalplayer = (movelocalplayer_t)            GAME_OFFSET(0x25770);
		this->drawcrosshair = (drawcrosshair_t)                GAME_OFFSET(0x8660);
		this->attackphysics = (attackphysics_t)                GAME_OFFSET(0x63786);
		this->playerincrosshair = (playerincrosshair_t)        GAME_OFFSET(0x607C0);
		this->drawscope = (drawscope_t)                        GAME_OFFSET(0x8080);
		this->p_glDrawRangeElements = (glDrawRangeElements_t*) GAME_OFFSET(0x109B44);
		this->TraceLine = (TraceLine_t)                        GAME_OFFSET(0x8A310);
		this->IsVisible = (IsVisible_t)                        GAME_OFFSET(0x8ABD0);
		this->dodamage = (dodamage_t)                          GAME_OFFSET(0x29C20);
		this->dodamage2 = (dodamage2_t)                        GAME_OFFSET(0x29D1F);
		this->checkheadshot = (midfunction_t)                  GAME_OFFSET(0x61751-0x4);
		this->doheadshot = (midfunction_t)                     GAME_OFFSET(0x61769);
		this->calclight = (calclight_t)                        GAME_OFFSET(0x54F70);
		this->fullbrightlight = (fullbrightlight_t)            GAME_OFFSET(0x54EF0);

		return true;
	}
};

class playerinfo_t
{
public:
	bool is_valid = false;
	bool is_visible = false;
	playerent* ent = nullptr;
	vec pos2D = {};
	vec pos3D = {};
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
			if (this->headpos3D.x == -1.0f || this->headpos3D.y == -1.0f || this->headpos2D.z == -1.0f)
				this->headpos3D = this->ent->o;
			this->pos3D = this->ent->o;
			this->pos3D.z -= this->ent->eyeheight;
			this->is_visible = IsVisible(this->ent);
			check &= WorldToScreen(this->pos3D, &this->pos2D);
			check &= WorldToScreen(this->headpos3D, &this->headpos2D);
		}

		this->is_valid = check;
		
	}
};

#endif