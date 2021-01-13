#include <pch.h>
#include <base.h>

void Base::Hacks::Crosshair()
{
	if (Data::Settings::EnableCrosshair)
	{
		ImDrawList* Draw = ImGui::GetBackgroundDrawList();
		ImVec2 WindowCenter = ImVec2((float)Data::WindowWidth / 2, (float)Data::WindowHeight / 2);
		ImColor LineColor = ImColor(Data::Settings::CrosshairColor[0], Data::Settings::CrosshairColor[1], Data::Settings::CrosshairColor[2], Data::Settings::CrosshairColor[3]);
		float LineLength = Data::Settings::CrosshairLength;
		float LineThickness = Data::Settings::CrosshairThickness;
		float Gap = Data::Settings::CrosshairGap;

		if (Data::Settings::CrosshairDot)
		{
			if(Data::Settings::CrosshairDotFilled)
				Draw->AddCircleFilled(WindowCenter, LineThickness, LineColor);
			else
				Draw->AddCircle(WindowCenter, LineThickness, LineColor);
		}

		switch(Data::Settings::CrosshairType)
		{
		case 0: //Default Crosshair
			if (Data::Settings::CrosshairTop)
			{
				ImVec2 LineTop[2] = {
					ImVec2(WindowCenter.x, WindowCenter.y - Gap),
					ImVec2(WindowCenter.x, WindowCenter.y - Gap - LineLength)
				};

				Draw->AddLine(LineTop[0], LineTop[1], LineColor, LineThickness);
			}

			if (Data::Settings::CrosshairLeft)
			{
				ImVec2 LineLeft[2] = {
					ImVec2(WindowCenter.x - Gap, WindowCenter.y),
					ImVec2(WindowCenter.x - Gap - LineLength, WindowCenter.y)
				};

				Draw->AddLine(LineLeft[0], LineLeft[1], LineColor, LineThickness);
			}

			if (Data::Settings::CrosshairBottom)
			{
				ImVec2 LineBottom[2] = {
					ImVec2(WindowCenter.x, WindowCenter.y + Gap),
					ImVec2(WindowCenter.x, WindowCenter.y + Gap + LineLength)
				};

				Draw->AddLine(LineBottom[0], LineBottom[1], LineColor, LineThickness);
			}


			if (Data::Settings::CrosshairRight)
			{
				ImVec2 LineRight[2] = {
					ImVec2(WindowCenter.x + Gap, WindowCenter.y),
					ImVec2(WindowCenter.x + Gap + LineLength, WindowCenter.y)
				};

				Draw->AddLine(LineRight[0], LineRight[1], LineColor, LineThickness);
			}

			break;

		case 1: //Triangle Crosshair
			LineLength += Gap;
			if (Data::Settings::CrosshairTop)
			{
				ImVec2 LineTop[] = {
					ImVec2(WindowCenter.x - LineLength, WindowCenter.y - LineLength / 2),
					ImVec2(WindowCenter.x + LineLength, WindowCenter.y - LineLength / 2)
				};

				Draw->AddLine(LineTop[0], LineTop[1], LineColor, LineThickness);
			}

			if (Data::Settings::CrosshairLeft)
			{
				ImVec2 LineLeft[] = {
					ImVec2(WindowCenter.x - LineLength, WindowCenter.y - LineLength / 2),
					ImVec2(WindowCenter.x, WindowCenter.y + LineLength / 2)
				};

				Draw->AddLine(LineLeft[0], LineLeft[1], LineColor, LineThickness);
			}

			if (Data::Settings::CrosshairRight)
			{
				ImVec2 LineRight[] = {
					ImVec2(WindowCenter.x, WindowCenter.y + LineLength / 2),
					ImVec2(WindowCenter.x + LineLength, WindowCenter.y - LineLength / 2)
				};

				Draw->AddLine(LineRight[0], LineRight[1], LineColor, LineThickness);
			}

			break;

		case 2: //Square Crosshair
			LineLength += Gap;
			if (Data::Settings::CrosshairTop)
			{
				ImVec2 LineTop[2] = {
					ImVec2(WindowCenter.x - LineLength / 2, WindowCenter.y - LineLength / 2),
					ImVec2(WindowCenter.x + LineLength / 2, WindowCenter.y - LineLength / 2)
				};

				Draw->AddLine(LineTop[0], LineTop[1], LineColor, LineThickness);
			}

			if (Data::Settings::CrosshairLeft)
			{
				ImVec2 LineLeft[2] = {
					ImVec2(WindowCenter.x - LineLength / 2, WindowCenter.y - LineLength / 2),
					ImVec2(WindowCenter.x - LineLength / 2, WindowCenter.y + LineLength / 2)
				};

				Draw->AddLine(LineLeft[0], LineLeft[1], LineColor, LineThickness);
			}

			if (Data::Settings::CrosshairBottom)
			{
				ImVec2 LineBottom[2] = {
					ImVec2(WindowCenter.x - LineLength / 2, WindowCenter.y + LineLength / 2),
					ImVec2(WindowCenter.x + LineLength / 2, WindowCenter.y + LineLength / 2)
				};

				Draw->AddLine(LineBottom[0], LineBottom[1], LineColor, LineThickness);
			}


			if (Data::Settings::CrosshairRight)
			{
				ImVec2 LineRight[2] = {
					ImVec2(WindowCenter.x + LineLength / 2, WindowCenter.y + LineLength / 2),
					ImVec2(WindowCenter.x + LineLength / 2, WindowCenter.y - LineLength / 2)
				};

				Draw->AddLine(LineRight[0], LineRight[1], LineColor, LineThickness);
			}
			break;

		case 3: //Circle Crosshair
			LineLength += Gap;

			Draw->AddCircle(WindowCenter, LineLength, LineColor, 0, LineThickness);

			break;
		default: //Unknown crosshair
			Data::Settings::CrosshairType = 0;
			return;
			//break;
		}
	}
}