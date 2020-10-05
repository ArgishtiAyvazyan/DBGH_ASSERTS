/**
 * @file        CAssertHandler.h
 * @author      Argishti Ayvazyan (ayvazyan.argishti@gmail.com)
 * @brief       Declaration for CAssertHandler class.
 * @date        18-07-2020
 * @copyright   Copyright (c) 2020
 */

#pragma once

#include <type_traits>
#include <memory>

#include "CAssertConfig.h"

#include "CHandlerExecutor.h"

namespace dbgh::impl
{

class CAssertHandler
{
    using TLine = decltype(__LINE__);

    enum class EAssertAction
    {
        Abort,
        Debug,
        Ignore,
        IgnoreAll,
        Throw
    }; // enum EAssertAction

public:

    struct SStartDebuggingException
    {
    };

public:
    CAssertHandler() = delete;

    ~CAssertHandler() = delete;

    CAssertHandler(CAssertHandler&&) noexcept = delete;

    CAssertHandler(const CAssertHandler&) = delete;

    CAssertHandler& operator=(CAssertHandler&&) = delete;

    CAssertHandler& operator=(const CAssertHandler&) = delete;

public:

    template<EAssertLevel T, std::enable_if_t<(EAssertLevel::Warning == T), int> = 0>
    static void HandleAssert(
            const char* message, const char* expression, const char* file, TLine line, const char* function);

    template<EAssertLevel T, std::enable_if_t<(EAssertLevel::Debug == T), int> = 0>
    static void HandleAssert(
            const char* message, const char* expression, const char* file, TLine line, const char* function,
            bool& ignore);

    template<EAssertLevel T, std::enable_if_t<(EAssertLevel::Error == T), int> = 0>
    static void HandleAssert(
            const char* message, const char* expression, const char* file, TLine line, const char* function);

    template<EAssertLevel T, std::enable_if_t<(EAssertLevel::Fatal == T), int> = 0>
    static void HandleAssert(
            const char* message, const char* expression, const char* file, TLine line, const char* function);

private:

    static EAssertAction waitForUserDecision();

    [[noreturn]] static void startDebugging();

    static std::string margeAssertInfo(
            EAssertLevel level, const char* message, const char* expression, const char* file, TLine line,
            const char* function);

private:


};


extern template void
CAssertHandler::HandleAssert<EAssertLevel::Warning>(const char*, const char*, const char*, TLine, const char*);

extern template void
CAssertHandler::HandleAssert<EAssertLevel::Debug>(const char*, const char*, const char*, TLine, const char*, bool&);

extern template void
CAssertHandler::HandleAssert<EAssertLevel::Error>(const char*, const char*, const char*, TLine, const char*);

extern template void
CAssertHandler::HandleAssert<EAssertLevel::Fatal>(const char*, const char*, const char*, TLine, const char*);

} // namespace dbgh
