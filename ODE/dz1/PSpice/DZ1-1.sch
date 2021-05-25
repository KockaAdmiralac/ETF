*version 9.1 922216956
u 323
R? 24
C? 10
V? 12
U? 22
? 7
I? 5
S? 3
@libraries
@analysis
.TRAN 1 0 0 0
+0 1ns
+1 500us
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
pageloc 1 0 10524 
@status
n 0 121:04:14:19:18:13;1621012693 e 
s 2832 121:04:14:19:18:36;1621012716 e 
c 121:04:14:19:18:07;1621012687
*page 1 0 970 720 iA
@ports
port 2 agnd 190 210 h
port 17 agnd 260 290 h
port 51 agnd 400 210 h
port 52 agnd 470 290 h
port 219 agnd 260 550 h
port 221 agnd 360 430 h
port 220 agnd 480 430 h
port 218 agnd 180 490 h
@parts
part 4 r 230 210 v
a 0 u 13 0 5 0 hln 100 VALUE=1.5k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R2
a 0 ap 9 0 15 0 hln 100 REFDES=R2
part 8 vdc 190 170 h
a 1 ap 9 0 -11 27 hcn 100 REFDES=V1
a 1 u 13 0 -11 18 hcn 100 DC=10V
a 0 sp 0 0 22 37 hln 100 PART=vdc
a 0 a 0:13 0 0 0 hln 100 PKGREF=V1
part 3 r 190 170 h
a 0 u 13 0 10 0 hln 100 VALUE=1.5k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R1
a 0 ap 9 0 15 -10 hln 100 REFDES=R1
part 6 r 230 290 v
a 0 u 13 0 15 5 hln 100 VALUE=1.5k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R4
a 0 ap 9 0 25 5 hln 100 REFDES=R4
part 48 r 440 210 v
a 0 u 13 0 5 5 hln 100 VALUE=1.5k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R7
a 0 ap 9 0 15 0 hln 100 REFDES=R7
part 45 r 400 170 h
a 0 u 13 0 15 0 hln 100 VALUE=1.5k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R5
a 0 ap 9 0 15 -10 hln 100 REFDES=R5
part 46 vdc 400 170 h
a 1 ap 9 0 -11 17 hcn 100 REFDES=V2
a 0 sp 0 0 22 37 hln 100 PART=vdc
a 0 a 0:13 0 0 0 hln 100 PKGREF=V2
a 1 u 13 0 -11 28 hcn 100 DC=10V
part 49 r 440 290 v
a 0 u 13 0 15 5 hln 100 VALUE=1.5k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R8
a 0 ap 9 0 25 0 hln 100 REFDES=R8
part 5 r 260 210 v
a 0 ap 9 0 35 35 hln 100 REFDES=R3
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R3
a 0 u 13 0 25 40 hln 100 VALUE=1.5k
part 7 c 260 280 v
a 0 ap 9 0 15 40 hln 100 REFDES=C1
a 0 sp 0 0 0 10 hlb 100 PART=c
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=C1
a 0 u 13 0 5 45 hln 100 VALUE=100n
part 57 Sw_tClose 270 210 d
a 0 u 13 13 -2 -4 hln 100 tClose=100u
a 0 u 0 0 0 30 hln 100 ttran=1u
a 0 u 0 0 0 50 hln 100 Rclosed=0.01
a 0 ap 9 0 10 -10 hln 100 REFDES=U4
a 0 sp 0 0 0 24 hln 100 PART=Sw_tClose
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=U4
part 47 r 470 210 v
a 0 ap 9 0 25 40 hln 100 REFDES=R6
a 0 u 13 0 15 45 hln 100 VALUE=1.5k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R6
part 50 c 470 280 v
a 0 ap 9 0 15 35 hln 100 REFDES=C2
a 0 sp 0 0 0 10 hlb 100 PART=c
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=C2
a 0 u 13 0 5 40 hln 100 VALUE=100n
part 54 Sw_tOpen 480 210 d
a 0 u 13 13 10 -4 hln 100 tOpen=90u
a 0 sp 0 0 0 24 hln 100 PART=Sw_tOpen
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=U3
a 0 ap 9 0 20 -10 hln 100 REFDES=U3
part 207 idc 520 390 d
a 1 u 13 0 -9 6 hcn 100 DC=10mA
a 0 sp 11 0 -15 30 hln 100 PART=idc
a 0 a 0:13 0 0 0 hln 100 PKGREF=I4
a 1 ap 9 0 -20 10 hcn 100 REFDES=I4
part 215 c 210 420 h
a 0 u 13 0 25 0 hln 100 VALUE=10n
a 0 sp 0 0 0 10 hlb 100 PART=c
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=C8
a 0 ap 9 0 5 0 hln 100 REFDES=C8
part 208 r 480 390 d
a 0 u 13 0 30 25 hln 100 VALUE=1k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R19
a 0 ap 9 0 20 30 hln 100 REFDES=R19
part 206 vdc 260 510 h
a 1 u 13 0 -11 18 hcn 100 DC=3V
a 0 sp 0 0 22 37 hln 100 PART=vdc
a 0 a 0:13 0 0 0 hln 100 PKGREF=V8
a 1 ap 9 0 -11 27 hcn 100 REFDES=V8
part 259 7400 610 470 h
a 0 sp 0 0 40 50 hln 100 MODEL=74HC00
a 0 sp 11 0 40 50 hln 100 PART=7400
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=DIP14
a 0 s 0:13 0 0 0 hln 100 GATE=A
a 0 a 0:13 0 0 0 hln 100 PKGREF=U19
a 0 ap 9 0 40 0 hln 100 REFDES=U19A
part 256 7404 680 480 h
a 0 sp 11 0 20 40 hln 100 PART=7404
a 0 sp 0 0 40 40 hln 100 MODEL=74HC04
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=DIP14
a 0 s 0:13 0 0 0 hln 100 GATE=A
a 0 a 0:13 0 0 0 hln 100 PKGREF=U17
a 0 ap 9 0 18 8 hln 100 REFDES=U17A
part 255 vdc 610 410 d
a 1 ap 9 0 -11 17 hcn 100 REFDES=V11
a 0 sp 0 0 22 37 hln 100 PART=vdc
a 0 a 0:13 0 0 0 hln 100 PKGREF=V11
a 1 u 13 0 -11 3 hcn 100 DC=5V
part 258 7404 740 480 h
a 0 sp 11 0 25 35 hln 100 PART=7404
a 0 sp 0 0 40 40 hln 100 MODEL=74HC04
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=DIP14
a 0 s 0:13 0 0 0 hln 100 GATE=A
a 0 a 0:13 0 0 0 hln 100 PKGREF=U18
a 0 ap 9 0 23 8 hln 100 REFDES=U18A
part 254 r 610 450 v
a 0 u 13 0 20 30 hln 100 VALUE=10k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R22
a 0 ap 9 0 30 35 hln 100 REFDES=R22
part 205 idc 180 450 h
a 1 u 13 0 -9 21 hcn 100 DC=2mA
a 0 sp 11 0 -20 10 hln 100 PART=idc
a 0 a 0:13 0 0 0 hln 100 PKGREF=I3
a 1 ap 9 0 -5 10 hcn 100 REFDES=I3
part 214 SBreak 370 430 V
a 0 s 13 0 20 60 hln 100 MODEL=Sbreak
a 0 a 0:13 0 0 0 hln 100 PKGREF=S2
a 0 ap 9 0 10 47 hln 100 REFDES=S2
part 286 opamp 180 490 U
a 0 ap 9 0 29 65 hln 100 REFDES=U21
a 0 u 0:13 0 20 72 hlb 100 GAIN=1E3
a 0 u 0:13 0 20 82 hlb 100 VPOS=+12V
a 0 u 0:13 0 20 91 hlb 100 VNEG=-12V
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=U21
a 0 sp 11 0 60 65 hln 100 PART=opamp
part 285 opamp 260 510 U
a 0 ap 9 0 44 65 hln 100 REFDES=U20
a 0 u 0:13 0 20 82 hlb 100 VPOS=+5V
a 0 u 0:13 0 20 91 hlb 100 VNEG=0V
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=
a 0 u 0:13 0 20 72 hlb 100 GAIN=1E3
a 0 a 0:13 0 0 0 hln 100 PKGREF=U20
a 0 sp 11 0 70 65 hln 100 PART=opamp
part 253 c 660 450 h
a 0 sp 0 0 0 10 hlb 100 PART=c
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=C9
a 0 ap 9 0 0 0 hln 100 REFDES=C9
a 0 u 13 0 15 0 hln 100 VALUE=1n
part 1 titleblk 970 720 h
a 1 s 13 0 350 10 hcn 100 PAGESIZE=A
a 1 s 13 0 180 60 hcn 100 PAGETITLE=
a 1 s 13 0 340 95 hrn 100 PAGECOUNT=1
a 1 s 13 0 300 95 hrn 100 PAGENO=1
part 319 nodeMarker 260 470 h
a 0 s 0 0 0 0 hln 100 PROBEVAR=S2:3
a 0 a 0 0 4 22 hlb 100 LABEL=6
@conn
w 240
a 0 up 0:33 0 0 0 hln 100 V=
s 730 450 730 480 239
s 690 450 730 450 241
a 0 up 33 0 710 434 hct 100 V=
s 740 480 730 480 243
w 273
a 0 up 0:33 0 0 0 hln 100 V=
s 610 490 340 490 272
a 0 up 33 0 475 489 hct 100 V=
w 188
a 0 up 0:33 0 0 0 hln 100 V=
s 520 410 570 410 290
s 520 410 520 430 294
s 520 390 520 410 189
a 0 up 33 0 512 375 hlt 100 V=
s 520 430 480 430 187
a 0 up 33 0 500 429 hct 100 V=
w 41
a 0 up 0:33 0 0 0 hln 100 V=
s 440 250 470 250 42
s 440 250 440 210 40
a 0 up 33 0 407 235 hlt 100 V=
w 39
a 0 up 0:33 0 0 0 hln 100 V=
s 440 170 470 170 38
a 0 up 33 0 455 149 hct 100 V=
w 20
a 0 up 0:33 0 0 0 hln 100 V=
s 230 250 230 210 29
a 0 up 33 0 197 235 hlt 100 V=
s 230 250 260 250 9
w 12
a 0 up 0:33 0 0 0 hln 100 V=
s 230 170 260 170 11
a 0 up 33 0 245 144 hct 100 V=
w 35
a 0 up 0:33 0 0 0 hln 100 V=
s 440 290 470 290 36
a 0 up 33 0 455 289 hct 100 V=
s 470 290 470 280 34
w 14
a 0 up 0:33 0 0 0 hln 100 V=
s 260 290 260 280 15
s 230 290 260 290 13
a 0 up 33 0 245 289 hct 100 V=
w 246
a 0 up 0:33 0 0 0 hln 100 V=
s 610 450 610 470 245
s 660 450 610 450 247
a 0 up 33 0 635 434 hct 100 V=
w 176
a 0 up 0:33 0 0 0 hln 100 V=
s 360 390 180 390 283
a 0 up 33 0 270 389 hct 100 V=
s 180 450 180 420 181
s 180 420 210 420 179
s 180 390 180 420 177
w 277
a 0 up 0:33 0 0 0 hln 100 V=
s 790 480 790 530 276
s 790 530 370 530 278
a 0 up 33 0 580 529 hct 100 V=
s 370 530 370 430 322
w 194
a 0 up 0:33 0 0 0 hln 100 V=
s 370 390 480 390 193
a 0 up 33 0 425 389 hct 100 V=
w 196
a 0 up 0:33 0 0 0 hln 100 V=
s 240 420 260 420 197
s 260 420 260 470 195
a 0 up 33 0 257 435 hlt 100 V=
@junction
j 230 170
+ p 4 2
+ p 3 2
j 190 170
+ p 8 +
+ p 3 1
j 190 210
+ p 8 -
+ s 2
j 440 170
+ p 48 2
+ p 45 2
j 400 170
+ p 45 1
+ p 46 +
j 400 210
+ p 46 -
+ s 51
j 260 210
+ p 5 1
+ p 57 1
j 260 250
+ p 7 2
+ p 57 2
j 470 210
+ p 47 1
+ p 54 1
j 470 250
+ p 50 2
+ p 54 2
j 480 390
+ p 207 -
+ p 208 1
j 480 430
+ p 208 2
+ s 220
j 360 430
+ p 214 2
+ s 221
j 260 550
+ p 206 -
+ s 219
j 180 490
+ p 205 -
+ s 218
j 610 410
+ p 254 2
+ p 255 +
j 610 450
+ p 254 1
+ w 246
j 730 480
+ p 256 Y
+ w 240
j 740 480
+ p 258 A
+ w 240
j 570 410
+ p 255 -
+ w 188
j 520 390
+ p 207 +
+ w 188
j 520 410
+ w 188
+ w 188
j 480 430
+ p 208 2
+ w 188
j 480 430
+ s 220
+ w 188
j 790 480
+ p 258 Y
+ w 277
j 370 430
+ p 214 1
+ w 277
j 240 420
+ p 215 2
+ w 196
j 360 390
+ p 214 4
+ w 176
j 180 450
+ p 205 +
+ w 176
j 210 420
+ p 215 1
+ w 176
j 180 420
+ w 176
+ w 176
j 480 390
+ p 207 -
+ w 194
j 480 390
+ p 208 1
+ w 194
j 370 390
+ p 214 3
+ w 194
j 440 250
+ p 49 2
+ w 41
j 470 250
+ p 50 2
+ w 41
j 470 250
+ p 54 2
+ w 41
j 440 210
+ p 48 1
+ w 41
j 440 170
+ p 48 2
+ w 39
j 440 170
+ p 45 2
+ w 39
j 470 170
+ p 47 2
+ w 39
j 230 210
+ p 4 1
+ w 20
j 230 250
+ p 6 2
+ w 20
j 260 250
+ p 7 2
+ w 20
j 260 250
+ p 57 2
+ w 20
j 230 170
+ p 4 2
+ w 12
j 230 170
+ p 3 2
+ w 12
j 260 170
+ p 5 2
+ w 12
j 440 290
+ p 49 1
+ w 35
j 470 290
+ s 52
+ w 35
j 470 280
+ p 50 1
+ w 35
j 260 280
+ p 7 1
+ w 14
j 260 290
+ s 17
+ w 14
j 230 290
+ p 6 1
+ w 14
j 660 450
+ p 253 1
+ w 246
j 690 450
+ p 253 2
+ w 240
j 680 480
+ p 259 Y
+ p 256 A
j 610 470
+ p 259 A
+ w 246
j 610 490
+ p 259 B
+ w 273
j 180 450
+ p 205 +
+ p 286 -
j 180 490
+ p 205 -
+ p 286 +
j 180 490
+ p 286 +
+ s 218
j 260 470
+ p 286 OUT
+ w 196
j 180 450
+ p 286 -
+ w 176
j 260 510
+ p 206 +
+ p 285 +
j 260 470
+ p 286 OUT
+ p 285 -
j 340 490
+ p 285 OUT
+ w 273
j 260 470
+ p 285 -
+ w 196
j 260 470
+ p 319 pin1
+ p 286 OUT
j 260 470
+ p 319 pin1
+ p 285 -
j 260 470
+ p 319 pin1
+ w 196
@attributes
a 0 s 0:13 0 0 0 hln 100 PAGETITLE=
a 0 s 0:13 0 0 0 hln 100 PAGENO=1
a 0 s 0:13 0 0 0 hln 100 PAGESIZE=A
a 0 s 0:13 0 0 0 hln 100 PAGECOUNT=1
@graphics
r 167 r 0 140 120 340 320
r 170 r 0 360 120 550 320
t 173 t 5 210 126 280 140 0 17
1. zadatak pod a)
t 174 t 5 420 126 490 140 0 17
1. zadatak pod b)
r 299 r 0 140 580 550 340
r 300 r 0 570 340 820 580
t 320 t 5 660 345 730 361 0 17
2. zadatak pod b)
t 321 t 5 320 345 390 361 0 17
2. zadatak pod c)
