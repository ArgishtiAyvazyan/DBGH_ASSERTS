#pragma once
#include <array>

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

    __END_ENUM__
};

class CAssertConfig
{
    CAssertConfig();
    ~CAssertConfig() = default;
    CAssertConfig(CAssertConfig&&) noexcept = delete;
    CAssertConfig(const CAssertConfig&) = delete;
    CAssertConfig& operator=(CAssertConfig&&) noexcept = delete;
    CAssertConfig& operator=(const CAssertConfig&) = delete;

public:

    static CAssertConfig& Get();

    void EnableAsserts(EAssertLevel level) noexcept;

    void DisableAsserts(EAssertLevel level) noexcept;

    bool IsActiveAssert(EAssertLevel level) const noexcept;

private:

    std::array<bool, static_cast<size_t>(EAssertLevel::__END_ENUM__)> m_arrEnableFlags;
};

inline CAssertConfig::CAssertConfig()
    : m_arrEnableFlags
    {
        true, // Warning default value.
        true, // Debug default value.
        true, // Error default value.
        false // Fatal default value.
    }
{ }

inline CAssertConfig& CAssertConfig::Get()
{
    static CAssertConfig uniqueInstance;
    return uniqueInstance;
}

inline void CAssertConfig::EnableAsserts(const EAssertLevel level) noexcept
{
    m_arrEnableFlags[static_cast<size_t>(level)] = true;
}

inline void CAssertConfig::DisableAsserts(const EAssertLevel level) noexcept
{
    m_arrEnableFlags[static_cast<size_t>(level)] = false;
}

inline bool CAssertConfig::IsActiveAssert(const EAssertLevel level) const noexcept
{
    return m_arrEnableFlags[static_cast<size_t>(level)];
}

} // namespace dbgh

