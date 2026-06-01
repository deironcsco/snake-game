# import
source ./vars.sh

# main-specific vars
PROJECT_SOURCE="${PROJECT_ROOT}/src/Window.cpp ${PROJECT_ROOT}/src/StartButton.cpp"
PROJECT_INCLUDE="-I${PROJECT_ROOT}/include"
MAIN_FILE="${PROJECT_ROOT}/src/main.cpp"

# delete main.exe
rm ${PROJECT_ROOT}/bin/main.exe 2>/dev/null

# compile
g++ ${MAIN_FILE} ${PROJECT_SOURCE} ${PROJECT_INCLUDE} ${SFML_INCLUDE} -o ${PROJECT_ROOT}/bin/main.exe 

# run
${PROJECT_ROOT}/bin/main.exe