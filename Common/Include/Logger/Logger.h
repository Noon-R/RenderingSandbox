#pragma once

#include "LogSink.h"
#include <vector>
#include <memory>
#include <mutex>
#include <string>

namespace RenderingSandbox {

/// <summary>
/// Loggerメインクラス（Singletonパターン）
/// 複数のSinkを管理し、ログメッセージをすべてのSinkに配信する
/// </summary>
class Logger {
public:
    /// <summary>
    /// Loggerのシングルトンインスタンスを取得
    /// </summary>
    /// <returns>Loggerインスタンスへの参照</returns>
    static Logger& GetInstance();

    // コピー・ムーブ禁止
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

    /// <summary>
    /// Sinkを追加
    /// </summary>
    /// <param name="sink">追加するSink（unique_ptr）</param>
    void AddSink(std::unique_ptr<ILogSink> sink);

    /// <summary>
    /// すべてのSinkをクリア
    /// </summary>
    void ClearSinks();

    /// <summary>
    /// ログメッセージを出力（汎用メソッド）
    /// </summary>
    /// <param name="level">ログレベル</param>
    /// <param name="message">メッセージ本文</param>
    /// <param name="category">カテゴリ（省略可）</param>
    /// <param name="file">ソースファイル名（省略可）</param>
    /// <param name="line">行番号（省略可）</param>
    void Log(LogLevel level,
             const std::string& message,
             const std::string& category = "",
             const char* file = "",
             int line = 0);

    /// <summary>
    /// Traceレベルのログを出力
    /// </summary>
    void Trace(const std::string& message, const std::string& category = "", const char* file = "", int line = 0);

    /// <summary>
    /// Debugレベルのログを出力
    /// </summary>
    void Debug(const std::string& message, const std::string& category = "", const char* file = "", int line = 0);

    /// <summary>
    /// Infoレベルのログを出力
    /// </summary>
    void Info(const std::string& message, const std::string& category = "", const char* file = "", int line = 0);

    /// <summary>
    /// Warningレベルのログを出力
    /// </summary>
    void Warning(const std::string& message, const std::string& category = "", const char* file = "", int line = 0);

    /// <summary>
    /// Errorレベルのログを出力
    /// </summary>
    void Error(const std::string& message, const std::string& category = "", const char* file = "", int line = 0);

    /// <summary>
    /// Fatalレベルのログを出力
    /// </summary>
    void Fatal(const std::string& message, const std::string& category = "", const char* file = "", int line = 0);

    /// <summary>
    /// グローバル最小ログレベルを設定（これ以下は全Sinkで出力しない）
    /// </summary>
    /// <param name="level">最小ログレベル</param>
    void SetGlobalMinLevel(LogLevel level);

    /// <summary>
    /// グローバル最小ログレベルを取得
    /// </summary>
    /// <returns>最小ログレベル</returns>
    LogLevel GetGlobalMinLevel() const;

    /// <summary>
    /// すべてのSinkをフラッシュ
    /// </summary>
    void Flush();

private:
    Logger();
    ~Logger();

    std::vector<std::unique_ptr<ILogSink>> m_sinks;     // 登録されたSinkのリスト
    LogLevel m_globalMinLevel;                          // グローバル最小ログレベル
    mutable std::mutex m_mutex;                         // スレッドセーフのためのミューテックス
};

} // namespace RenderingSandbox
