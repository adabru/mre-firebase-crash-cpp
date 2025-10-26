cmake_minimum_required(VERSION 3.20)
project(mre_firebase_crash_cpp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)


# Set Firebase SDK directory
set(FIREBASE_CPP_SDK_DIR "$ENV{USERPROFILE}/Downloads/firebase_cpp_sdk_13.2.0/firebase_cpp_sdk")

# Include Firebase headers
include_directories("${FIREBASE_CPP_SDK_DIR}/include")

# Create executable
add_executable(${PROJECT_NAME}
    src/main.cpp
)

# Set correct library path (for Windows 64-bit)
set(FIREBASE_LIB_DIR "${FIREBASE_CPP_SDK_DIR}/libs/windows/VS2019/MT/x64/Release")
# Link Firebase prebuilt libraries
target_link_libraries(${PROJECT_NAME}
    "${FIREBASE_LIB_DIR}/firebase_app.lib"
    "${FIREBASE_LIB_DIR}/firebase_auth.lib"
    "${FIREBASE_LIB_DIR}/firebase_firestore.lib"
)
