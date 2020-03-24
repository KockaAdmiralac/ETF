*version 9.1 790072219
u 202
V? 5
R? 9
Q? 9
C? 6
@libraries
@analysis
.TRAN 1 0 0 0
+0 0
+1 10ms
@targets
@attributes
@translators
a 0 u 13 0 0 0 hln 100 PCBOARDS=PCB
a 0 u 13 0 0 0 hln 100 PSPICE=PSPICE
a 0 u 13 0 0 0 hln 100 XILINX=XILINX
@setup
unconnectedPins 0
connectViaLabel 0
connectViaLocalLabels 0
NoStim4ExtIFPortsWarnings 1
AutoGenStim4ExtIFPorts 1
@index
pageloc 1 0 9415 
@status
n 0 120:00:22:18:41:27;1579747287 e 
s 0 120:00:22:18:41:27;1579747287 e 
*page 1 0 970 720 iA
@ports
port 44 agnd 30 60 h
port 96 agnd 110 150 h
port 157 agnd 210 60 h
port 158 agnd 290 150 h
@parts
part 54 c 60 90 h
a 0 xp 9 0 10 0 hln 100 REFDES=C1
a 0 sp 0 0 0 10 hlb 100 PART=c
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=C1
a 0 u 13 0 5 25 hln 100 VALUE=100u
part 85 c 130 70 h
a 0 x 0:13 0 0 0 hln 100 PKGREF=C2
a 0 xp 9 0 10 0 hln 100 REFDES=C2
a 0 sp 0 0 0 10 hlb 100 PART=c
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 u 13 0 5 25 hln 100 VALUE=100u
part 86 c 130 110 d
a 0 x 0:13 0 0 0 hln 100 PKGREF=C3
a 0 xp 9 0 15 0 hln 100 REFDES=C3
a 0 sp 0 0 0 10 hlb 100 PART=c
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 u 13 0 25 0 hln 100 VALUE=100u
part 140 vdc 210 20 h
a 0 sp 0 0 22 37 hln 100 PART=vdc
a 1 u 13 0 -6 28 hcn 100 DC=12
a 0 x 0:13 0 0 0 hln 100 PKGREF=V1i
a 1 xp 9 0 -6 12 hcn 100 REFDES=V1i
part 144 r 230 20 d
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 u 13 0 30 5 hln 100 VALUE=5512
a 0 x 0:13 0 0 0 hln 100 PKGREF=R3i
a 0 xp 9 0 20 5 hln 100 REFDES=R3i
part 146 r 270 20 d
a 0 u 13 0 20 30 hln 100 VALUE=730k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=R2i
a 0 xp 9 0 10 25 hln 100 REFDES=R2i
part 143 r 290 20 d
a 0 u 13 0 25 0 hln 100 VALUE=2k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=R1i
a 0 xp 9 0 15 0 hln 100 REFDES=R1i
part 150 c 310 110 d
a 0 sp 0 0 0 10 hlb 100 PART=c
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 u 13 0 25 0 hln 100 VALUE=100u
a 0 x 0:13 0 0 0 hln 100 PKGREF=C3i
a 0 xp 9 0 15 0 hln 100 REFDES=C3i
part 149 c 310 70 h
a 0 sp 0 0 0 10 hlb 100 PART=c
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 u 13 0 5 25 hln 100 VALUE=100u
a 0 x 0:13 0 0 0 hln 100 PKGREF=C2i
a 0 xp 9 0 10 0 hln 100 REFDES=C2i
part 193 vsin 340 70 h
a 0 x 0:13 0 0 0 hln 100 PKGREF=V3
a 1 xp 9 0 30 5 hcn 100 REFDES=V3
a 1 u 13 13 40 15 hcn 100 VOFF=0
a 1 u 13 13 45 25 hcn 100 VAMPL=1m
a 1 u 13 13 45 35 hcn 100 FREQ=1k
part 142 c 240 90 h
a 0 x 0:13 0 0 0 hln 100 PKGREF=C1i
a 0 xp 9 0 10 0 hln 100 REFDES=C1i
a 0 sp 0 0 0 10 hlb 100 PART=c
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 u 13 0 5 25 hln 100 VALUE=100u
part 151 r 310 70 d
a 0 xp 9 0 15 30 hln 100 REFDES=R4i
a 0 u 13 0 25 25 hln 100 VALUE=4k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=R4i
part 154 qbreakn 250 130 H
a 0 sp 13 0 50 85 hln 100 MODEL=QbreakN
a 0 x 0:13 0 0 0 hln 100 PKGREF=Q4i
a 0 xp 9 0 -5 30 hln 100 REFDES=Q4i
a 0 sp 0 0 0 50 hln 100 PART=qbreakn
part 152 qbreakn 270 130 h
a 0 sp 13 0 -100 85 hln 100 MODEL=QbreakN
a 0 x 0:13 0 0 0 hln 100 PKGREF=Q1i
a 0 xp 9 0 -5 30 hln 100 REFDES=Q1i
a 0 sp 0 0 0 50 hln 100 PART=qbreakn
part 156 qbreakn 270 90 h
a 0 sp 13 0 -100 125 hln 100 MODEL=QbreakN
a 0 x 0:13 0 0 0 hln 100 PKGREF=Q2i
a 0 xp 9 0 5 5 hln 100 REFDES=Q2i
a 0 sp 0 0 0 50 hln 100 PART=qbreakn
part 70 r 110 20 d
a 0 u 13 0 25 0 hln 100 VALUE=2k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=R1
a 0 xp 9 0 15 0 hln 100 REFDES=R1
part 55 r 90 20 d
a 0 u 13 0 20 30 hln 100 VALUE=730k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=R2
a 0 xp 9 0 10 25 hln 100 REFDES=R2
part 87 r 160 70 d
a 0 u 13 0 30 0 hln 100 VALUE=200k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=Rp
a 0 xp 9 0 20 0 hln 100 REFDES=Rp
part 80 r 130 70 d
a 0 u 13 0 25 25 hln 100 VALUE=4k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=R4
a 0 xp 9 0 15 25 hln 100 REFDES=R4
part 61 qbreakn 90 130 h
a 0 sp 13 0 80 85 hln 100 MODEL=QbreakN
a 0 x 0:13 0 0 0 hln 100 PKGREF=Q1
a 0 xp 9 0 -5 30 hln 100 REFDES=Q1
a 0 sp 0 0 0 50 hln 100 PART=qbreakn
part 48 qbreakn 70 130 H
a 0 sp 13 0 -130 85 hln 100 MODEL=QbreakN
a 0 ap 9 0 -5 30 hln 100 REFDES=Q4
a 0 sp 0 0 0 50 hln 100 PART=qbreakn
a 0 a 0:13 0 0 0 hln 100 PKGREF=Q4
part 46 vsin 30 90 h
a 1 u 13 13 0 60 hcn 100 FREQ=1k
a 0 x 0:13 0 0 0 hln 100 PKGREF=V2
a 1 xp 9 0 -5 10 hcn 100 REFDES=V2
a 1 u 13 13 -5 40 hcn 100 VOFF=0
a 1 u 13 13 0 50 hcn 100 VAMPL=1m
part 45 vdc 30 20 h
a 0 sp 0 0 22 37 hln 100 PART=vdc
a 1 u 13 0 -6 28 hcn 100 DC=12
a 0 x 0:13 0 0 0 hln 100 PKGREF=V1
a 1 xp 9 0 -6 12 hcn 100 REFDES=V1
part 49 r 50 20 d
a 0 xp 9 0 20 5 hln 100 REFDES=R3
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=R3
a 0 u 13 0 30 5 hln 100 VALUE=5512
part 60 qbreakn 90 90 h
a 0 sp 13 0 80 125 hln 100 MODEL=QbreakN
a 0 x 0:13 0 0 0 hln 100 PKGREF=Q2
a 0 xp 9 0 5 5 hln 100 REFDES=Q2
a 0 sp 0 0 0 50 hln 100 PART=qbreakn
part 1 titleblk 970 720 h
a 1 s 13 0 350 10 hcn 100 PAGESIZE=A
a 1 s 13 0 180 60 hcn 100 PAGETITLE=
a 1 s 13 0 300 95 hrn 100 PAGENO=1
a 1 s 13 0 340 95 hrn 100 PAGECOUNT=1
@conn
w 139
a 0 up 0:33 0 0 0 hln 100 V=
s 230 60 230 110 138
a 0 up 33 0 232 85 hlt 100 V=
w 135
a 0 up 0:33 0 0 0 hln 100 V=
s 270 60 270 90 134
a 0 up 33 0 272 75 hlt 100 V=
w 133
a 0 up 0:33 0 0 0 hln 100 V=
s 250 130 270 130 132
a 0 up 33 0 260 129 hct 100 V=
w 123
a 0 up 0:33 0 0 0 hln 100 V=
s 290 60 290 70 124
s 310 70 290 70 122
a 0 up 33 0 300 69 hct 100 V=
w 121
a 0 up 0:33 0 0 0 hln 100 V=
s 290 110 310 110 120
a 0 up 33 0 300 109 hct 100 V=
w 107
a 0 up 0:33 0 0 0 hln 100 V=
s 230 150 290 150 155
s 290 150 310 150 153
s 310 150 310 140 110
s 310 150 340 150 108
s 340 150 340 110 106
s 210 150 230 150 116
s 210 90 240 90 136
s 210 90 210 150 169
a 0 up 33 0 212 120 hlt 100 V=
w 127
a 0 sr 0:3 0 250 18 hcn 100 LABEL=VCCi
a 0 up 0:33 0 0 0 hln 100 V=
s 230 20 270 20 145
a 0 sr 3 0 250 18 hcn 100 LABEL=VCCi
a 0 up 33 0 250 19 hct 100 V=
s 270 20 290 20 147
s 210 20 230 20 130
w 74
a 0 sr 0 0 0 0 hln 100 LABEL=VCC
a 0 up 0:33 0 0 0 hln 100 V=
s 50 20 90 20 75
a 0 up 0:33 0 70 19 hct 100 V=
a 0 sr 3 0 70 18 hcn 100 LABEL=VCC
s 90 20 110 20 77
s 30 20 50 20 73
w 72
a 0 up 0:33 0 0 0 hln 100 V=
s 130 70 110 70 83
a 0 up 0:33 0 140 84 hct 100 V=
s 110 60 110 70 71
a 0 up 33 0 112 55 hlt 100 V=
w 51
a 0 up 0:33 0 0 0 hln 100 V=
s 50 60 50 110 50
a 0 up 0:33 0 52 85 hlt 100 V=
s 50 110 70 110 198
s 70 130 90 130 62
a 0 up 0:33 0 80 129 hct 100 V=
s 70 110 70 130 200
w 57
a 0 up 0:33 0 0 0 hln 100 V=
s 90 60 90 90 56
a 0 up 0:33 0 82 50 hlt 100 V=
w 53
a 0 up 0:33 0 0 0 hln 100 V=
s 30 90 60 90 52
a 0 up 0:33 0 45 89 hct 100 V=
w 65
a 0 up 0:33 0 0 0 hln 100 V=
s 160 150 160 110 94
s 130 150 160 150 92
s 130 150 130 140 90
s 110 150 130 150 88
s 50 150 110 150 68
a 0 up 0:33 0 80 149 hct 100 V=
s 30 150 50 150 66
s 30 150 30 130 64
w 82
a 0 up 0:33 0 0 0 hln 100 V=
s 110 110 130 110 81
a 0 up 33 0 90 109 hct 100 V=
@junction
j 130 70
+ p 80 1
+ p 85 1
j 130 110
+ p 80 2
+ p 86 1
j 160 70
+ p 85 2
+ p 87 1
j 110 150
+ p 61 e
+ s 96
j 30 60
+ p 45 -
+ s 44
j 160 110
+ p 87 2
+ w 65
j 130 140
+ p 86 2
+ w 65
j 110 150
+ p 61 e
+ w 65
j 110 150
+ s 96
+ w 65
j 130 150
+ w 65
+ w 65
j 50 150
+ p 48 e
+ w 65
j 30 130
+ p 46 -
+ w 65
j 130 110
+ p 80 2
+ w 82
j 130 110
+ p 86 1
+ w 82
j 110 110
+ p 61 c
+ w 82
j 130 70
+ p 80 1
+ w 72
j 130 70
+ p 85 1
+ w 72
j 90 20
+ p 55 1
+ w 74
j 50 20
+ p 49 1
+ w 74
j 30 20
+ p 45 +
+ w 74
j 90 60
+ p 55 2
+ w 57
j 30 90
+ p 46 +
+ w 53
j 50 60
+ p 49 2
+ w 51
j 50 110
+ p 48 c
+ w 51
j 90 90
+ p 54 2
+ w 57
j 60 90
+ p 54 1
+ w 53
j 110 60
+ p 70 2
+ w 72
j 110 20
+ p 70 1
+ w 74
j 90 90
+ p 54 2
+ p 60 b
j 110 110
+ p 61 c
+ p 60 e
j 110 110
+ p 60 e
+ w 82
j 110 70
+ p 60 c
+ w 72
j 90 90
+ p 60 b
+ w 57
j 310 70
+ p 151 1
+ p 149 1
j 310 110
+ p 151 2
+ p 150 1
j 290 110
+ p 152 c
+ p 156 e
j 290 150
+ p 152 e
+ s 158
j 270 90
+ p 156 b
+ p 142 2
j 210 60
+ p 140 -
+ s 157
j 230 60
+ p 144 2
+ w 139
j 230 110
+ p 154 c
+ w 139
j 270 90
+ p 156 b
+ w 135
j 270 60
+ p 146 2
+ w 135
j 270 90
+ p 142 2
+ w 135
j 270 130
+ p 152 b
+ w 133
j 250 130
+ p 154 b
+ w 133
j 270 20
+ p 146 1
+ w 127
j 290 20
+ p 143 1
+ w 127
j 210 20
+ p 140 +
+ w 127
j 230 20
+ p 144 1
+ w 127
j 290 70
+ p 156 c
+ w 123
j 290 60
+ p 143 2
+ w 123
j 310 70
+ p 151 1
+ w 123
j 310 70
+ p 149 1
+ w 123
j 310 110
+ p 151 2
+ w 121
j 290 110
+ p 152 c
+ w 121
j 290 110
+ p 156 e
+ w 121
j 310 110
+ p 150 1
+ w 121
j 290 150
+ p 152 e
+ w 107
j 230 150
+ p 154 e
+ w 107
j 290 150
+ s 158
+ w 107
j 310 140
+ p 150 2
+ w 107
j 310 150
+ w 107
+ w 107
j 240 90
+ p 142 1
+ w 107
j 340 70
+ p 193 +
+ p 149 2
j 340 110
+ p 193 -
+ w 107
j 90 130
+ p 61 b
+ w 51
j 70 130
+ p 48 b
+ w 51
@attributes
a 0 s 0:13 0 0 0 hln 100 PAGETITLE=
a 0 s 0:13 0 0 0 hln 100 PAGENO=1
a 0 s 0:13 0 0 0 hln 100 PAGESIZE=A
a 0 s 0:13 0 0 0 hln 100 PAGECOUNT=1
@graphics
t 196 t 6 30 180 160 220 0 86
Kolo za verifikaciju DC napona i struja, parametara za mali signal i ulazne otpornosti
t 197 t 6 210 180 340 220 0 39
Kolo za verifikaciju izlazne otpornosti
