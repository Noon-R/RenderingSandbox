#pragma once

#include "LogLevel.h"
#include <string>
#include <chrono>
#include <thread>

namespace RenderingSandbox {

/// <summary>
/// ログメッセージ構造体
/// タイムスタンプ、ログレベル、メッセージ本文、カテゴリ、ソースファイル情報を保持
/// </summary>
struct LogMessage {
    LogLevel level;                                         // ログレベル
    std::string message;                                    // メッセージ本文
    std::string category;                                   // カテゴリ（オプション）
    std::string file;                                       // ソースファイル名
    int line;                                               // 行番号
    std::chrono::system_clock::time_point timestamp;        // タイムスタンプ
    std::thread::id threadId;                               // スレッドID

    /// <summary>
    /// フォーマット済みログメッセージ文字列を生成
    /// 形式: [HH:MM:SS.mmm] [LEVEL] [Category] message (file:line) [ThreadID]
    /// </summary>
    /// <returns>フォーマット済み文字列</returns>
    std::string Format() const;
};

} // namespace RenderingSandbox
