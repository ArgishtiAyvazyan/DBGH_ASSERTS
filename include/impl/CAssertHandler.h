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

    /**
     * @internal
     * @brief The value type for containing a code line number.
     */
    using TLine = decltype(__LINE__);

    /**
     * @internal
     * @enum       EAssertAction
     * @brief      This enum describes available action to debugging assert.
     */
    enum class EAssertAction
    {
        Abort,
        Debug,
        Ignore,
        IgnoreForever,
        Throw
    }; // enum EAssertAction

public:

    /**
     * @internal
     * @struct     SStartDebuggingException
     * @brief      The empty exception, using for the invite for start debugging.
     */
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

    /**
     * @internal
     * @brief      The internal handler for the assertion.
     *             Template function specialization for Warning assert.
     *
     * @param[in]  message       The error description.
     * @param[in]  expression    Expression to be evaluated, as a string.
     * @param[in]  file          The filename that contains the code is a failed assertion.
     * @param[in]  line          The line number in the file that contains the code that is failed assertion.
     * @param[in]  function      The function that contains the code is a failed assertion.
     *
     * @enum       T             The \ref EAssertLevel enum value, type of assert.
     */
    template<EAssertLevel T, std::enable_if_t<(EAssertLevel::Warning == T), int> = 0>
    static void HandleAssert(
            std::string message, const char* expression, const char* file, TLine line, const char* function);

    /**
     * @internal
     * @brief      The internal handler for the assertion.
     *             Template function specialization for Debug assert.
     *
     * @param[in]  message       The error description.
     * @param[in]  expression    Expression to be evaluated, as a string.
     * @param[in]  file          The filename that contains the code is a failed assertion.
     * @param[in]  line          The line number in the file that contains the code that is failed assertion.
     * @param[in]  function      The function that contains the code is a failed assertion.
     *
     * @enum       T             The \ref EAssertLevel enum value, type of assert.
     */
    template<EAssertLevel T, std::enable_if_t<(EAssertLevel::Debug == T), int> = 0>
    static void HandleAssert(
            std::string message, const char* expression, const char* file, TLine line, const char* function,
            bool& ignore);

    /**
     * @internal
     * @brief      The internal handler for the assertion.
     *             Template function specialization for Error assert.
     *
     * @param[in]  message       The error description.
     * @param[in]  expression    Expression to be evaluated, as a string.
     * @param[in]  file          The filename that contains the code is a failed assertion.
     * @param[in]  line          The line number in the file that contains the code that is failed assertion.
     * @param[in]  function      The function that contains the code is a failed assertion.
     *
     * @enum       T             The \ref EAssertLevel enum value, type of assert.
     */
    template<EAssertLevel T, std::enable_if_t<(EAssertLevel::Error == T), int> = 0>
    static void HandleAssert(
            std::string message, const char* expression, const char* file, TLine line, const char* function);

    /**
     * @internal
     * @brief      The internal handler for the assertion.
     *             Template function specialization for Fatal assert.
     *
     * @param[in]  message       The error description.
     * @param[in]  expression    Expression to be evaluated, as a string.
     * @param[in]  file          The filename that contains the code is a failed assertion.
     * @param[in]  line          The line number in the file that contains the code that is failed assertion.
     * @param[in]  function      The function that contains the code is a failed assertion.
     *
     * @enum       T             The \ref EAssertLevel enum value, type of assert.
     */
    template<EAssertLevel T, std::enable_if_t<(EAssertLevel::Fatal == T), int> = 0>
    static void HandleAssert(
            std::string message, const char* expression, const char* file, TLine line, const char* function);

private:

    /**
     * @internal
     * @brief      { function_description }
     *
     * @return     The e assert action.
     */
    static EAssertAction waitForUserDecision();

    /**
     * @internal
     * @brief      Starts a debugging.
     *
     * @throw      SStartDebuggingException the signal for starting debugging.
     */
    [[noreturn]] static void startDebugging();

    /**
     * @internal
     * @brief      Merges information about assertion.
     *
     * @param[in]  level         The assert level.
     * @param[in]  message       The error description.
     * @param[in]  expression    Expression to be evaluated, as a string.
     * @param[in]  file          The filename that contains the code is a failed assertion.
     * @param[in]  line          The line number in the file that contains the code that is failed assertion.
     * @param[in]  function      The function that contains the code is a failed assertion.
     *
     * @return     Merged information as a string.
     */
    static std::string margeAssertInfo(
            EAssertLevel level, const std::string& message, const char* expression, const char* file, TLine line,
            const char* function);

private:


};


extern template void
CAssertHandler::HandleAssert<EAssertLevel::Warning>(std::string, const char*, const char*, TLine, const char*);

extern template void
CAssertHandler::HandleAssert<EAssertLevel::Debug>(std::string, const char*, const char*, TLine, const char*, bool&);

extern template void
CAssertHandler::HandleAssert<EAssertLevel::Error>(std::string, const char*, const char*, TLine, const char*);

extern template void
CAssertHandler::HandleAssert<EAssertLevel::Fatal>(std::string, const char*, const char*, TLine, const char*);

} // namespace dbgh
