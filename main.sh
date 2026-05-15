PROJECT_ROOT="/c/Users/conno/SnakeGame"
SFML_ROOT="/c/Users/conno/SFML-3.0.0"
SFML_INCLUDE="-I${SFML_ROOT}/include -L${SFML_ROOT}/lib -lsfml-graphics -lsfml-window -lsfml-system"
SOURCE_FILES="${PROJECT_ROOT}/src/main.cpp ${PROJECT_ROOT}/src/Window.cpp"
g++ ${SOURCE_FILES} -I${PROJECT_ROOT}/include ${SFML_INCLUDE} -o ${PROJECT_ROOT}/bin/main.exe 
${PROJECT_ROOT}/bin/main.exe