CXXFLAGS += -std=c++20 -Og -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference
#CXXFLAGS += -std=c++20 -Ofast

MKDIR_P = mkdir -p
OUT_DIR = ./build

%: %.cpp
	@${MKDIR_P} ${OUT_DIR}
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o ./build/$@.exe
	/usr/bin/time ./build/$@.exe ../input/$@.in

clean:
	rm -fr ./build

.PHONY: clean
