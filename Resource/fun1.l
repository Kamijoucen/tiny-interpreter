
var f = def[](a) {
    return def[a](b) {
        return def[a,b](c) {
            return a + b + c;
        };
    };
};
var ff = f(1);
var fff = ff(2);
print fff(3);
