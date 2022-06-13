.global g1, g2, g3, .ivt
.extern e1, e2, e3, label
.section sec1
label: .word 4
.word g2, .ivt, g3
.skip 2
.ascii "lol"
.section ivt
.skip 16
.section sec2
.equ g1, 10
.equ g2, b+c-(-d-e+(a+d))+5
.equ g3, e1+6
#.end                   # Terminating early with unapplied patches
.equ a, 7
.equ b, 8
.equ c, d
.equ d, 11
.equ e, 010
#.global .ivt           # Attempting to mark a section as global
#.extern .ivt           # Symbol being marked external already defined locally
#.section ivt           # Duplicate symbol
