#include <chrono>
#include <iostream>
#include <numeric>
#include "RenderPlot.h"


RenderPlot::RenderPlot()
{

}

ImGui::PlotConfig RenderPlot::GetConfigEx1()
{
	//data from speed test
	float y_data[11];
	for (size_t i{}; i < m_TimeSamplesEx1.size(); ++i)
	{
		y_data[i] = m_TimeSamplesEx1[i];
	}

	float x_data[] = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f };

	static ImU32 colors[3] = { ImColor(0, 255, 0), ImColor(255, 0, 0), ImColor(0, 0, 255) };
	static uint32_t selection_start = 0, selection_length = 0;

	//render plot ex 1
	ImGui::PlotConfig config;
	config.values.xs = x_data;
	config.values.count = 10;
	config.values.ys = y_data;
	config.values.ys_count = 11;
	config.values.colors = colors;
	config.scale.min = 0;
	config.scale.max = 50000;
	config.tooltip.show = true;
	config.tooltip.format = "x=%.2f, y=%.2f";
	config.grid_x.show = true;
	config.grid_x.size = 50;
	config.grid_x.subticks = 4;
	config.grid_y.show = true;
	config.grid_y.size = 500.f;
	config.grid_y.subticks = 10;
	config.selection.show = true;
	config.selection.start = &selection_start;
	config.selection.length = &selection_length;
	config.frame_size = ImVec2(250, 150);

	return config;
}

ImGui::PlotConfig RenderPlot::GetConfigEx2()
{
	// data from speed test
	float y_data[10];
	for (size_t i{}; i < m_TimeSamplesEx2.size(); ++i)
	{
		y_data[i] = m_TimeSamplesEx2[i];
	}

	float x_data[] = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };

	static ImU32 colors[3] = { ImColor(0, 255, 0), ImColor(255, 0, 0), ImColor(0, 0, 255) };
	static uint32_t selection_start = 0, selection_length = 0;

	//render plot ex 2
	ImGui::PlotConfig config;
	config.values.xs = x_data;
	config.values.count = 10;
	config.values.ys = y_data;
	config.values.ys_count = 10;
	config.values.colors = colors;
	config.scale.min = 0;
	config.scale.max = 40000;
	config.tooltip.show = true;
	config.tooltip.format = "x=%.2f, y=%.2f";
	config.grid_x.show = true;
	config.grid_x.size = 50;
	config.grid_x.subticks = 4;
	config.grid_y.show = true;
	config.grid_y.size = 6000.f;
	config.grid_y.subticks = 10;
	config.selection.show = true;
	config.selection.start = &selection_start;
	config.selection.length = &selection_length;
	config.frame_size = ImVec2(250, 150);

	return config;
}

ImGui::PlotConfig RenderPlot::GetConfigEx3()
{
	// data from speed test
	float y_data[10];
	for (size_t i{}; i < m_TimeSamplesEx3.size(); ++i)
	{
		y_data[i] = m_TimeSamplesEx3[i];
	}

	float x_data[] = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };

	static ImU32 colors[3] = { ImColor(0, 255, 0), ImColor(255, 0, 0), ImColor(0, 0, 255) };
	static uint32_t selection_start = 0, selection_length = 0;

	//render plot ex 3
	ImGui::PlotConfig config;
	config.values.xs = x_data;
	config.values.count = 10;
	config.values.ys = y_data;
	config.values.ys_count = 10;
	config.values.colors = colors;
	config.scale.min = 0;
	config.scale.max = 20000;
	config.tooltip.show = true;
	config.tooltip.format = "x=%.2f, y=%.2f";
	config.grid_x.show = true;
	config.grid_x.size = 50;
	config.grid_x.subticks = 4;
	config.grid_y.show = true;
	config.grid_y.size = 1000.f;
	config.grid_y.subticks = 10;
	config.selection.show = true;
	config.selection.start = &selection_start;
	config.selection.length = &selection_length;
	config.frame_size = ImVec2(250, 150);

	return config;
}



void RenderPlot::MeasureIntListCreation(int SampleAmount)
{
	std::cout << "EXERCISE 0" << '\n';
	//EXERCISE 0
	size_t length{ 10000000 };
	auto buffer{ std::vector<int>(length, 3) };
	
	for (size_t step{ 1 }; step <= 1024; step *= 2)
	{
		std::vector<float> timesamples;
		for (int sample{}; sample < SampleAmount; ++sample)
		{
			const auto start = std::chrono::high_resolution_clock::now();
			for (size_t i{}; i < length; i += step)
			{
				buffer[i] *= 2;
			}

			const auto end = std::chrono::high_resolution_clock::now();
			const auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			timesamples.push_back(static_cast<float>(total));
		}

		auto min = std::min_element(std::begin(timesamples), std::end(timesamples));
		timesamples.erase(min);
		auto max = std::max_element(std::begin(timesamples), std::end(timesamples));
		timesamples.erase(max);


		float average = std::accumulate(timesamples.begin(), timesamples.end(), 0.0f) / static_cast<float>(timesamples.size());

		m_TimeSamplesEx1.push_back(average);
		std::cout << step << "; " << average << std::endl;
	}
}

void RenderPlot::MeasureGameObject3D()
{
	//EXERCISE 1
	size_t length{ 10000000 };
	GameObject3D* buffer = new GameObject3D[length]{};
	
	for (size_t step{ 1 }; step <= 1024; step *= 2)
	{
		const auto start = std::chrono::high_resolution_clock::now();
		for (size_t i{}; i < length; i += step)
		{
			buffer[i].ID *= 2;
		}

		const auto end = std::chrono::high_resolution_clock::now();
		const auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

		std::cout << step << "; " << total << std::endl;
		m_TimeSamplesEx2.push_back(static_cast<float>(total));
	}


	auto max = std::max_element(std::begin(m_TimeSamplesEx2), std::end(m_TimeSamplesEx2));
	auto min = std::min_element(std::begin(m_TimeSamplesEx2), std::end(m_TimeSamplesEx2));

	// make sure max and min are not the same element
	if (max != min) {
		m_TimeSamplesEx2.erase(min);
		m_TimeSamplesEx2.erase(max);
	}
	else if (min != std::end(m_TimeSamplesEx2))
	{
		m_TimeSamplesEx2.erase(max);
	}

	float average = std::accumulate(m_TimeSamplesEx2.begin(), m_TimeSamplesEx2.end(), 0.0f) / static_cast<float>(m_TimeSamplesEx2.size());

	//warning evasion
	average = average;

	delete[] buffer;
}

void RenderPlot::MeasureGameObject3DAlt()
{
	//EXERCISE 2
	size_t length{ 10000000 };
	GameObject3DAlt* buffer = new GameObject3DAlt[length]{};
	
	for (size_t step{ 1 }; step <= 1024; step *= 2)
	{
		const auto start = std::chrono::high_resolution_clock::now();
		for (size_t i{}; i < length; i += step)
		{
			buffer[i].ID *= 2;
		}

		const auto end = std::chrono::high_resolution_clock::now();
		const auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

		std::cout << step << "; " << total << std::endl;
		m_TimeSamplesEx3.push_back(static_cast<float>(total));
	}


	auto max = std::max_element(std::begin(m_TimeSamplesEx3), std::end(m_TimeSamplesEx3));
	auto min = std::min_element(std::begin(m_TimeSamplesEx3), std::end(m_TimeSamplesEx3));

	// make sure max and min are not the same element
	if (max != min) {
		m_TimeSamplesEx3.erase(min);
		m_TimeSamplesEx3.erase(max);
	}
	else if (min != std::end(m_TimeSamplesEx3))
	{
		m_TimeSamplesEx3.erase(max);
	}

	float average = std::accumulate(m_TimeSamplesEx3.begin(), m_TimeSamplesEx3.end(), 0.0f) / static_cast<float>(m_TimeSamplesEx3.size());

	//warning evasion
	average = average;

	delete[] buffer;
}
