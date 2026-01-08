#include "Logger/FileSink.h"
#include <iostream>

namespace RenderingSandbox {

FileSink::FileSink(const std::filesystem::path& filePath, bool append)
    : m_filePath(filePath)
{
    // 親ディレクトリが存在しない場合は作成
    if (filePath.has_parent_path()) {
        std::filesystem::path parentPath = filePath.parent_path();
        if (!parentPath.empty() && !std::filesystem::exists(parentPath)) {
            std::filesystem::create_directories(parentPath);
        }
    }

    // ファイルを開く
    auto mode = std::ios::out;
    if (append) {
        mode |= std::ios::app;
    } else {
        mode |= std::ios::trunc;
    }

    m_file.open(filePath, mode);

    if (!m_file.is_open()) {
        // ファイルオープンに失敗した場合はエラー出力（標準エラー出力へ）
        std::cerr << "FileSink: Failed to open log file: " << filePath << std::endl;
    }
}

FileSink::~FileSink() {
    if (m_file.is_open()) {
        Flush();
        m_file.close();
    }
}

void FileSink::Write(const LogMessage& message) {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!ShouldWrite(message) || !m_file.is_open()) {
        return;
    }

    // フォーマット済みメッセージを取得してファイルに書き込み
    std::string formattedMessage = message.Format();
    m_file << formattedMessage << std::endl;
}

void FileSink::Flush() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_file.is_open()) {
        m_file.flush();
    }
}

bool FileSink::IsOpen() const {
    return m_file.is_open();
}

} // namespace RenderingSandbox
