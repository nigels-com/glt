ADD_CUSTOM_COMMAND(OUTPUT vertexShader.cpp   COMMAND ${GLT_TEXT2SRC} vertexShader.txt -o vertexShader.cpp DEPENDS vertexShader.txt) 
ADD_CUSTOM_COMMAND(OUTPUT fragmentShader.cpp COMMAND ${GLT_TEXT2SRC} fragmentShader.txt -o fragmentShader.cpp DEPENDS fragmentShader.txt) 
ADD_CUSTOM_COMMAND(OUTPUT noise1.cpp         COMMAND ${GLT_BIN2SRC} -image noise1.png        -o noise1.cpp        DEPENDS noise1.png) 
ADD_CUSTOM_COMMAND(OUTPUT noise2.cpp         COMMAND ${GLT_BIN2SRC} -image noise2.png        -o noise2.cpp        DEPENDS noise2.png) 
ADD_CUSTOM_COMMAND(OUTPUT windowShader1.cpp  COMMAND ${GLT_BIN2SRC} -image windowShader1.png -o windowShader1.cpp DEPENDS windowShader1.png) 
ADD_CUSTOM_COMMAND(OUTPUT windowShader2.cpp  COMMAND ${GLT_BIN2SRC} -image windowShader2.png -o windowShader2.cpp DEPENDS windowShader2.png) 
ADD_CUSTOM_COMMAND(OUTPUT windowShader3.cpp  COMMAND ${GLT_BIN2SRC} -image windowShader3.png -o windowShader3.cpp DEPENDS windowShader3.png) 
ADD_CUSTOM_COMMAND(OUTPUT windowShader4.cpp  COMMAND ${GLT_BIN2SRC} -image windowShader4.png -o windowShader4.cpp DEPENDS windowShader4.png) 
ADD_CUSTOM_COMMAND(OUTPUT windowShader5.cpp  COMMAND ${GLT_BIN2SRC} -image windowShader5.png -o windowShader5.cpp DEPENDS windowShader5.png) 

ADD_EXECUTABLE(
    glsl main.cpp window.cpp windowShader.cpp vertexShader.cpp fragmentShader.cpp 
    noise1.cpp noise2.cpp 
    windowShader1.cpp windowShader2.cpp windowShader3.cpp windowShader4.cpp windowShader5.cpp
)
ADD_DEPENDENCIES(glsl bin2src)
ADD_DEPENDENCIES(glsl text2src)
TARGET_LINK_LIBRARIES(glsl ${GLT_LINK_LIBRARIES})
