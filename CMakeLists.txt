# CMakeList.txt: проект CMake для Homework_4; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Homework_4")

# Добавьте источник в исполняемый файл этого проекта.
add_executable(Main main.cpp)

# Включите подпроекты.
add_subdirectory (SpaceBattle)
add_subdirectory (Test)

target_link_libraries(Main PRIVATE
	SpaceBattle
)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
