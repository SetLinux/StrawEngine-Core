cmake_minimum_required(VERSION 3.0.0)
project(StrawEngine VERSION 0.1.0)

include(CTest)
enable_testing()
find_package(glfw3 REQUIRED)
find_package(PkgConfig REQUIRED)
find_package (Threads)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
pkg_search_module(GLFW REQUIRED glfw3)

pkg_search_module(GLEW REQUIRED glew)
add_executable(StrawEngine 

Engine/GUI/imconfig.h
Engine/GUI/imgui.cpp
Engine/GUI/imgui_demo.cpp
Engine/GUI/imgui_draw.cpp
Engine/GUI/imgui.h
Engine/GUI/imgui_internal.h
Engine/GUI/imgui_widgets.cpp
Engine/GUI/imstb_rectpack.h
Engine/GUI/imstb_textedit.h
Engine/GUI/imstb_truetype.h

Engine/Utils/nuklear.h
Engine/Utils/nuklear_glfw_gl4.h
Engine/Utils/SNuklear.h
Engine/Utils/SNuklear.cpp
Engine/GUI/imgui_impl_opengl3.h
Engine/GUI/imgui_impl_opengl3.cpp

Engine/Physics/ContactListener.h
Engine/Physics/ContactListener.cpp
Engine/Addons/Sprite.h
Engine/Addons/Sprite.cpp
Engine/GUI/GUISystem.cpp
Engine/Rendering/Animation.h
Engine/Rendering/Animation.cpp
Engine/IO/Window.h
Engine/IO/Window.cpp
Engine/Game/Addon.h
Engine/Game/Addon.cpp
Engine/Utils/stb_image.h
Engine/Utils/ImageLoader.cpp
Engine/Utils/LogSystem.h
Engine/Addons/Animator.h
Engine/Addons/Animator.cpp
Engine/Addons/Physics.h
Engine/Addons/Physics.cpp
Engine/Rendering/FBO.h
Engine/Rendering/FBO.cpp
Engine/Game/Game.h
Engine/Game/Game.cpp
Engine/Game/Camera.h
Engine/Game/Camera.cpp
Engine/Core.h
Engine/Rendering/Renderer.h
Engine/Rendering/Renderer.cpp
Engine/Math/Math.h
Engine/Rendering/Shader.h
Engine/Rendering/Shader.cpp
Engine/Rendering/Texture.h
Engine/Rendering/Texture.cpp
Engine/Physics/PhysicsSystem.h
Engine/Physics/PhysicsSystem.cpp
Engine/Physics/RaycastHandler.h
Engine/Physics/RaycastHandler.cpp
StrawEngine.cpp)

target_include_directories(StrawEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/Box2D/)

target_link_libraries(StrawEngine PRIVATE   ${CMAKE_THREAD_LIBS_INIT} ${GLFW_LIBRARIES} ${CMAKE_CURRENT_SOURCE_DIR}/libs/Box2D/libBox2D.a ${GLEW_LIBRARIES})
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
