cmake_minimum_required(VERSION 3.12)

project(bulk_prj)

set(main_files 
    main.cpp
    m_exceptions.h
    observer.h
)
set(Parser
    parser.cpp
    parser.h
)
set(CommandReader
    cmd_reader.cpp
    cmd_reader.h
)


add_executable(bulk ${main_files} ${Parser} ${CommandReader})

if(MSVC)
	    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT bulk)
        set_target_properties(bulk PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS "3") #default N-value
        source_group("Main" FILES ${main_files})
        source_group("Parser" FILES ${Parser})
        source_group("CommandReader" FILES ${CommandReader})
endif ()


target_compile_options(bulk PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX >
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
        )

set_target_properties(bulk PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

