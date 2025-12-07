// ImGuiライブラリ動作確認テスト

#include "TestImGui.h"
#include "imgui/imgui.h"
#include <iostream>

void RunImGuiTest()
{
    std::cout << "### ImGui Library Test ###" << std::endl;
    std::cout << std::endl;

    // テスト1: インクルード確認
    std::cout << "[ImGui Test 1] Include check: OK" << std::endl;
    std::cout << "  - imgui.h successfully included" << std::endl;
    std::cout << std::endl;

    // テスト2: バージョン情報
    std::cout << "[ImGui Test 2] Version information" << std::endl;
    std::cout << "  - ImGui Version: " << IMGUI_VERSION << std::endl;
    std::cout << "  - Version Number: " << IMGUI_VERSION_NUM << std::endl;
    std::cout << std::endl;

    // テスト3: コンテキスト作成と破棄
    std::cout << "[ImGui Test 3] Context creation test" << std::endl;
    ImGuiContext* ctx = ImGui::CreateContext();
    if (ctx) {
        std::cout << "  SUCCESS: ImGui context created!" << std::endl;
        std::cout << "  - Context pointer: " << ctx << std::endl;

        // ImGuiIOの取得テスト
        ImGuiIO& io = ImGui::GetIO();
        std::cout << "  - ImGuiIO retrieved successfully" << std::endl;
        std::cout << "  - Display size (default): " << io.DisplaySize.x << " x " << io.DisplaySize.y << std::endl;

        ImGui::DestroyContext(ctx);
        std::cout << "  SUCCESS: ImGui context destroyed!" << std::endl;
    }
    else {
        std::cout << "  FAILED: Could not create ImGui context" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "### ImGui Test Completed ###" << std::endl;
    std::cout << std::endl;
}
