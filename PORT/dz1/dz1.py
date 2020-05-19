for vector in range(16):
    a0 = (vector & 0b0001) != 0
    a1 = (vector & 0b0010) != 0
    a2 = (vector & 0b0100) != 0
    a3 = (vector & 0b1000) != 0
    a = (not a3) * (not a1) * (a2 * (not a0) + (not a2) * a0)
    b = a3 * (a2 + a1) + a2 * ((not a1) * a0 + a1 * (not a0))
    # b = a3 * (a2 + a1) + (not a3) * (not a1) * a0 + a2 * a1 * (not a0)
    c = (a2 + a1) * (a3 + (not a2)) * (a3 + (not a0))
    # c = (not a2) * ((not a3) * (not a1) * a0 + a1 * (not a0)) + a3 * (a2 + a1)
    d = (not a3) * (a2 * ((not a1) * (not a0) + a2 * a1) + (not a2) * (not a1) * (not a0))
    # d = (not a3) * ((not a1) * (a2 * (not a0) + (not a2) * a0) + a2 * a1 * a0)
    e = (not a3) * a0 + (not a1) * ((not a3) * a2 + (not a2) * a0)
    # e = (not a3) * (a2 * (not a1) + a1 * a0) + a3 * (not a2) * (not a1) * a0
    f = (not a3) * (a2 + (not a1)) * ((not a2) + (not a1) + (not a0)) * ((not a3) + a2)
    # f = (not a3) * a1 * (a0 + (not a2))
    g = (not a3) * ((not a2) * (not a1) + a2 * a1 * a0)
    print(
        vector,
        '\n-----\n {0} \n{5} {1}\n {6} \n{4} {2}\n {3} '.format(
            *[' ' if int(num) != 0 else '■' for num in [a, b, c, d, e, f, g]]
        ),
        '\n-----'
    )
