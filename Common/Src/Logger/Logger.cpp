#include "Logger/Logger.h"
#include <chrono>
#include <thread>

namespace RenderingSandbox {

Logger& Logger::GetInstance() {
    // C++11以降、staticローカル変数の初期化はスレッドセーフ
    static Logger instance;
    return instance;
}

Logger::Logger()
    : m_globalMinLevel(LogLevel::Trace)
{
}

Logger::~Logger() {
    Flush();
}

void Logger::AddSink(std::unique_ptr<ILogSink> sink) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (sink) {
        m_sinks.push_back(std::move(sink));
    }
}

void Logger::ClearSinks() {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_sinks.clear();
}

void Logger::Log(LogLevel level,
                 const std::string& category,
                 const std::string& message,
                 const char* file,
                 int line)
{
    // カテゴリ固有のレベルチェック（設定されている場合）
    LogLevel minLevel = m_globalMinLevel;
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        auto it = m_categoryLevels.find(category);
        if (it != m_categoryLevels.end()) {
            minLevel = it->second;
        }
    }

    // レベルチェックで早期リターン
    if (level < minLevel) {
        return;
    }

    // LogMessageの構築
    LogMessage logMessage{
        level,
        message,
        category,
        file ? file : "",
        line,
        std::chrono::system_clock::now(),
        std::this_thread::get_id()
    };

    // すべてのSinkにメッセージを配信
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto& sink : m_sinks) {
        if (sink) {
            sink->Write(logMessage);
        }
    }
}

void Logger::Trace(const std::string& category, const std::string& message, const char* file, int line) {
    Log(LogLevel::Trace, category, message, file, line);
}

void Logger::Debug(const std::string& category, const std::string& message, const char* file, int line) {
    Log(LogLevel::Debug, category, message, file, line);
}

void Logger::Info(const std::string& category, const std::string& message, const char* file, int line) {
    Log(LogLevel::Info, category, message, file, line);
}

void Logger::Warning(const std::string& category, const std::string& message, const char* file, int line) {
    Log(LogLevel::Warning, category, message, file, line);
}

void Logger::Error(const std::string& category, const std::string& message, const char* file, int line) {
    Log(LogLevel::Error, category, message, file, line);
}

void Logger::Fatal(const std::string& category, const std::string& message, const char* file, int line) {
    Log(LogLevel::Fatal, category, message, file, line);
}

void Logger::SetGlobalMinLevel(LogLevel level) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_globalMinLevel = level;
}

LogLevel Logger::GetGlobalMinLevel() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_globalMinLevel;
}

void Logger::Flush() {
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto& sink : m_sinks) {
        if (sink) {
            sink->Flush();
        }
    }
}

void Logger::SetCategoryLevel(const std::string& category, LogLevel level) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_categoryLevels[category] = level;
}

void Logger::ClearCategoryLevel(const std::string& category) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_categoryLevels.erase(category);
}

LogLevel Logger::GetCategoryLevel(const std::string& category) const {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_categoryLevels.find(category);
    if (it != m_categoryLevels.end()) {
        return it->second;
    }
    return m_globalMinLevel;
}

} // namespace RenderingSandbox
