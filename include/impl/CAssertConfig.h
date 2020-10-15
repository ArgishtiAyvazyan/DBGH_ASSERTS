/**
 * @file        CAssertConfig.h
 * @author      Argishti Ayvazyan (ayvazyan.argishti@gmail.com)
 * @brief       Declaration for CAssertConfig class.
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

/**
 * @enum       EAssertLevel
 * @brief      The described types for assertions.
 */
enum class EAssertLevel : size_t
{
    /**
     * @brief   The enum value mapped to \ref ASSERT_WARNING assert.
     */
    Warning,

    /**
     * @brief   The enum value mapped to \ref ASSERT_DEBUG assert.
     */
    Debug,

    /**
     * @brief   The enum value mapped to \ref ASSERT_ERROR assert.
     */
    Error,

    /**
     * @brief   The enum value mapped to \ref ASSERT_FATAL assert.
     */
    Fatal,

    /**
     * @internal
     * @breaf   An enumeration value that indicates the end of the enumeration.
     */
    END_ENUM_
};


/**
 * @class      CAssertConfig
 * @brief      This singleton class describes an assert configuration.
 *
 * @details    The CAssertConfig class holds the configuration and state of an Assertions.
 *              Allows you to enable or disable specific types of Assertions.
 * @example    dbgh::CAssertConfig::Get().EnableAsserts(dbgh::EAssertLevel::Fatal);
 *             dbgh::CAssertConfig::Get().DisableAsserts(dbgh::EAssertLevel::Debug);
 *
 * @details    Allows to set of a new executor which defines assertions behavior.
 * @example    class NewExecutor : public dbgh::CHandlerExecutor { ... };
 *             dbgh::CAssertConfig::Get().SetExecutor(std::make_unique<NewExecutor>());
 */
class CAssertConfig
{
    CAssertConfig();

    ~CAssertConfig();

public:

    CAssertConfig(CAssertConfig&&) noexcept = delete;

    CAssertConfig(const CAssertConfig&) = delete;

    CAssertConfig& operator=(CAssertConfig&&) noexcept = delete;

    CAssertConfig& operator=(const CAssertConfig&) = delete;

    /**
     * @brief      Gets a reference to the singleton CAssertConfig object.
     *
     * @return     The reference to the object.
     */
    static CAssertConfig& Get();


    /**
     * @brief      Enables the assert a given type.
     *
     * @example    dbgh::CAssertConfig::Get().EnableAsserts(dbgh::EAssertLevel::Fatal);
     *
     * @param[in]  level  The type of assert. Types defined in enum \ref dbgh::EAssertLevel.
     */
    [[maybe_unused]] void EnableAsserts(EAssertLevel level) noexcept;

    /**
     * @brief      Disables the assert a given type.
     *
     * @example    dbgh::CAssertConfig::Get().DisableAsserts(dbgh::EAssertLevel::Fatal);
     *
     * @param[in]  level  The type of assert. Types defined in enum \ref dbgh::EAssertLevel.
     */
    [[maybe_unused]] void DisableAsserts(EAssertLevel level) noexcept;


    /**
     * @internal
     * @brief      Determines whether the specified level is active assert.
     *
     * @param[in]  level  The level
     *
     * @return     True if the asserts of a given type are active, False otherwise.
     */
    [[nodiscard]] bool IsActiveAssert(EAssertLevel level) const noexcept;

    /**
     * @brief      Sets the new executor.
     *
     * @details    Executor defines the behavior of the assertion, if you need to change their
     *              behavior or add new features, you need to create a class that will inherit
     *              from dbgh::CHandlerExecutor and override the virtual functions that are
     *              responsible for the behavior and set a new executor in \ref dbgh::CAssertConfig.
     *              For example, you can add a stack trace, add a log file, and more.
     *
     * @note       The more details you can see in the documentation for dbgh::CAssertConfig.
     * @example     class NewExecutor : public dbgh::CHandlerExecutor { ... };
     *              dbgh::CAssertConfig::Get().SetExecutor(std::make_unique<NewExecutor>());
     *
     * @note       SetExecutor without arguments resets the current executor to default state.
     * @example    dbgh::CAssertConfig::Get().SetExecutor();
     *
     * @throw      std::invalid_argument exception if the new executor is null.
     *              The exception message is "Executor cannot be null."
     *
     * @param[in]  executor  The unique pointer to the new executor.
     */
    [[maybe_unused]] void SetExecutor(
            std::unique_ptr<dbgh::CHandlerExecutor> executor = std::make_unique<dbgh::CHandlerExecutor>());

    /**
     * @brief      Gets the raw pointer to the current executor.
     *
     * @return     The raw pointer to the executor.
     */
    [[nodiscard]] dbgh::CHandlerExecutor* GetExecutor() const noexcept;

private:

    /**
     * @internal
     * @brief      An array that stores the state of the assertion (enabled(true) or disabled(false)).
     */
    std::array<bool, static_cast<size_t>(EAssertLevel::END_ENUM_)> m_arrEnableFlags;

    /**
     * @internal
     * @brief      The pointer to executor.
     */
    std::unique_ptr<dbgh::CHandlerExecutor> m_pHandlerExecutor;

};

} // namespace dbgh

