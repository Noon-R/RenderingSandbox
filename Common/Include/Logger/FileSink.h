#pragma once

#include "LogSink.h"
#include <fstream>
#include <filesystem>
#include <mutex>

namespace RenderingSandbox {

/// <summary>
/// ファイル出力Sink
/// ログをファイルに書き込む（RAII原則に基づいた自動クローズ）
/// </summary>
class FileSink : public ILogSink {
public:
    /// <summary>
    /// ファイルパスを指定してFileSinkを構築
    /// </summary>
    /// <param name="filePath">ログファイルのパス</param>
    /// <param name="append">trueの場合は追記モード、falseの場合は上書きモード</param>
    explicit FileSink(const std::filesystem::path& filePath, bool append = true);

    ~FileSink() override;

    /// <summary>
    /// ログメッセージをファイルに書き込む
    /// </summary>
    /// <param name="message">ログメッセージ</param>
    void Write(const LogMessage& message) override;

    /// <summary>
    /// ファイルバッファをフラッシュ
    /// </summary>
    void Flush() override;

    /// <summary>
    /// ログファイルのパスを取得
    /// </summary>
    /// <returns>ログファイルのパス</returns>
    const std::filesystem::path& GetFilePath() const { return m_filePath; }

    /// <summary>
    /// ファイルが正常に開いているかを確認
    /// </summary>
    /// <returns>ファイルが開いている場合true</returns>
    bool IsOpen() const;

    /// <summary>
    /// 最大ファイルサイズを設定（これを超えるとローテーション）
    /// </summary>
    /// <param name="bytes">最大ファイルサイズ（バイト）</param>
    void SetMaxFileSize(size_t bytes) { m_maxFileSize = bytes; }

    /// <summary>
    /// 最大ファイルサイズを取得
    /// </summary>
    /// <returns>最大ファイルサイズ（バイト）</returns>
    size_t GetMaxFileSize() const { return m_maxFileSize; }

    /// <summary>
    /// 保持する最大世代数を設定
    /// </summary>
    /// <param name="count">最大世代数</param>
    void SetMaxFiles(size_t count) { m_maxFiles = count; }

    /// <summary>
    /// 保持する最大世代数を取得
    /// </summary>
    /// <returns>最大世代数</returns>
    size_t GetMaxFiles() const { return m_maxFiles; }

private:
    /// <summary>
    /// ファイルサイズをチェックし、必要に応じてローテーション
    /// </summary>
    void CheckAndRotate();

    std::filesystem::path m_filePath;       // ログファイルのパス
    std::ofstream m_file;                   // ファイルストリーム
    size_t m_currentSize;                   // 現在のファイルサイズ
    size_t m_maxFileSize;                   // 最大ファイルサイズ（デフォルト10MB）
    size_t m_maxFiles;                      // 最大世代数（デフォルト5）
    std::mutex m_mutex;                     // スレッドセーフのためのミューテックス
};

} // namespace RenderingSandbox
