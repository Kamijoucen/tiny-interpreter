
var f = def[](a) {
    return def[a](b) {
        return def[a,b](c) {
            return a + b + c;
        };
    };
};
// print f(1)(2)(3);

def fun(ff) {
    return ff;
}

print fun(f)(1)(2)(3);

// (def[](a){print a;})(15);
