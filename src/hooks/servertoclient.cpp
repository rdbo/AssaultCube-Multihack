#include <pch.h>
#include <base.h>

void Base::Hooks::servertoclient(int chan, uchar* buf, int len, bool demo)
{
	return Data::o_servertoclient(chan, buf, len, demo);
}