#include <pch.h>
#include <base.h>

static std::string sOriginal = "";
static bool bChanged = false;
static clock_t last = 0;
static int LastIndex = 0;

static const char* BotNames[] = {
	"Killer",
	"Mike",
	"ACAddict",
	"Supa",
	"Shootme",
	"Coolbot",
	"stefanhendriks",
	"Dude",
	"Dumb",
	"Rabid_Newb",
	"Eek",
	"w00t",
	"Pwned",
	"Indoor_Terrain",
	"Dumbstruck",
	"[prrt]brainfart",
	"Santa_Far",
	"TinCan-Sam",
	"Aristotles",
	"MuHaHaHa",
	"0x0DEFACED",
	"James_Bonk",
	"Rotaredom_Murof",
	"zaiBan",
	"YHWH",
	"gruiiik_gruiiik",
	"Lady_Die",
	"!!!BUY_NOW!!!",
	"where_am_i",
	"PMB",
	"Leagle_Eagle",
	"Maleficus",
	"Grolsch",
	"Gambrinius",
	"Staropramen",
	"Carlsberg",
	"Tuborg",
	"Heineken",
	"Amstel",
	"Kilkenny",
	"Kronebourg",
	"Hell",
	"Koff",
	"Orval",
	"Zlatopramen",
	"Lapin_Kulta",
	"Kaltenberg",
	"Zeunerts",
	"Bluesman",
	"Stefan",
	"Dumber",
	"XP|TheNameless",
	"todesgurke",
	"trm",
	"Sabre",
	"Oldy",
	"kiki",
	"b00nkind",
	"Spider_Scouter",
	"GDawg",
	"Memed",
	"Whistler",
	"SoUlFaThEr",
	"botmeister",
	"davek",
	"Dave",
	"Siro",
	"MikeJ",
	"Dude",
	"Dodging_Bullet",
	"Tomahawk",
	"Target",
	"Mom",
	"Newbie",
	"Killah",
	"Azrael",
	"Blaster",
	"GrandMa",
	"Robot",
	"CPU",
	"Coward",
	"FragMe",
	"ILikeCheese",
	"Freshmeat",
	"Dragon",
	"Dr00l",
	"Dunno",
	"New_B",
	"L33t_kR3W",
	"Bones",
	"MrJoe",
	"Shrike",
	"Captain_Shrimps",
	"Count_Draculol",
	"Harun_Al-RushIt",
	"Honey_Bunny",
	"Joe_Blow",
	"Z00per_N00b",
	"Corporal_Clegg",
	"Rushing_Russian",
	"Johnny_Crash",
	"Private_Parts",
	"Major_Headache",
	"General_Surgery",
	"luggable",
	"fried_circuits",
	"Byte_my_ASCII!",
	"CPLD",
	"FPGA",
	"THE_STORM",
	"Die_Hard",
	"Bad_boy",
	"Beast",
	"Dead_man",
	"chibby",
	"teh_ownerer",
	"teh_masterer",
	"ThE_MarD",
	"teh_smex",
	"t3h_p@!|\|",
	"KillSwitch",
	"InsertNameHere",
	"Sprah",
	"Johnny5"
};

void Base::Hacks::NameChanger()
{
	if (Data::Settings::EnableNameChanger)
	{
		clock_t now = clock();
		playerent* ent = nullptr;
		int bot_list_len = sizeof(BotNames) / sizeof(BotNames[0]);

		if (((Data::Settings::NameChangerAntiSpam && (now - last >= (clock_t)(Data::Settings::NameChangerAntiSpamValue * 1000.0f)))) || !Data::Settings::NameChangerAntiSpam)
		{
			last = now;
			switch (Data::Settings::NameChangerType)
			{
			case 0: //Bot Names
				++LastIndex;
				if (LastIndex >= bot_list_len)
					LastIndex = 0;
				Data::game.newname(BotNames[LastIndex]);
				bChanged = true;
				break;
			case 1: //Connected Player Names
				if (!Data::game.players->inrange(0)) break;
				++LastIndex;
				if (!Data::game.players->inrange(LastIndex))
					LastIndex = 0;
				ent = Data::game.players->operator[](LastIndex);

				if (!ent)
				{
					++LastIndex;
					if (!Data::game.players->inrange(LastIndex))
						LastIndex = 0;
					ent = Data::game.players->operator[](LastIndex);
				}

				if (!ent) break;
				Data::game.newname(ent->name);
				ent = nullptr;
				bChanged = true;
				break;
			default:
				Data::Settings::NameChangerType = 0;
				break;
			}
		}
	}

	else if (bChanged)
	{
		Data::game.newname(sOriginal.c_str());
		bChanged = false;
	}

	else
	{
		sOriginal = Data::game.player1->name;
	}
}