
var f = def[](a) {
    return def[a](b) {
        return def[a,b](c) {
            print "我是闭包3";
            return a + b + c;
        };
    };
};
var ff = f(1);
var fff = ff(2);
print fff(3);
