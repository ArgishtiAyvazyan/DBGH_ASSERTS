project (impl_dbgh_asserts)

add_library(impl_dbgh_asserts_lib STATIC CAssertException.cpp CAssertHandler.cpp)

target_include_directories(impl_dbgh_asserts_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(impl_dbgh_asserts_lib INTERFACE )

target_link_libraries(impl_dbgh_asserts_lib PRIVATE)