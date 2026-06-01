# import
source ./vars.sh

# test-specific vars
TEST_SOURCE="${PROJECT_ROOT}/src/Window.cpp ${PROJECT_ROOT}/src/StartButton.cpp ${PROJECT_ROOT}/src/test/TestWindow.cpp"
TEST_INCLUDE="-I${PROJECT_ROOT}/include -I${PROJECT_ROOT}/include/test"
TEST_FILE="${PROJECT_ROOT}/test/test.cpp"

# delete test.exe
rm ${PROJECT_ROOT}/bin/test.exe 2>/dev/null

# compile
g++ ${TEST_FILE} ${TEST_SOURCE} ${TEST_INCLUDE} ${SFML_INCLUDE} -o ${PROJECT_ROOT}/bin/test.exe

# run
${PROJECT_ROOT}/bin/test.exe