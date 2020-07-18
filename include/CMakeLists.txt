project (dbgh_asserts)

add_library(dbgh_asserts_lib STATIC)

target_include_directories(dbgh_asserts_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(dbgh_asserts_lib INTERFACE )

add_subdirectory(impl)

target_link_libraries(dbgh_asserts_lib PRIVATE impl_dbgh_asserts_lib)
