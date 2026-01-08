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

private:
    std::filesystem::path m_filePath;   // ログファイルのパス
    std::ofstream m_file;               // ファイルストリーム
    std::mutex m_mutex;                 // スレッドセーフのためのミューテックス
};

} // namespace RenderingSandbox
