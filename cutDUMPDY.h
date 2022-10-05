#ifndef _CUTDUMPDY_H
#define _CUTDUMPDY_H
//Track and dimuon label event selections

string pos = "atan(y1_st3/y1_st1)>0.67 && atan(y1_st3/y1_st1) <1.6&& z1_v > -45.5 && z1_v < 150.0&& x1_t*x1_t+(y1_t-1.6)*(y1_t-1.6) <1425.0 && x1_d*x1_d+(y1_d -1.6)*(y1_d-1.6) <141.0&& abs(px1_st1-px1_st3)> 0.412 &&  abs(px1_st1-px1_st3)<0.420 && abs(py1_st1-py1_st3)< 0.005&& abs(pz1_st1-pz1_st3)<0.06&&(chisq1_target-chisq1_dump) >-2.5 && (chisq1_target-chisq1_dump)<77.5&& pz1_st1 > 9 && pz1_st1 < 78 && nHits1 > 13 &&(y1_st1*y1_st3) > 0 &&";

string neg = "atan(y2_st3/y2_st1)>0.67 && atan(y2_st3/y2_st1) <1.6&& z2_v > -45.5 && z2_v < 150.0&& x2_t*x2_t+(y2_t-1.6)*(y2_t-1.6) <1485.0 && x2_d*x2_d+(y2_d-1.6)*(y2_d-1.6) <201.0&& abs(px2_st1-px2_st3)> 0.412 &&  abs(px2_st1-px2_st3)<0.420 && abs(py2_st1-py2_st3)< 0.005&& abs(pz2_st1-pz2_st3)<0.06&&(chisq2_target-chisq2_dump) >-2.5 && (chisq2_target-chisq2_dump)<77.5&&  pz2_st1 > 9 && pz2_st1 < 78 && nHits2 > 13 &&(y2_st1*y2_st3) > 0&&";


string dimu= "dz>0.0 && dz< 150.0&& abs(dx) < 0.262 && abs(dy-1.6) < 0.23 &&  abs(dpx) < 2.0 && abs(dpy) < 2.4 && dpz > 35.0 && dpz < 114.0 && abs(x1_st1 + x2_st1) < 30 && dpx*dpx + dpy*dpy < 4.5 && dx*dx + (dy-1.6)*(dy-1.6) < 0.105  && y1_st3*y2_st3 < 0 && nHits1 + nHits2 > 29 && nHits1St1 + nHits2St1 >8 &&";

//string occu2 ="D1<150";
//string dumpCutRD= pos+neg+dimu+occu2;
#endif
