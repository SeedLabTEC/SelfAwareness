static-compile:
	g++ -c self-monitor.cpp
	ar rvs libselfmonitor.a self-monitor.o
	cc -fPIC -shared -o libselfmonitor.so self-monitor.cpp
	g++ -c env-monitor.cpp
	ar rvs libenvmonitor.a env-monitor.o
	cc -fPIC -shared -o libenvmonitor.so env-monitor.cpp
	ls -ld .
	sudo rm -fv --interactive=never *.o
