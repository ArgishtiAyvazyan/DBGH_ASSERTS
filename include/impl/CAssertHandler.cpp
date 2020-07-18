#include <iostream>
#include <map>
#include <cassert>

#include "CAssertHandler.h"
#include "CAssertException.h"

namespace dbgh
{
namespace impl
{

namespace
{
    const char* ToString(const EAssertLevel level)
    {
        switch (level)
        {
        case EAssertLevel::Warning: return "WARNING";
        case EAssertLevel::Error:   return "ERROR";
        case EAssertLevel::Debug:   return "DEBUG";
        case EAssertLevel::Fatal:   return "FATAL";
        case EAssertLevel::__END_ENUM__: [[fallthrough]];
        default:                    return "[Unknown asset level]";
        }
    }
}  // unnamed namespace

template<EAssertLevel T, std::enable_if_t<(EAssertLevel::Warning == T), int>>
inline void CAssertHandler::HandleAssert(const char* message, const char* expression, const char* file, TLine line, const char* function)
{
    showAssertInfo(T, message, expression, file, line, function);

}

template<EAssertLevel T, std::enable_if_t<(EAssertLevel::Debug == T), int>>
inline void CAssertHandler::HandleAssert(const char* message, const char* expression, const char* file, TLine line, const char* function, bool& ignore)
{
    showAssertInfo(T, message, expression, file, line, function);
    const auto action = waitForUserDecision();
    switch (action)
    {
    case EAssertAction::Abort:
        abort();
        break;
    case EAssertAction::Throw:
        throwAssertException(message, expression, file, line, function);
        break;
    case EAssertAction::Debug:
        startDebugging();
        break;
    case EAssertAction::Ignore:
        ignore = true;
        return;
    case EAssertAction::IgnoreAll:
        CAssertConfig::Get().DisableAsserts(T);
        break;
    }
}

template<EAssertLevel T, std::enable_if_t<(EAssertLevel::Error == T), int>>
inline void CAssertHandler::HandleAssert(const char* message, const char* expression, const char* file, TLine line, const char* function)
{
    showAssertInfo(T, message, expression, file, line, function);

}

template<EAssertLevel T, std::enable_if_t<(EAssertLevel::Fatal == T), int>>
inline void CAssertHandler::HandleAssert(const char* message, const char* expression, const char* file, TLine line, const char* function)
{
    showAssertInfo(T, message, expression, file, line, function);
    std::cout << std::endl;
}


void CAssertHandler::showAssertInfo(EAssertLevel level, const char* message, const char* expression, const char* file, TLine line, const char* function)
{
    std::cout << ToString(level) << " ASSERT:" << std::endl;
    std::cout << "  [file]:       " << file << std::endl;
    std::cout << "  [line]:       " << line << std::endl;
    std::cout << "  [function]:   " << function << std::endl;
    std::cout << "  [expression]: " << expression << std::endl;
    std::cout << "  [what]:       " << message << std::endl;
    std::cout << std::endl;
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

    std::cerr << "Press (I)gnore / Ignore (A)ll / (D)ebug / A(b)ort: " << std::endl;

    for ( ;; )
    {
        char input;
        std::cin >> input;
        auto actionIter = symbolToAction.find(input);
        if (std::end(symbolToAction) == actionIter)
        {
            std::cerr << "ERROR: Invalid action, please try again." << std::endl;
            continue;
        }
        return actionIter->second;
    }
}

void CAssertHandler::abort()
{
    std::abort();
}

void CAssertHandler::throwAssertException(const char* message, const char* expression, const char* file, const TLine line, const char* function)
{
    throw CAssertException { message, expression, file, line, function };
}

void CAssertHandler::startDebugging()
{
    throw SStartDebuggingException {};
}

template void CAssertHandler::HandleAssert<EAssertLevel::Warning>(const char*
    , const char*, const char*, TLine, const char*);

template void CAssertHandler::HandleAssert<EAssertLevel::Debug>(const char*
    , const char*, const char*, TLine, const char*, bool&);

template void CAssertHandler::HandleAssert<EAssertLevel::Error>(const char*
    , const char*, const char*, TLine, const char*);

template void CAssertHandler::HandleAssert<EAssertLevel::Fatal>(const char*
    , const char*, const char*, TLine, const char*);

} // namespace impl
} // namespace dbgh