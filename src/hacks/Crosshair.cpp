#include <pch.h>
#include <base.h>

void Base::Hacks::Crosshair()
{
	if (Data::Settings::EnableCrosshair)
	{
		ImDrawList* Draw = ImGui::GetBackgroundDrawList();
		ImVec2 WindowCenter = ImVec2((float)Data::WindowWidth / 2, (float)Data::WindowHeight / 2);
		ImColor LineColor = ImColor(Data::Settings::CrosshairColor[0], Data::Settings::CrosshairColor[1], Data::Settings::CrosshairColor[2], Data::Settings::CrosshairColor[3]);
		float LineThickness = Data::Settings::CrosshairThickness;

		if (Data::Settings::CrosshairTop)
		{
			ImVec2 LineTop[2] = {
				ImVec2(WindowCenter.x, WindowCenter.y - Data::Settings::CrosshairGap),
				ImVec2(WindowCenter.x, WindowCenter.y - Data::Settings::CrosshairGap - Data::Settings::CrosshairLength)
			};

			Draw->AddLine(LineTop[0], LineTop[1], LineColor, LineThickness);
		}

		if (Data::Settings::CrosshairLeft)
		{
			ImVec2 LineLeft[2] = {
				ImVec2(WindowCenter.x - Data::Settings::CrosshairGap, WindowCenter.y),
				ImVec2(WindowCenter.x - Data::Settings::CrosshairGap - Data::Settings::CrosshairLength, WindowCenter.y)
			};

			Draw->AddLine(LineLeft[0], LineLeft[1], LineColor, LineThickness);
		}

		if (Data::Settings::CrosshairBottom)
		{
			ImVec2 LineBottom[2] = {
				ImVec2(WindowCenter.x, WindowCenter.y + Data::Settings::CrosshairGap),
				ImVec2(WindowCenter.x, WindowCenter.y + Data::Settings::CrosshairGap + Data::Settings::CrosshairLength)
			};

			Draw->AddLine(LineBottom[0], LineBottom[1], LineColor, LineThickness);
		}


		if (Data::Settings::CrosshairRight)
		{
			ImVec2 LineRight[2] = {
				ImVec2(WindowCenter.x + Data::Settings::CrosshairGap, WindowCenter.y),
				ImVec2(WindowCenter.x + Data::Settings::CrosshairGap + Data::Settings::CrosshairLength, WindowCenter.y)
			};

			Draw->AddLine(LineRight[0], LineRight[1], LineColor, LineThickness);
		}
	}
}