cmake_minimum_required (VERSION 2.6)
project (BattleShipExtreme)


SET ( OSG_ROOT "../OpenSceneGraph-3.0.1/" CACHE STRING "this should point to the osg root")
SET ( OSG_BIN_PATH "../osgBuild/bin/" CACHE STRING "this should point to the osg build/bin")
SET ( OSG_INCLUDE_PATH "../OpenSceneGraph-3.0.1/include" "../osgBuild/include" CACHE STRING "this should point to the osg root/include")
SET ( OSG_LIB_PATH "../osgBuild/lib/" CACHE STRING "this should point to the osg build/lib")

SET ( LIBS_LIST osgd osgUtild osgViewerd osgDBd osgGAd )

include_directories( ${OSG_INCLUDE_PATH} )
link_directories( ${OSG_LIB_PATH} )


add_executable(BSE board.cpp bsTest.cpp player.cpp ship.cpp osgGraphics.cpp osgUI.cpp humanPlayer.cpp)
target_link_libraries(BSE ${LIBS_LIST} )