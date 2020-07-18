#include <iostream>

#include "Assert.h"


void foo()
{
    ASSERT_DEBUG(5 == 6, "Error");
}

int main()
{
    foo();
    foo();
    foo();
    foo();
    foo();


    ASSERT_WARNING(5 == 6, "Error");
    ASSERT_WARNING(5 != 6, "Error");
    ASSERT_DEBUG(5 == 6, "Error");
    ASSERT_DEBUG(5 == 6, "Error");
    ASSERT_DEBUG(5 == 6, "Error");
    ASSERT_DEBUG(5 != 6, "Error");
    ASSERT_DEBUG(5 == 6, "Error");
    ASSERT_DEBUG(5 != 6, "Error");
    ASSERT_ERROR(5 == 6, "Error");
    ASSERT_ERROR(5 != 6, "Error");
    ASSERT_FATAL(5 == 6, "Error");
    ASSERT_FATAL(5 != 6, "Error");

    std::cout << "__END__" << std::endl;
    return 0;
}
