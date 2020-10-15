#include <iostream>

#include "Assert.h"

void WarningExample(int* value)
{
    ASSERT_WARNING(nullptr != value, "The value is can not be null.");

    // *value = 123;
}

void ErrorExample(int* value)
{
    ASSERT_ERROR(nullptr != value, "The value is can not be null.");

    // *value = 123;
}

void DebugExample(int* value)
{
    ASSERT_DEBUG(nullptr != value, "The value is can not be null.");

    // *value = 123;
}

void FatalExample(int* value)
{
    // By default disabled.
    ASSERT_FATAL(nullptr != value, "The value is can not be null.");

    // *value = 123;
}

int main()
{
    int* valuePtr = new int(0);
    WarningExample(valuePtr);
    ErrorExample(valuePtr);
    DebugExample(valuePtr);
    FatalExample(valuePtr);

    int* invalidPtr = nullptr;
    WarningExample(invalidPtr);
    try
    {
        ErrorExample(invalidPtr);
    }
    catch (const dbgh::CAssertException& e)
    {
        std::cout << "Exception handling." << std::endl
            << "Message: "     << e.Message()    << std::endl
            << "FileName: "    << e.FileName()   << std::endl
            << "Function: "    << e.Function()   << std::endl
            << "LineNumber: "  << e.LineNumber() << std::endl
            << std::endl;
    }


    DebugExample(invalidPtr);
    FatalExample(invalidPtr);


    delete valuePtr;
    std::cout << "__END__" << std::endl;
    return 0;
}
