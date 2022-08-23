say_hello:
	echo "Hello world :)"



final_target: tag main.cpp
        g++

tag: tag.hpp tag.cpp
        g++
