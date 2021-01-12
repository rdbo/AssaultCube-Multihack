#include <pch.h>
#include <base.h>

BOOL __stdcall Base::Hooks::SwapBuffers(_In_ HDC hdc)
{
	Data::oContext = wglGetCurrentContext();

	if(!Data::InitSwapBuffers)
	{
		Data::hWindow  = WindowFromDC(hdc);
		Data::oWndProc = (WndProc_t)SetWindowLongPtr(Data::hWindow, GWL_WNDPROC, (LONG_PTR)Hooks::WndProc);

		Data::glContext = wglCreateContext(hdc);
		wglMakeCurrent(hdc, Data::glContext);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		GLint m_viewport[4];
		glGetIntegerv(GL_VIEWPORT, m_viewport);
		glOrtho(0, m_viewport[2], m_viewport[3], 0, 1, -1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glClearColor(0, 0, 0, 1);

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplWin32_Init(Data::hWindow);
		ImGui_ImplOpenGL2_Init();

		Data::InitSwapBuffers = true;
	}

	wglMakeCurrent(hdc, Data::glContext);

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (Data::ShowMenu)
	{
		ImGui::Begin("ImGui Window");
		ImGui::Text("Test ImGUI Window");

		ImGui::SliderFloat3("Teleport Position", Data::Settings::TeleportPosition, -5000, 5000);
		ImGui::Checkbox("Force Teleport X", &Data::Settings::TeleportForce[0]);
		ImGui::Checkbox("Force Teleport Y", &Data::Settings::TeleportForce[1]);
		ImGui::Checkbox("Force Teleport Z", &Data::Settings::TeleportForce[2]);
		if (ImGui::Button("Save Pos")) Data::Settings::TeleportSaveQueued = true;
		if (ImGui::Button("Teleport")) Data::Settings::TeleportQueued = true;

		if (ImGui::Button("Detach"))
		{
			ImGui::End();
			ImGui::Render();
			ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
			wglMakeCurrent(hdc, Data::oContext);
			wglDeleteContext(Data::glContext);
			Base::Unload();
			return Data::oSwapBuffers(hdc);
		}
		ImGui::End();
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	wglMakeCurrent(hdc, Data::oContext);

	return Data::oSwapBuffers(hdc);
}