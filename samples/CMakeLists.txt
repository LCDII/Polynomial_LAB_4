# samples/CMakeLists.txt
set(target sample)

file(GLOB SAMPLE_SRCS "*.cpp")

add_executable(${target} ${SAMPLE_SRCS})

# samples нужно видеть заголовки библиотеки и ANTLR
target_include_directories(${target} PRIVATE
    ${INCLUDE}
)

# Линкуем с нашей библиотекой и с ANTLR runtime
target_link_libraries(${target} PRIVATE
    ${LIBRARY}
)

install(TARGETS sample RUNTIME DESTINATION bin)