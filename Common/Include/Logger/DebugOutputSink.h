#pragma once

#include "LogSink.h"
#include <mutex>

namespace RenderingSandbox {

/// <summary>
/// Visual Studio出力ウィンドウへのログ出力Sink
/// OutputDebugStringW()を使用してVSの出力ウィンドウにログを送信
/// </summary>
class DebugOutputSink : public ILogSink {
public:
    DebugOutputSink() = default;
    ~DebugOutputSink() override = default;

    /// <summary>
    /// ログメッセージをVisual Studio出力ウィンドウに出力
    /// </summary>
    /// <param name="message">ログメッセージ</param>
    void Write(const LogMessage& message) override;

private:
    std::mutex m_mutex;     // スレッドセーフのためのミューテックス
};

} // namespace RenderingSandbox
