* Schematics Aliases *

.ALIASES
X_U1A           U1A(A=$N_0001 Y=$N_0002 PWR=$G_DPWR GND=$G_DGND )
R_R1            R1(1=$N_0004 2=$N_0003 )
I_I1            I1(+=0 -=$N_0005 )
R_R3            R3(1=$N_0005 2=0 )
V_V1            V1(+=$N_0003 -=0 )
S_S1            S1(3=$N_0005 4=$N_0007 1=$N_0006 2=0 )
RS_S1           S1(1=$N_0006 2=0 )
I_I3            I3(+=$N_0007 -=0 )
V_V2            V2(+=$N_0008 -=0 )
C_C2            C2(1=$N_0009 2=$N_0007 )
E_U5            U5(OUT=$N_0009 +=0 -=$N_0007 )
X_U3A           U3A(A=$N_0010 B=$N_0004 Y=$N_0001 PWR=$G_DPWR GND=$G_DGND )
E_U6            U6(OUT=$N_0010 +=$N_0008 -=$N_0009 )
X_U2A           U2A(A=$N_0004 Y=$N_0006 PWR=$G_DPWR GND=$G_DGND )
R_R2            R2(1=$N_0006 2=0 )
C_C1            C1(1=$N_0002 2=$N_0004 )
_    _($G_DGND=$G_DGND)
_    _($G_DPWR=$G_DPWR)
.ENDALIASES

