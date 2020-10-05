/**
 * @file        CAssertConfig.cpp
 * @author      Argishti Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief       Implementation for CAssertException class.
 * @date        27-09-2020
 * @copyright   Copyright (c) 2020
 */

#include <stdexcept>

#include "CAssertConfig.h"

namespace dbgh
{

CAssertConfig::CAssertConfig()
        : m_arrEnableFlags {
        true,    // Warning default value.
        true,    // Debug default value.
        true,    // Error default value.
        false }, // Fatal default value.
    m_pHandlerExecutor { std::make_unique<dbgh::CHandlerExecutor>() }
{ }


CAssertConfig::~CAssertConfig() = default;

CAssertConfig& CAssertConfig::Get()
{
    static CAssertConfig uniqueInstance;
    return uniqueInstance;
}

[[maybe_unused]] void CAssertConfig::EnableAsserts(const EAssertLevel level) noexcept
{
    m_arrEnableFlags[static_cast<size_t>(level)] = true;
}

[[maybe_unused]] void CAssertConfig::DisableAsserts(const EAssertLevel level) noexcept
{
    m_arrEnableFlags[static_cast<size_t>(level)] = false;
}

bool CAssertConfig::IsActiveAssert(const EAssertLevel level) const noexcept
{
    return m_arrEnableFlags[static_cast<size_t>(level)];
}

[[maybe_unused]] void CAssertConfig::SetExecutor(std::unique_ptr<dbgh::CHandlerExecutor> executor)
{
    if (nullptr == executor)
    {
        throw std::invalid_argument { "Executor cannot be null." };
    }
    m_pHandlerExecutor = std::move(executor);
}

CHandlerExecutor* CAssertConfig::GetExecutor() const noexcept
{
    return m_pHandlerExecutor.get();
}

} // namespace dbgh

