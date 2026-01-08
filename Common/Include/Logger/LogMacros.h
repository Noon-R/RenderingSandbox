#pragma once

#include "Logger.h"
#include <format>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace RenderingSandbox {
    /// <summary>
    /// HRESULTからエラーメッセージを取得
    /// </summary>
    inline std::string GetHResultMessage(HRESULT hr) {
        wchar_t* messageBuffer = nullptr;
        DWORD size = FormatMessageW(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr,
            hr,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            reinterpret_cast<LPWSTR>(&messageBuffer),
            0,
            nullptr
        );

        std::string message;
        if (size > 0 && messageBuffer != nullptr) {
            // UTF-16からUTF-8に変換
            int utf8Size = WideCharToMultiByte(CP_UTF8, 0, messageBuffer, -1, nullptr, 0, nullptr, nullptr);
            if (utf8Size > 0) {
                std::string utf8Message(utf8Size - 1, '\0');
                WideCharToMultiByte(CP_UTF8, 0, messageBuffer, -1, &utf8Message[0], utf8Size, nullptr, nullptr);
                message = utf8Message;
                // 末尾の改行を削除
                while (!message.empty() && (message.back() == '\n' || message.back() == '\r')) {
                    message.pop_back();
                }
            }
            LocalFree(messageBuffer);
        }

        if (message.empty()) {
            message = "Unknown error";
        }

        return std::format("HRESULT 0x{:08X}: {}", static_cast<unsigned int>(hr), message);
    }
}

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

    // ==================================================
    // HRESULT用マクロ
    // ==================================================

    /// <summary>
    /// HRESULTが失敗していた場合にエラーログを出力
    /// 使用例: LOG_IF_FAILED("D3D12", hr, "Failed to create device")
    /// </summary>
    #define LOG_IF_FAILED(category, hr, msg) \
        do { \
            HRESULT _hr_result = (hr); \
            if (FAILED(_hr_result)) { \
                std::string _full_msg = std::string(msg) + " - " + ::RenderingSandbox::GetHResultMessage(_hr_result); \
                ::RenderingSandbox::Logger::GetInstance().Error(category, _full_msg, __FILE__, __LINE__); \
            } \
        } while(0)

    /// <summary>
    /// HRESULTの結果をログに出力（成功時はInfo、失敗時はError）
    /// 使用例: LOG_HRESULT("D3D12", hr, "Device creation result")
    /// </summary>
    #define LOG_HRESULT(category, hr, msg) \
        do { \
            HRESULT _hr_result = (hr); \
            std::string _full_msg = std::string(msg) + " - " + ::RenderingSandbox::GetHResultMessage(_hr_result); \
            if (FAILED(_hr_result)) { \
                ::RenderingSandbox::Logger::GetInstance().Error(category, _full_msg, __FILE__, __LINE__); \
            } else { \
                ::RenderingSandbox::Logger::GetInstance().Info(category, _full_msg, __FILE__, __LINE__); \
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
    #define LOG_IF_FAILED(category, hr, msg)      ((void)0)
    #define LOG_HRESULT(category, hr, msg)        ((void)0)

#endif // LOG_ENABLED
