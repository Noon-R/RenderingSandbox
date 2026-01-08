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
                 const std::string& message,
                 const std::string& category,
                 const char* file,
                 int line)
{
    // グローバルレベルチェックで早期リターン
    if (level < m_globalMinLevel) {
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

void Logger::Trace(const std::string& message, const std::string& category, const char* file, int line) {
    Log(LogLevel::Trace, message, category, file, line);
}

void Logger::Debug(const std::string& message, const std::string& category, const char* file, int line) {
    Log(LogLevel::Debug, message, category, file, line);
}

void Logger::Info(const std::string& message, const std::string& category, const char* file, int line) {
    Log(LogLevel::Info, message, category, file, line);
}

void Logger::Warning(const std::string& message, const std::string& category, const char* file, int line) {
    Log(LogLevel::Warning, message, category, file, line);
}

void Logger::Error(const std::string& message, const std::string& category, const char* file, int line) {
    Log(LogLevel::Error, message, category, file, line);
}

void Logger::Fatal(const std::string& message, const std::string& category, const char* file, int line) {
    Log(LogLevel::Fatal, message, category, file, line);
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

} // namespace RenderingSandbox
