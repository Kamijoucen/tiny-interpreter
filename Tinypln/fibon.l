
var i = 0;
while (i < 10) {
    i = i + 1;
    print fibon(i);
}
def fibon(n) {
    if(n == 0) { return 0; }
    if(n == 1) { return 1; }
    return fibon(n - 1) + fibon(n - 2);
}