/**
 * @file        CAssertHandler.cpp
 * @author      Argishty Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief       Implementation for CAssertHandler class.
 * @date        18-07-2020
 * @copyright   Copyright (c) 2020
 */

#include <map>
#include <sstream>
#include <cassert>

#include "CAssertHandler.h"

using namespace std::string_view_literals;

namespace dbgh::impl
{

namespace
{
const char* ToString(const EAssertLevel level)
{
    switch (level)
    {
        case EAssertLevel::Warning:
            return "WARNING";
        case EAssertLevel::Error:
            return "ERROR";
        case EAssertLevel::Debug:
            return "DEBUG";
        case EAssertLevel::Fatal:
            return "FATAL";
        case EAssertLevel::END_ENUM_:
            [[fallthrough]];
        default:
            return "[Unknown asset level]";
    }
}
}  // unnamed namespace

template<EAssertLevel T, std::enable_if_t<(EAssertLevel::Warning == T), int>>
inline void CAssertHandler::HandleAssert(
        const char* message, const char* expression, const char* file, TLine line, const char* function)
{
    CAssertConfig::Get().GetExecutor()->HandleWarning(margeAssertInfo(T, message, expression, file, line, function));
}

template<EAssertLevel T, std::enable_if_t<(EAssertLevel::Debug == T), int>>
inline void CAssertHandler::HandleAssert(
        const char* message, const char* expression, const char* file, TLine line, const char* function, bool& ignore)
{
    const auto action = waitForUserDecision();
    switch (action)
    {
        case EAssertAction::Abort:
            CAssertConfig::Get().GetExecutor()->Terminate(
                    margeAssertInfo(T, message, expression, file, line, function));
            break;
        case EAssertAction::Throw:
            throw CAssertException { message, expression, file, line, function };
            break;
        case EAssertAction::Debug:
            startDebugging();
            break;
        case EAssertAction::Ignore:
            return;
        case EAssertAction::IgnoreAll:
            ignore = true;
            break;
        default:
            assert(false);
    }
}

template<EAssertLevel T, std::enable_if_t<(EAssertLevel::Error == T), int>>
inline void CAssertHandler::HandleAssert(
        const char* message, const char* expression, const char* file, TLine line, const char* function)
{
    CAssertConfig::Get().GetExecutor()->HandleError(margeAssertInfo(T, message, expression, file, line, function)
                                                    , CAssertException { message, expression, file, line, function });
}

template<EAssertLevel T, std::enable_if_t<(EAssertLevel::Fatal == T), int>>
inline void CAssertHandler::HandleAssert(
        const char* message, const char* expression, const char* file, TLine line, const char* function)
{
    CAssertConfig::Get().GetExecutor()->Terminate(margeAssertInfo(T, message, expression, file, line, function));
}

std::string CAssertHandler::margeAssertInfo(
        EAssertLevel level, const char* message, const char* expression, const char* file, TLine line,
        const char* function)
{
    std::stringstream ss;
    ss << ToString(level) << " ASSERT:" << std::endl;
    ss << "  [file]:       " << file << std::endl;
    ss << "  [line]:       " << line << std::endl;
    ss << "  [function]:   " << function << std::endl;
    ss << "  [expression]: " << expression << std::endl;
    ss << "  [what]:       " << message << std::endl;
    ss << std::endl;
    return std::move(ss).str();
}

auto CAssertHandler::waitForUserDecision() -> EAssertAction
{
    const static std::map<char, EAssertAction> symbolToAction
            {
                    std::make_pair('b', EAssertAction::Abort),
                    std::make_pair('B', EAssertAction::Abort),
                    std::make_pair('d', EAssertAction::Debug),
                    std::make_pair('D', EAssertAction::Debug),
                    std::make_pair('i', EAssertAction::Ignore),
                    std::make_pair('I', EAssertAction::Ignore),
                    std::make_pair('a', EAssertAction::IgnoreAll),
                    std::make_pair('A', EAssertAction::IgnoreAll),
            };

    CAssertConfig::Get().GetExecutor()->ShowMessage("Press (I)gnore / Ignore (A)ll / (D)ebug / A(b)ort: \n"sv);

    for (;;)
    {
        char input =  CAssertConfig::Get().GetExecutor()->GetUserInput();
        auto actionIter = symbolToAction.find(input);
        if (std::end(symbolToAction) == actionIter)
        {
            CAssertConfig::Get().GetExecutor()->ShowMessage("ERROR: Invalid action, please try again.\n"sv);
            continue;
        }
        return actionIter->second;
    }
}

void CAssertHandler::startDebugging()
{
    throw SStartDebuggingException { };
}

template void
CAssertHandler::HandleAssert<EAssertLevel::Warning>(const char*, const char*, const char*, TLine, const char*);

template void CAssertHandler::HandleAssert<EAssertLevel::Debug>(
        const char*, const char*, const char*, TLine, const char*, bool&);

template void
CAssertHandler::HandleAssert<EAssertLevel::Error>(const char*, const char*, const char*, TLine, const char*);

template void
CAssertHandler::HandleAssert<EAssertLevel::Fatal>(const char*, const char*, const char*, TLine, const char*);

} // namespace dbgh::impl
