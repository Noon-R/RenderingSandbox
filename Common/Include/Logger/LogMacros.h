#pragma once

#include "Logger.h"
#include <format>

// デバッグビルドでのみログを有効化
#ifdef _DEBUG
    #define LOG_ENABLED 1
#else
    #define LOG_ENABLED 0
#endif

#if LOG_ENABLED

    // ==================================================
    // 基本マクロ（ファイル名と行番号を自動付加）
    // ==================================================

    /// <summary>
    /// Traceレベルのログを出力
    /// </summary>
    #define LOG_TRACE(msg) \
        ::RenderingSandbox::Logger::GetInstance().Trace(msg, "", __FILE__, __LINE__)

    /// <summary>
    /// Debugレベルのログを出力
    /// </summary>
    #define LOG_DEBUG(msg) \
        ::RenderingSandbox::Logger::GetInstance().Debug(msg, "", __FILE__, __LINE__)

    /// <summary>
    /// Infoレベルのログを出力
    /// </summary>
    #define LOG_INFO(msg) \
        ::RenderingSandbox::Logger::GetInstance().Info(msg, "", __FILE__, __LINE__)

    /// <summary>
    /// Warningレベルのログを出力
    /// </summary>
    #define LOG_WARNING(msg) \
        ::RenderingSandbox::Logger::GetInstance().Warning(msg, "", __FILE__, __LINE__)

    /// <summary>
    /// Errorレベルのログを出力
    /// </summary>
    #define LOG_ERROR(msg) \
        ::RenderingSandbox::Logger::GetInstance().Error(msg, "", __FILE__, __LINE__)

    /// <summary>
    /// Fatalレベルのログを出力（conditionがfalseの時にログ出力してexit）
    /// デバッガがアタッチされている場合はDebugBreak()で停止
    /// </summary>
    #define LOG_FATAL(condition, msg) \
        do { \
            if (!(condition)) { \
                ::RenderingSandbox::Logger::GetInstance().Fatal(msg, "", __FILE__, __LINE__); \
                ::RenderingSandbox::Logger::GetInstance().Flush(); \
                if (::IsDebuggerPresent()) { \
                    ::DebugBreak(); \
                } \
                std::exit(1); \
            } \
        } while(0)

    // ==================================================
    // カテゴリ指定版マクロ
    // ==================================================

    /// <summary>
    /// Traceレベルのログをカテゴリ指定で出力
    /// </summary>
    #define LOG_TRACE_C(category, msg) \
        ::RenderingSandbox::Logger::GetInstance().Trace(msg, category, __FILE__, __LINE__)

    /// <summary>
    /// Debugレベルのログをカテゴリ指定で出力
    /// </summary>
    #define LOG_DEBUG_C(category, msg) \
        ::RenderingSandbox::Logger::GetInstance().Debug(msg, category, __FILE__, __LINE__)

    /// <summary>
    /// Infoレベルのログをカテゴリ指定で出力
    /// </summary>
    #define LOG_INFO_C(category, msg) \
        ::RenderingSandbox::Logger::GetInstance().Info(msg, category, __FILE__, __LINE__)

    /// <summary>
    /// Warningレベルのログをカテゴリ指定で出力
    /// </summary>
    #define LOG_WARNING_C(category, msg) \
        ::RenderingSandbox::Logger::GetInstance().Warning(msg, category, __FILE__, __LINE__)

    /// <summary>
    /// Errorレベルのログをカテゴリ指定で出力
    /// </summary>
    #define LOG_ERROR_C(category, msg) \
        ::RenderingSandbox::Logger::GetInstance().Error(msg, category, __FILE__, __LINE__)

    /// <summary>
    /// Fatalレベルのログをカテゴリ指定で出力（conditionがfalseの時にログ出力してexit）
    /// デバッガがアタッチされている場合はDebugBreak()で停止
    /// </summary>
    #define LOG_FATAL_C(condition, category, msg) \
        do { \
            if (!(condition)) { \
                ::RenderingSandbox::Logger::GetInstance().Fatal(msg, category, __FILE__, __LINE__); \
                ::RenderingSandbox::Logger::GetInstance().Flush(); \
                if (::IsDebuggerPresent()) { \
                    ::DebugBreak(); \
                } \
                std::exit(1); \
            } \
        } while(0)

    // ==================================================
    // フォーマット文字列版マクロ（C++20 std::format使用）
    // ==================================================

    /// <summary>
    /// Traceレベルのログをフォーマット文字列で出力
    /// 例: LOG_TRACE_F("Value: {}", 42)
    /// </summary>
    #define LOG_TRACE_F(fmt, ...) \
        ::RenderingSandbox::Logger::GetInstance().Trace(std::format(fmt, ##__VA_ARGS__), "", __FILE__, __LINE__)

    /// <summary>
    /// Debugレベルのログをフォーマット文字列で出力
    /// </summary>
    #define LOG_DEBUG_F(fmt, ...) \
        ::RenderingSandbox::Logger::GetInstance().Debug(std::format(fmt, ##__VA_ARGS__), "", __FILE__, __LINE__)

    /// <summary>
    /// Infoレベルのログをフォーマット文字列で出力
    /// </summary>
    #define LOG_INFO_F(fmt, ...) \
        ::RenderingSandbox::Logger::GetInstance().Info(std::format(fmt, ##__VA_ARGS__), "", __FILE__, __LINE__)

    /// <summary>
    /// Warningレベルのログをフォーマット文字列で出力
    /// </summary>
    #define LOG_WARNING_F(fmt, ...) \
        ::RenderingSandbox::Logger::GetInstance().Warning(std::format(fmt, ##__VA_ARGS__), "", __FILE__, __LINE__)

    /// <summary>
    /// Errorレベルのログをフォーマット文字列で出力
    /// </summary>
    #define LOG_ERROR_F(fmt, ...) \
        ::RenderingSandbox::Logger::GetInstance().Error(std::format(fmt, ##__VA_ARGS__), "", __FILE__, __LINE__)

    /// <summary>
    /// Fatalレベルのログをフォーマット文字列で出力（conditionがfalseの時にログ出力してexit）
    /// デバッガがアタッチされている場合はDebugBreak()で停止
    /// </summary>
    #define LOG_FATAL_F(condition, fmt, ...) \
        do { \
            if (!(condition)) { \
                ::RenderingSandbox::Logger::GetInstance().Fatal(std::format(fmt, ##__VA_ARGS__), "", __FILE__, __LINE__); \
                ::RenderingSandbox::Logger::GetInstance().Flush(); \
                if (::IsDebuggerPresent()) { \
                    ::DebugBreak(); \
                } \
                std::exit(1); \
            } \
        } while(0)

#else
    // ==================================================
    // リリースビルドでは完全に無効化（コンパイラが最適化で削除）
    // ==================================================

    #define LOG_TRACE(msg)              ((void)0)
    #define LOG_DEBUG(msg)              ((void)0)
    #define LOG_INFO(msg)               ((void)0)
    #define LOG_WARNING(msg)            ((void)0)
    #define LOG_ERROR(msg)              ((void)0)
    #define LOG_FATAL(condition, msg)   ((void)0)

    #define LOG_TRACE_C(category, msg)  ((void)0)
    #define LOG_DEBUG_C(category, msg)  ((void)0)
    #define LOG_INFO_C(category, msg)   ((void)0)
    #define LOG_WARNING_C(category, msg) ((void)0)
    #define LOG_ERROR_C(category, msg)  ((void)0)
    #define LOG_FATAL_C(condition, category, msg)  ((void)0)

    #define LOG_TRACE_F(fmt, ...)       ((void)0)
    #define LOG_DEBUG_F(fmt, ...)       ((void)0)
    #define LOG_INFO_F(fmt, ...)        ((void)0)
    #define LOG_WARNING_F(fmt, ...)     ((void)0)
    #define LOG_ERROR_F(fmt, ...)       ((void)0)
    #define LOG_FATAL_F(condition, fmt, ...)       ((void)0)

#endif // LOG_ENABLED
