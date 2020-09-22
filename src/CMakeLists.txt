
add_executable(beziercurves
	"main.cpp"
 "UI/IDrawable.hpp" "UI/Vertex.hpp" "UI/Vertex.cpp" "BezierCurve.hpp" "BezierCurve.cpp" "UI/Line.hpp" "UI/Line.cpp")

if(WIN32)
target_include_directories(beziercurves PRIVATE
	SDL2::SDL2
)
else()
target_include_directories(beziercurves PRIVATE
	${SDL2_INCLUDE_DIRS}
)
endif()


if(WIN32)
target_link_libraries(beziercurves PRIVATE
	SDL2::SDL2
)
else()
target_link_libraries(beziercurves PRIVATE
	${SDL2_LIBRARIES} m
)
endif()

if(WIN32)
	add_custom_command(TARGET beziercurves POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${SDL2_DIR}/../bin/ $<TARGET_FILE_DIR:beziercurves>
	)
endif()