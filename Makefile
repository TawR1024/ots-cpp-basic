.PHONY: format

format:
	find hw8.crc.threading -name "*.hpp" -o -name "*.cpp" | xargs clang-format -i

generate_data_files:
	dd if=/dev/urandom bs=1 count=100 2>/dev/null | base64 | tr -d '\n' | head -c 100 >  $(CURDIR)/hw8.crc.threading/test-data/in.txt