cmake_minimum_required(VERSION 3.20)
project(cpp_cli_app)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build type to Debug by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Add compile definitions for Windows
add_definitions(-DWIN32_LEAN_AND_MEAN -DNOMINMAX)

# Set Firebase SDK directory
set(FIREBASE_CPP_SDK_DIR "$ENV{USERPROFILE}/Downloads/firebase_cpp_sdk_13.2.0/firebase_cpp_sdk")
# Add Firebase libraries to the target using the function from the SDK.
add_subdirectory(${FIREBASE_CPP_SDK_DIR} bin/ EXCLUDE_FROM_ALL)


# Create executable
add_executable(${PROJECT_NAME}
    src/main.cpp
)

# Add the Firebase SDKs for the products you want to use in your app
set(firebase_libs firebase_auth firebase_firestore firebase_app)
target_link_libraries(${PROJECT_NAME} "${firebase_libs}")


# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Enable console subsystem for Windows
if(WIN32 AND MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:CONSOLE"
    )
endif()