*version 9.1 970229
u 48
V? 5
R? 6
D? 5
U? 2
? 2
@libraries
@analysis
.DC 1 0 0 0 1 1
+ 0 0 Vg
+ 0 4 -3.5
+ 0 5 3.5
+ 0 6 0.1
.LIB C:\Users\sl190368d\Downloads\OE\D21\D21.lib
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
pageloc 1 0 3870 
@status
n 0 119:11:29:22:48:40;1577688520 e 
s 2832 119:11:29:23:18:37;1577690317 e 
*page 1 0 970 720 iA
@ports
port 2 agnd 50 150 h
port 27 agnd 160 190 h
port 26 agnd 190 150 h
@parts
part 5 r 50 80 h
a 0 u 13 0 25 0 hln 100 VALUE=10k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R2
a 0 ap 9 0 10 0 hln 100 REFDES=R2
part 22 vdc 160 190 u
a 1 u 13 0 29 23 hcn 100 DC=2.5
a 0 sp 0 0 22 37 hln 100 PART=vdc
a 0 a 0:13 0 0 0 hln 100 PKGREF=V4
a 1 ap 9 0 29 32 hcn 100 REFDES=V4
part 19 r 160 80 h
a 0 u 13 0 25 0 hln 100 VALUE=20k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R4
a 0 ap 9 0 5 0 hln 100 REFDES=R4
part 3 vdc 50 110 h
a 1 u 13 0 -11 28 hcn 100 DC=0
a 0 x 0:13 0 0 0 hln 100 PKGREF=Vg
a 1 xp 9 0 -11 17 hcn 100 REFDES=Vg
a 0 sp 0 0 22 37 hln 100 PART=vdc
part 28 r 230 50 h
a 0 u 13 0 25 0 hln 100 VALUE=10k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R5
a 0 ap 9 0 10 0 hln 100 REFDES=R5
part 21 vdc 190 50 v
a 1 u 13 0 24 33 hcn 100 DC=5
a 0 sp 0 0 22 37 hln 100 PART=vdc
a 0 a 0:13 0 0 0 hln 100 PKGREF=V3
a 1 ap 9 0 24 17 hcn 100 REFDES=V3
part 4 r 50 110 h
a 0 u 13 0 25 0 hln 100 VALUE=10k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R1
a 0 ap 9 0 10 0 hln 100 REFDES=R1
part 18 r 160 150 v
a 0 u 13 0 15 35 hln 100 VALUE=10k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R3
a 0 ap 9 0 25 30 hln 100 REFDES=R3
part 20 dbreak 160 50 h
a 0 sp 13 0 0 0 hln 100 MODEL=Dideal
a 0 x 0:13 0 0 0 hln 100 PKGREF=D2
a 0 xp 9 0 0 -10 hln 100 REFDES=D2
part 9 dbreak 130 110 h
a 0 sp 13 0 0 35 hln 100 MODEL=Dideal
a 0 x 0:13 0 0 0 hln 100 PKGREF=D1
a 0 xp 9 0 10 25 hln 100 REFDES=D1
part 6 vdc 130 110 d
a 1 u 13 0 -6 3 hcn 100 DC=2.5
a 0 sp 0 0 22 37 hln 100 PART=vdc
a 0 a 0:13 0 0 0 hln 100 PKGREF=V2
a 1 ap 9 0 -6 22 hcn 100 REFDES=V2
part 23 opamp 190 150 U
a 0 ap 9 0 49 10 hln 100 REFDES=U1
a 0 u 0:13 0 20 82 hlb 100 VPOS=+900V
a 0 u 0:13 0 20 91 hlb 100 VNEG=-900V
a 0 sp 11 0 50 60 hln 100 PART=opamp
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=U1
a 0 u 0:13 0 20 72 hlb 100 GAIN=1E6
part 1 titleblk 970 720 h
a 1 s 13 0 350 10 hcn 100 PAGESIZE=A
a 1 s 13 0 180 60 hcn 100 PAGETITLE=
a 1 s 13 0 340 95 hrn 100 PAGECOUNT=1
a 1 s 13 0 300 95 hrn 100 PAGENO=1
part 35 nodeMarker 270 130 h
a 0 s 0 0 0 0 hln 100 PROBEVAR=V2:+
a 0 s 0 0 0 0 hln 100 PROBEVAR=
a 0 a 0 0 4 22 hlb 100 LABEL=1
@conn
w 11
a 0 up 0:33 0 0 0 hln 100 V=
s 50 110 50 80 10
a 0 up 33 0 52 95 hlt 100 V=
w 13
a 0 up 0:33 0 0 0 hln 100 V=
s 90 80 160 80 12
a 0 up 33 0 125 64 hct 100 V=
s 160 80 160 110 14
s 160 80 160 50 16
s 160 110 190 110 46
w 30
a 0 up 0:33 0 0 0 hln 100 V=
s 200 80 270 80 29
a 0 up 33 0 235 79 hct 100 V=
s 270 50 270 80 33
s 270 80 270 130 36
@junction
j 50 150
+ p 3 -
+ s 2
j 50 110
+ p 3 +
+ w 11
j 190 50
+ p 21 +
+ p 20 2
j 230 50
+ p 28 1
+ p 21 -
j 50 110
+ p 4 1
+ p 3 +
j 90 110
+ p 6 -
+ p 4 2
j 50 110
+ p 4 1
+ w 11
j 50 80
+ p 5 1
+ w 11
j 160 110
+ p 18 2
+ w 13
j 160 150
+ p 22 -
+ p 18 1
j 160 190
+ s 27
+ p 22 +
j 200 80
+ p 19 2
+ w 30
j 270 50
+ p 28 2
+ w 30
j 270 80
+ w 30
+ w 30
j 160 80
+ w 13
+ w 13
j 160 80
+ p 19 1
+ w 13
j 160 50
+ p 20 1
+ w 13
j 90 80
+ p 5 2
+ w 13
j 190 150
+ p 23 +
+ s 26
j 270 130
+ p 23 OUT
+ w 30
j 190 110
+ p 23 -
+ w 13
j 130 110
+ p 9 1
+ p 6 +
j 160 110
+ p 9 2
+ w 13
j 160 110
+ p 18 2
+ p 9 2
j 270 130
+ p 35 pin1
+ p 23 OUT
j 270 130
+ p 35 pin1
+ w 30
@attributes
a 0 s 0:13 0 0 0 hln 100 PAGETITLE=
a 0 s 0:13 0 0 0 hln 100 PAGENO=1
a 0 s 0:13 0 0 0 hln 100 PAGESIZE=A
a 0 s 0:13 0 0 0 hln 100 PAGECOUNT=1
@graphics
