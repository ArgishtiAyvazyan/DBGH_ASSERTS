project (impl_dbgh_asserts)

add_library(impl_dbgh_asserts_lib STATIC "CAssertConfig.h" "CAssertException.cpp" "CAssertException.h" "CAssertHandler.cpp" "CAssertHandler.h" CHandlerExecutor.cpp CHandlerExecutor.h CAssertConfig.cpp)

target_include_directories(impl_dbgh_asserts_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(impl_dbgh_asserts_lib INTERFACE )

target_link_libraries(impl_dbgh_asserts_lib PRIVATE)