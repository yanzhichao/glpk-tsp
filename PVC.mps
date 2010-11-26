* Problem:    PVC2
* Class:      LP
* Rows:       19
* Columns:    27
* Non-zeros:  81
* Format:     Free MPS
*
NAME PVC2
ROWS
 E pred[1]
 E pred[2]
 E pred[3]
 E pred[4]
 E pred[5]
 E pred[6]
 E pred[7]
 E pred[8]
 E pred[9]
 E succ[1]
 E succ[2]
 E succ[3]
 E succ[4]
 E succ[5]
 E succ[6]
 E succ[7]
 E succ[8]
 E succ[9]
 N obj
COLUMNS
 x[2,1] obj 4 succ[2] 1
 x[2,1] pred[1] 1
 x[7,1] obj 6 succ[7] 1
 x[7,1] pred[1] 1
 x[1,2] obj 8 succ[1] 1
 x[1,2] pred[2] 1
 x[6,2] obj 7 succ[6] 1
 x[6,2] pred[2] 1
 x[7,2] obj 5 succ[7] 1
 x[7,2] pred[2] 1
 x[5,3] obj 8 succ[5] 1
 x[5,3] pred[3] 1
 x[6,3] obj 6 succ[6] 1
 x[6,3] pred[3] 1
 x[7,4] obj 10 succ[7] 1
 x[7,4] pred[4] 1
 x[8,4] obj 4 succ[8] 1
 x[8,4] pred[4] 1
 x[3,5] obj 9 succ[3] 1
 x[3,5] pred[5] 1
 x[4,5] obj 8 succ[4] 1
 x[4,5] pred[5] 1
 x[8,5] obj 6 succ[8] 1
 x[8,5] pred[5] 1
 x[9,5] obj 4 succ[9] 1
 x[9,5] pred[5] 1
 x[1,6] obj 10 succ[1] 1
 x[1,6] pred[6] 1
 x[2,6] obj 9 succ[2] 1
 x[2,6] pred[6] 1
 x[3,6] obj 8 succ[3] 1
 x[3,6] pred[6] 1
 x[5,6] obj 5 succ[5] 1
 x[5,6] pred[6] 1
 x[9,6] obj 10 succ[9] 1
 x[9,6] pred[6] 1
 x[1,7] obj 3 succ[1] 1
 x[1,7] pred[7] 1
 x[2,7] obj 5 succ[2] 1
 x[2,7] pred[7] 1
 x[5,7] obj 9 succ[5] 1
 x[5,7] pred[7] 1
 x[6,7] obj 11 succ[6] 1
 x[6,7] pred[7] 1
 x[4,8] obj 4 succ[4] 1
 x[4,8] pred[8] 1
 x[9,8] obj 7 succ[9] 1
 x[9,8] pred[8] 1
 x[3,9] obj 5 succ[3] 1
 x[3,9] pred[9] 1
 x[5,9] obj 7 succ[5] 1
 x[5,9] pred[9] 1
 x[8,9] obj 8 succ[8] 1
 x[8,9] pred[9] 1
RHS
 RHS1 pred[1] 1 pred[2] 1
 RHS1 pred[3] 1 pred[4] 1
 RHS1 pred[5] 1 pred[6] 1
 RHS1 pred[7] 1 pred[8] 1
 RHS1 pred[9] 1 succ[1] 1
 RHS1 succ[2] 1 succ[3] 1
 RHS1 succ[4] 1 succ[5] 1
 RHS1 succ[6] 1 succ[7] 1
 RHS1 succ[8] 1 succ[9] 1
ENDATA
