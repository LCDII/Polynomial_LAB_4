# test/CMakeLists.txt

# имя тестового exe
set(target test_Polynomial)

file(GLOB TEST_SRCS "*.cpp")

add_executable(${target} ${TEST_SRCS})

target_include_directories(${target}
    PRIVATE
        ${INCLUDE}
)

target_link_libraries(${target}
    PRIVATE
        GTest::gtest
        ${LIBRARY}
)

install(TARGETS ${TESTS} RUNTIME DESTINATION bin)