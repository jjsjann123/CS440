cmake_minimum_required (VERSION 2.6)
project (BattleShipExtreme)


SET ( OSG_ROOT "../OpenSceneGraph-3.0.1/" )
SET ( OSG_BIN_PATH "../osgBuild/bin/" )
SET ( OSG_INCLUDE_PATH "../OpenSceneGraph-3.0.1/include" "../osgBuild/include" )
SET ( OSG_LIB_PATH "../osgBuild/lib/" )

SET ( LIBS_LIST osgd osgUtild osgViewerd osgDBd osgGAd )

include_directories( ${OSG_INCLUDE_PATH} )
link_directories( ${OSG_LIB_PATH} )


add_executable(BSE board.cpp bsTest.cpp player.cpp ship.cpp osgGraphics.cpp osgUI.cpp humanPlayer.cpp gameStateMachine.cpp )
target_link_libraries(BSE ${LIBS_LIST} )