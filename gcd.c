int gcd(int a, int b) {
    int i;
    for (i = a; i > 0; i--) {
        // a と bどちらもiで割り切れていたら終了
        if (a % i == 0 && b % i == 0) {
            break;
        }
    }
    return i;
}

