// stbライブラリ動作確認テスト

#include "TestStb.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb/stb_image_resize2.h"

#include <iostream>
#include <filesystem>

void RunStbTest()
{
    std::cout << "### stb Library Test ###" << std::endl;
    std::cout << std::endl;

    // テスト1: インクルードの確認
    std::cout << "[Test 1] Include check: OK" << std::endl;
    std::cout << "  - stb_image.h successfully included" << std::endl;
    std::cout << "  - stb_image_resize2.h successfully included" << std::endl;
    std::cout << std::endl;

    // テスト2: 基本機能の確認（バージョン情報）
    std::cout << "[Test 2] Version information" << std::endl;
    std::cout << "  - STBI_VERSION: " << STBI_VERSION << std::endl;
    std::cout << std::endl;

    // テスト3: サポートされているフォーマットの確認
    std::cout << "[Test 3] Supported formats" << std::endl;
    std::cout << "  - JPEG, PNG, BMP, TGA, GIF, PSD, HDR, PIC, PNM" << std::endl;
    std::cout << std::endl;

    // テスト4（オプション）: 実際の画像読み込みテスト
    std::cout << "[Test 4] Image loading test (optional)" << std::endl;

    // 実行ファイルのディレクトリを表示
    std::filesystem::path exePath = std::filesystem::current_path();
    std::cout << "  Current directory: " << exePath.string() << std::endl;
    std::cout << "  Note: To test image loading, place 'test.png' in this directory" << std::endl;
    std::cout << "        and uncomment the code below." << std::endl;
    std::cout << std::endl;

    // 画像読み込みテストのサンプルコード
    const char* testImagePath = "test.jpg";

    // ファイルの存在確認
    std::filesystem::path imagePath = std::filesystem::current_path() / testImagePath;
    std::cout << "  Checking file: " << imagePath.string() << std::endl;

    if (std::filesystem::exists(imagePath)) {
        std::cout << "  File exists: YES" << std::endl;
        std::cout << "  File size: " << std::filesystem::file_size(imagePath) << " bytes" << std::endl;
    }
    else {
        std::cout << "  File exists: NO" << std::endl;
        std::cout << "  ERROR: File not found!" << std::endl;
    }
    std::cout << std::endl;

    // 画像読み込みを試行
    std::cout << "  Attempting to load image..." << std::endl;
    int width, height, channels;
    unsigned char* imageData = stbi_load(testImagePath, &width, &height, &channels, 0);

    if (imageData)
    {
        std::cout << "  SUCCESS: Image loaded!" << std::endl;
        std::cout << "    - Size: " << width << " x " << height << std::endl;
        std::cout << "    - Channels: " << channels << std::endl;
        std::cout << "    - Memory: " << (width * height * channels) << " bytes" << std::endl;
        stbi_image_free(imageData);
    }
    else
    {
        std::cout << "  FAILED: Image could not be loaded" << std::endl;
        std::cout << "  Error reason: " << stbi_failure_reason() << std::endl;
        std::cout << std::endl;

        // 絶対パスでも試してみる
        std::cout << "  Trying with absolute path..." << std::endl;
        imageData = stbi_load(imagePath.string().c_str(), &width, &height, &channels, 0);

        if (imageData) {
            std::cout << "  SUCCESS with absolute path!" << std::endl;
            std::cout << "    - Size: " << width << " x " << height << std::endl;
            std::cout << "    - Channels: " << channels << std::endl;
            stbi_image_free(imageData);
        }
        else {
            std::cout << "  FAILED with absolute path too" << std::endl;
            std::cout << "  Error reason: " << stbi_failure_reason() << std::endl;
        }
    }

    std::cout << "### stb Test Completed ###" << std::endl;
    std::cout << std::endl;
}
