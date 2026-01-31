cmake_minimum_required(VERSION 4.0)
project(Mini_Renderer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Good warnings (MSVC vs others)
if (MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(Mini_Renderer
        src/core/Intersection.h
        src/core/BVH.h
        include/Sphere.h
        src/geometry/Triangle.cpp
        src/geometry/Mesh.cpp
        src/shading/BSDF.h
        src/shading/Lambert.cpp
        src/shading/Metal.cpp
        src/shading/Dielectric.cpp
        src/renderer/PathTracer.cpp
        src/renderer/Integrator.h
        src/main.cpp
        tests/intersection_tests.cpp
        src/core/Camera.cpp
        include/Hittable.h
        include/HittableList.h
        include/Material.h
        include/Lambertian.h
        include/Metal.h
)

target_include_directories(Mini_Renderer PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_definitions(Mini_Renderer PRIVATE
        PROJECT_ROOT_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
)
set_target_properties(Mini_Renderer PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
# (Optional) later: tests
option(BUILD_TESTS "Build tests" ON)
if (BUILD_TESTS)
    enable_testing()
    # We'll add a tests target on Day 2/3
endif()