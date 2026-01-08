#include "Logger/ConsoleSink.h"
#include <iostream>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

namespace RenderingSandbox {

ConsoleSink::ConsoleSink()
    : m_colorEnabled(true)
{
#ifdef _WIN32
    // Windows Console APIの標準出力ハンドルを取得
    m_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    // UTF-8サポートのためのコンソールコードページ設定
    SetConsoleOutputCP(CP_UTF8);
#else
    m_consoleHandle = nullptr;
#endif
}

ConsoleSink::~ConsoleSink() {
    Flush();
}

void ConsoleSink::Write(const LogMessage& message) {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!ShouldWrite(message)) {
        return;
    }

    // フォーマット済みメッセージを取得
    std::string formattedMessage = message.Format();

#ifdef _WIN32
    if (m_colorEnabled && m_consoleHandle) {
        // 現在の色を保存
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(static_cast<HANDLE>(m_consoleHandle), &csbi);
        WORD originalColor = csbi.wAttributes;

        // ログレベルに応じた色を設定
        WORD color = LogLevelToConsoleColor(message.level);
        SetConsoleTextAttribute(static_cast<HANDLE>(m_consoleHandle), color);

        // メッセージ出力
        if (message.level >= LogLevel::Error) {
            std::cerr << formattedMessage << std::endl;
        } else {
            std::cout << formattedMessage << std::endl;
        }

        // 元の色に戻す
        SetConsoleTextAttribute(static_cast<HANDLE>(m_consoleHandle), originalColor);
    } else {
        // 色なし出力
        if (message.level >= LogLevel::Error) {
            std::cerr << formattedMessage << std::endl;
        } else {
            std::cout << formattedMessage << std::endl;
        }
    }
#else
    // Windows以外のプラットフォーム（将来の拡張用）
    if (message.level >= LogLevel::Error) {
        std::cerr << formattedMessage << std::endl;
    } else {
        std::cout << formattedMessage << std::endl;
    }
#endif
}

void ConsoleSink::Flush() {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::cout.flush();
    std::cerr.flush();
}

} // namespace RenderingSandbox
