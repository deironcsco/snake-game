#include <string>

class DivideByZeroException {
public:
    DivideByZeroException() = default;
    int getValue() { return -2; } // TODO does this need to be a different number? it can't be -1? does it need a value?
    std::string getMessage() { return "Division by Zero Exception"; }
    // TODO does this need to have an implementaiton file? does it matter? when .h vs .cpp?
};