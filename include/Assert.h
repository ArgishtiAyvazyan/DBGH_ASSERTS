/**
 * @file        CAssertHandler.h
 * @author      Argishti Ayvazyan (ayvazyan.argishti@gmail.com)
 * @brief       Declaration for asserts.
 * @date        18-07-2020
 * @copyright   Copyright (c) 2020
 */

#pragma once

#include "impl/CAssertException.h"
#include "impl/CAssertConfig.h"
#include "impl/CAssertHandler.h"


#ifdef _MSC_VER
#define START_DEBUGGING  __debugbreak()
#else
#define START_DEBUGGING __asm__ volatile("int $0x03")
#endif

#define IMPL_DBGH_ASSERT(_level_, _expression_, _message_)                                                                             \
    if ( dbgh::CAssertConfig::Get().IsActiveAssert(_level_) && ! bool(_expression_) )                                                  \
    {                                                                                                                                  \
        dbgh::impl::CAssertHandler::HandleAssert<_level_>(_message_, #_expression_ , __FILE__, __LINE__, __func__);                    \
    }                                                                                                                                  \
    (void) 0

#define IMPL_DBGH_ASSERT_DEBUG(_level_, _expression_, _message_)                                                                       \
    {                                                                                                                                  \
        static bool __ignore { false };                                                                                                \
        if ( (! __ignore) && (dbgh::CAssertConfig::Get().IsActiveAssert(_level_)) && (! bool(_expression_)) )                          \
        {                                                                                                                              \
            try {                                                                                                                      \
                dbgh::impl::CAssertHandler::HandleAssert<_level_>(_message_, #_expression_ , __FILE__, __LINE__, __func__, __ignore);  \
            } catch (const dbgh::impl::CAssertHandler::SStartDebuggingException) {                                                     \
                 START_DEBUGGING;                                                                                                      \
            }                                                                                                                          \
        }                                                                                                                              \
    } (void) 0

#define ASSERT_WARNING(_expression_, _message_)  IMPL_DBGH_ASSERT(dbgh::EAssertLevel::Warning, _expression_, _message_)
#define ASSERT_DEBUG(_expression_, _message_)    IMPL_DBGH_ASSERT_DEBUG(dbgh::EAssertLevel::Debug, _expression_, _message_)
#define ASSERT_ERROR(_expression_, _message_)    IMPL_DBGH_ASSERT(dbgh::EAssertLevel::Error, _expression_, _message_)
#define ASSERT_FATAL(_expression_, _message_)    IMPL_DBGH_ASSERT(dbgh::EAssertLevel::Fatal, _expression_, _message_)
