#include "Logger/DebugOutputSink.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

namespace RenderingSandbox {

void DebugOutputSink::Write(const LogMessage& message) {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!ShouldWrite(message)) {
        return;
    }

#ifdef _WIN32
    // フォーマット済みメッセージを取得
    std::string formattedMessage = message.Format();
    formattedMessage += "\n";

    // UTF-8からUTF-16への変換
    int wideSize = MultiByteToWideChar(CP_UTF8, 0, formattedMessage.c_str(), -1, nullptr, 0);
    if (wideSize > 0) {
        std::wstring wideMessage(wideSize, L'\0');
        MultiByteToWideChar(CP_UTF8, 0, formattedMessage.c_str(), -1, &wideMessage[0], wideSize);

        // Visual Studio出力ウィンドウに送信
        OutputDebugStringW(wideMessage.c_str());
    }
#endif
}

} // namespace RenderingSandbox
