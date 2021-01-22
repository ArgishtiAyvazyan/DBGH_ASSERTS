#add_definitions(-DDEBUG)

add_executable(
    main_exec
    main.cpp
)

target_link_libraries(main_exec dbgh_asserts_lib)
