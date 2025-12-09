// Assimpライブラリ動作確認テスト

#include "TestAssimp.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/version.h>

#include <iostream>

void RunAssimpTest()
{
    std::cout << "### Assimp Library Test ###" << std::endl;
    std::cout << std::endl;

    // テスト1: インクルード確認
    std::cout << "[Assimp Test 1] Include check: OK" << std::endl;
    std::cout << "  - assimp/Importer.hpp successfully included" << std::endl;
    std::cout << "  - assimp/scene.h successfully included" << std::endl;
    std::cout << "  - assimp/postprocess.h successfully included" << std::endl;
    std::cout << std::endl;

    // テスト2: バージョン情報
    std::cout << "[Assimp Test 2] Version information" << std::endl;
    std::cout << "  - Assimp Version: " << aiGetVersionMajor() << "."
              << aiGetVersionMinor() << "." << aiGetVersionPatch() << std::endl;
    std::cout << "  - Compile Flags: " << aiGetCompileFlags() << std::endl;
    std::cout << std::endl;

    // テスト3: Importer作成
    std::cout << "[Assimp Test 3] Importer creation test" << std::endl;
    try {
        Assimp::Importer importer;
        std::cout << "  SUCCESS: Assimp::Importer created!" << std::endl;

        // サポートされているフォーマットの数を取得
        std::string extensions;
        importer.GetExtensionList(extensions);
        std::cout << "  - Supported formats: " << extensions.substr(0, 100) << "..." << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "  FAILED: " << e.what() << std::endl;
    }
    std::cout << std::endl;

    std::cout << "### Assimp Test Completed ###" << std::endl;
    std::cout << std::endl;
}
