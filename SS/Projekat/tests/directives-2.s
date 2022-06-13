.global e1, e2, e3
.extern g1
.section data
e1: .word g1
e2: .word 2
e3: .word 3
g2: .word 4
#.global g2             # Duplicate definition
