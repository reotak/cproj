#---- Outputs ----#
TARGET_BASE = testbin
TARGET = $(TARGET_BASE)

#--- Inputs ----#
PROJECT_HOME_DIR = .
UNITY_HOME = $(HOME)/tools/Unity
UNITY_FIXTURE = $(UNITY_HOME)/extras/fixture

C_COMPILER=gcc

# Unity File
SRC_FILES  =$(UNITY_HOME)/src/unity.c
# Unity Fixture File
SRC_FILES +=$(UNITY_FIXTURE)/src/unity_fixture.c

# Source Files
SRC_FILES += src/Logger/Logger.c
SRC_FILES += src/Logger/Logger_Logs.c
SRC_FILES += src/Logger/Logger_Event.c
SRC_FILES += src/Logger/Logger_Image.c

# Test Files
TEST_FILES += unity/AllTests.c
TEST_FILES += unity/Logger/LoggerTest.c
TEST_FILES += unity/Logger/LoggerTestRunner.c
TEST_FILES += unity/Logger/LoggerLogsTest.c
TEST_FILES += unity/Logger/LoggerLogsTestRunner.c
TEST_FILES += unity/Logger/LoggerEventTest.c
TEST_FILES += unity/Logger/LoggerEventTestRunner.c
TEST_FILES += unity/Logger/LoggerImageTest.c
TEST_FILES += unity/Logger/LoggerImageTestRunner.c

# Utilities
SRC_FILES += mocks/RuntimeErrorStub.c

INC_DIRS  =-I./src
INC_DIRS +=-I./mocks
INC_DIRS +=-I./include
INC_DIRS +=-I$(UNITY_HOME)/src
INC_DIRS +=-I$(UNITY_FIXTURE)/src

#SYMBOLS=-DTEST -DUNITY_SUPPORT_64

CLEANUP = rm -f *.o ; rm -f $(TARGET); rm -f $(TARGET2) ;

all: default

default:
	$(C_COMPILER) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES) $(TEST_FILES) -o $(TARGET)
	./$(TARGET)
