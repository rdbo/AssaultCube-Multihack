#include <pch.h>
#include <base.h>

static bool bEnabled = false;
static constexpr size_t szOriginalCode[4] = { 3, 6, 3, 6 };
static mem::byte_t OriginalCode[szOriginalCode[0] + szOriginalCode[1] + szOriginalCode[2] + szOriginalCode[3]];
static mem::byte_t Payload[sizeof(OriginalCode)] = { /* 0 */ 0x39, 0xC0, 0x90, /* 1 */ 0x39, 0xC9, 0x90, 0x90, 0x90, 0x90, /* 2 */ 0x39, 0xDB, 0x90, /* 3 */ 0x39, 0xC0, 0x90, 0x90, 0x90, 0x90 };

void Base::Hacks::RadarHack()
{
	if (Data::Settings::EnableRadarHack)
	{
		if (!bEnabled)
		{
			DWORD OldProtect[4] = {};
			VirtualProtect(Data::game.radar_check0, szOriginalCode[0], PAGE_EXECUTE_READWRITE, &OldProtect[0]);
			VirtualProtect(Data::game.radar_check1, szOriginalCode[1], PAGE_EXECUTE_READWRITE, &OldProtect[1]);
			VirtualProtect(Data::game.radar_check2, szOriginalCode[2], PAGE_EXECUTE_READWRITE, &OldProtect[2]);
			VirtualProtect(Data::game.radar_check3, szOriginalCode[3], PAGE_EXECUTE_READWRITE, &OldProtect[3]);

			mem::in::read(Data::game.radar_check0, (mem::voidptr_t)OriginalCode, szOriginalCode[0]);
			mem::in::read(Data::game.radar_check1, (mem::voidptr_t)POINTER_OFFSET(OriginalCode, szOriginalCode[0]), szOriginalCode[1]);
			mem::in::read(Data::game.radar_check2, (mem::voidptr_t)POINTER_OFFSET(OriginalCode, szOriginalCode[1]), szOriginalCode[2]);
			mem::in::read(Data::game.radar_check3, (mem::voidptr_t)POINTER_OFFSET(OriginalCode, szOriginalCode[2]), szOriginalCode[3]);

			mem::in::write(Data::game.radar_check0, (mem::voidptr_t)Payload, szOriginalCode[0]);
			mem::in::write(Data::game.radar_check1, (mem::voidptr_t)POINTER_OFFSET(Payload, szOriginalCode[0]), szOriginalCode[1]);
			mem::in::write(Data::game.radar_check2, (mem::voidptr_t)POINTER_OFFSET(Payload, szOriginalCode[1]), szOriginalCode[2]);
			mem::in::write(Data::game.radar_check3, (mem::voidptr_t)POINTER_OFFSET(Payload, szOriginalCode[2]), szOriginalCode[3]);

			VirtualProtect(Data::game.radar_check0, szOriginalCode[0], OldProtect[0], &OldProtect[0]);
			VirtualProtect(Data::game.radar_check1, szOriginalCode[1], OldProtect[1], &OldProtect[1]);
			VirtualProtect(Data::game.radar_check2, szOriginalCode[2], OldProtect[2], &OldProtect[2]);
			VirtualProtect(Data::game.radar_check3, szOriginalCode[3], OldProtect[3], &OldProtect[3]);

			bEnabled = true;
		}
	}

	else if(bEnabled)
	{
		DWORD OldProtect[4] = {};
		VirtualProtect(Data::game.radar_check0, szOriginalCode[0], PAGE_EXECUTE_READWRITE, &OldProtect[0]);
		VirtualProtect(Data::game.radar_check1, szOriginalCode[1], PAGE_EXECUTE_READWRITE, &OldProtect[1]);
		VirtualProtect(Data::game.radar_check2, szOriginalCode[2], PAGE_EXECUTE_READWRITE, &OldProtect[2]);
		VirtualProtect(Data::game.radar_check3, szOriginalCode[3], PAGE_EXECUTE_READWRITE, &OldProtect[3]);

		mem::in::write(Data::game.radar_check0, (mem::voidptr_t)OriginalCode, szOriginalCode[0]);
		mem::in::write(Data::game.radar_check1, (mem::voidptr_t)POINTER_OFFSET(OriginalCode, szOriginalCode[0]), szOriginalCode[1]);
		mem::in::write(Data::game.radar_check2, (mem::voidptr_t)POINTER_OFFSET(OriginalCode, szOriginalCode[1]), szOriginalCode[2]);
		mem::in::write(Data::game.radar_check3, (mem::voidptr_t)POINTER_OFFSET(OriginalCode, szOriginalCode[2]), szOriginalCode[3]);

		VirtualProtect(Data::game.radar_check0, szOriginalCode[0], OldProtect[0], &OldProtect[0]);
		VirtualProtect(Data::game.radar_check1, szOriginalCode[1], OldProtect[1], &OldProtect[1]);
		VirtualProtect(Data::game.radar_check2, szOriginalCode[2], OldProtect[2], &OldProtect[2]);
		VirtualProtect(Data::game.radar_check3, szOriginalCode[3], OldProtect[3], &OldProtect[3]);

		bEnabled = false;
	}
}