#include <pch.h>
#include <base.h>

void Base::Hacks::Wallhack(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices)
{
	if (Data::Settings::EnableWallhack)
	{
		glDisable(GL_DEPTH_TEST);
		Data::o_glDrawRangeElements(mode, start, end, count, type, indices);
		glEnable(GL_DEPTH_TEST);
	}
}