// OpenGL CSG Rendering
//
// Nigel Stewart (nigels@nigels.com)
// RMIT Department of Mechanical and Manufacturing Engineering
// RMIT School of Computer Science and IT
//
// Sample CSG models

char defaultTree[] =
"X1 = sphere    yellow scale 2.0 2.0 2.0\n"
"X2 = box       green  scale 1.5 1.5 1.5\n"
"A = cylinder  orange scale 0.8 0.8 5.0 translate 0.0 0.0 -2.5\n"
"B = cylinder  orange scale 0.8 0.8 5.0 translate 0.0 0.0 -2.5 rotate 0.0 1.0 0.0 90.0\n"
"Tree = (X1+X2)\n"
"Tree = (X1.X2)\n"
"Tree = (X1-X2)\n"
"Tree = (X2-X1)\n"
"Tree = (A+B)\n"
"Tree = (A.B)\n"
"Tree = ((X1+X2)+(A+B))\n"
"Tree = ((X1.X2)-(A+B))\n"
"Tree = (X1-(A+B))\n"
"Tree = (X2-(A+B))\n"
"Tree = ((X1-X2)-(A+B))\n"
"Tree = ((X1-X2)+(A+B))\n"
"Tree = (((X1-X2)+(A+B))-(X1.(A+B)))\n"
"Tree = (X1-A)\n"
"Tree = (X1-B)\n"
"Tree = (X2-A)\n"
"Tree = (X2-B)\n";

char rowTree[] =
"S00 =    sphere blue scale 0.2 0.2 0.2 translate -1.0  0.0 0.2\n"
"S01 =    sphere blue scale 0.2 0.2 0.2 translate -0.5 -0.0 0.2\n"
"S02 =    sphere blue scale 0.2 0.2 0.2 translate -0.0 -0.0 0.2\n"
"S03 =    sphere blue scale 0.2 0.2 0.2 translate  0.5  0.0 0.2\n"
"S04 =    sphere blue scale 0.2 0.2 0.2 translate  1.0  0.0 0.2\n"
"Tree = (S00+(S01+(S02+(S03+S04))))\n"
"Tree = (S00-S01)\n"
"Tree = (S00.S01)\n";

char gridTree[] =
"WP  = box    slateBlue   scale 1.0 1.0 0.1\n"
"S00 = sphere grey           scale 0.2 0.2 0.2 translate -0.8 -0.8  0.2\n"
"S01 = sphere grey           scale 0.2 0.2 0.2 translate -0.4 -0.8  0.2\n"
"S02 = sphere grey           scale 0.2 0.2 0.2 translate -0.0 -0.8  0.2\n"
"S03 = sphere grey           scale 0.2 0.2 0.2 translate  0.4 -0.8  0.2\n"
"S04 = sphere grey           scale 0.2 0.2 0.2 translate  0.8 -0.8  0.2\n"
"S05 = sphere grey           scale 0.2 0.2 0.2 translate -0.8 -0.4  0.2\n"
"S06 = sphere grey           scale 0.2 0.2 0.2 translate -0.4 -0.4  0.2\n"
"S07 = sphere grey           scale 0.2 0.2 0.2 translate -0.0 -0.4  0.2\n"
"S08 = sphere grey           scale 0.2 0.2 0.2 translate  0.4 -0.4  0.2\n"
"S09 = sphere grey           scale 0.2 0.2 0.2 translate  0.8 -0.4  0.2\n"
"S10 = sphere grey           scale 0.2 0.2 0.2 translate -0.8  0.0  0.2\n"
"S11 = sphere grey           scale 0.2 0.2 0.2 translate -0.4  0.0  0.2\n"
"S12 = sphere grey           scale 0.2 0.2 0.2 translate -0.0  0.0  0.2\n"
"S13 = sphere grey           scale 0.2 0.2 0.2 translate  0.4  0.0  0.2\n"
"S14 = sphere grey           scale 0.2 0.2 0.2 translate  0.8  0.0  0.2\n"
"S15 = sphere grey           scale 0.2 0.2 0.2 translate -0.8  0.4  0.2\n"
"S16 = sphere grey           scale 0.2 0.2 0.2 translate -0.4  0.4  0.2\n"
"S17 = sphere grey           scale 0.2 0.2 0.2 translate -0.0  0.4  0.2\n"
"S18 = sphere grey           scale 0.2 0.2 0.2 translate  0.4  0.4  0.2\n"
"S19 = sphere grey           scale 0.2 0.2 0.2 translate  0.8  0.4  0.2\n"
"S20 = sphere grey           scale 0.2 0.2 0.2 translate -0.8  0.8  0.2\n"
"S21 = sphere grey           scale 0.2 0.2 0.2 translate -0.4  0.8  0.2\n"
"S22 = sphere grey           scale 0.2 0.2 0.2 translate -0.0  0.8  0.2\n"
"S23 = sphere grey           scale 0.2 0.2 0.2 translate  0.4  0.8  0.2\n"
"S24 = sphere grey           scale 0.2 0.2 0.2 translate  0.8  0.8  0.2\n"
"Tree = (WP-(S00+(S01+(S02+(S03+(S04+(S05+(S06+(S07+(S08+(S09+(S10+(S11+(S12+(S13+(S14+(S15+(S16+(S17+(S18+(S19+(S20+(S21+(S22+(S23+S24)))))))))))))))))))))))))\n"
"Tree = (WP+(S00+(S01+(S02+(S03+(S04+(S05+(S06+(S07+(S08+(S09+(S10+(S11+(S12+(S13+(S14+(S15+(S16+(S17+(S18+(S19+(S20+(S21+(S22+(S23+S24)))))))))))))))))))))))))\n"
"Tree =     (S00+(S01+(S02+(S03+(S04+(S05+(S06+(S07+(S08+(S09+(S10+(S11+(S12+(S13+(S14+(S15+(S16+(S17+(S18+(S19+(S20+(S21+(S22+(S23+S24))))))))))))))))))))))))\n";

char hollowTree[] =
"A = cylinder blue  scale 1.0 1.0 3.0 translate 0.0 0.0 -1.5\n"
"B = cylinder green scale 0.7 0.7 3.4 translate 0.0 0.0 -1.7\n"
"C = cylinder red   scale 0.6 0.6 2.0 translate 0.0 0.0 -1.0 rotate 1.0 0.0 0.0 90 translate 0.0 1.0 0.0\n"
"Tree = (A+(B+C))\n"
"Tree = (A-(B+C))\n";

char boxSphereTree[] =
"A = box       green  scale 3.0 3.0 0.5\n"
"B = sphere    yellow scale 2.5 2.5 2.5 translate 0 0 1.5\n"
"C = cone      blue   scale 2.5 2.5 2.5 translate 0 0 1.5\n"
"Tree = (A+B)\n"
"Tree = (A-B)\n"
"Tree = (A.B)\n"
"Tree = (A+(B+C))\n"
"Tree = (A-(B+C))\n";

char helixTree[] =
"A = cylinder          slateBlue scale 1.0 1.0 4.0 translate 0.0 0.0 0.5\n"
"B = helix 0.4 5.0 2.0 15 20 orange \n"
"C = helix 0.4 5.0 2.0 15 20 yellow rotate 0.0 0.0 1.0 180.0  \n"
"Tree = (A+B)\n"
"Tree = (A-B)\n"
"Tree = (A.B)\n"
"Tree = (B-A)\n"
"Tree = (B+C)\n"
"Tree = (A-(B+C))\n"
"Transform = translate 0.0 0.0 -2.5\n";

char segmentedHelixTree[] =
"X = cylinder          slateBlue scale 1.0 1.0 4.0 translate 0.0 0.0 0.5\n"
"B0 = helixseg 0.4 5.0 2.0 15 20  0 orange \n"
"C0 = helixseg 0.4 5.0 2.0 15 20  1 orange \n"
"D0 = helixseg 0.4 5.0 2.0 15 20  2 orange \n"
"E0 = helixseg 0.4 5.0 2.0 15 20  3 orange \n"
"F0 = helixseg 0.4 5.0 2.0 15 20  4 orange \n"
"G0 = helixseg 0.4 5.0 2.0 15 20  5 orange \n"
"H0 = helixseg 0.4 5.0 2.0 15 20  6 orange \n"
"I0 = helixseg 0.4 5.0 2.0 15 20  7 orange \n"
"J0 = helixseg 0.4 5.0 2.0 15 20  8 orange \n"
"K0 = helixseg 0.4 5.0 2.0 15 20  9 orange \n"
"L0 = helixseg 0.4 5.0 2.0 15 20 10 orange \n"
"M0 = helixseg 0.4 5.0 2.0 15 20 11 orange \n"
"N0 = helixseg 0.4 5.0 2.0 15 20 12 orange \n"
"O0 = helixseg 0.4 5.0 2.0 15 20 13 orange \n"
"P0 = helixseg 0.4 5.0 2.0 15 20 14 orange \n"
"Q0 = helixseg 0.4 5.0 2.0 15 20 15 orange \n"
"R0 = helixseg 0.4 5.0 2.0 15 20 16 orange \n"
"S0 = helixseg 0.4 5.0 2.0 15 20 17 orange \n"
"T0 = helixseg 0.4 5.0 2.0 15 20 18 orange \n"
"U0 = helixseg 0.4 5.0 2.0 15 20 19 orange \n"
"B1 = helixseg 0.4 5.0 2.0 15 20  0 yellow rotate 0.0 0.0 1.0 180.0 \n"
"C1 = helixseg 0.4 5.0 2.0 15 20  1 yellow rotate 0.0 0.0 1.0 180.0 \n"
"D1 = helixseg 0.4 5.0 2.0 15 20  2 yellow rotate 0.0 0.0 1.0 180.0 \n"
"E1 = helixseg 0.4 5.0 2.0 15 20  3 yellow rotate 0.0 0.0 1.0 180.0 \n"
"F1 = helixseg 0.4 5.0 2.0 15 20  4 yellow rotate 0.0 0.0 1.0 180.0 \n"
"G1 = helixseg 0.4 5.0 2.0 15 20  5 yellow rotate 0.0 0.0 1.0 180.0 \n"
"H1 = helixseg 0.4 5.0 2.0 15 20  6 yellow rotate 0.0 0.0 1.0 180.0 \n"
"I1 = helixseg 0.4 5.0 2.0 15 20  7 yellow rotate 0.0 0.0 1.0 180.0 \n"
"J1 = helixseg 0.4 5.0 2.0 15 20  8 yellow rotate 0.0 0.0 1.0 180.0 \n"
"K1 = helixseg 0.4 5.0 2.0 15 20  9 yellow rotate 0.0 0.0 1.0 180.0 \n"
"L1 = helixseg 0.4 5.0 2.0 15 20 10 yellow rotate 0.0 0.0 1.0 180.0 \n"
"M1 = helixseg 0.4 5.0 2.0 15 20 11 yellow rotate 0.0 0.0 1.0 180.0 \n"
"N1 = helixseg 0.4 5.0 2.0 15 20 12 yellow rotate 0.0 0.0 1.0 180.0 \n"
"O1 = helixseg 0.4 5.0 2.0 15 20 13 yellow rotate 0.0 0.0 1.0 180.0 \n"
"P1 = helixseg 0.4 5.0 2.0 15 20 14 yellow rotate 0.0 0.0 1.0 180.0 \n"
"Q1 = helixseg 0.4 5.0 2.0 15 20 15 yellow rotate 0.0 0.0 1.0 180.0 \n"
"R1 = helixseg 0.4 5.0 2.0 15 20 16 yellow rotate 0.0 0.0 1.0 180.0 \n"
"S1 = helixseg 0.4 5.0 2.0 15 20 17 yellow rotate 0.0 0.0 1.0 180.0 \n"
"T1 = helixseg 0.4 5.0 2.0 15 20 18 yellow rotate 0.0 0.0 1.0 180.0 \n"
"U1 = helixseg 0.4 5.0 2.0 15 20 19 yellow rotate 0.0 0.0 1.0 180.0 \n"
"Tree = ( B0 + ( C0 + ( D0 + ( E0 + ( F0 + ( G0 + ( H0 + ( I0 + ( J0 + ( K0 + ( L0 + ( M0 + ( N0 + ( O0 + ( P0 + ( Q0 + ( R0 + ( S0 + ( T0 + U0 ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) \n"
"Tree = ( B1 + ( C1 + ( D1 + ( E1 + ( F1 + ( G1 + ( H1 + ( I1 + ( J1 + ( K1 + ( L1 + ( M1 + ( N1 + ( O1 + ( P1 + ( Q1 + ( R1 + ( S1 + ( T1 + U1 ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) \n"
"Tree = ( B0 + ( C0 + ( D0 + ( E0 + ( F0 + ( G0 + ( H0 + ( I0 + ( J0 + ( K0 + ( L0 + ( M0 + ( N0 + ( O0 + ( P0 + ( Q0 + ( R0 + ( S0 + ( T0 + ( U0 + ( B1 + ( C1 + ( D1 + ( E1 + ( F1 + ( G1 + ( H1 + ( I1 + ( J1 + ( K1 + ( L1 + ( M1 + ( N1 + ( O1 + ( P1 + ( Q1 + ( R1 + ( S1 + ( T1 + U1 ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) \n"
"Tree = ( X + ( B0 + ( C0 + ( D0 + ( E0 + ( F0 + ( G0 + ( H0 + ( I0 + ( J0 + ( K0 + ( L0 + ( M0 + ( N0 + ( O0 + ( P0 + ( Q0 + ( R0 + ( S0 + ( T0 + U0 ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) )\n"
"Tree = ( X - ( B0 + ( C0 + ( D0 + ( E0 + ( F0 + ( G0 + ( H0 + ( I0 + ( J0 + ( K0 + ( L0 + ( M0 + ( N0 + ( O0 + ( P0 + ( Q0 + ( R0 + ( S0 + ( T0 + U0 ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) )\n"
"Tree = ( X + ( B0 + ( C0 + ( D0 + ( E0 + ( F0 + ( G0 + ( H0 + ( I0 + ( J0 + ( K0 + ( L0 + ( M0 + ( N0 + ( O0 + ( P0 + ( Q0 + ( R0 + ( S0 + ( T0 + ( U0 + ( B1 + ( C1 + ( D1 + ( E1 + ( F1 + ( G1 + ( H1 + ( I1 + ( J1 + ( K1 + ( L1 + ( M1 + ( N1 + ( O1 + ( P1 + ( Q1 + ( R1 + ( S1 + ( T1 + U1 ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) )\n"
"Tree = ( X - ( B0 + ( C0 + ( D0 + ( E0 + ( F0 + ( G0 + ( H0 + ( I0 + ( J0 + ( K0 + ( L0 + ( M0 + ( N0 + ( O0 + ( P0 + ( Q0 + ( R0 + ( S0 + ( T0 + ( U0 + ( B1 + ( C1 + ( D1 + ( E1 + ( F1 + ( G1 + ( H1 + ( I1 + ( J1 + ( K1 + ( L1 + ( M1 + ( N1 + ( O1 + ( P1 + ( Q1 + ( R1 + ( S1 + ( T1 + U1 ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) )\n"
"Transform = translate 0.0 0.0 -2.5\n";

char swissCheeseTree[] =
"Sphere      = sphere orange scale 2 2 2\n"
"ClipTop     = box yellow scale 2 0.7 2      translate 0 1.3 0\n"
"ClipBottom  = box yellow scale 2 0.7 2      translate 0 -1.3 0\n"
"ClipLeft    = box yellow scale 2.1 0.8 1.05 translate 0 0 1.05\n"
"ClipRight   = box yellow scale 2.1 0.8 1.05 translate 0 0 1.05 rotate 0 1 0 240\n"
"Hole1  = sphere orange scale   0.17   0.17   0.17 translate   1.04  -0.44   0.00 rotate 0 1 0 -158.4\n"
"Hole2  = sphere orange scale   0.23   0.23   0.23 translate   1.48  -0.19   0.00 rotate 0 1 0 -166.4\n"
"Hole3  = sphere orange scale   0.19   0.19   0.19 translate   1.46   0.35   0.00 rotate 0 1 0 -137.0\n"
"Hole4  = sphere orange scale   0.19   0.19   0.19 translate   1.84   0.00   0.00 rotate 0 1 0 -128.7\n"
"Hole5  = sphere orange scale   0.13   0.13   0.13 translate   1.28   0.06   0.00 rotate 0 1 0 -177.6\n"
"Hole6  = sphere orange scale   0.13   0.13   0.13 translate   0.87  -0.60   0.00 rotate 0 1 0 -149.9\n"
"Hole7  = sphere orange scale   0.10   0.10   0.10 translate   1.07   0.09   0.00 rotate 0 1 0 -148.6\n"
"Hole8  = sphere orange scale   0.11   0.11   0.11 translate   1.58   0.15   0.00 rotate 0 1 0 -147.3\n"
"Hole9  = sphere orange scale   0.17   0.17   0.17 translate   2.04  -0.32   0.00 rotate 0 1 0 -159.2\n"
"Hole10  = sphere orange scale   0.12   0.12   0.12 translate   2.20   0.37   0.00 rotate 0 1 0 -127.1\n"
"Hole11  = sphere orange scale   0.12   0.12   0.12 translate   1.69  -0.09   0.00 rotate 0 1 0 -139.8\n"
"Hole12  = sphere orange scale   0.14   0.14   0.14 translate   1.16   0.42   0.00 rotate 0 1 0 -173.5\n"
"Hole13  = sphere orange scale   0.10   0.10   0.10 translate   2.12   0.07   0.00 rotate 0 1 0 -163.8\n"
"Hole14  = sphere orange scale   0.18   0.18   0.18 translate   1.30   0.24   0.00 rotate 0 1 0 -127.5\n"
"Hole15  = sphere orange scale   0.14   0.14   0.14 translate   1.69   0.12   0.00 rotate 0 1 0 -130.7\n"
"Hole16  = sphere orange scale   0.16   0.16   0.16 translate   1.73   0.56   0.00 rotate 0 1 0 -135.4\n"
"Hole17  = sphere orange scale   0.15   0.15   0.15 translate   2.12   0.29   0.00 rotate 0 1 0 -164.1\n"
"Hole18  = sphere orange scale   0.15   0.15   0.15 translate   1.90   0.17   0.00 rotate 0 1 0 -131.9\n"
"Hole19  = sphere orange scale   0.17   0.17   0.17 translate   1.96  -0.15   0.00 rotate 0 1 0 -137.6\n"
"Hole20  = sphere orange scale   0.13   0.13   0.13 translate   1.57   0.28   0.00 rotate 0 1 0 -159.9\n"
"Hole21  = sphere orange scale   0.10   0.10   0.10 translate   1.88   0.52   0.00 rotate 0 1 0 -163.9\n"
"Hole22  = sphere orange scale   0.15   0.15   0.15 translate   0.18  -0.58   0.00 rotate 0 1 0 -141.9\n"
"Hole23  = sphere orange scale   0.12   0.12   0.12 translate   2.16   0.27   0.00 rotate 0 1 0 -138.5\n"
"Hole24  = sphere orange scale   0.13   0.13   0.13 translate   2.11  -0.57   0.00 rotate 0 1 0 -166.8\n"
"Hole25  = sphere orange scale   0.15   0.15   0.15 translate   2.20  -0.11   0.00 rotate 0 1 0 -137.3\n"
"Hole26  = sphere orange scale   0.22   0.22   0.22 translate   1.83   0.35   0.00 rotate 0 1 0 -170.3\n"
"Hole27  = sphere orange scale   0.18   0.18   0.18 translate   1.99   0.60   0.00 rotate 0 1 0 -131.0\n"
"Hole28  = sphere orange scale   0.14   0.14   0.14 translate   1.85  -0.29   0.00 rotate 0 1 0 -162.2\n"
"Hole29  = sphere orange scale   0.16   0.16   0.16 translate   1.86  -0.45   0.00 rotate 0 1 0 -171.6\n"
"Hole30  = sphere orange scale   0.10   0.10   0.10 translate   0.96  -0.26   0.00 rotate 0 1 0 -124.8\n"
"Hole31  = sphere orange scale   0.16   0.16   0.16 translate   2.18  -0.46   0.00 rotate 0 1 0 -132.3\n"
"Hole32  = sphere orange scale   0.13   0.13   0.13 translate   1.71  -0.36   0.00 rotate 0 1 0 -163.4\n"
"Hole33  = sphere orange scale   0.12   0.12   0.12 translate   1.23   0.30   0.00 rotate 0 1 0 -129.3\n"
"Hole34  = sphere orange scale   0.21   0.21   0.21 translate   2.15   0.51   0.00 rotate 0 1 0 -173.7\n"
"Hole35  = sphere orange scale   0.18   0.18   0.18 translate   1.85  -0.04   0.00 rotate 0 1 0 -164.6\n"
"Hole36  = sphere orange scale   0.18   0.18   0.18 translate   1.48   0.04   0.00 rotate 0 1 0 -139.9\n"
"Hole37  = sphere orange scale   0.18   0.18   0.18 translate   2.09   0.44   0.00 rotate 0 1 0 -140.5\n"
"Hole38  = sphere orange scale   0.13   0.13   0.13 translate   1.86  -0.18   0.00 rotate 0 1 0 -155.5\n"
"Hole39  = sphere orange scale   0.13   0.13   0.13 translate   2.19  -0.15   0.00 rotate 0 1 0 -166.1\n"
"Hole40  = sphere orange scale   0.15   0.15   0.15 translate   1.01   0.36   0.00 rotate 0 1 0 -129.7\n"
"Hole41  = sphere orange scale   0.20   0.20   0.20 translate   1.74  -0.60   0.00 rotate 0 1 0 -133.6\n"
"Hole42  = sphere orange scale   0.10   0.10   0.10 translate   1.79   0.25   0.00 rotate 0 1 0 -150.6\n"
"Hole43  = sphere orange scale   0.12   0.12   0.12 translate   0.91   0.36   0.00 rotate 0 1 0 -139.7\n"
"Hole44  = sphere orange scale   0.17   0.17   0.17 translate   1.11   0.07   0.00 rotate 0 1 0 -168.3\n"
"Hole45  = sphere orange scale   0.29   0.29   0.29 translate   0.61   0.20   0.00 rotate 0 1 0 -164.7\n"
"Hole46  = sphere orange scale   0.12   0.12   0.12 translate   0.25  -0.58   0.00 rotate 0 1 0 -148.3\n"
"Hole47  = sphere orange scale   0.22   0.22   0.22 translate   0.77   0.39   0.00 rotate 0 1 0 -150.4\n"
"Hole48  = sphere orange scale   0.17   0.17   0.17 translate   0.53   0.44   0.00 rotate 0 1 0 -159.1\n"
"Hole49  = sphere orange scale   0.11   0.11   0.11 translate   1.22   0.12   0.00 rotate 0 1 0 -142.1\n"
"Hole50  = sphere orange scale   0.10   0.10   0.10 translate   1.28   0.52   0.00 rotate 0 1 0 -175.9\n"
"Tree = (Sphere-(ClipTop+(ClipBottom+(ClipLeft+ClipRight))))\n"
"Tree = (Sphere+(ClipTop+(ClipBottom+(ClipLeft+(ClipRight+(Hole1+(Hole2+(Hole3+(Hole4+(Hole5+(Hole6+(Hole7+(Hole8+(Hole9+(Hole10+(Hole11+(Hole12+(Hole13+(Hole14+(Hole15+(Hole16+(Hole17+(Hole18+(Hole19+(Hole20+(Hole21+(Hole22+(Hole23+(Hole24+(Hole25+(Hole26+(Hole27+(Hole28+(Hole29+(Hole30+(Hole31+(Hole32+(Hole33+(Hole34+(Hole35+(Hole36+(Hole37+(Hole38+(Hole39+(Hole40+(Hole41+(Hole42+(Hole43+(Hole44+(Hole45+(Hole46+(Hole47+(Hole48+(Hole49+Hole50))))))))))))))))))))))))))))))))))))))))))))))))))))))\n"
"Tree = (Sphere-(ClipTop+(ClipBottom+(ClipLeft+(ClipRight+(Hole1+(Hole2+(Hole3+(Hole4+(Hole5+(Hole6+(Hole7+(Hole8+(Hole9+(Hole10+(Hole11+(Hole12+(Hole13+(Hole14+(Hole15+(Hole16+(Hole17+(Hole18+(Hole19+(Hole20+(Hole21+(Hole22+(Hole23+(Hole24+(Hole25+(Hole26+(Hole27+(Hole28+(Hole29+(Hole30+(Hole31+(Hole32+(Hole33+(Hole34+(Hole35+(Hole36+(Hole37+(Hole38+(Hole39+(Hole40+(Hole41+(Hole42+(Hole43+(Hole44+(Hole45+(Hole46+(Hole47+(Hole48+(Hole49+Hole50))))))))))))))))))))))))))))))))))))))))))))))))))))))\n"
"Tree = (ClipTop+(ClipBottom+(ClipLeft+(ClipRight+(Hole1+(Hole2+(Hole3+(Hole4+(Hole5+(Hole6+(Hole7+(Hole8+(Hole9+(Hole10+(Hole11+(Hole12+(Hole13+(Hole14+(Hole15+(Hole16+(Hole17+(Hole18+(Hole19+(Hole20+(Hole21+(Hole22+(Hole23+(Hole24+(Hole25+(Hole26+(Hole27+(Hole28+(Hole29+(Hole30+(Hole31+(Hole32+(Hole33+(Hole34+(Hole35+(Hole36+(Hole37+(Hole38+(Hole39+(Hole40+(Hole41+(Hole42+(Hole43+(Hole44+(Hole45+(Hole46+(Hole47+(Hole48+(Hole49+Hole50)))))))))))))))))))))))))))))))))))))))))))))))))))))\n"
"Tree = (Hole1+(Hole2+(Hole3+(Hole4+(Hole5+(Hole6+(Hole7+(Hole8+(Hole9+(Hole10+(Hole11+(Hole12+(Hole13+(Hole14+(Hole15+(Hole16+(Hole17+(Hole18+(Hole19+(Hole20+(Hole21+(Hole22+(Hole23+(Hole24+(Hole25+(Hole26+(Hole27+(Hole28+(Hole29+(Hole30+(Hole31+(Hole32+(Hole33+(Hole34+(Hole35+(Hole36+(Hole37+(Hole38+(Hole39+(Hole40+(Hole41+(Hole42+(Hole43+(Hole44+(Hole45+(Hole46+(Hole47+(Hole48+(Hole49+Hole50)))))))))))))))))))))))))))))))))))))))))))))))))";

//
// Version 2 of Swiss Cheese
//
// Here we place the subtracted slipping boxes
// with intersecting boxes.  This simplifies the
// adjacency graph, allowing faster drawing.
//
// Perhaps this technique could be generalised
// to any sitation a subtraction can be converted
// to an intersection.
//                             NS 21/04/2001
//
//

//"ClipLeft    = box yellow scale 2.1 0.8 1.05 translate 0 0 1.05\n"
//"ClipRight   = box yellow scale 2.1 0.8 1.05 translate 0 0 1.05 rotate 0 1 0 240\n"

char swissCheeseTree2[] =
"Sphere      = sphere orange scale 2 2 2\n"
"Slice1      = box yellow scale 2 0.6 2\n"
"Slice2      = box yellow translate 1 0 1 scale 1 0.61 1 rotate 0 1 0 180\n"
"Slice3      = box yellow translate 1 0 1 scale 1 0.61 1 rotate 0 1 0 150\n"
"Hole1  = sphere orange scale   0.17   0.17   0.17 translate   1.04  -0.44   0.00 rotate 0 1 0 -158.4\n"
"Hole2  = sphere orange scale   0.23   0.23   0.23 translate   1.48  -0.19   0.00 rotate 0 1 0 -166.4\n"
"Hole3  = sphere orange scale   0.19   0.19   0.19 translate   1.46   0.35   0.00 rotate 0 1 0 -137.0\n"
"Hole4  = sphere orange scale   0.19   0.19   0.19 translate   1.84   0.00   0.00 rotate 0 1 0 -128.7\n"
"Hole5  = sphere orange scale   0.13   0.13   0.13 translate   1.28   0.06   0.00 rotate 0 1 0 -177.6\n"
"Hole6  = sphere orange scale   0.13   0.13   0.13 translate   0.87  -0.60   0.00 rotate 0 1 0 -149.9\n"
"Hole7  = sphere orange scale   0.10   0.10   0.10 translate   1.07   0.09   0.00 rotate 0 1 0 -148.6\n"
"Hole8  = sphere orange scale   0.11   0.11   0.11 translate   1.58   0.15   0.00 rotate 0 1 0 -147.3\n"
"Hole9  = sphere orange scale   0.17   0.17   0.17 translate   2.04  -0.32   0.00 rotate 0 1 0 -159.2\n"
"Hole10  = sphere orange scale   0.12   0.12   0.12 translate   2.20   0.37   0.00 rotate 0 1 0 -127.1\n"
"Hole11  = sphere orange scale   0.12   0.12   0.12 translate   1.69  -0.09   0.00 rotate 0 1 0 -139.8\n"
"Hole12  = sphere orange scale   0.14   0.14   0.14 translate   1.16   0.42   0.00 rotate 0 1 0 -173.5\n"
"Hole13  = sphere orange scale   0.10   0.10   0.10 translate   2.12   0.07   0.00 rotate 0 1 0 -163.8\n"
"Hole14  = sphere orange scale   0.18   0.18   0.18 translate   1.30   0.24   0.00 rotate 0 1 0 -127.5\n"
"Hole15  = sphere orange scale   0.14   0.14   0.14 translate   1.69   0.12   0.00 rotate 0 1 0 -130.7\n"
"Hole16  = sphere orange scale   0.16   0.16   0.16 translate   1.73   0.56   0.00 rotate 0 1 0 -135.4\n"
"Hole17  = sphere orange scale   0.15   0.15   0.15 translate   2.12   0.29   0.00 rotate 0 1 0 -164.1\n"
"Hole18  = sphere orange scale   0.15   0.15   0.15 translate   1.90   0.17   0.00 rotate 0 1 0 -131.9\n"
"Hole19  = sphere orange scale   0.17   0.17   0.17 translate   1.96  -0.15   0.00 rotate 0 1 0 -137.6\n"
"Hole20  = sphere orange scale   0.13   0.13   0.13 translate   1.57   0.28   0.00 rotate 0 1 0 -159.9\n"
"Hole21  = sphere orange scale   0.10   0.10   0.10 translate   1.88   0.52   0.00 rotate 0 1 0 -163.9\n"
"Hole22  = sphere orange scale   0.15   0.15   0.15 translate   0.18  -0.58   0.00 rotate 0 1 0 -141.9\n"
"Hole23  = sphere orange scale   0.12   0.12   0.12 translate   2.16   0.27   0.00 rotate 0 1 0 -138.5\n"
"Hole24  = sphere orange scale   0.13   0.13   0.13 translate   2.11  -0.57   0.00 rotate 0 1 0 -166.8\n"
"Hole25  = sphere orange scale   0.15   0.15   0.15 translate   2.20  -0.11   0.00 rotate 0 1 0 -137.3\n"
"Hole26  = sphere orange scale   0.22   0.22   0.22 translate   1.83   0.35   0.00 rotate 0 1 0 -170.3\n"
"Hole27  = sphere orange scale   0.18   0.18   0.18 translate   1.99   0.60   0.00 rotate 0 1 0 -131.0\n"
"Hole28  = sphere orange scale   0.14   0.14   0.14 translate   1.85  -0.29   0.00 rotate 0 1 0 -162.2\n"
"Hole29  = sphere orange scale   0.16   0.16   0.16 translate   1.86  -0.45   0.00 rotate 0 1 0 -171.6\n"
"Hole30  = sphere orange scale   0.10   0.10   0.10 translate   0.96  -0.26   0.00 rotate 0 1 0 -124.8\n"
"Hole31  = sphere orange scale   0.16   0.16   0.16 translate   2.18  -0.46   0.00 rotate 0 1 0 -132.3\n"
"Hole32  = sphere orange scale   0.13   0.13   0.13 translate   1.71  -0.36   0.00 rotate 0 1 0 -163.4\n"
"Hole33  = sphere orange scale   0.12   0.12   0.12 translate   1.23   0.30   0.00 rotate 0 1 0 -129.3\n"
"Hole34  = sphere orange scale   0.21   0.21   0.21 translate   2.15   0.51   0.00 rotate 0 1 0 -173.7\n"
"Hole35  = sphere orange scale   0.18   0.18   0.18 translate   1.85  -0.04   0.00 rotate 0 1 0 -164.6\n"
"Hole36  = sphere orange scale   0.18   0.18   0.18 translate   1.48   0.04   0.00 rotate 0 1 0 -139.9\n"
"Hole37  = sphere orange scale   0.18   0.18   0.18 translate   2.09   0.44   0.00 rotate 0 1 0 -140.5\n"
"Hole38  = sphere orange scale   0.13   0.13   0.13 translate   1.86  -0.18   0.00 rotate 0 1 0 -155.5\n"
"Hole39  = sphere orange scale   0.13   0.13   0.13 translate   2.19  -0.15   0.00 rotate 0 1 0 -166.1\n"
"Hole40  = sphere orange scale   0.15   0.15   0.15 translate   1.01   0.36   0.00 rotate 0 1 0 -129.7\n"
"Hole41  = sphere orange scale   0.20   0.20   0.20 translate   1.74  -0.60   0.00 rotate 0 1 0 -133.6\n"
"Hole42  = sphere orange scale   0.10   0.10   0.10 translate   1.79   0.25   0.00 rotate 0 1 0 -150.6\n"
"Hole43  = sphere orange scale   0.12   0.12   0.12 translate   0.91   0.36   0.00 rotate 0 1 0 -139.7\n"
"Hole44  = sphere orange scale   0.17   0.17   0.17 translate   1.11   0.07   0.00 rotate 0 1 0 -168.3\n"
"Hole45  = sphere orange scale   0.29   0.29   0.29 translate   0.61   0.20   0.00 rotate 0 1 0 -164.7\n"
"Hole46  = sphere orange scale   0.12   0.12   0.12 translate   0.25  -0.58   0.00 rotate 0 1 0 -148.3\n"
"Hole47  = sphere orange scale   0.22   0.22   0.22 translate   0.77   0.39   0.00 rotate 0 1 0 -150.4\n"
"Hole48  = sphere orange scale   0.17   0.17   0.17 translate   0.53   0.44   0.00 rotate 0 1 0 -159.1\n"
"Hole49  = sphere orange scale   0.11   0.11   0.11 translate   1.22   0.12   0.00 rotate 0 1 0 -142.1\n"
"Hole50  = sphere orange scale   0.10   0.10   0.10 translate   1.28   0.52   0.00 rotate 0 1 0 -175.9\n"
"Tree = (Sphere.(Slice1.(Slice2.Slice3)))\n"
"Tree = (Sphere.(Slice1.(Slice2.(Slice3-(Hole1+(Hole2+(Hole3+(Hole4+(Hole5+(Hole6+(Hole7+(Hole8+(Hole9+(Hole10+(Hole11+(Hole12+(Hole13+(Hole14+(Hole15+(Hole16+(Hole17+(Hole18+(Hole19+(Hole20+(Hole21+(Hole22+(Hole23+(Hole24+(Hole25+(Hole26+(Hole27+(Hole28+(Hole29+(Hole30+(Hole31+(Hole32+(Hole33+(Hole34+(Hole35+(Hole36+(Hole37+(Hole38+(Hole39+(Hole40+(Hole41+(Hole42+(Hole43+(Hole44+(Hole45+(Hole46+(Hole47+(Hole48+(Hole49+Hole50)))))))))))))))))))))))))))))))))))))))))))))))))))))\n"
"Tree = (Hole1+(Hole2+(Hole3+(Hole4+(Hole5+(Hole6+(Hole7+(Hole8+(Hole9+(Hole10+(Hole11+(Hole12+(Hole13+(Hole14+(Hole15+(Hole16+(Hole17+(Hole18+(Hole19+(Hole20+(Hole21+(Hole22+(Hole23+(Hole24+(Hole25+(Hole26+(Hole27+(Hole28+(Hole29+(Hole30+(Hole31+(Hole32+(Hole33+(Hole34+(Hole35+(Hole36+(Hole37+(Hole38+(Hole39+(Hole40+(Hole41+(Hole42+(Hole43+(Hole44+(Hole45+(Hole46+(Hole47+(Hole48+(Hole49+Hole50)))))))))))))))))))))))))))))))))))))))))))))))))";

char pipeTree[] =
"PO = cylinder  orangeRed scale 0.3 0.3 2.00\n"
"PI = cylinder  pink      scale 0.2 0.2 2.02\n"
"QO = cylinder  orangeRed scale 0.3 0.3 2.00 rotate 0 1 0 120\n"
"QI = cylinder  pink      scale 0.2 0.2 2.02 rotate 0 1 0 120\n"
"SO  = sphere    orangeRed scale 0.3 0.3 0.3\n"
"SI  = sphere    pink      scale 0.2 0.2 0.2\n"
"Tree = (PO+PI)\n"
"Tree = (PO-PI)\n"
"Tree = (QO+QI)\n"
"Tree = (QO-QI)\n"
"Tree = (SO+(PO+QO))\n"
"Tree = (SI+(PI+QI))\n"
"Tree = (PO+(PI+(QO+QI)))\n"
"Tree = (SO-(PI+(QI+SI)))\n"
"Tree = ((SO+(PO+QO)) - (SI+(PI+QI)))";

char trickleTree[] =
"A = box green  scale 1.0 1.0 1.0\n"
"B = box red    scale 0.6 1.1 0.8 translate 0.5 0.0 0.4\n"
"C = box blue   scale 1.2 0.6 0.5 translate 0.0 0.6 0.6\n"
"Tree = (A+(B+C))\n"
"Tree = (A-(B+C))\n"
"Tree = (B+C)\n"
"Tree = (A-B)\n"
"Tree = (A-C)\n"
"Tree = (A.(B+C))\n";

char csgNormalisationTest[] =
    "X = sphere red   scale 1 1 0.7 translate 0 0 0 \n"
    "Y = sphere green scale 1 1 0.7 translate 1 0 0 rotate 0 0 1 60\n"
    "Z = sphere blue  scale 1 1 0.7 translate 1 0 0 rotate 0 0 1 120\n"
    "Tree = (X+Y)\n"
    "Tree = (X.Y)\n"
    "Tree = (X-Y)\n"
    "Tree = (X+Z)\n"
    "Tree = (X.Z)\n"
    "Tree = (X-Z)\n"
    "Tree = (Y+Z)\n"
    "Tree = (Y.Z)\n"
    "Tree = (Y-Z)\n"
    "Tree = (Y-X)\n"
    "Tree = (Z-X)\n"
    "Tree = (Z-Y)\n"
    "Tree = (X-(Y+Z))\n"
    "Tree = (X.(Y+Z))\n"
    "Tree = (X-(Y.Z))\n"
    "Tree = (X.(Y.Z))\n"
    "Tree = (X-(Y-Z))\n"
    "Tree = (X.(Y-Z))\n"
    "Tree = ((X+Y)-Z)\n"
    "Tree = ((X+Y).Z)\n";

char degenerateTree[] =
"A = sphere yellow \n"
"B = sphere green translate 0.0 2.5 0.0\n"
"Tree = (A+B)\n"
"Tree = (A.B)\n"
"Tree = (A-B)\n";

char gscsAcyclicTree[] =
"A = cylinder grey scale 1 1 2 translate 0 0 -1\n"
"B = sphere red   translate -1.2 0.0 0.0\n"
"C = sphere green translate  0.0 1.2 0.0\n"
"D = sphere blue  translate  1.2 0.0 0.0\n"
"Tree = (A+(B+(C+D)))\n"
"Tree = (A-(B+(C+D)))\n"
"Tree = (A.(B+(C+D)))\n";

char gscsRing4Tree[] =
"A = cylinder grey scale 1 1 2 translate 0 0 -1\n"
"B = sphere red    translate -1.2  0.0 0\n"
"C = sphere green  translate  0.0  1.2 0\n"
"D = sphere blue   translate  1.2  0.0 0\n"
"E = sphere orange translate  0.0 -1.2 0\n"
"Tree = (A+(B+(C+(D+E))))\n"
"Tree = (A-(B+(C+(D+E))))\n"
"Tree = (A.(B+(C+(D+E))))\n";

char gscsRing5Tree[] =
"A = cylinder grey scale 1.2 1.2 2 translate 0 0 -1\n"
"B = sphere red    translate  1.5 0 0                 \n"
"C = sphere green  translate  1.5 0 0 rotate 0 0 1  72\n"
"D = sphere blue   translate  1.5 0 0 rotate 0 0 1 144\n"
"E = sphere orange translate  1.5 0 0 rotate 0 0 1 216\n"
"F = sphere yellow translate  1.5 0 0 rotate 0 0 1 288\n"
"Tree = (A+(B+(C+(D+(E+F)))))\n"
"Tree = (A-(B+(C+(D+(E+F)))))\n"
"Tree = (A.(B+(C+(D+(E+F)))))\n";

// Non-intersecting

char gscsCase0[] =
"A = box    red   translate -1.2 0 0\n"
"B = sphere green translate  1.2 0 0\n"
"Tree = (A+B)\n"
"Tree = (A.B)\n"
"Tree = (A-B)\n";

// External Object

char gscsCase1[] =
"X = box grey scale 3 3 .3\n"
"A = cylinder green scale 1 1 2 translate 0 0 4\n"
"Tree = (X+A)\n"
"Tree = (X.A)\n"
"Tree = (X-A)\n";

// Two subtractions

char gscsCase2[] =
"A = box grey scale 3 3 .3\n"
"B = cylinder red   translate 0 0 -.5 scale 1.3 1.3 5 translate -1.5 0 0\n"
"C = cylinder green translate 0 0 -.5 scale 1.3 1.3 5 translate  1.5 0 0\n"
"Tree = (A+(B+C))\n"
"Tree = (A.(B+C))\n"
"Tree = (A-(B+C))\n";

// Acyclic

char gscsCase3[] =
"X = box grey scale 3 3 .3\n"
"A = cylinder red   translate 0 0 -.5 scale 1 1 4.00 translate -1.5 0 0\n"
"B = cylinder green translate 0 0 -.5 scale 1 1 4.01 translate  0.0 0 0\n"
"C = cylinder blue  translate 0 0 -.5 scale 1 1 4.02 translate  1.5 0 0\n"
"Tree = (X+(A+(B+C)))\n"
"Tree = (X.(A+(B+C)))\n"
"Tree = (X-(A+(B+C)))\n";

// Ring

char gscsCase4[] =
"X = box grey scale 3 3 .3\n"
"A = cylinder red    translate 0 0 -.5 scale 1 1 4.00 translate  1.3  0.0 0\n"
"B = cylinder green  translate 0 0 -.5 scale 1 1 4.01 translate  0.0  1.3 0\n"
"C = cylinder blue   translate 0 0 -.5 scale 1 1 4.02 translate -1.3  0.0 0\n"
"D = cylinder yellow translate 0 0 -.5 scale 1 1 4.03 translate  0.0 -1.3 0\n"
"Tree = (X+(A+(B+(C+D))))\n"
"Tree = (X.(A+(B+(C+D))))\n"
"Tree = (X-(A+(B+(C+D))))\n";

// All Touching

char gscsCase5[] =
"A = box grey scale 3 3 .3\n"
"B = cylinder red    translate 0 0 -.5 scale 1 1 4.00 translate  0.8  0.0 0\n"
"C = cylinder green  translate 0 0 -.5 scale 1 1 4.01 translate -0.8  0.0 0\n"
"D = cylinder blue   translate 0 0 -.5 scale 1 1 4.02 translate  0.0  0.8 0\n"
"E = cylinder yellow translate 0 0 -.5 scale 1 1 4.03 translate  0.0 -0.8 0\n"
"Tree = (A+(B+(C+(D+E))))\n"
"Tree = (A.(B+(C+(D+E))))\n"
"Tree = (A-(B+(C+(D+E))))\n";

// Two Subgraphs (Each Acyclic)

char gscsCase6[] =
"X = box grey scale 3 3 .3\n"
"A = cylinder red    translate 0 0 -.5 scale 1 1 4.00 translate -1.5  0.7 0\n"
"B = cylinder green  translate 0 0 -.5 scale 1 1 4.01 translate -1.5 -0.7 0\n"
"C = cylinder blue   translate 0 0 -.5 scale 1 1 4.02 translate  1.5  0.7 0\n"
"D = cylinder yellow translate 0 0 -.5 scale 1 1 4.03 translate  1.5 -0.7 0\n"
"Tree = (X+(A+(B+(C+D))))\n"
"Tree = (X.(A+(B+(C+D))))\n"
"Tree = (X-(A+(B+(C+D))))\n";

// Articulation point

char gscsCase7[] =
"A = box grey scale 3 3 .3\n"
"B = cylinder red    translate 0 0 -.5 scale 1 1 4.00 translate -1.6  0.7 0\n"
"C = cylinder red    translate 0 0 -.5 scale 1 1 4.00 translate -1.6 -0.7 0\n"
"D = cylinder green  translate 0 0 -.5 scale 1 1 4.01 translate -0.8  0.0 0\n"
"E = cylinder green  translate 0 0 -.5 scale 1 1 4.01 translate  0.8  0.0 0\n"
"F = cylinder yellow translate 0 0 -.5 scale 1 1 4.00 translate  1.6  0.7 0\n"
"G = cylinder yellow translate 0 0 -.5 scale 1 1 4.00 translate  1.6 -0.7 0\n"
"Tree = (A+(B+(C+(D+(E+(F+G))))))\n"
"Tree = (A.(B+(C+(D+(E+(F+G))))))\n"
"Tree = (A-(B+(C+(D+(E+(F+G))))))\n";

// Two subgraphs (Each ring)

char gscsCase8[] =
"X = box grey scale 3 3 .3\n"
"A = cylinder red   translate 0 0 -.5 scale 0.8 0.8 4 translate -1  0.7 0\n"
"B = cylinder red   translate 0 0 -.5 scale 0.8 0.8 4 translate -1 -0.7 0\n"
"C = cylinder red   translate 0 0 -.5 scale 0.8 0.8 4 translate -1.9  0.0 0\n"
"D = cylinder green translate 0 0 -.5 scale 0.8 0.8 4 translate  1  0.7 0\n"
"E = cylinder green translate 0 0 -.5 scale 0.8 0.8 4 translate  1 -0.7 0\n"
"F = cylinder green translate 0 0 -.5 scale 0.8 0.8 4 translate  1.9  0.0 0\n"
"Tree = (X+(A+(B+(C+(D+(E+F))))))\n"
"Tree = (X.(A+(B+(C+(D+(E+F))))))\n"
"Tree = (X-(A+(B+(C+(D+(E+F))))))\n";

/////////////////////////////////////////////////

char gscsSpiral[] =
"X = box gray95 scale 20 20 5.0\n"
"C0 = sphere yellow     scale 4.5 4.5 4.5 translate 0 10 5\n"
"C1 = sphere yellow     scale 4.5 4.5 4.5 translate 4.62086 9.59532 5\n"
"C2 = sphere yellow     scale 4.5 4.5 4.5 translate 8.8347 7.04543 5\n"
"C3 = sphere yellow     scale 4.5 4.5 4.5 translate 11.6504 2.65913 5\n"
"C4 = sphere yellow     scale 4.5 4.5 4.5 translate 12.2841 -2.80376 5\n"
"C5 = sphere yellow     scale 4.5 4.5 4.5 translate 10.3593 -8.26124 5\n"
"C6 = sphere yellow     scale 4.5 4.5 4.5 translate 6.03098 -12.5235 5\n"
"C7 = sphere yellow     scale 4.5 4.5 4.5 translate 1.7818e-015 -14.55 5\n"
"C8 = sphere yellow     scale 4.5 4.5 4.5 translate -6.59503 -13.6947 5\n"
"C9 = sphere yellow     scale 4.5 4.5 4.5 translate -12.392 -9.88231 5\n"
"C10 = sphere yellow    scale 4.5 4.5 4.5 translate -16.0863 -3.6716 5\n"
"C11 = sphere yellow    scale 4.5 4.5 4.5 translate -16.72 3.81623 5\n"
"C12 = sphere yellow    scale 4.5 4.5 4.5 translate -13.9166 11.0981 5\n"
"C13 = sphere yellow    scale 4.5 4.5 4.5 translate -8.00515 16.6229 5\n"
"C14 = sphere yellow    scale 4.5 4.5 4.5 translate -4.678e-015 19.1 5\n"
"Tree = (X-(C0+(C1+(C2+(C3+(C4+(C5+(C6+(C7+(C8+(C9+(C10+(C11+(C12+(C13+C14)))))))))))))))\n"
"Tree = (C0+(C1+(C2+(C3+(C4+(C5+(C6+(C7+(C8+(C9+(C10+(C11+(C12+(C13+C14))))))))))))))\n";

/////////////////////////////////////////////////

char gscsRing[] =
"X = box gray95 scale 20 20 5.0\n"
"C0 = sphere yellow     scale 4.5 4.5 4.5 translate 0 16.5 5\n"
"C1 = sphere yellow     scale 4.5 4.5 4.5 translate 6.71115 15.0735 5\n"
"C2 = sphere yellow     scale 4.5 4.5 4.5 translate 12.2619 11.0407 5\n"
"C3 = sphere yellow     scale 4.5 4.5 4.5 translate 15.6924 5.09878 5\n"
"C4 = sphere yellow     scale 4.5 4.5 4.5 translate 16.4096 -1.72472 5\n"
"C5 = sphere yellow     scale 4.5 4.5 4.5 translate 14.2894 -8.25 5\n"
"C6 = sphere yellow     scale 4.5 4.5 4.5 translate 9.69846 -13.3488 5\n"
"C7 = sphere yellow     scale 4.5 4.5 4.5 translate 3.43054 -16.1394 5\n"
"C8 = sphere yellow     scale 4.5 4.5 4.5 translate -3.43054 -16.1394 5\n"
"C9 = sphere yellow     scale 4.5 4.5 4.5 translate -9.69846 -13.3488 5\n"
"C10 = sphere yellow    scale 4.5 4.5 4.5 translate -14.2894 -8.25 5\n"
"C11 = sphere yellow    scale 4.5 4.5 4.5 translate -16.4096 -1.72472 5\n"
"C12 = sphere yellow    scale 4.5 4.5 4.5 translate -15.6924 5.09878 5\n"
"C13 = sphere yellow    scale 4.5 4.5 4.5 translate -12.2619 11.0407 5\n"
"C14 = sphere yellow    scale 4.5 4.5 4.5 translate -6.71115 15.0735 5\n"
"Tree = (X-(C0+(C1+(C2+(C3+(C4+(C5+(C6+(C7+(C8+(C9+(C10+(C11+(C12+(C13+C14)))))))))))))))\n"
"Tree = (C0+(C1+(C2+(C3+(C4+(C5+(C6+(C7+(C8+(C9+(C10+(C11+(C12+(C13+C14))))))))))))))\n";

