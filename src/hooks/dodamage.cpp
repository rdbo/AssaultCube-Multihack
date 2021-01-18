#include <pch.h>
#include <base.h>

static playerent* actor = nullptr;
static playerent* receiver = nullptr;

__declspec(naked) void Base::Hooks::dodamage(void)
{
	__asm
	{
		mov actor, edi
		mov receiver, esi
		jmp Data::o_dodamage
	}
}

__declspec(naked) void Base::Hooks::dodamage2(void)
{
	__asm
	{
		test Data::Settings::EnableServerSide, 0x1
		je original_code
		push eax
		mov eax, receiver
		cmp eax, Data::game.player1
		pop eax
		jne instant_kill
		godmode:
		test Data::Settings::EnableGodmode, 0x1
		je original_code
		call Hacks::Godmode
		jmp original_code

		instant_kill:
		test Data::Settings::EnableInstantKill, 0x1
		je original_code
		push eax
		mov eax, actor
		cmp eax, Data::game.player1
		pop eax
		jne original_code
		call Hacks::InstantKill

		original_code:
		jmp Data::o_dodamage2
	}
}