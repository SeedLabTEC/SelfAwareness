CC=g++
SELFMONITOR_NAME=selfMonitor
ENVMONITOR_NAME=envMonitor
MODEL_NAME=powerModel
EXECUTION_QUEUE_NAME=executionqueue
AR=ar
AR_FLAGS=rvs
CFLAGS_LIB= -shared
CFLAGS= -fpic
WD=$(shell pwd)
HEADER=include

main: object-generator static-compile dynamic-compile clean-objects
	@echo "Compilation Finished"

object-generator: object-envmonitor object-selfmonitor object-model object-execution-queue
	@echo "Object generated"

object-envmonitor:
	${CC} -Wall -o ${ENVMONITOR_NAME}.o -c env-monitor.cpp ${CFLAGS} -lm -I"$(WD)/../$(HEADER)"

object-selfmonitor:
	${CC} -Wall -o ${SELFMONITOR_NAME}.o -c self-monitor.cpp ${CFLAGS} -lm -I"$(WD)/../$(HEADER)"

object-model:
	${CC} -Wall -o ${MODEL_NAME}.o -c powerModel.cpp -ljsoncpp ${CFLAGS} -lm -I"$(WD)/../$(HEADER)"

object-execution-queue:
	${CC} -Wall -o ${EXECUTION_QUEUE_NAME}.o -c executionQueue.cpp ${CFLAGS} -lm -I"$(WD)/../$(HEADER)"

static-compile: static-envmonitor static-selfmonitor static-model static-execution-queue
	@echo "Static libs generated"

static-envmonitor:
	${AR} ${AR_FLAGS} lib${ENVMONITOR_NAME}.a ${ENVMONITOR_NAME}.o

static-selfmonitor:
	${AR} ${AR_FLAGS} lib${SELFMONITOR_NAME}.a ${SELFMONITOR_NAME}.o

static-model:
	${AR} ${AR_FLAGS} lib${MODEL_NAME}.a ${MODEL_NAME}.o

static-execution-queue:
	${AR} ${AR_FLAGS} lib${EXECUTION_QUEUE_NAME}.a ${EXECUTION_QUEUE_NAME}.o

dynamic-compile: dynamic-envmonitor dynamic-selfmonitor dynamic-model dynamic-execution-queue
	@echo "Dynamic libs generated"

dynamic-envmonitor:
	@$(CC) -Wall $(ENVMONITOR_NAME).o -o lib$(ENVMONITOR_NAME).so $(CFLAGS_LIB)

dynamic-selfmonitor:
	@$(CC) -Wall $(SELFMONITOR_NAME).o -o lib$(SELFMONITOR_NAME).so $(CFLAGS_LIB)

dynamic-model:
	@$(CC) -Wall $(MODEL_NAME).o -o lib$(MODEL_NAME).so $(CFLAGS_LIB)

dynamic-execution-queue:
	@$(CC) -Wall $(EXECUTION_QUEUE_NAME).o -o lib$(EXECUTION_QUEUE_NAME).so $(CFLAGS_LIB)


clean-objects:
	@rm *.a *.o 2> /dev/null
