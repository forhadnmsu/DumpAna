#include "ana_const.h"
#ifndef _CUTDUMPDY_H
#define _CUTDUMPDY_H
//Track and dimuon, physics label event selections

string pos = "atan(y1_st3/y1_st1)>1.2 && atan(y1_st3/y1_st1) <1.6&& z1_v > -31.5 && z1_v < 145.0&& x1_t*x1_t+(y1_t-1.6)*(y1_t-1.6) <1300.0 && x1_d*x1_d+(y1_d -1.6)*(y1_d-1.6) <93.0&& abs(px1_st1-px1_st3)> 0.415 &&  abs(px1_st1-px1_st3)<0.420 && abs(py1_st1-py1_st3)< 0.01&& abs(pz1_st1-pz1_st3)<0.05&&(chisq1_target-chisq1_dump) >-2.5 && (chisq1_target-chisq1_dump)<77.5&& pz1_st1 > 9 && pz1_st1 < 78 && nHits1 > 13 &&(y1_st1*y1_st3) > 0 && chisq1_dump/chisq1_upstream < 0.195&&";
TCut posCut = "atan(y1_st3/y1_st1)>1.2 && atan(y1_st3/y1_st1) <1.6&& z1_v > -31.5 && z1_v < 145.0&& x1_t*x1_t+(y1_t-1.6)*(y1_t-1.6) <1300.0 && x1_d*x1_d+(y1_d -1.6)*(y1_d-1.6) <93.0&& abs(px1_st1-px1_st3)> 0.415 &&  abs(px1_st1-px1_st3)<0.420 && abs(py1_st1-py1_st3)< 0.01&& abs(pz1_st1-pz1_st3)<0.05&&(chisq1_target-chisq1_dump) >-2.5 && (chisq1_target-chisq1_dump)<77.5&& pz1_st1 > 9 && pz1_st1 < 78 && nHits1 > 13 &&(y1_st1*y1_st3) > 0 && chisq1_dump/chisq1_upstream < 0.195";

string neg = "atan(y2_st3/y2_st1)>1.2 && atan(y2_st3/y2_st1) <1.6&& z2_v > -31.5 && z2_v < 145.0&& x2_t*x2_t+(y2_t-1.6)*(y2_t-1.6) <1400.0 && x2_d*x2_d+(y2_d-1.6)*(y2_d-1.6) <100.0&& abs(px2_st1-px2_st3)> 0.415 &&  abs(px2_st1-px2_st3)<0.420 && abs(py2_st1-py2_st3)< 0.01&& abs(pz2_st1-pz2_st3)<0.05&&(chisq2_target-chisq2_dump) >-2.5 && (chisq2_target-chisq2_dump)<77.5&&  pz2_st1 > 9 && pz2_st1 < 78 && nHits2 > 13 &&(y2_st1*y2_st3) > 0&& chisq2_dump/chisq2_upstream < 0.165 &&";
TCut negCut = "atan(y2_st3/y2_st1)>1.2 && atan(y2_st3/y2_st1) <1.6&& z2_v > -31.5 && z2_v < 145.0&& x2_t*x2_t+(y2_t-1.6)*(y2_t-1.6) <1400.0 && x2_d*x2_d+(y2_d-1.6)*(y2_d-1.6) <100.0&& abs(px2_st1-px2_st3)> 0.415 &&  abs(px2_st1-px2_st3)<0.420 && abs(py2_st1-py2_st3)< 0.01&& abs(pz2_st1-pz2_st3)<0.05&&(chisq2_target-chisq2_dump) >-2.5 && (chisq2_target-chisq2_dump)<77.5&&  pz2_st1 > 9 && pz2_st1 < 78 && nHits2 > 13 &&(y2_st1*y2_st3) > 0&& chisq2_dump/chisq2_upstream < 0.165";

string dimu= "dz>0.0 && dz< 150.0&& abs(dx) < 0.262 && abs(dy-1.6) < 0.23 &&  abs(dpx) < 2.0 && abs(dpy) < 2.4 && dpz > 32.0 && dpz < 102.0 && abs(x1_st1 + x2_st1) < 30 && dpx*dpx + dpy*dpy < 4.5 && dx*dx + (dy-1.6)*(dy-1.6) < 0.06  && y1_st3*y2_st3 < 0 && nHits1 + nHits2 > 29 && nHits1St1 + nHits2St1 >8 &&chisq_dimuon>0.0&&chisq_dimuon<11.5&&(chisq1_dump+chisq2_dump-chisq_dimuon)<19.27&&";
TCut dimuCut= "dz>0.0 && dz< 150.0&& abs(dx) < 0.262 && abs(dy-1.6) < 0.23 &&  abs(dpx) < 2.0 && abs(dpy) < 2.4 && dpz > 32.0 && dpz < 102.0 && abs(x1_st1 + x2_st1) < 30 && dpx*dpx + dpy*dpy < 4.5 && dx*dx + (dy-1.6)*(dy-1.6) < 0.06  && y1_st3*y2_st3 < 0 && nHits1 + nHits2 > 29 && nHits1St1 + nHits2St1 >8 &&chisq_dimuon>0.0&&chisq_dimuon<11.5&&(chisq1_dump+chisq2_dump-chisq_dimuon)<19.27";

string physics = "abs(costh) < 0.5 && xF > -0.18 && xF <0.94&& xT > 0.007 && xT <0.54";
TCut massCUT = Form("mass>%f &&mass<%f",MassMin, MassMax);
TCut basicCut = posCut&&negCut&&dimuCut&&massCUT; 

string dumpCutRD= pos+neg+dimu+physics;
#endif
