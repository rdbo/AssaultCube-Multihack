#include <pch.h>
#include <base.h>

#define _STRINGIFY(str) #str
#define STRINGIFY(str) _STRINGIFY(str)
#define WRITE_CONFIG_SETTINGS(val) WRITE_CONFIG(j, "Settings", STRINGIFY(val), Base::Data::Settings::val)
#define WRITE_CONFIG_KEYS(val) WRITE_CONFIG(j, "Keys", STRINGIFY(val), Base::Data::Keys::val)
#define READ_CONFIG_SETTINGS(val) Base::Data::Settings::val = READ_CONFIG(j, "Settings", STRINGIFY(val))
#define READ_CONFIG_SETTINGS_BUF(val) for(int i = 0; i < sizeof(Base::Data::Settings::val)/sizeof(Base::Data::Settings::val[0]); i++) Base::Data::Settings::val[i] = READ_CONFIG(j, "Settings", STRINGIFY(val))[i];
#define READ_CONFIG_KEYS(val) Base::Data::Keys::val = READ_CONFIG(j, "Keys", STRINGIFY(val))
#define CHECK_CFG_FILE(var) (var.length() > 0 && var.find('.') == var.npos && var.find('\\') == var.npos && var.find('/') == var.npos)

bool Base::LoadConfig(std::string ConfigName)
{
	try
	{
		std::string ConfigAbsPath = Data::ConfigPath + "\\" + ConfigName + ".acmh";

		ACMH_DEBUG_LOG("[*] Loading Config File: '%s'\n", ConfigAbsPath.c_str());

		if (!CHECK_CFG_FILE(ConfigName))
		{
			ACMH_DEBUG_LOG("[*] Bad Config Name: '%s'\n", ConfigName.c_str());
			return false;
		}

		std::ifstream cfg_file(ConfigAbsPath);
		if (!cfg_file.is_open())
		{
			ACMH_DEBUG_LOG("[!] Unable to Load Config File\n");
			return false;
		}
		std::stringstream ss;
		ss << cfg_file.rdbuf();
		cfg_file.close();
		
		nlohmann::json j = nlohmann::json::parse(ss.str());
		Base::LoadConfig(j);
	}

	catch (...)
	{
		ACMH_DEBUG_LOG("[!] Exception caught on Load Config File!\n");
		return false;
	}

	return true;
}

bool Base::SaveConfig(std::string ConfigName)
{
	try
	{
		std::string ConfigAbsPath = Data::ConfigPath + "\\" + ConfigName + ".acmh";
		ACMH_DEBUG_LOG("[*] Saving Config File: '%s'\n", ConfigAbsPath.c_str());

		if (!CHECK_CFG_FILE(ConfigName))
		{
			ACMH_DEBUG_LOG("[*] Bad Config Name: '%s'\n", ConfigName.c_str());
			return false;
		}

		nlohmann::json j;
		Base::SaveConfig(j);

		std::ofstream cfg_file(ConfigAbsPath);
		if (!cfg_file.is_open())
		{
			ACMH_DEBUG_LOG("[!] Unable to Save Config File\n");
			return false;
		}
		std::stringstream ss;
		ss << j.dump();
		cfg_file.write(ss.str().c_str(), ss.str().length());
		cfg_file.close();
	}

	catch (...)
	{
		ACMH_DEBUG_LOG("[!] Exception caught on Save Config File!\n");
		return false;
	}

	return true;
}

void Base::LoadConfig(nlohmann::json& Config)
{
	nlohmann::json j = Config;

	//Load Settings
	READ_CONFIG_SETTINGS(EnableCrosshair);
	READ_CONFIG_SETTINGS(CrosshairType);
	READ_CONFIG_SETTINGS(CrosshairLength);
	READ_CONFIG_SETTINGS(CrosshairThickness);
	READ_CONFIG_SETTINGS(CrosshairGap);
	READ_CONFIG_SETTINGS(CrosshairTop);
	READ_CONFIG_SETTINGS(CrosshairLeft);
	READ_CONFIG_SETTINGS(CrosshairBottom);
	READ_CONFIG_SETTINGS(CrosshairRight);
	READ_CONFIG_SETTINGS(CrosshairDot);
	READ_CONFIG_SETTINGS(CrosshairDotFilled);
	READ_CONFIG_SETTINGS_BUF(CrosshairColor);

	READ_CONFIG_SETTINGS(EnableEspTeam);
	READ_CONFIG_SETTINGS(EnableEspEnemy);

	READ_CONFIG_SETTINGS(EnableEspSnaplines);
	READ_CONFIG_SETTINGS(EspSnaplinesVisibilityCheck);
	READ_CONFIG_SETTINGS(EspSnaplinesThickness);
	READ_CONFIG_SETTINGS_BUF(EspSnaplinesColorTeam);
	READ_CONFIG_SETTINGS_BUF(EspSnaplinesColorEnemy);
	READ_CONFIG_SETTINGS_BUF(EspSnaplinesColorTeamVisible);
	READ_CONFIG_SETTINGS_BUF(EspSnaplinesColorEnemyVisible);
	READ_CONFIG_SETTINGS(EspSnaplinesPos);

	READ_CONFIG_SETTINGS(EnableEspBox);
	READ_CONFIG_SETTINGS(EspBoxVisibilyCheck);
	READ_CONFIG_SETTINGS(EspBoxThickness);
	READ_CONFIG_SETTINGS_BUF(EspBoxColorTeam);
	READ_CONFIG_SETTINGS_BUF(EspBoxColorFillTeam);
	READ_CONFIG_SETTINGS_BUF(EspBoxColorEnemy);
	READ_CONFIG_SETTINGS_BUF(EspBoxColorFillEnemy);
	READ_CONFIG_SETTINGS_BUF(EspBoxColorTeamVisible);
	READ_CONFIG_SETTINGS_BUF(EspBoxColorFillTeamVisible);
	READ_CONFIG_SETTINGS_BUF(EspBoxColorEnemyVisible);
	READ_CONFIG_SETTINGS_BUF(EspBoxColorFillEnemyVisible);

	READ_CONFIG_SETTINGS(EnableTeleport);
	READ_CONFIG_SETTINGS(TeleportQueued);
	READ_CONFIG_SETTINGS(TeleportSaveQueued);
	READ_CONFIG_SETTINGS_BUF(TeleportPosition);
	READ_CONFIG_SETTINGS_BUF(TeleportForce);

	READ_CONFIG_SETTINGS(EnableNoRecoil);

	READ_CONFIG_SETTINGS(EnableSpeedhack);
	READ_CONFIG_SETTINGS(SpeedhackValue);

	READ_CONFIG_SETTINGS(EnableTriggerbot);
	READ_CONFIG_SETTINGS(TriggerbotToggle);
	READ_CONFIG_SETTINGS(TriggerbotToggleState);

	READ_CONFIG_SETTINGS(EnableFlyHack);

	READ_CONFIG_SETTINGS(EnableNoScope);

	READ_CONFIG_SETTINGS(EnableTeleportPlayers);
	READ_CONFIG_SETTINGS(TeleportPlayersDistance);
	READ_CONFIG_SETTINGS(TeleportPlayersTeam);
	READ_CONFIG_SETTINGS(TeleportPlayersEnemy);

	READ_CONFIG_SETTINGS(EnableEspHealth);
	READ_CONFIG_SETTINGS_BUF(EspHealthColor);
	READ_CONFIG_SETTINGS_BUF(EspHealthDmgColor);

	READ_CONFIG_SETTINGS(EnableEspArmor);
	READ_CONFIG_SETTINGS_BUF(EspArmorColor);
	READ_CONFIG_SETTINGS_BUF(EspArmorDmgColor);

	READ_CONFIG_SETTINGS(EnableEspName);
	READ_CONFIG_SETTINGS_BUF(EspNameColorTeam);
	READ_CONFIG_SETTINGS_BUF(EspNameColorEnemy);

	READ_CONFIG_SETTINGS(EnableBunnyhop);
	READ_CONFIG_SETTINGS(BunnyhopToggle);
	READ_CONFIG_SETTINGS(BunnyhopToggleState);

	READ_CONFIG_SETTINGS(EnableWallhack);

	READ_CONFIG_SETTINGS(EnableAimbot);
	READ_CONFIG_SETTINGS(AimbotToggle);
	READ_CONFIG_SETTINGS(AimbotToggleState);
	READ_CONFIG_SETTINGS(AimbotSmooth);
	READ_CONFIG_SETTINGS(AimbotSmoothValue);
	READ_CONFIG_SETTINGS(AimbotTargetPreference);

	READ_CONFIG_SETTINGS(EnableServerSide);
	READ_CONFIG_SETTINGS(EnableGodmode);
	READ_CONFIG_SETTINGS(EnableInstantKill);
	READ_CONFIG_SETTINGS(EnableInfiniteAmmo);
	READ_CONFIG_SETTINGS(EnableNoGunWait);

	READ_CONFIG_SETTINGS(EnableAlwaysHeadshot);

	READ_CONFIG_SETTINGS(EnableInfiniteArmor);

	READ_CONFIG_SETTINGS(EnableInfiniteHealth);

	READ_CONFIG_SETTINGS(EnableAutoGuns);

	READ_CONFIG_SETTINGS(EnableFullBright);

	READ_CONFIG_SETTINGS(EnableNameChanger);
	READ_CONFIG_SETTINGS(NameChangerType);
	READ_CONFIG_SETTINGS(NameChangerAntiSpam);
	READ_CONFIG_SETTINGS(NameChangerAntiSpamValue);

	//Load Keys
	READ_CONFIG_KEYS(Bhop);
	READ_CONFIG_KEYS(Triggerbot);
	READ_CONFIG_KEYS(TeleportSavePos);
	READ_CONFIG_KEYS(Teleport);
	READ_CONFIG_KEYS(Aimbot);
}

void Base::SaveConfig(nlohmann::json& ConfigOut)
{
	nlohmann::json& j = ConfigOut;

	//Save Settings
	WRITE_CONFIG_SETTINGS(EnableCrosshair);
	WRITE_CONFIG_SETTINGS(CrosshairType);
	WRITE_CONFIG_SETTINGS(CrosshairLength);
	WRITE_CONFIG_SETTINGS(CrosshairThickness);
	WRITE_CONFIG_SETTINGS(CrosshairGap);
	WRITE_CONFIG_SETTINGS(CrosshairTop);
	WRITE_CONFIG_SETTINGS(CrosshairLeft);
	WRITE_CONFIG_SETTINGS(CrosshairBottom);
	WRITE_CONFIG_SETTINGS(CrosshairRight);
	WRITE_CONFIG_SETTINGS(CrosshairDot);
	WRITE_CONFIG_SETTINGS(CrosshairDotFilled);
	WRITE_CONFIG_SETTINGS(CrosshairColor);

	WRITE_CONFIG_SETTINGS(EnableEspTeam);
	WRITE_CONFIG_SETTINGS(EnableEspEnemy);

	WRITE_CONFIG_SETTINGS(EnableEspSnaplines);
	WRITE_CONFIG_SETTINGS(EspSnaplinesVisibilityCheck);
	WRITE_CONFIG_SETTINGS(EspSnaplinesThickness);
	WRITE_CONFIG_SETTINGS(EspSnaplinesColorTeam);
	WRITE_CONFIG_SETTINGS(EspSnaplinesColorEnemy);
	WRITE_CONFIG_SETTINGS(EspSnaplinesColorTeamVisible);
	WRITE_CONFIG_SETTINGS(EspSnaplinesColorEnemyVisible);
	WRITE_CONFIG_SETTINGS(EspSnaplinesPos);

	WRITE_CONFIG_SETTINGS(EnableEspBox);
	WRITE_CONFIG_SETTINGS(EspBoxVisibilyCheck);
	WRITE_CONFIG_SETTINGS(EspBoxThickness);
	WRITE_CONFIG_SETTINGS(EspBoxColorTeam);
	WRITE_CONFIG_SETTINGS(EspBoxColorFillTeam);
	WRITE_CONFIG_SETTINGS(EspBoxColorEnemy);
	WRITE_CONFIG_SETTINGS(EspBoxColorFillEnemy);
	WRITE_CONFIG_SETTINGS(EspBoxColorTeamVisible);
	WRITE_CONFIG_SETTINGS(EspBoxColorFillTeamVisible);
	WRITE_CONFIG_SETTINGS(EspBoxColorEnemyVisible);
	WRITE_CONFIG_SETTINGS(EspBoxColorFillEnemyVisible);

	WRITE_CONFIG_SETTINGS(EnableTeleport);
	WRITE_CONFIG_SETTINGS(TeleportQueued);
	WRITE_CONFIG_SETTINGS(TeleportSaveQueued);
	WRITE_CONFIG_SETTINGS(TeleportPosition);
	WRITE_CONFIG_SETTINGS(TeleportForce);

	WRITE_CONFIG_SETTINGS(EnableNoRecoil);

	WRITE_CONFIG_SETTINGS(EnableSpeedhack);
	WRITE_CONFIG_SETTINGS(SpeedhackValue);

	WRITE_CONFIG_SETTINGS(EnableTriggerbot);
	WRITE_CONFIG_SETTINGS(TriggerbotToggle);
	WRITE_CONFIG_SETTINGS(TriggerbotToggleState);

	WRITE_CONFIG_SETTINGS(EnableFlyHack);

	WRITE_CONFIG_SETTINGS(EnableNoScope);

	WRITE_CONFIG_SETTINGS(EnableTeleportPlayers);
	WRITE_CONFIG_SETTINGS(TeleportPlayersDistance);
	WRITE_CONFIG_SETTINGS(TeleportPlayersTeam);
	WRITE_CONFIG_SETTINGS(TeleportPlayersEnemy);

	WRITE_CONFIG_SETTINGS(EnableEspHealth);
	WRITE_CONFIG_SETTINGS(EspHealthColor);
	WRITE_CONFIG_SETTINGS(EspHealthDmgColor);

	WRITE_CONFIG_SETTINGS(EnableEspArmor);
	WRITE_CONFIG_SETTINGS(EspArmorColor);
	WRITE_CONFIG_SETTINGS(EspArmorDmgColor);

	WRITE_CONFIG_SETTINGS(EnableEspName);
	WRITE_CONFIG_SETTINGS(EspNameColorTeam);
	WRITE_CONFIG_SETTINGS(EspNameColorEnemy);

	WRITE_CONFIG_SETTINGS(EnableBunnyhop);
	WRITE_CONFIG_SETTINGS(BunnyhopToggle);
	WRITE_CONFIG_SETTINGS(BunnyhopToggleState);

	WRITE_CONFIG_SETTINGS(EnableWallhack);

	WRITE_CONFIG_SETTINGS(EnableAimbot);
	WRITE_CONFIG_SETTINGS(AimbotToggle);
	WRITE_CONFIG_SETTINGS(AimbotToggleState);
	WRITE_CONFIG_SETTINGS(AimbotSmooth);
	WRITE_CONFIG_SETTINGS(AimbotSmoothValue);
	WRITE_CONFIG_SETTINGS(AimbotTargetPreference);

	WRITE_CONFIG_SETTINGS(EnableServerSide);
	WRITE_CONFIG_SETTINGS(EnableGodmode);
	WRITE_CONFIG_SETTINGS(EnableInstantKill);
	WRITE_CONFIG_SETTINGS(EnableInfiniteAmmo);
	WRITE_CONFIG_SETTINGS(EnableNoGunWait);

	WRITE_CONFIG_SETTINGS(EnableAlwaysHeadshot);

	WRITE_CONFIG_SETTINGS(EnableInfiniteArmor);

	WRITE_CONFIG_SETTINGS(EnableInfiniteHealth);

	WRITE_CONFIG_SETTINGS(EnableAutoGuns);

	WRITE_CONFIG_SETTINGS(EnableFullBright);

	WRITE_CONFIG_SETTINGS(EnableNameChanger);
	WRITE_CONFIG_SETTINGS(NameChangerType);
	WRITE_CONFIG_SETTINGS(NameChangerAntiSpam);
	WRITE_CONFIG_SETTINGS(NameChangerAntiSpamValue);

	//Save Keys
	WRITE_CONFIG_KEYS(Bhop);
	WRITE_CONFIG_KEYS(Triggerbot);
	WRITE_CONFIG_KEYS(TeleportSavePos);
	WRITE_CONFIG_KEYS(Teleport);
	WRITE_CONFIG_KEYS(Aimbot);
}