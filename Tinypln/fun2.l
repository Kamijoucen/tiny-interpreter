
var f = def[](a) {
    return def[a](b) {
		//var a = 15; // fix me
        return def[a,b](c) {
			var d = a + c + b;
			var innerfun = def[d](nn, nnn) {
				print "-------------";
				print d;
				print "-------------";
				if (nn > nnn) {
					return nn;
				} else {
					return nnn;
				}
			};
            return innerfun;
        };
    };
};
// print f(1)(2)(3);

def fun(ff) {
    return ff;
}

print fun(f)(1)(2)(3)(55, 555);

// (def[](a){print a;})(15);
