#include "Logger/LogMessage.h"
#include <sstream>
#include <iomanip>
#include <ctime>

namespace RenderingSandbox {

std::string LogMessage::Format() const {
    std::ostringstream oss;

    // タイムスタンプ [HH:MM:SS.mmm]
    auto timeT = std::chrono::system_clock::to_time_t(timestamp);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        timestamp.time_since_epoch()) % 1000;

    std::tm tmBuf{};
#ifdef _WIN32
    localtime_s(&tmBuf, &timeT);
#else
    localtime_r(&timeT, &tmBuf);
#endif

    oss << "[" << std::put_time(&tmBuf, "%H:%M:%S")
        << "." << std::setfill('0') << std::setw(3) << ms.count() << "] ";

    // ログレベル [LEVEL]
    oss << "[" << LogLevelToString(level) << "] ";

    // カテゴリ [Category]（指定されている場合）
    if (!category.empty()) {
        oss << "[" << category << "] ";
    }

    // メッセージ本文
    oss << message;

    // ファイル名と行番号（指定されている場合）
    if (!file.empty() && line > 0) {
        // ファイルパスからファイル名のみを抽出
        std::string filename = file;
        size_t lastSlash = filename.find_last_of("/\\");
        if (lastSlash != std::string::npos) {
            filename = filename.substr(lastSlash + 1);
        }
        oss << " (" << filename << ":" << line << ")";
    }

    return oss.str();
}

} // namespace RenderingSandbox
