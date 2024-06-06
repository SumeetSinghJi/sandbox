// Module interface file: math_module.ixx
export module math_module;

export namespace math {
    int add(int a, int b);
    int subtract(int a, int b);
}

// Module implementation file: math_module.cpp
module math_module;

namespace math {
    int add(int a, int b) {
        return a + b;
    }

    int subtract(int a, int b) {
        return a - b;
    }
}
