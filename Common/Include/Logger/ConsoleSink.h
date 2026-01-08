#pragma once

#include "LogSink.h"
#include <mutex>

namespace RenderingSandbox {

/// <summary>
/// コンソール出力Sink
/// std::cout/std::cerrへログを出力し、Windows Console APIで色付き表示を実現
/// </summary>
class ConsoleSink : public ILogSink {
public:
    ConsoleSink();
    ~ConsoleSink() override;

    /// <summary>
    /// ログメッセージをコンソールに出力
    /// </summary>
    /// <param name="message">ログメッセージ</param>
    void Write(const LogMessage& message) override;

    /// <summary>
    /// コンソールバッファをフラッシュ
    /// </summary>
    void Flush() override;

    /// <summary>
    /// 色付き出力の有効/無効を設定
    /// </summary>
    /// <param name="enabled">有効にする場合true</param>
    void SetColorEnabled(bool enabled) { m_colorEnabled = enabled; }

    /// <summary>
    /// 色付き出力が有効かどうかを取得
    /// </summary>
    /// <returns>有効な場合true</returns>
    bool IsColorEnabled() const { return m_colorEnabled; }

private:
    void* m_consoleHandle;      // HANDLE型（Windows.hへの依存を隠蔽するためvoid*）
    bool m_colorEnabled;        // 色付き出力が有効かどうか
    std::mutex m_mutex;         // スレッドセーフのためのミューテックス
};

} // namespace RenderingSandbox
