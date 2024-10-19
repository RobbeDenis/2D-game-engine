#include "TrashTheCash.h"
#include "GameObject.h"
#include "ImGuiRenderer.h"
#include <chrono>
#include <imgui.h>
#include <backends/imgui_impl_opengl2.h>
#include <backends/imgui_impl_sdl2.h>
#include <imgui_plot.h>
#include <algorithm> 

struct Transform
{
    float matrix[16] =
    {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0
    };
};

class Gameobject3D
{
public:
    Transform transform{};
    int ID{};
};

class Gameobject3DAlt
{
public:
    Transform* transform = nullptr;
    int ID{};
};

dae::TrashTheCash::TrashTheCash(GameObject* gameObject)
	: Component(gameObject)
    , m_Ex1Samples{10}
    , m_Ex2Samples{10}
    , m_OutlierPercentage{0.1f}
    , m_pImGui{nullptr}
{

}

dae::TrashTheCash::~TrashTheCash()
{
    
}

void dae::TrashTheCash::Loaded()
{
	m_pImGui = GetGameObject()->GetComponent<ImGuiRenderer>();
}

void dae::TrashTheCash::Start()
{
    m_pImGui->AddWindowFunction([this]() { Exercise1Window(); });
    m_pImGui->AddWindowFunction([this]() { Exercise2Window(); });
}

void dae::TrashTheCash::Exercise1Window()
{
    ImGui::Begin("Exercise 1");

    ImGui::InputInt("# samples", &m_Ex1Samples, 1, 100);

    if (ImGui::Button("Trash the cache")) Exercise1();

    ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_PlotLines, IM_COL32(242, 142, 19, 255));
    ImGui::PlotLines("", m_Ex1Data.data(), int(m_Ex1Data.size()), 0, nullptr, FLT_MAX, FLT_MAX, { 260, 120 });
    ImGui::PopStyleColor();

    ImGui::End();
}

void dae::TrashTheCash::Exercise2Window()
{
    ImGui::Begin("Exercise 2");

    ImGui::InputInt("# samples", &m_Ex2Samples, 1, 100);

    if (ImGui::Button("Trash the cache with GameObject3D")) Exercise2();

    ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_PlotLines, IM_COL32(86, 242, 19, 255));
    ImGui::PlotLines("", m_Ex2Data.data(), int(m_Ex2Data.size()), 0, nullptr, FLT_MAX, FLT_MAX, { 260, 120 });
    ImGui::PopStyleColor();

    if (ImGui::Button("Trash the cache with GameObject3DAlt")) Exercise2Alt();

    ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_PlotLines, IM_COL32(24, 240, 236, 255));
    ImGui::PlotLines("", m_Ex2DataAlt.data(), int(m_Ex2DataAlt.size()), 0, nullptr, FLT_MAX, FLT_MAX, { 260, 120 });
    ImGui::PopStyleColor();

    ImGui::End();
}

void dae::TrashTheCash::Exercise1()
{
    m_Ex1Data.erase(begin(m_Ex1Data), end(m_Ex1Data));

    const unsigned int size{ static_cast<unsigned int>(pow(2, 26)) };
    int* integers = new int[size] {};
    const int maxStep = 11;
    std::vector<std::vector<unsigned int>> stepAverages;

    const int aOutliers{ static_cast<int>(m_Ex1Samples * m_OutlierPercentage) };
    stepAverages.resize(maxStep, {});
    for (std::vector<unsigned int>& times : stepAverages)
    {
        times.resize(m_Ex1Samples);
    }

    for (size_t poolIdx = 0; static_cast<int>(poolIdx) < m_Ex1Samples; ++poolIdx)
    {
        int step{ 1 };
        for (int averageIdx = 0; averageIdx < maxStep; ++averageIdx, step *= 2)
        {
            auto start = std::chrono::high_resolution_clock::now();

            for (unsigned int i = 0; i < size; i += step)
                integers[i] *= 2;

            auto end = std::chrono::high_resolution_clock::now();
            const auto delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            stepAverages[averageIdx][poolIdx] = static_cast<unsigned int>(delta);
        }
    }

    std::cout << std::endl;
    int step{ 1 };
    for (int i = 0; i < maxStep; ++i, step *= 2)
    {
        auto& times = stepAverages[i];
        std::sort(begin(times), end(times));
        times.erase(begin(times), begin(times) + aOutliers);
        times.erase(end(times) - aOutliers, end(times));

        float average{};
        for (auto time : times)
            average += time;
        average /= static_cast<unsigned int>(times.size());

        m_Ex1Data.push_back(average);
    }

    delete[] integers;
}

void dae::TrashTheCash::Exercise2()
{
    m_Ex2Data.erase(begin(m_Ex2Data), end(m_Ex2Data));

    const unsigned int size{ static_cast<unsigned int>(pow(2, 26)) };
    Gameobject3D* integers = new Gameobject3D[size]{};
    const int maxStep = 11;
    std::vector<std::vector<unsigned int>> stepAverages;

    const int aOutliers{ static_cast<int>(m_Ex2Samples * m_OutlierPercentage) };
    stepAverages.resize(maxStep, {});
    for (std::vector<unsigned int>& times : stepAverages)
    {
        times.resize(m_Ex2Samples);
    }

    for (size_t poolIdx = 0; static_cast<int>(poolIdx) < m_Ex2Samples; ++poolIdx)
    {
        int step{ 1 };
        for (int averageIdx = 0; averageIdx < maxStep; ++averageIdx, step *= 2)
        {
            auto start = std::chrono::high_resolution_clock::now();

            for (unsigned int i = 0; i < size; i += step)
                integers[i].ID *= 2;

            auto end = std::chrono::high_resolution_clock::now();
            const auto delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            stepAverages[averageIdx][poolIdx] = static_cast<unsigned int>(delta);
        }
    }

    std::cout << std::endl;
    int step{ 1 };
    for (int i = 0; i < maxStep; ++i, step *= 2)
    {
        auto& times = stepAverages[i];
        std::sort(begin(times), end(times));
        times.erase(begin(times), begin(times) + aOutliers);
        times.erase(end(times) - aOutliers, end(times));

        float average{};
        for (auto time : times)
            average += time;
        average /= static_cast<unsigned int>(times.size());

        m_Ex2Data.push_back(average);
    }

    delete[] integers;
}

void dae::TrashTheCash::Exercise2Alt()
{
    m_Ex2DataAlt.erase(begin(m_Ex2DataAlt), end(m_Ex2DataAlt));

    const unsigned int size{ static_cast<unsigned int>(pow(2, 26)) };
    Gameobject3DAlt* integers = new Gameobject3DAlt[size]{};
    const int maxStep = 11;
    std::vector<std::vector<unsigned int>> stepAverages;

    const int aOutliers{ static_cast<int>(m_Ex2Samples * m_OutlierPercentage) };
    stepAverages.resize(maxStep, {});
    for (std::vector<unsigned int>& times : stepAverages)
    {
        times.resize(m_Ex2Samples);
    }

    for (size_t poolIdx = 0; static_cast<int>(poolIdx) < m_Ex2Samples; ++poolIdx)
    {
        int step{ 1 };
        for (int averageIdx = 0; averageIdx < maxStep; ++averageIdx, step *= 2)
        {
            auto start = std::chrono::high_resolution_clock::now();

            for (unsigned int i = 0; i < size; i += step)
                integers[i].ID *= 2;

            auto end = std::chrono::high_resolution_clock::now();
            const auto delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            stepAverages[averageIdx][poolIdx] = static_cast<unsigned int>(delta);
        }
    }

    std::cout << std::endl;
    int step{ 1 };
    for (int i = 0; i < maxStep; ++i, step *= 2)
    {
        auto& times = stepAverages[i];
        std::sort(begin(times), end(times));
        times.erase(begin(times), begin(times) + aOutliers);
        times.erase(end(times) - aOutliers, end(times));

        float average{};
        for (auto time : times)
            average += time;
        average /= static_cast<unsigned int>(times.size());

        m_Ex2DataAlt.push_back(average);
    }

    delete[] integers;
}