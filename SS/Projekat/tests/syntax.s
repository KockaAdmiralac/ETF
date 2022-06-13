.section text
label1: halt
label2: .word 4
label3: ldr r0, [r0+4] # comment
label4: .ascii "lol" # comment
label5: # comment
jmp *[r5 + sym]
jgt %sym2 # comment
.extern sym, sym2 # comment

# comment
