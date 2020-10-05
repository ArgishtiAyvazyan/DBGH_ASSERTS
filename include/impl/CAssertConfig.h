/**
 * @file        CHandlerExecutor.h
 * @author      Argishti Ayvazyan (ayvazyan.argishti@gmail.com)
 * @brief       Declaration for CAssertException class.
 * @date        27-09-2020
 * @copyright   Copyright (c) 2020
 */

#pragma once

#include <array>
#include <memory>
#include <exception>

#include "CHandlerExecutor.h"

namespace dbgh
{

enum class EAssertLevel : size_t
{
    /**
     * @brief Print the assertion message to std::cerr.
     */
    Warning,

    /**
     * @brief Print the assertion message to stderr and prompt the user for action.
     */
    Debug,

    /**
     * @brief Throw an CAssertionException.
     */
    Error,

    /**
     * @brief Abort the program.
     */
    Fatal,

    END_ENUM_
};

class CAssertConfig
{
    CAssertConfig();

    ~CAssertConfig();

public:

    CAssertConfig(CAssertConfig&&) noexcept = delete;

    CAssertConfig(const CAssertConfig&) = delete;

    CAssertConfig& operator=(CAssertConfig&&) noexcept = delete;

    CAssertConfig& operator=(const CAssertConfig&) = delete;

    static CAssertConfig& Get();

    [[maybe_unused]] void EnableAsserts(EAssertLevel level) noexcept;

    [[maybe_unused]] void DisableAsserts(EAssertLevel level) noexcept;

    [[nodiscard]] bool IsActiveAssert(EAssertLevel level) const noexcept;

    [[maybe_unused]] void SetExecutor(
            std::unique_ptr<dbgh::CHandlerExecutor> executor = std::make_unique<dbgh::CHandlerExecutor>());

    [[nodiscard]] dbgh::CHandlerExecutor* GetExecutor() const noexcept;

private:

    std::array<bool, static_cast<size_t>(EAssertLevel::END_ENUM_)> m_arrEnableFlags;

    std::unique_ptr<dbgh::CHandlerExecutor> m_pHandlerExecutor;

};

} // namespace dbgh

