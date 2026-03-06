cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME Polynomial)
project(${PROJECT_NAME})

# ---------------- C++ ----------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY
        "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"
        CACHE STRING "" FORCE)
endif()

# ---------------- Пути проекта ----------------
set(LIBRARY "${PROJECT_NAME}")
set(INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SOURCE  "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(TESTS   "test_${PROJECT_NAME}")

# ---------------- CMAKE_INSTALL_PREFIX ----------------
# Удобный локальный путь для INSTALL
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Installation Directory")

# =========================================================
# 🔵 ANTLR SECTION
# =========================================================
include(FetchContent)

# 1️⃣ Скачать runtime автоматически
FetchContent_Declare(
    antlr4_runtime
    GIT_REPOSITORY https://github.com/antlr/antlr4.git
    GIT_TAG 4.13.2
    SOURCE_SUBDIR runtime/Cpp
)
FetchContent_MakeAvailable(antlr4_runtime)

# Include для runtime
set(ANTLR4_RUNTIME_INCLUDE_DIR ${antlr4_runtime_SOURCE_DIR}/runtime/src)

# 2️⃣ Пути к ANTLR tool и грамматике
set(ANTLR_JAR ${CMAKE_SOURCE_DIR}/antlr/antlr-4.13.2-complete.jar)
set(GRAMMAR ${CMAKE_SOURCE_DIR}/grammar/Polynomial.g4)
set(GENERATED_DIR ${CMAKE_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${GENERATED_DIR})

# 3️⃣ Генерация parser автоматически
add_custom_command(
    OUTPUT
        ${GENERATED_DIR}/PolynomialLexer.cpp
        ${GENERATED_DIR}/PolynomialParser.cpp
        ${GENERATED_DIR}/PolynomialBaseVisitor.cpp
        ${GENERATED_DIR}/PolynomialVisitor.cpp
    COMMAND java -jar ${ANTLR_JAR}
            -Dlanguage=Cpp
            -visitor
            -o ${GENERATED_DIR}
            ${GRAMMAR}
    DEPENDS ${GRAMMAR}
    COMMENT "Generating ANTLR parser..."
)

set(ANTLR_SRCS
    ${GENERATED_DIR}/PolynomialLexer.cpp
    ${GENERATED_DIR}/PolynomialParser.cpp
    ${GENERATED_DIR}/PolynomialBaseVisitor.cpp
    ${GENERATED_DIR}/PolynomialVisitor.cpp
)

# ---------------- GoogleTest ----------------
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

# ---------------- Библиотека Polynomial ----------------
file(GLOB LIB_SRCS "${SOURCE}/*.cpp")
file(GLOB LIB_H "${INCLUDE}/*.h")

add_library(${LIBRARY} STATIC ${LIB_SRCS} ${LIB_H} ${ANTLR_SRCS})

# Include paths
target_include_directories(${LIBRARY} PUBLIC
    ${INCLUDE}
    ${GENERATED_DIR}
    ${antlr4_runtime_SOURCE_DIR}/runtime/Cpp/runtime/src/
)

# Линковка с ANTLR runtime
target_link_libraries(${LIBRARY} PUBLIC antlr4_static)


# ---------------- Install ----------------
install(TARGETS ${LIBRARY}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY ${INCLUDE}/ DESTINATION include)
install(DIRECTORY ${GENERATED_DIR}/ DESTINATION include)

# ---------------- Subdirectories ----------------
add_subdirectory(samples)
add_subdirectory(test)