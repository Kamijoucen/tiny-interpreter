
var li = "lisicen";
var a = 555.0;
var b = false;

var fun = def[li, a, b](aa, bb, cc) {
    print a;
    print li;
    print b;
    print aa;
    print bb;
    print cc;
};

var fff = def[fun]() {
    print "11111";
    fun()
};


fff()
