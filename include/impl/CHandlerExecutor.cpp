/**
 * @file        CHandlerExecutor.h
 * @author      Argishti Ayvazyan (ayvazyan.argishti@gmail.com)
 * @brief       Implementation for CHandlerExecutor class.
 * @date        26-09-2020
 * @copyright   Copyright (c) 2020
 */


#include <iostream>

#include "CHandlerExecutor.h"

#include "CAssertConfig.h"

namespace dbgh
{

void CHandlerExecutor::Terminate(std::string_view message)
{
    Logs(message);
    std::terminate();
}

void CHandlerExecutor::HandleWarning(std::string_view message)
{
    Logs(message);
}

void CHandlerExecutor::HandleError(std::string_view message, const CAssertException& exception)
{
    Logs(message);
    throw exception;
}

void CHandlerExecutor::Logs(std::string_view message)
{
    std::cerr << message << std::endl;
}

void CHandlerExecutor::ShowMessage(std::string_view message)
{
    std::cout << message << std::endl;
}

char CHandlerExecutor::GetUserInput()
{
    char ch = 0;
    std::cin >> ch;
    return ch;
}

} // namespace dbgh
