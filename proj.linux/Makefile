EXECUTABLE = neoballnoid

COCOS_ROOT = $(COCOS2DX_ROOT)

INCLUDES +=  -I../ \
    -I../src \
    -I$(COCOS_ROOT)/external/ \

SOURCES = main.cpp \
        ../src/AppDelegate.cpp \
        ../src/GameScene.cpp \
        ../src/MainScene.cpp \
        ../src/box2d/ContactListener.cpp \
        ../src/sprites/Sprite.cpp \
        ../src/sprites/Background.cpp \
        ../src/sprites/Pad.cpp \
        ../src/sprites/Ball.cpp \
        ../src/sprites/Brick.cpp \

ifdef DEBUGDRAW
DEFINES += -DDEBUGDRAW
SOURCES += ../src/box2d/Box2DDebug.cpp
endif

include ./cocos2dx.mk

SHAREDLIBS += -lcocos2d -lGL
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so

STATICLIBS += \
    $(LIB_DIR)/libbox2d.a \

$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: ../%.c $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@
