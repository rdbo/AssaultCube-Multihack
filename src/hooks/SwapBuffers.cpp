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

	GetClientRect(Data::hWindow, &Data::WindowRect);
	Data::WindowWidth = Data::WindowRect.right - Data::WindowRect.left;
	Data::WindowHeight = Data::WindowRect.bottom - Data::WindowRect.top;

	wglMakeCurrent(hdc, Data::glContext);

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Hacks::Crosshair();

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

		ImGui::Checkbox("Enable Crosshair", &Data::Settings::EnableCrosshair);
		if (Data::Settings::EnableCrosshair)
		{
			const char* CrosshairTypes[] = { "Default", "Triangle", "Square", "Circle" };
			ImGui::ListBox("Crosshair Type", &Data::Settings::CrosshairType, CrosshairTypes, 4);
			ImGui::SliderFloat("Crosshair Length", &Data::Settings::CrosshairLength, 0, 100, "%.0f");
			ImGui::SliderFloat("Crosshair Thickness", &Data::Settings::CrosshairThickness, 0, 100, "%.0f");
			ImGui::SliderFloat("Crosshair Gap", &Data::Settings::CrosshairGap, 0, 100, "%.0f");
			ImGui::Checkbox("Crosshair Top", &Data::Settings::CrosshairTop);
			ImGui::Checkbox("Crosshair Left", &Data::Settings::CrosshairLeft);
			ImGui::Checkbox("Crosshair Bottom", &Data::Settings::CrosshairBottom);
			ImGui::Checkbox("Crosshair Right", &Data::Settings::CrosshairRight);
			ImGui::Checkbox("Crosshair Dot", &Data::Settings::CrosshairDot);
			if (Data::Settings::CrosshairDot)
				ImGui::Checkbox("Crosshair Dot Filled", &Data::Settings::CrosshairDotFilled);
			ImGui::ColorEdit4("Crosshair Color", Data::Settings::CrosshairColor);
		}

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