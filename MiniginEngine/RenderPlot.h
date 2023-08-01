#pragma once
#include <vector>
#include "imgui.h"
#include "imgui_impl_opengl2.h"
#include "imgui_impl_sdl2.h"
#include "imgui_plot.h"

struct Transform
{
	float Matrix[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1 };
};

class GameObject3D
{
public:
	Transform transform{};
	int ID{};
};

class GameObject3DAlt
{
public:
	Transform* transform{};
	int ID{};
};

class RenderPlot
{
public:
	RenderPlot();
	ImGui::PlotConfig GetConfigEx1();
	ImGui::PlotConfig GetConfigEx2();
	ImGui::PlotConfig GetConfigEx3();
	void MeasureIntListCreation(int SampleAmount);
	void MeasureGameObject3D();
	void MeasureGameObject3DAlt();
	
private:


	std::vector<float> m_TimeSamplesEx1{};
	std::vector<float> m_TimeSamplesEx2{};
	std::vector<float> m_TimeSamplesEx3{};
};

