# cf. https://github.com/firebase/quickstart-cpp/blob/main/firestore/testapp/CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(mre_firebase_crash_cpp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Set Firebase SDK directory
set(FIREBASE_CPP_SDK_DIR "$ENV{USERPROFILE}/Downloads/firebase_cpp_sdk_13.0.0/firebase_cpp_sdk")
# set(FIREBASE_CPP_SDK_DIR "$ENV{USERPROFILE}/Downloads/firebase_cpp_sdk_13.1.0/firebase_cpp_sdk")
set(FIREBASE_LIB_DIR "${FIREBASE_CPP_SDK_DIR}/libs/windows/VS2019/MT/x64/$<CONFIG>")

# Include Firebase headers
include_directories("${FIREBASE_CPP_SDK_DIR}/include")

# Create executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Set MSVC runtime library to MultiThreaded (/MT) and MultiThreadedDebug (/MTd) for Debug.
set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Suppress PDB warnings for Firebase libraries in Debug builds
target_link_options(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:/IGNORE:4099>
)

# Link Firebase prebuilt libraries
target_link_libraries(${PROJECT_NAME}
    "${FIREBASE_LIB_DIR}/firebase_app.lib"
    "${FIREBASE_LIB_DIR}/firebase_auth.lib"
    "${FIREBASE_LIB_DIR}/firebase_firestore.lib"
    "advapi32.lib"
    "ws2_32.lib"
    "crypt32.lib"
    "rpcrt4.lib"
    "ole32.lib"
    "shell32.lib"
    "dbghelp.lib"
    "bcrypt.lib"
)
