cmake_minimum_required(VERSION 3.9)
project(WormholeDash)
include_directories("/opt/local/include")
include_directories("${PROJECT_SOURCE_DIR}/extra/usr/local/include/bullet")
include_directories("${PROJECT_SOURCE_DIR}/OBJ-Loader/Source")
link_directories("/opt/local/lib")
link_directories("${PROJECT_SOURCE_DIR}/extra/usr/local/lib")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -w -framework OpenGL -g -Dsprintf_s=sprintf")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON )

add_executable(WormholeDash src/WormholeDash.cpp src/engine/Actor.cpp src/engine/Actor.h src/engine/OpenGLWrapper.cpp src/engine/OpenGLWrapper.h src/engine/Game.cpp src/engine/Game.h src/engine/Scene.cpp src/engine/Scene.h src/engine/SceneManager.cpp src/engine/SceneManager.h src/engine/Camera.cpp src/engine/Camera.h src/game/scenes/GameScreen.cpp src/game/scenes/GameScreen.h src/game/actors/SpeedBuggy.cpp src/game/actors/SpeedBuggy.h src/game/actors/start-screen/StartBackground.cpp src/game/actors/start-screen/StartBackground.h src/glheaders.h src/engine/Command.cpp src/engine/Command.h src/game/CommandCodes.h src/game/actors/Track.cpp src/game/actors/Track.h src/engine/DebugDraw.cpp src/engine/DebugDraw.h src/game/actors/GroundRigid.cpp src/game/actors/GroundRigid.h src/game/actors/SpeedBuggyWheel.cpp src/game/actors/SpeedBuggyWheel.h src/engine/getBMP.cpp src/engine/getBMP.h src/game/actors/TextureBox.cpp src/game/actors/TextureBox.h src/game/actors/StartText.cpp src/game/actors/StartText.h src/game/actors/TimerText.cpp src/game/actors/TimerText.h)
target_link_libraries(WormholeDash GLUT glew BulletDynamics BulletCollision LinearMath)
