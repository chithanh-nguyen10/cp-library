auto floor_div = [] (int64_t a, int64_t b) {
    // Warning !!!! b must be NON-ZERO
    if (b < 0) {a = -a; b = -b;}
    if (a >= 0) return a / b;
    return -((b - a - 1) / b);
};  

auto ceil_div = [] (int64_t a, int64_t b) {
    // Warning !!!! b must be NON-ZERO
    if (b < 0) {a = -a; b = -b;}
    if (a >= 0) return (a + b - 1) / b;
    return -((-a) / b);
};