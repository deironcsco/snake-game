PROJECT_ROOT="/c/Users/conno/SnakeGame"
PROJECT_SOURCE="${PROJECT_ROOT}/src/main.cpp ${PROJECT_ROOT}/src/Window.cpp ${PROJECT_ROOT}/src/StartButton.cpp"
PROJECT_INCLUDE="-I${PROJECT_ROOT}/include"
SFML_ROOT="/c/Users/conno/SFML-3.0.0"
SFML_INCLUDE="-I${SFML_ROOT}/include -L${SFML_ROOT}/lib -lsfml-graphics -lsfml-window -lsfml-system"

# delete main.exe
rm ${PROJECT_ROOT}/bin/main.exe 2>/dev/null

# compile
g++ ${PROJECT_SOURCE} ${PROJECT_INCLUDE} ${SFML_INCLUDE} -o ${PROJECT_ROOT}/bin/main.exe 

# run
${PROJECT_ROOT}/bin/main.exe