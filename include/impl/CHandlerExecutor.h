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

class CHandlerExecutor
{
public:

    CHandlerExecutor() = default;

    virtual ~CHandlerExecutor() = default;

    CHandlerExecutor(CHandlerExecutor &&) = delete;

    CHandlerExecutor(const CHandlerExecutor &) = delete;

    CHandlerExecutor &operator=(CHandlerExecutor &&) = delete;

    CHandlerExecutor &operator=(const CHandlerExecutor &) = delete;

    [[noreturn]] virtual void Terminate(std::string_view message);

    virtual void HandleWarning(std::string_view message);

    virtual void HandleError(std::string_view message, const CAssertException &exception);

    virtual void Logs(std::string_view message);

    virtual void ShowMessage(std::string_view message);

    virtual char GetUserInput();

}; // class CHandlerExecutor

} // namespace dbgh
