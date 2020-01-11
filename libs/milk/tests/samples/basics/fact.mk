fn fact(x: u64) : u64 {
    return x <= 1 ? 1 : x * fact(x - 1);
}
