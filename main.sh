# import
source ./vars.sh

# main-specific vars
SRC_ROOT="${PROJECT_ROOT}/src"
PROJECT_SOURCE="${SRC_ROOT}/Window.cpp ${SRC_ROOT}/Button.cpp ${SRC_ROOT}/StartButtonNew.cpp"
PROJECT_INCLUDE="-I${PROJECT_ROOT}/include"
MAIN_FILE="${PROJECT_ROOT}/src/main.cpp"

# delete main.exe
rm ${PROJECT_ROOT}/bin/main.exe

# compile
# g++ ${MAIN_FILE} ${PROJECT_SOURCE} ${PROJECT_INCLUDE} ${SFML_INCLUDE} -o ${PROJECT_ROOT}/bin/main.exe 

# debug
# should not silence error output for rm
g++ -g ${MAIN_FILE} ${PROJECT_SOURCE} ${PROJECT_INCLUDE} ${SFML_INCLUDE} -o ${PROJECT_ROOT}/bin/main.exe 
echo "debugged"

# run
${PROJECT_ROOT}/bin/main.exe