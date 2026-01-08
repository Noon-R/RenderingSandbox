#pragma once

#include "LogSink.h"
#include <vector>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

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
    /// <param name="category">カテゴリ</param>
    /// <param name="message">メッセージ本文</param>
    /// <param name="file">ソースファイル名（省略可）</param>
    /// <param name="line">行番号（省略可）</param>
    void Log(LogLevel level,
             const std::string& category,
             const std::string& message,
             const char* file = "",
             int line = 0);

    /// <summary>
    /// Traceレベルのログを出力
    /// </summary>
    void Trace(const std::string& category, const std::string& message, const char* file = "", int line = 0);

    /// <summary>
    /// Debugレベルのログを出力
    /// </summary>
    void Debug(const std::string& category, const std::string& message, const char* file = "", int line = 0);

    /// <summary>
    /// Infoレベルのログを出力
    /// </summary>
    void Info(const std::string& category, const std::string& message, const char* file = "", int line = 0);

    /// <summary>
    /// Warningレベルのログを出力
    /// </summary>
    void Warning(const std::string& category, const std::string& message, const char* file = "", int line = 0);

    /// <summary>
    /// Errorレベルのログを出力
    /// </summary>
    void Error(const std::string& category, const std::string& message, const char* file = "", int line = 0);

    /// <summary>
    /// Fatalレベルのログを出力
    /// </summary>
    void Fatal(const std::string& category, const std::string& message, const char* file = "", int line = 0);

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
    /// カテゴリ固有の最小ログレベルを設定
    /// </summary>
    /// <param name="category">カテゴリ名</param>
    /// <param name="level">カテゴリ固有の最小ログレベル</param>
    void SetCategoryLevel(const std::string& category, LogLevel level);

    /// <summary>
    /// カテゴリ固有の最小ログレベルをクリア（グローバルレベルに戻す）
    /// </summary>
    /// <param name="category">カテゴリ名</param>
    void ClearCategoryLevel(const std::string& category);

    /// <summary>
    /// カテゴリ固有の最小ログレベルを取得
    /// </summary>
    /// <param name="category">カテゴリ名</param>
    /// <returns>カテゴリ固有のレベル（未設定の場合はグローバルレベル）</returns>
    LogLevel GetCategoryLevel(const std::string& category) const;

    /// <summary>
    /// すべてのSinkをフラッシュ
    /// </summary>
    void Flush();

private:
    Logger();
    ~Logger();

    std::vector<std::unique_ptr<ILogSink>> m_sinks;                     // 登録されたSinkのリスト
    LogLevel m_globalMinLevel;                                          // グローバル最小ログレベル
    std::unordered_map<std::string, LogLevel> m_categoryLevels;         // カテゴリ固有のログレベル
    mutable std::mutex m_mutex;                                         // スレッドセーフのためのミューテックス
};

} // namespace RenderingSandbox
