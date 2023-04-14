n = 2048
mat = [[1 + x + y * n for x in range(n)] for y in range(n)]

print(f'int mat[{n}][{n}] = {"{"}')
for row in mat:
    print('\t{', end='')
    print(*row, sep=', ', end='},\n')
print(f'{"}"};\nint* matp[{n}] = {"{"}', end='')
for idx, _ in enumerate(mat):
    print(f'mat[{idx}], ', end='')
print('};\nint** matpp = matp;')
