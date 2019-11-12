compile:
	g++ -c self-monitorCPU.cpp
	ar rvs libselfmonitorCPU.a self-monitorCPU.o
	cc -fPIC -shared -o libselfmonitorCPU.so self-monitorCPU.cpp
	ls -ld .
	rm -fv --interactive=never *.o