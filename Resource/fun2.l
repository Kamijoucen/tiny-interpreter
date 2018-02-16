
var f = def[](a) {
    return def[a](b) {
        return def[a,b](c) {
            return a + b + c;
        };
    };
};
print f(1)(550)(1);

// (def[](a){print a;})(15);
