.PHONY: format

format:
	find hw6.custom.containers/src -name "*.hpp" -o -name "*.cpp" | xargs clang-format -i
	find hw6.custom.containers/include -name "*.hpp" -o -name "*.cpp" | xargs clang-format -i
	clang-format -i hw6.custom.containers/main.cpp