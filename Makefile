# IMPORTANT: this is just a shortcut to invoke cmake from build/ directory
default:
	cd build/ && cmake .. && make
clean:
	rm -rf build/*
