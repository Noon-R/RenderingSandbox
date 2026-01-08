#pragma once

#include "LogMessage.h"

namespace RenderingSandbox {

/// <summary>
/// ログ出力先の抽象基底クラス
/// Strategy Patternを使用して、様々な出力先（コンソール、ファイル、デバッグ出力等）を抽象化
/// </summary>
class ILogSink {
public:
    virtual ~ILogSink() = default;

    /// <summary>
    /// ログメッセージを出力する（純粋仮想関数）
    /// </summary>
    /// <param name="message">ログメッセージ</param>
    virtual void Write(const LogMessage& message) = 0;

    /// <summary>
    /// バッファをフラッシュする（オプション）
    /// </summary>
    virtual void Flush() {}

    /// <summary>
    /// このSinkの有効/無効を設定
    /// </summary>
    /// <param name="enabled">有効にする場合true</param>
    void SetEnabled(bool enabled) { m_enabled = enabled; }

    /// <summary>
    /// このSinkが有効かどうかを取得
    /// </summary>
    /// <returns>有効な場合true</returns>
    bool IsEnabled() const { return m_enabled; }

    /// <summary>
    /// このSinkの最小ログレベルを設定（これ以下のレベルは出力しない）
    /// </summary>
    /// <param name="level">最小ログレベル</param>
    void SetMinLevel(LogLevel level) { m_minLevel = level; }

    /// <summary>
    /// このSinkの最小ログレベルを取得
    /// </summary>
    /// <returns>最小ログレベル</returns>
    LogLevel GetMinLevel() const { return m_minLevel; }

protected:
    /// <summary>
    /// このメッセージを出力すべきかどうかを判定
    /// </summary>
    /// <param name="message">ログメッセージ</param>
    /// <returns>出力すべき場合true</returns>
    bool ShouldWrite(const LogMessage& message) const {
        return m_enabled && message.level >= m_minLevel;
    }

private:
    bool m_enabled = true;                      // Sinkが有効かどうか
    LogLevel m_minLevel = LogLevel::Trace;      // 最小ログレベル
};

} // namespace RenderingSandbox
