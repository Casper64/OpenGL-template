#include "pch.h"
#include "main.h"

void render()
{
    static float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    ImGui::Begin("Test tool");
    ImGui::ColorEdit4("Pick me!", color);
    const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
    ImGui::PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));

    // Display contents in a scrolling region
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
    ImGui::BeginChild("Scrolling");
    for (int n = 0; n < 50; n++)
        ImGui::Text("%04d: Some text", n);
    ImGui::EndChild();
    ImGui::End();
}

int main(int argc, char **argv)
{
    WindowProps props("My awesome project", 1280, 720);
    Application *app = new Application(props);

    app->set_main_loop(render);

    app->run();
    return 0;
}