; int a, *b, c, d, e, f;
; f = (a + b[c])/((a*4 + d) * (1 - e))
; OC reg, reg, reg/imm
; LOAD/STORE reg, mem
ORG 100h
LOAD R1, b
LOAD R2, c
ADD R1, R1, R2
LOAD R2, a
ADD R1, R1, R2
ASL R2, R2, #4
LOAD R3, d
ADD R2, R2, R3
LOAD R3, #1
LOAD R4, e
SUB R3, R3, R4
MUL R2, R2, R3
DIV R1, R1, R2
STORE R1, f

; MOVC srclen, srcaddr, fill, dstlen, dstaddr
; MOVTC srclen, srcaddr, fill, tbladdr, dstlen, dstaddr
; CMPC src1len, src1addr, fill, src2len, src2addr
; LOCC len, addr, char
; SKPC len, addr, char
; MATCHC src1len, src1addr, src2len, src2addr
; ACB limit, step, index, displ
; AOB limit, index, displ
; SOB index, displ
; CASE selector, base, limit, displ[0], displ[1],... displ[limit-base]
; BBS base, pos, displ
