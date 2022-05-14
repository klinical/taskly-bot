add_library(my_lib
		src/my_lib.cpp
		)

target_include_directories(my_lib
		PUBLIC
		include
		)