#include <iostream>

#include "DBGHAssert.h"

namespace
{

class DummyExecutor : public dbgh::CHandlerExecutor
{
public:
    void Terminate([[maybe_unused]] std::string_view message) override
    {
        s_bTerminateCalled = true;
    }

    void HandleWarning([[maybe_unused]] std::string_view message) override
    {
        s_bHandleWarningCalled = true;
    }

    void HandleError(
            [[maybe_unused]] std::string_view message,
            [[maybe_unused]] const dbgh::CAssertException& exception) override
    {
        s_bHandleErrorCalled = true;
    }

    void Logs([[maybe_unused]] std::string_view message) override
    {
    }

    void ShowMessage([[maybe_unused]] std::string_view message) override
    {
    }

    char GetUserInput() override
    {
        return s_cUserInput;
    }

    static inline bool s_bTerminateCalled = false;
    static inline bool s_bHandleWarningCalled = false;
    static inline bool s_bHandleErrorCalled = false;
    static inline char s_cUserInput = 'i';
};

}

#define TEST_ASSERT(exp) if (!bool(exp))            \
{ std::cout << "FAIL: " << __LINE__ << std::endl; } \
else { std::cout << "PASS" << std::endl; }          \
(void)0

void TestFatalAssert()
{
    std::cout << "Start Terminate testing." << std::endl;
    dbgh::CAssertConfig::Get().EnableAsserts(dbgh::EAssertLevel::Fatal);
    dbgh::CAssertConfig::Get().SetExecutor(std::make_unique<DummyExecutor>());

    DummyExecutor::s_bTerminateCalled = false;
    ASSERT_FATAL(2 * 2 == 4, "PASS");
    TEST_ASSERT(DummyExecutor::s_bTerminateCalled == false);
    ASSERT_FATAL(2 * 3 == 4, "FAIL");
    TEST_ASSERT(DummyExecutor::s_bTerminateCalled == true);
    DummyExecutor::s_bTerminateCalled = false;
    ASSERT_FATAL(2 * 2 == 4, "PASS");
    TEST_ASSERT(DummyExecutor::s_bTerminateCalled == false);

    dbgh::CAssertConfig::Get().DisableAsserts(dbgh::EAssertLevel::Fatal);
    ASSERT_FATAL(2 * 2 == 4, "PASS");
    TEST_ASSERT(DummyExecutor::s_bTerminateCalled == false);
    ASSERT_FATAL(2 * 3 == 4, "FAIL");
    TEST_ASSERT(DummyExecutor::s_bTerminateCalled == false);
    DummyExecutor::s_bTerminateCalled = false;
    std::cout << "End Terminate testing." << std::endl << std::endl;

    dbgh::CAssertConfig::Get().SetExecutor();
}

void TestWarningAssert()
{
    std::cout << "Start Warning Assert testing." << std::endl;
    dbgh::CAssertConfig::Get().EnableAsserts(dbgh::EAssertLevel::Warning);
    dbgh::CAssertConfig::Get().SetExecutor(std::make_unique<DummyExecutor>());

    DummyExecutor::s_bHandleWarningCalled = false;
    ASSERT_WARNING(2 * 2 == 4, "PASS");
    TEST_ASSERT(DummyExecutor::s_bHandleWarningCalled == false);
    ASSERT_WARNING(2 * 3 == 4, "FAIL");
    TEST_ASSERT(DummyExecutor::s_bHandleWarningCalled == true);
    DummyExecutor::s_bHandleWarningCalled = false;
    ASSERT_WARNING(2 * 2 == 4, "PASS");
    TEST_ASSERT(DummyExecutor::s_bHandleWarningCalled == false);

    dbgh::CAssertConfig::Get().DisableAsserts(dbgh::EAssertLevel::Warning);
    ASSERT_WARNING(2 * 2 == 4, "PASS");
    TEST_ASSERT(DummyExecutor::s_bHandleWarningCalled == false);
    ASSERT_WARNING(2 * 3 == 4, "FAIL");
    TEST_ASSERT(DummyExecutor::s_bHandleWarningCalled == false);
    DummyExecutor::s_bHandleWarningCalled = false;
    std::cout << "End Warning Assert testing." << std::endl << std::endl;

    dbgh::CAssertConfig::Get().SetExecutor();
}

void TestErrorAssert()
{
    std::cout << "Start Error Assert testing." << std::endl;
    dbgh::CAssertConfig::Get().EnableAsserts(dbgh::EAssertLevel::Error);
    dbgh::CAssertConfig::Get().SetExecutor(std::make_unique<DummyExecutor>());

    DummyExecutor::s_bHandleErrorCalled = false;
    ASSERT_ERROR(2 * 2 == 4, "PASS");
    TEST_ASSERT(DummyExecutor::s_bHandleErrorCalled == false);
    ASSERT_ERROR(2 * 3 == 4, "FAIL");
    TEST_ASSERT(DummyExecutor::s_bHandleErrorCalled == true);
    DummyExecutor::s_bHandleErrorCalled = false;
    ASSERT_ERROR(2 * 2 == 4, "PASS");
    TEST_ASSERT(DummyExecutor::s_bHandleErrorCalled == false);

    dbgh::CAssertConfig::Get().DisableAsserts(dbgh::EAssertLevel::Error);
    ASSERT_ERROR(2 * 2 == 4, "PASS");
    TEST_ASSERT(DummyExecutor::s_bHandleErrorCalled == false);
    ASSERT_ERROR(2 * 3 == 4, "FAIL");
    TEST_ASSERT(DummyExecutor::s_bHandleErrorCalled == false);
    DummyExecutor::s_bHandleErrorCalled = false;
    std::cout << "End Warning Assert testing." << std::endl << std::endl;

    dbgh::CAssertConfig::Get().SetExecutor();
}

void TestDebugAssert()
{
    std::cout << "Start Debug Assert testing." << std::endl;
    dbgh::CAssertConfig::Get().EnableAsserts(dbgh::EAssertLevel::Error);
    dbgh::CAssertConfig::Get().SetExecutor(std::make_unique<DummyExecutor>());

    constexpr int testCount = 100;

    DummyExecutor::s_cUserInput = 'i';
    DummyExecutor::s_bTerminateCalled = false;
    for (int i = 0; i < testCount; ++i)
    {
        ASSERT_DEBUG(2 * 3 == 213, "FAIL");
        ASSERT_DEBUG(2 * 3 == 6, "PASS");
        DummyExecutor::s_cUserInput = 'b';
    }
    TEST_ASSERT(DummyExecutor::s_bTerminateCalled == true);

    DummyExecutor::s_cUserInput = 'f';
    DummyExecutor::s_bTerminateCalled = false;
    for (int i = 0; i < testCount; ++i)
    {
        ASSERT_DEBUG(2 * 3 == 213, "FAIL");
        ASSERT_DEBUG(2 * 3 == 6, "PASS");
        DummyExecutor::s_cUserInput = 'b';
    }
    TEST_ASSERT(DummyExecutor::s_bTerminateCalled == false);

    DummyExecutor::s_cUserInput = 't';
    try
    {
        ASSERT_DEBUG(2 * 3 == 213, "FAIL");
        TEST_ASSERT(false);
    }
    catch ([[maybe_unused]] const dbgh::CAssertException& e)
    {
        TEST_ASSERT(true);
    }

    std::cout << "End Debug Assert testing." << std::endl << std::endl;

    dbgh::CAssertConfig::Get().SetExecutor();
}

int main()
{
    TestFatalAssert();
    TestWarningAssert();
    TestErrorAssert();
    TestDebugAssert();

    std::cout << "__END_OF_TESTING__" << std::endl;
    return 0;
}
