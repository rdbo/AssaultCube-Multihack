#include <pch.h>
#include <base.h>

void __stdcall Base::Hooks::glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices)
{
	if (Data::Settings::EnableWallhack)
		Hacks::Wallhack(mode, start, end, count, type, indices);
	else
		Data::o_glDrawRangeElements(mode, start, end, count, type, indices);

	return;
}