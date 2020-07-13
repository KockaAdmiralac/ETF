*version 9.1 915938214
u 48
V? 3
R? 9
U? 3
D? 2
? 2
@libraries
@analysis
.DC 1 0 0 0 1 1
+ 0 0 Vg
+ 0 4 0
+ 0 5 4
+ 0 6 0.1
.LIB C:\Users\sl190368d\Downloads\OE\D22\D22.lib
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
pageloc 1 0 3990 
@status
c 119:11:29:22:59:17;1577689157
n 0 119:11:29:22:59:21;1577689161 e 
s 0 119:11:29:22:59:22;1577689162 e 
*page 1 0 970 720 iA
@ports
port 1 agnd 20 170 h
port 10 agnd 60 230 h
port 30 agnd 140 120 h
@parts
part 19 r 80 20 h
a 0 u 13 0 25 0 hln 100 VALUE=20k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R5
a 0 ap 9 0 5 0 hln 100 REFDES=R5
part 28 r 140 80 h
a 0 u 13 0 25 0 hln 100 VALUE=10k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R6
a 0 ap 9 0 10 0 hln 100 REFDES=R6
part 29 r 140 80 d
a 0 u 13 0 35 25 hln 100 VALUE=10k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R7
a 0 ap 9 0 25 25 hln 100 REFDES=R7
part 33 vdc 180 80 h
a 1 u 13 0 -6 28 hcn 100 DC=5
a 0 sp 0 0 22 37 hln 100 PART=vdc
a 0 x 0:13 0 0 0 hln 100 PKGREF=Vcc
a 1 xp 9 0 -11 17 hcn 100 REFDES=Vcc
part 8 r 60 190 h
a 0 u 13 0 25 25 hln 100 VALUE=10k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R3
a 0 ap 9 0 10 25 hln 100 REFDES=R3
part 9 r 60 190 d
a 0 u 13 0 25 30 hln 100 VALUE=10k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R4
a 0 ap 9 0 15 25 hln 100 REFDES=R4
part 5 opamp 60 130 h
a 0 ap 9 0 44 10 hln 100 REFDES=U1
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=U1
a 0 sp 11 0 35 55 hln 100 PART=opamp
part 18 opamp 140 40 H
a 0 ap 9 0 39 10 hln 100 REFDES=U2
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=U2
a 0 sp 11 0 35 55 hln 100 PART=opamp
part 4 r 60 130 v
a 0 u 13 0 15 35 hln 100 VALUE=10k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R2
a 0 ap 9 0 25 30 hln 100 REFDES=R2
part 3 r 20 130 h
a 0 u 13 0 20 0 hln 100 VALUE=10k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R1
a 0 ap 9 0 5 0 hln 100 REFDES=R1
part 2 vdc 20 130 h
a 1 u 13 0 29 28 hcn 100 DC=0
a 0 sp 0 0 22 37 hln 100 PART=vdc
a 0 x 0:13 0 0 0 hln 100 PKGREF=Vg
a 1 xp 9 0 29 17 hcn 100 REFDES=Vg
part 34 r 140 40 h
a 0 u 13 0 25 0 hln 100 VALUE=10k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R8
a 0 ap 9 0 10 0 hln 100 REFDES=R8
part 17 dbreak 60 90 v
a 0 a 0:13 0 0 0 hln 100 PKGREF=D1
a 0 ap 9 0 20 0 hln 100 REFDES=D1
a 0 sp 13 0 10 5 hln 100 MODEL=Dbreak
part 47 nodeMarker 200 150 h
a 0 s 0 0 0 0 hln 100 PROBEVAR=
a 0 s 0 0 0 0 hln 100 PROBEVAR=
a 0 a 0 0 4 22 hlb 100 LABEL=1
@conn
w 25
a 0 up 0:33 0 0 0 hln 100 V=
s 140 20 140 40 26
s 120 20 140 20 24
a 0 up 33 0 130 19 hct 100 V=
w 32
a 0 up 0:33 0 0 0 hln 100 V=
s 140 120 180 120 31
a 0 up 33 0 160 119 hct 100 V=
w 21
a 0 up 0:33 0 0 0 hln 100 V=
s 60 20 80 20 22
s 60 60 60 20 20
a 0 up 33 0 62 40 hlt 100 V=
w 7
a 0 up 0:33 0 0 0 hln 100 V=
s 60 170 60 190 6
a 0 up 33 0 62 180 hlt 100 V=
w 12
a 0 up 0:33 0 0 0 hln 100 V=
s 200 40 180 40 39
s 200 150 200 40 37
a 0 up 33 0 202 95 hlt 100 V=
s 140 150 200 150 35
s 140 190 140 150 13
s 100 190 140 190 11
@junction
j 60 130
+ p 3 2
+ p 4 1
j 20 130
+ p 3 1
+ p 2 +
j 60 130
+ p 3 2
+ p 5 +
j 60 190
+ p 9 1
+ p 8 1
j 60 230
+ p 9 2
+ s 10
j 60 90
+ p 4 2
+ p 17 1
j 60 130
+ p 4 1
+ p 5 +
j 60 60
+ p 17 2
+ p 18 OUT
j 140 80
+ p 29 1
+ p 28 1
j 140 80
+ p 29 1
+ p 18 -
j 140 120
+ p 29 2
+ s 30
j 180 80
+ p 28 2
+ p 33 +
j 140 80
+ p 28 1
+ p 18 -
j 20 170
+ p 2 -
+ s 1
j 140 40
+ p 18 +
+ p 34 1
j 180 40
+ p 34 2
+ w 12
j 140 150
+ p 5 OUT
+ w 12
j 100 190
+ p 8 2
+ w 12
j 140 40
+ p 18 +
+ w 25
j 140 40
+ p 34 1
+ w 25
j 120 20
+ p 19 2
+ w 25
j 140 120
+ p 29 2
+ w 32
j 180 120
+ p 33 -
+ w 32
j 140 120
+ s 30
+ w 32
j 80 20
+ p 19 1
+ w 21
j 60 60
+ p 17 2
+ w 21
j 60 60
+ p 18 OUT
+ w 21
j 60 190
+ p 9 1
+ w 7
j 60 190
+ p 8 1
+ w 7
j 60 170
+ p 5 -
+ w 7
j 200 150
+ p 47 pin1
+ w 12
@attributes
a 0 s 0:13 0 0 0 hln 100 PAGETITLE=
a 0 s 0:13 0 0 0 hln 100 PAGENO=1
a 0 s 0:13 0 0 0 hln 100 PAGESIZE=A
a 0 s 0:13 0 0 0 hln 100 PAGECOUNT=1
@graphics
