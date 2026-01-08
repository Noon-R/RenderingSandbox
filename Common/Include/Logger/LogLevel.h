#pragma once

#include <cstdint>

namespace RenderingSandbox {

/// <summary>
/// ログレベルの定義
/// </summary>
enum class LogLevel : uint8_t {
    Trace = 0,      // 詳細なトレース情報
    Debug = 1,      // デバッグ情報
    Info = 2,       // 一般情報
    Warning = 3,    // 警告
    Error = 4,      // エラー
    Fatal = 5       // 致命的エラー
};

/// <summary>
/// ログレベルを文字列に変換
/// </summary>
/// <param name="level">ログレベル</param>
/// <returns>ログレベルの文字列表現</returns>
constexpr const char* LogLevelToString(LogLevel level) {
    switch (level) {
        case LogLevel::Trace:   return "TRACE";
        case LogLevel::Debug:   return "DEBUG";
        case LogLevel::Info:    return "INFO ";
        case LogLevel::Warning: return "WARN ";
        case LogLevel::Error:   return "ERROR";
        case LogLevel::Fatal:   return "FATAL";
        default:                return "UNKNOWN";
    }
}

/// <summary>
/// ログレベルをコンソールカラーコードに変換（Windows Console API用）
/// </summary>
/// <param name="level">ログレベル</param>
/// <returns>Windowsコンソールカラーコード</returns>
constexpr uint16_t LogLevelToConsoleColor(LogLevel level) {
    // Windows Console Color Codes
    // Reference: https://docs.microsoft.com/en-us/windows/console/console-screen-buffers#character-attributes
    switch (level) {
        case LogLevel::Trace:   return 8;  // Dark Gray
        case LogLevel::Debug:   return 7;  // Light Gray (default)
        case LogLevel::Info:    return 10; // Light Green
        case LogLevel::Warning: return 14; // Yellow
        case LogLevel::Error:   return 12; // Light Red
        case LogLevel::Fatal:   return 13; // Light Magenta
        default:                return 7;  // Light Gray (default)
    }
}

} // namespace RenderingSandbox
