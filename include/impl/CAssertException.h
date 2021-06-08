/**
 * @file        CAssertException.h
 * @author      Argishti Ayvazyan (ayvazyan.argishti@gmail.com)
 * @brief       Declaration for CAssertException class.
 * @date        18-07-2020
 * @copyright   Copyright (c) 2020
 */

#pragma once

#include <string>
#include <string_view>


namespace dbgh
{
/**
 * @internal
 * @brief The value type for containing a code line number.
 */
using TLine = decltype(__LINE__);

/**
 * @class CAssertException
 * @brief The class for all exceptional conditions for asserts.
 */
class CAssertException : public std::exception
{
public:

    /**
     * @brief               Construct a new CAssertException object.
     *
     * @param[in] message       The error description.
     * @param[in] expression    Not a valid expression that threw the exception, as a string.
     * @param[in] file          The filename that contains the code that is throwing an exception.
     * @param[in] line          The line number in the file that contains the code that is throwing an exception.
     * @param[in] function      The function that contains the code that is throwing an exception.
     */
    CAssertException(
            std::string message,
            const char* expression,
            const char* file,
            TLine line,
            const char* function);

    /**
     * @brief   Gets a message that describes the current exception.
     *
     * @return  std::string_view The error message that explains the \n
     *           reason for the exception, or an empty string_view ("")
     */
    [[nodiscard]] std::string_view Message() const noexcept;


    /**
     * @brief   Gets the filename that contains the code that is throwing an exception.
     *
     * @return  std::string_view The file name, or Empty string if the file name \n
     *           cannot be determined.
     */
    [[nodiscard]] std::string_view FileName() const noexcept;

    /**
     * @brief   Gets the line number in the file that contains the code that is throwing an exception.
     *
     * @return  std::string_view The file line number, or 0 (zero) if the file line \n
     *           number cannot be determined.
     */
    [[nodiscard]] TLine LineNumber() const noexcept;

    /**
     * @brief   Gets the function that contains the code that is throwing an exception.
     *
     * @return  std::string_view The function name, or Empty string if the function name \n
     *           cannot be determined.
     */
    [[nodiscard]] std::string_view Function() const noexcept;

    /**
     * @brief   Gets the unacceptable expression that threw the exception.
     *
     * @return  std::string_view The expression, or Empty string if the expression \n
     *           cannot be determined.
     */
    [[nodiscard]] std::string_view Expression() const noexcept;


    /**
     * @brief   Gets a message that describes the current exception.
     *
     * @return  const char* The error message that explains the \n
     *           reason for the exception, or nullptr
     */
    [[nodiscard]] const char* what() const noexcept override;

private:

    /**
     * @internal
     * @brief   The error description.
     */
    std::string m_strMessage;

    /**
     * @internal
     * @brief   The filename that contains the code that is throwing an exception.
     */
    const char* m_strFileName;

    /**
     * @internal
     * @brief   Not a valid expression that threw the exception, as a string.
     */
    const char* m_strExpression;

    /**
     * @internal
     * @brief   The function that contains the code that is throwing an exception.
     */
    const char* m_strFunction;

    /**
     * @internal
     * @brief The line number in the file that contains the code that is throwing an exception.
     */
    TLine m_iLineNumber;

}; // class CAssertException
} // namespace dbgh

