// ライブラリ動作確認用テストコード
// このファイルは動作確認のための一時的なテストコードです

#include "Tests/TestImGui.h"
#include "Tests/TestStb.h"
#include "Tests/TestAssimp.h"

#include <iostream>

int main()
{
    std::cout << "=== Library Test ===" << std::endl;
    std::cout << std::endl;

    // ImGuiテスト実行
    RunImGuiTest();

    // stbテスト実行
    RunStbTest();

    // Assimpテスト実行
    RunAssimpTest();

    std::cout << "=== All Library Tests Completed ===" << std::endl;
    std::cout << std::endl;
    std::cout << "Press Enter to exit...";
    std::cin.get();

    return 0;
}
