.PHONY: build clean

build:
	cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain.cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo . -B cmake-build-minsizerel \
 		&& cmake --build cmake-build-minsizerel

clean:
	rm -r cmake-build-minsizerel