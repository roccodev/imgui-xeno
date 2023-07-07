all: build-lib build-nro

build-lib:
	cmake -DCMAKE_TOOLCHAIN_FILE=../../../../cmake/toolchain.cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ../.. -B lib/cmake-build && cmake --build lib/cmake-build

build-nro:
	cargo skyline build

clean:
	rm -r lib/cmake-build && cargo clean || true