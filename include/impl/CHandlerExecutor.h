/**
 * @file        CHandlerExecutor.h
 * @author      Argishti Ayvazyan (ayvazyan.argishti@gmail.com)
 * @brief       Declaration for CHandlerExecutor class.
 * @date        26-09-2020
 * @copyright   Copyright (c) 2020
 */

#pragma once

#include <string_view>

#include "CAssertException.h"

namespace dbgh
{

/**
 * @class       CHandlerExecutor
 * @brief       This class describes behaving for assertions.
 *
 * @details     Executor defines the behavior of the assertion, if you need to change their
 *              behavior or add new features, you need to create a class that will inherit
 *              from dbgh::CHandlerExecutor and override the virtual functions that are
 *              responsible for the behavior and set a new executor in \ref dbgh::CAssertConfig.
 *              For example, you can add a stack trace, add a log file, and more.
 *
 * @example     class NewExecutor : public dbgh::CHandlerExecutor { ... };
 *              dbgh::CAssertConfig::Get().SetExecutor(std::make_unique<NewExecutor>());
 */
class CHandlerExecutor
{
public:

    CHandlerExecutor() = default;

    virtual ~CHandlerExecutor() = default;

    CHandlerExecutor(CHandlerExecutor &&) = delete;

    CHandlerExecutor(const CHandlerExecutor &) = delete;

    CHandlerExecutor &operator=(CHandlerExecutor &&) = delete;

    CHandlerExecutor &operator=(const CHandlerExecutor &) = delete;

    /**
     * @brief      The terminator for asserts.
     *
     * @details    After the assertion failure where it is necessary to terminate the program execution, Terminate is used.
     *              By default writes the specified string value, using CHandlerExecutor::Logs then calls std::terminate.
     *
     * @note       To change or add new behavior, defined the new class inherits from
     *              \ref dbgh::CHandlerExecutor and override this method, and set in dbgh::CAssertConfig.
     *             For example, possible to add a stack trace logging or notify other processes, and so on.
     *
     * @example    void Terminate(std::string_view message) override
     *             {
     *                 std::stringstream ss;
     *                 ss << boost::stacktrace::stacktrace() << std::endl;
     *                 ss << message << std::endl;
     *                 Logs(ss.str());
     *                 std::terminate();
     *             }
     *
     * @param[in]  message  The message for logging.
     */
    [[noreturn]] virtual void Terminate(std::string_view message);

    /**
     * @brief      The handler for warning assert.
     *
     * @details    By default writes the message using \ref CHandlerExecutor::Logs.
     *
     * @note       To change or add new behavior, defined the new class inherits from
     *              \ref dbgh::CHandlerExecutor and override this method, and set in dbgh::CAssertConfig.
     *             For example, possible to add a stack trace logging or notify other processes, and so on.
     *
     * @example    void HandleWarning(std::string_view message) override
     *             {
     *                 std::stringstream ss;
     *                 ss << boost::stacktrace::stacktrace() << std::endl;
     *                 ss << message << std::endl;
     *                 Logs(ss.str());
     *             }
     *
     * @param[in]  message  The message for logging.
     */
    virtual void HandleWarning(std::string_view message);

    /**
     * @brief      The handler for error assert.
     *
     * @details    By default writes the message using \ref CHandlerExecutor::Logs and throw the given exception.
     *
     * @note       To change or add new behavior, defined the new class inherits from
     *              \ref dbgh::CHandlerExecutor and override this method, and set in dbgh::CAssertConfig.
     *             For example, possible to add a stack trace logging or notify other processes, and so on.
     *
     * @example    void HandleError(std::string_view message, const CAssertException &exception) override
     *             {
     *                 std::stringstream ss;
     *                 ss << boost::stacktrace::stacktrace() << std::endl;
     *                 ss << message << std::endl;
     *                 Logs(ss.str());
     *                 throw exception;
     *             }
     *
     * @param[in]  message  The message for logging.
     */
    [[noreturn]] virtual void HandleError(std::string_view message, const CAssertException &exception);

    /**
     * @brief      The Logs method defines a method for logging information about violated assertions.
     *
     * @details    By default writes the specified string value, followed by the current line terminator,
     *              to the standard error output stream (std::cerr).
     *
     * @note       To change or add a new way for logging, defined the new class inherits from
     *              \ref dbgh::CHandlerExecutor and override this method, and set in dbgh::CAssertConfig.
     *             For example, possible to add a file for logging or notify other processes, and so on.
     *
     * @example    void Logs(std::string_view message) override
     *             {
     *                 std::fstream { "asserts.log", std::ios_base::app } << message << std::endl;
     *             }
     *
     * @param[in]  message  The message for logging.
     */
    virtual void Logs(std::string_view message);

    /**
     * @brief      A ShowMessage mostly used for short-term tasks and brief communications with the user.
     *
     * @details    By default writes the specified string value, followed by the current line terminator,
     *              to the standard output stream (std::cout).
     *
     * @note       To change, defined the new class inherits from \ref dbgh::CHandlerExecutor and override
     *              this method, and set in dbgh::CAssertConfig.
     *             For example, possible to use dialog windows in the GUI.
     *
     * @example    void ShowMessage(std::string_view message) override
     *             {
     *                 QMessageBox msgBox;
     *                 msgBox.setText(message);
     *                 msgBox.exec();
     *             }
     *
     * @param[in]  message  The message
     */
    virtual void ShowMessage(std::string_view message);

    /**
     * @brief      Gets the user input.
     *
     * @details    By default read the specified char value, using the standard input (std::cin).
     *
     * @note       To change, defined the new class inherits from \ref dbgh::CHandlerExecutor and override
     *              this method, and set in dbgh::CAssertConfig.
     *             For example, possible to get input using dialog windows.
     *
     * @return     The user input.
     */
    virtual char GetUserInput();

    /**
     * @brief      The pre handle for ASSERT_DEBUG.
     *
     * @details    By default empty.
     *
     * @note       To add new behavior, defined the new class inherits from
     *              \ref dbgh::CHandlerExecutor and override this method, and set in dbgh::CAssertConfig.
     *             For example, possible to add a stack trace logging or notify other processes, and so on.
     *
     * @example    void DebugPreCall(std::string_view message, const CAssertException &exception) override
     *             {
     *                 std::stringstream ss;
     *                 ss << boost::stacktrace::stacktrace() << std::endl;
     *                 ss << message << std::endl;
     *                 Logs(ss.str());
     *             }
     */
    virtual void DebugPreCall();

}; // class CHandlerExecutor

} // namespace dbgh
