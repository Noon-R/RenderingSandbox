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
    // ログマクロ（カテゴリ指定必須）
    // ==================================================

    /// <summary>
    /// Traceレベルのログを出力
    /// </summary>
    #define LOG_TRACE(category, msg) \
        ::RenderingSandbox::Logger::GetInstance().Trace(category, msg, __FILE__, __LINE__)

    /// <summary>
    /// Debugレベルのログを出力
    /// </summary>
    #define LOG_DEBUG(category, msg) \
        ::RenderingSandbox::Logger::GetInstance().Debug(category, msg, __FILE__, __LINE__)

    /// <summary>
    /// Infoレベルのログを出力
    /// </summary>
    #define LOG_INFO(category, msg) \
        ::RenderingSandbox::Logger::GetInstance().Info(category, msg, __FILE__, __LINE__)

    /// <summary>
    /// Warningレベルのログを出力
    /// </summary>
    #define LOG_WARNING(category, msg) \
        ::RenderingSandbox::Logger::GetInstance().Warning(category, msg, __FILE__, __LINE__)

    /// <summary>
    /// Errorレベルのログを出力
    /// </summary>
    #define LOG_ERROR(category, msg) \
        ::RenderingSandbox::Logger::GetInstance().Error(category, msg, __FILE__, __LINE__)

    /// <summary>
    /// Fatalレベルのログを出力（conditionがfalseの時にログ出力してexit）
    /// デバッガがアタッチされている場合はDebugBreak()で停止
    /// </summary>
    #define LOG_FATAL(condition, category, msg) \
        do { \
            if (!(condition)) { \
                ::RenderingSandbox::Logger::GetInstance().Fatal(category, msg, __FILE__, __LINE__); \
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

    #define LOG_TRACE(category, msg)              ((void)0)
    #define LOG_DEBUG(category, msg)              ((void)0)
    #define LOG_INFO(category, msg)               ((void)0)
    #define LOG_WARNING(category, msg)            ((void)0)
    #define LOG_ERROR(category, msg)              ((void)0)
    #define LOG_FATAL(condition, category, msg)   ((void)0)

#endif // LOG_ENABLED
