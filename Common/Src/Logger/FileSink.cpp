#include "Logger/FileSink.h"
#include <iostream>

namespace RenderingSandbox {

FileSink::FileSink(const std::filesystem::path& filePath, bool append)
    : m_filePath(filePath)
    , m_currentSize(0)
    , m_maxFileSize(10 * 1024 * 1024)  // デフォルト10MB
    , m_maxFiles(5)                     // デフォルト5世代
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
    } else if (append && std::filesystem::exists(filePath)) {
        // 追記モードの場合、既存のファイルサイズを取得
        m_currentSize = static_cast<size_t>(std::filesystem::file_size(filePath));
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

    // ファイルサイズチェックとローテーション
    CheckAndRotate();

    // フォーマット済みメッセージを取得してファイルに書き込み
    std::string formattedMessage = message.Format();
    m_file << formattedMessage << std::endl;

    // 書き込んだサイズを加算（改行文字も含む）
    m_currentSize += formattedMessage.size() + 1;
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

void FileSink::CheckAndRotate() {
    // ファイルサイズが最大サイズを超えていない場合は何もしない
    if (m_currentSize < m_maxFileSize) {
        return;
    }

    // 現在のファイルを閉じる
    if (m_file.is_open()) {
        m_file.close();
    }

    // 既存のバックアップファイルをローテーション
    // 例: .log.4 -> .log.5, .log.3 -> .log.4, ... , .log.1 -> .log.2
    for (int i = static_cast<int>(m_maxFiles) - 1; i >= 1; --i) {
        std::filesystem::path oldPath = m_filePath.string() + "." + std::to_string(i);
        std::filesystem::path newPath = m_filePath.string() + "." + std::to_string(i + 1);

        if (std::filesystem::exists(oldPath)) {
            // 最古のファイルは削除、それ以外はリネーム
            if (i == static_cast<int>(m_maxFiles) - 1) {
                std::filesystem::remove(oldPath);
            } else {
                std::error_code ec;
                std::filesystem::rename(oldPath, newPath, ec);
                if (ec) {
                    std::cerr << "FileSink: Failed to rename " << oldPath << " to " << newPath
                              << " : " << ec.message() << std::endl;
                }
            }
        }
    }

    // 現在のログファイルを .log.1 にリネーム
    if (std::filesystem::exists(m_filePath)) {
        std::filesystem::path backupPath = m_filePath.string() + ".1";
        std::error_code ec;
        std::filesystem::rename(m_filePath, backupPath, ec);
        if (ec) {
            std::cerr << "FileSink: Failed to rename " << m_filePath << " to " << backupPath
                      << " : " << ec.message() << std::endl;
        }
    }

    // 新しいファイルを開く
    m_file.open(m_filePath, std::ios::out | std::ios::trunc);
    m_currentSize = 0;

    if (!m_file.is_open()) {
        std::cerr << "FileSink: Failed to reopen log file after rotation: " << m_filePath << std::endl;
    }
}

} // namespace RenderingSandbox
