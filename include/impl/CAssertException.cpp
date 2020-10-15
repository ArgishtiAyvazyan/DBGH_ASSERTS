/**
 * @file        CAssertException.cpp
 * @author      Argishty Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief       Implementation for CAssertException class.
 * @date        18-07-2020
 * @copyright   Copyright (c) 2020
 */

#include "CAssertException.h"


namespace dbgh
{

using namespace std::string_literals;

CAssertException::CAssertException(
        const char* message,
        const char* expression,
        const char* file,
        TLine line,
        const char* function) noexcept
        : std::exception (),
        m_strMessage(message),
        m_strFileName(file),
        m_strExpression(expression),
        m_strFunction(function),
        m_iLineNumber(line)
{ }

std::string_view CAssertException::Message() const noexcept
{
    return m_strMessage;
}

std::string_view CAssertException::FileName() const noexcept
{
    return m_strFileName;
}

TLine CAssertException::LineNumber() const noexcept
{
    return m_iLineNumber;
}

std::string_view CAssertException::Function() const noexcept
{
    return m_strFunction;
}

std::string_view CAssertException::Expression() const noexcept
{
    return m_strExpression;
}

const char* CAssertException::what() const noexcept
{
    return m_strMessage;
}

} // namespace dbgh
