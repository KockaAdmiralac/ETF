*version 9.1 1037395354
u 90
V? 3
U? 7
R? 4
C? 3
I? 4
S? 2
? 4
@libraries
@analysis
.TRAN 1 0 0 0
+0 0ns
+1 400u
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
pageloc 1 0 6085 
@status
c 121:04:21:02:19:49;1621556389
n 0 121:04:21:02:19:54;1621556394 e 
s 2832 121:04:21:02:20:07;1621556407 e 
*page 1 0 970 720 iA
@ports
port 16 agnd 730 430 v
port 54 agnd 640 350 u
port 22 agnd 720 370 h
port 83 agnd 300 420 h
port 25 agnd 330 440 h
@parts
part 9 7404 560 430 h
a 0 sp 11 0 25 45 hln 100 PART=7404
a 0 sp 0 0 40 40 hln 100 MODEL=74HC04
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=DIP14
a 0 s 0:13 0 0 0 hln 100 GATE=A
a 0 a 0:13 0 0 0 hln 100 PKGREF=U1
a 0 ap 9 0 3 48 hln 100 REFDES=U1A
part 10 r 640 430 v
a 0 ap 9 0 25 25 hln 100 REFDES=R1
a 0 u 13 0 15 25 hln 100 VALUE=10k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R1
part 20 idc 760 330 d
a 1 u 13 0 -9 6 hcn 100 DC=10m
a 0 sp 11 0 0 50 hln 100 PART=idc
a 0 a 0:13 0 0 0 hln 100 PKGREF=I1
a 1 ap 9 0 -10 30 hcn 100 REFDES=I1
part 21 r 720 330 d
a 0 ap 9 0 20 5 hln 100 REFDES=R3
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R3
a 0 u 13 0 30 5 hln 100 VALUE=1k
part 8 vdc 640 390 u
a 1 u 13 0 24 18 hcn 100 DC=5V
a 0 sp 0 0 22 37 hln 100 PART=vdc
a 0 a 0:13 0 0 0 hln 100 PKGREF=V1
a 1 ap 9 0 24 27 hcn 100 REFDES=V1
part 45 sbreak 690 370 V
a 0 ap 9 0 45 12 hln 100 REFDES=S1
a 0 a 0:13 0 0 0 hln 100 PKGREF=S1
a 0 s 13 0 45 40 hln 100 MODEL=Sbreak
part 80 idc 300 380 h
a 0 sp 11 0 -15 35 hln 100 PART=idc
a 1 ap 9 0 -10 10 hcn 100 REFDES=I3
a 0 a 0:13 0 0 0 hln 100 PKGREF=I3
a 1 u 13 0 -9 21 hcn 100 DC=2m
part 32 vdc 410 440 d
a 1 ap 9 0 -6 17 hcn 100 REFDES=V2
a 0 sp 0 0 22 37 hln 100 PART=vdc
a 0 a 0:13 0 0 0 hln 100 PKGREF=V2
a 1 u 13 0 -6 3 hcn 100 DC=3V
part 38 c 370 360 H
a 0 u 0 0 0 0 hln 100 IC=0
a 0 u 13 0 20 0 hln 100 VALUE=10n
a 0 sp 0 0 0 10 hlb 100 PART=c
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=C2
a 0 ap 9 0 5 0 hln 100 REFDES=C2
part 28 opamp 330 420 U
a 0 ap 9 0 79 55 hln 100 REFDES=U5
a 0 u 0:13 0 20 82 hlb 100 VPOS=+12V
a 0 u 0:13 0 20 91 hlb 100 VNEG=-12V
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=U5
a 0 sp 11 0 65 55 hln 100 PART=opamp
part 14 7400 490 420 h
a 0 sp 11 0 40 0 hln 100 PART=7400
a 0 sp 0 0 40 50 hln 100 MODEL=74HC00
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=DIP14
a 0 s 0:13 0 0 0 hln 100 GATE=A
a 0 a 0:13 0 0 0 hln 100 PKGREF=U3
a 0 ap 9 0 15 0 hln 100 REFDES=U3A
part 29 opamp 410 440 U
a 0 ap 9 0 69 60 hln 100 REFDES=U6
a 0 u 0:13 0 20 91 hlb 100 VNEG=0V
a 0 u 0:13 0 20 82 hlb 100 VPOS=5V
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=U6
a 0 sp 11 0 50 60 hln 100 PART=opamp
part 11 c 610 430 h
a 0 sp 0 0 0 10 hlb 100 PART=c
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=C1
a 0 ap 9 0 5 25 hln 100 REFDES=C1
a 0 u 13 0 20 25 hln 100 VALUE=6n
part 13 r 690 430 h
a 0 u 13 0 20 0 hln 100 VALUE=1k
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R2
a 0 ap 9 0 5 0 hln 100 REFDES=R2
part 12 7404 640 430 h
a 0 sp 11 0 35 45 hln 100 PART=7404
a 0 sp 0 0 40 40 hln 100 MODEL=74HC04
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=DIP14
a 0 s 0:13 0 0 0 hln 100 GATE=A
a 0 a 0:13 0 0 0 hln 100 PKGREF=U2
a 0 ap 9 0 18 43 hln 100 REFDES=U2A
part 1 titleblk 970 720 h
a 1 s 13 0 350 10 hcn 100 PAGESIZE=A
a 1 s 13 0 180 60 hcn 100 PAGETITLE=
a 1 s 13 0 340 95 hrn 100 PAGECOUNT=1
a 1 s 13 0 300 95 hrn 100 PAGENO=1
part 73 nodeMarker 410 400 h
a 0 s 0 0 0 0 hln 100 PROBEVAR=
a 0 s 0 0 0 0 hln 100 PROBEVAR=
a 0 s 0 0 0 0 hln 100 PROBEVAR=R2:1
a 0 a 0 0 4 22 hlb 100 LABEL=1
part 88 nodeMarker 490 420 h
a 0 s 0 0 0 0 hln 100 PROBEVAR=
a 0 s 0 0 0 0 hln 100 PROBEVAR=
a 0 s 0 0 0 0 hln 100 PROBEVAR=
a 0 a 0 0 4 22 hlb 100 LABEL=2
@conn
w 3
a 0 up 0:33 0 0 0 hln 100 V=
s 640 430 640 480 2
s 640 480 490 480 4
a 0 up 33 0 565 479 hct 100 V=
s 490 480 490 440 6
w 70
a 0 up 0:33 0 0 0 hln 100 V=
s 760 330 760 370 69
s 760 370 720 370 71
a 0 up 33 0 740 369 hct 100 V=
w 47
a 0 up 0:33 0 0 0 hln 100 V=
s 720 330 690 330 46
a 0 up 33 0 705 329 hct 100 V=
w 62
a 0 up 0:33 0 0 0 hln 100 V=
s 640 350 660 350 61
s 660 370 680 370 65
s 660 350 660 370 63
a 0 up 33 0 662 360 hlt 100 V=
w 79
a 0 up 0:33 0 0 0 hln 100 V=
s 330 440 330 420 35
s 370 440 330 440 33
a 0 up 33 0 350 439 hct 100 V=
w 87
a 0 up 0:33 0 0 0 hln 100 V=
s 330 360 340 360 41
s 330 380 330 360 39
s 330 360 330 330 86
s 330 380 300 380 81
s 680 330 330 330 48
a 0 up 33 0 505 329 hct 100 V=
w 49
a 0 up 0:33 0 0 0 hln 100 V=
s 410 400 410 360 36
s 370 360 410 360 43
a 0 up 33 0 390 359 hct 100 V=
w 59
a 0 up 0:33 0 0 0 hln 100 V=
s 690 430 690 370 74
a 0 up 33 0 692 400 hlt 100 V=
@junction
j 640 430
+ p 10 1
+ w 3
j 610 430
+ p 11 1
+ p 9 Y
j 640 430
+ p 11 2
+ p 10 1
j 640 430
+ p 11 2
+ w 3
j 640 430
+ p 12 A
+ p 10 1
j 640 430
+ p 12 A
+ p 11 2
j 640 430
+ p 12 A
+ w 3
j 690 430
+ p 13 1
+ p 12 Y
j 560 430
+ p 14 Y
+ p 9 A
j 490 440
+ p 14 B
+ w 3
j 730 430
+ s 16
+ p 13 2
j 640 390
+ p 8 +
+ p 10 2
j 640 350
+ s 54
+ p 8 -
j 720 330
+ p 21 1
+ p 20 -
j 720 370
+ p 21 2
+ s 22
j 720 330
+ p 21 1
+ w 47
j 720 330
+ p 20 -
+ w 47
j 690 430
+ p 12 Y
+ w 59
j 690 430
+ p 13 1
+ w 59
j 680 330
+ p 45 4
+ w 87
j 690 330
+ p 45 3
+ w 47
j 690 370
+ p 45 1
+ w 59
j 640 350
+ p 8 -
+ w 62
j 640 350
+ s 54
+ w 62
j 680 370
+ p 45 2
+ w 62
j 760 330
+ p 20 +
+ w 70
j 720 370
+ p 21 2
+ w 70
j 720 370
+ s 22
+ w 70
j 370 440
+ p 32 -
+ w 79
j 300 380
+ p 80 +
+ w 87
j 300 420
+ s 83
+ p 80 -
j 330 440
+ s 25
+ w 79
j 340 360
+ p 38 2
+ w 87
j 330 360
+ w 87
+ w 87
j 490 420
+ p 88 pin1
+ p 14 A
j 410 400
+ p 28 OUT
+ p 29 -
j 330 420
+ p 28 +
+ w 79
j 410 400
+ p 28 OUT
+ w 49
j 330 380
+ p 28 -
+ w 87
j 410 400
+ p 73 pin1
+ p 28 OUT
j 490 420
+ p 29 OUT
+ p 14 A
j 410 440
+ p 32 +
+ p 29 +
j 410 400
+ p 29 -
+ w 49
j 410 400
+ p 73 pin1
+ p 29 -
j 490 420
+ p 88 pin1
+ p 29 OUT
j 370 360
+ p 38 1
+ w 49
j 410 400
+ p 73 pin1
+ w 49
@attributes
a 0 s 0:13 0 0 0 hln 100 PAGETITLE=
a 0 s 0:13 0 0 0 hln 100 PAGENO=1
a 0 s 0:13 0 0 0 hln 100 PAGESIZE=A
a 0 s 0:13 0 0 0 hln 100 PAGECOUNT=1
@graphics
