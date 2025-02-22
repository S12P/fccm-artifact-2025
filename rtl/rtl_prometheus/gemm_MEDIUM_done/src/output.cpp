#include "output_2.h"

#define READ_RANGE(Arr, data_size, l)                                          \
  (Arr.data.range((data_size) * (l) + (data_size) - 1, (data_size) * (l)))

/****************************************************
 This file was automatically generated by Prometheus
****************************************************/
void load_vA_for_task1(hls::stream<float16> &fifo_A_from_off_chip_to_S1,
                       float16 vA[3000]) {
#pragma HLS inline off
  for (int i = 0; i < 3000; i++) {
#pragma HLS pipeline II = 1
    fifo_A_from_off_chip_to_S1.write(vA[i]);
  }
}

void load_vB_for_task1(hls::stream<float16> &fifo_B_from_off_chip_to_S1,
                       float16 vB[3360]) {
#pragma HLS inline off
  for (int i = 0; i < 3360; i++) {
#pragma HLS pipeline II = 1
    fifo_B_from_off_chip_to_S1.write(vB[i]);
  }
}

void load_vC_for_task0(hls::stream<float16> &fifo_C_from_off_chip_to_S0,
                       float16 vC[2800]) {
#pragma HLS inline off
  for (int i = 0; i < 2800; i++) {
#pragma HLS pipeline II = 1
    fifo_C_from_off_chip_to_S0.write(vC[i]);
  }
}

void store_vC_for_task0(hls::stream<float16> &fifo_C_to_off_chip,
                        float16 vC[2800]) {
#pragma HLS inline off
  for (int i = 0; i < 2800; i++) {
#pragma HLS pipeline II = 1
    vC[i] = fifo_C_to_off_chip.read();
  }
}

void FT0_level0(float alpha, float beta,
                hls::stream<float16> &fifo_A_from_off_chip_to_S1,
                hls::stream<float16> &fifo_B_from_off_chip_to_S1,
                hls::stream<float16> &fifo_C_from_off_chip_to_S0,
                hls::stream<float16> &fifo_C_to_off_chip) {
#pragma HLS inline off
  float A_0[40][240];
  // FT0
#pragma HLS array_partition variable = A_0 cyclic factor = 40 dim = 1
#pragma HLS array_partition variable = A_0 cyclic factor = 3 dim = 2
  float A_1[40][240];
  // FT0
#pragma HLS array_partition variable = A_1 cyclic factor = 40 dim = 1
#pragma HLS array_partition variable = A_1 cyclic factor = 3 dim = 2
  float B_0[240][224];
#pragma HLS array_partition variable = B_0 cyclic factor = 3 dim = 1
#pragma HLS array_partition variable = B_0 cyclic factor = 16 dim = 2
  float B_1[240][224];
#pragma HLS array_partition variable = B_1 cyclic factor = 3 dim = 1
#pragma HLS array_partition variable = B_1 cyclic factor = 16 dim = 2
  float B_2[240][224];
#pragma HLS array_partition variable = B_2 cyclic factor = 3 dim = 1
#pragma HLS array_partition variable = B_2 cyclic factor = 16 dim = 2
  read_A_FT0(A_0, fifo_A_from_off_chip_to_S1, 0);
  for (int i0 = 0; i0 < 5; i0++) {
    if (i0 % 2 == 0) {
      read_A_FT0(A_1, fifo_A_from_off_chip_to_S1, i0 + 1);
      FT0_level1(alpha, beta, fifo_A_from_off_chip_to_S1,
                 fifo_B_from_off_chip_to_S1, fifo_C_from_off_chip_to_S0,
                 fifo_C_to_off_chip, A_0, B_0, B_1, B_2, i0);
    } else if (i0 % 2 == 1) {
      read_A_FT0(A_0, fifo_A_from_off_chip_to_S1, i0 + 1);
      FT0_level1(alpha, beta, fifo_A_from_off_chip_to_S1,
                 fifo_B_from_off_chip_to_S1, fifo_C_from_off_chip_to_S0,
                 fifo_C_to_off_chip, A_1, B_0, B_1, B_2, i0);
    }
  }
}
void compute_FT0_level1(float alpha, float beta,
                        hls::stream<float16> &fifo_A_from_off_chip_to_S1,
                        hls::stream<float16> &fifo_B_from_off_chip_to_S1,
                        hls::stream<float16> &fifo_C_from_off_chip_to_S0,
                        hls::stream<float16> &fifo_C_to_off_chip,
                        float A[40][240], int i0, int j0, float C_0[40][16],
                        float C_1[40][16], float C_2[40][16],
                        float B_0[240][224], float B_1[240][224],
                        float B_2[240][224]) {
#pragma HLS inline off
#pragma HLS dataflow
  read_C_FT0(C_0, fifo_C_from_off_chip_to_S0, j0 + 1, i0);
  read_B_FT0(B_0, fifo_B_from_off_chip_to_S1, j0 + 1, i0);
  task0_intra(alpha, beta, A, B_1, i0, C_1, j0);
  task1_intra(alpha, beta, A, B_1, i0, C_1, j0);
  write_C_FT0(C_2, fifo_C_to_off_chip, j0 - 1, i0);
}

void FT0_level1(float alpha, float beta,
                hls::stream<float16> &fifo_A_from_off_chip_to_S1,
                hls::stream<float16> &fifo_B_from_off_chip_to_S1,
                hls::stream<float16> &fifo_C_from_off_chip_to_S0,
                hls::stream<float16> &fifo_C_to_off_chip, float A[40][240],
                float B_0[240][224], float B_1[240][224], float B_2[240][224],
                int i0) {
#pragma HLS inline off
  float C_0[40][16];
  // FT0
#pragma HLS array_partition variable = C_0 cyclic factor = 40 dim = 1
#pragma HLS array_partition variable = C_0 cyclic factor = 16 dim = 2
  float C_1[40][16];
  // FT0
#pragma HLS array_partition variable = C_1 cyclic factor = 40 dim = 1
#pragma HLS array_partition variable = C_1 cyclic factor = 16 dim = 2
  float C_2[40][16];
  // FT0
#pragma HLS array_partition variable = C_2 cyclic factor = 40 dim = 1
#pragma HLS array_partition variable = C_2 cyclic factor = 16 dim = 2
  read_C_FT0(C_0, fifo_C_from_off_chip_to_S0, 0, i0);
  read_B_FT0(B_0, fifo_B_from_off_chip_to_S1, 0, i0);
  for (int j0 = 0; j0 < 14; j0++) {

    if (j0 % 3 == 0) {
      //     read_C_FT0(C_1, fifo_C_from_off_chip_to_S0, j0+1, i0);
      //     read_B_FT0(B_1, fifo_B_from_off_chip_to_S1, j0+1, i0);
      //     task0_intra(alpha, beta, A, B_0, i0, C_0, j0);
      //     task1_intra(alpha, beta, A, B_0, i0, C_0, j0);
      //     write_C_FT0(C_2, fifo_C_to_off_chip, j0-1, i0);
      compute_FT0_level1(alpha, beta, fifo_A_from_off_chip_to_S1,
                         fifo_B_from_off_chip_to_S1, fifo_C_from_off_chip_to_S0,
                         fifo_C_to_off_chip, A, i0, j0, C_1, C_0, C_2, B_1, B_0,
                         B_2);
    } else if (j0 % 3 == 1) {
      //     read_C_FT0(C_2, fifo_C_from_off_chip_to_S0, j0+1, i0);
      //     read_B_FT0(B_2, fifo_B_from_off_chip_to_S1, j0+1, i0);
      //     task0_intra(alpha, beta, A, B_1, i0, C_1, j0);
      //     task1_intra(alpha, beta, A, B_1, i0, C_1, j0);
      //     write_C_FT0(C_0, fifo_C_to_off_chip, j0-1, i0);
      compute_FT0_level1(alpha, beta, fifo_A_from_off_chip_to_S1,
                         fifo_B_from_off_chip_to_S1, fifo_C_from_off_chip_to_S0,
                         fifo_C_to_off_chip, A, i0, j0, C_2, C_1, C_0, B_2, B_1,
                         B_0);
    } else if (j0 % 3 == 2) {
      //     read_C_FT0(C_0, fifo_C_from_off_chip_to_S0, j0+1, i0);
      //     read_B_FT0(B_0, fifo_B_from_off_chip_to_S1, j0+1, i0);
      //     task0_intra(alpha, beta, A, B_2, i0, C_2, j0);
      //     task1_intra(alpha, beta, A, B_2, i0, C_2, j0);
      //     write_C_FT0(C_1, fifo_C_to_off_chip, j0-1, i0);
      compute_FT0_level1(alpha, beta, fifo_A_from_off_chip_to_S1,
                         fifo_B_from_off_chip_to_S1, fifo_C_from_off_chip_to_S0,
                         fifo_C_to_off_chip, A, i0, j0, C_0, C_2, C_1, B_0, B_2,
                         B_1);
    }
  }
  write_C_FT0(C_1, fifo_C_to_off_chip, 13, i0);
}
void task0_intra(float alpha, float beta, float A[40][240], float B[240][224],
                 int i0, float C[40][16], int j0) {
#pragma HLS inline off
  int i;
  int j;
  for (int i1 = 0; i1 < 40; i1++) {
#pragma HLS unroll
    for (int j1 = 0; j1 < 16; j1++) {
#pragma HLS unroll
      i = i0 * 40 + i1;
      j = j0 * 16 + j1;
      C[i1][j1] = C[i1][j1] * beta;
    }
  }
}

void task1_intra(float alpha, float beta, float A[40][240], float B[240][224],
                 int i0, float C[40][16], int j0) {
#pragma HLS inline off
  int i;
  int j;
  int k;
  for (int k0 = 0; k0 < 80; k0++) {
#pragma HLS pipeline II = 2
    for (int i1 = 0; i1 < 40; i1++) {
#pragma HLS unroll
      for (int j1 = 0; j1 < 16; j1++) {
#pragma HLS unroll
        for (int k1 = 0; k1 < 3; k1++) {
#pragma HLS unroll
          i = i0 * 40 + i1;
          j = j0 * 16 + j1;
          k = k0 * 3 + k1;
          C[i1][j1] = C[i1][j1] + alpha * A[i1][k] * B[k][j];
        }
      }
    }
  }
}

void read_A_FT0(float A[40][240],
                hls::stream<float16> &fifo_A_from_off_chip_to_S1, int i0) {
#pragma HLS inline off
  if (i0 >= 5) {
    return;
  }
  for (int d0 = 0; d0 < 40; d0++) {
    for (int d1 = 0; d1 < 240; d1 += 16) {
#pragma HLS pipeline II = 1
      float16 tmp_fifo = fifo_A_from_off_chip_to_S1.read();
      A[d0 + 0][d1 + 0 + 0] = tmp_fifo[0];
      A[d0 + 0][d1 + 0 + 1] = tmp_fifo[1];
      A[d0 + 0][d1 + 0 + 2] = tmp_fifo[2];
      A[d0 + 0][d1 + 0 + 3] = tmp_fifo[3];
      A[d0 + 0][d1 + 0 + 4] = tmp_fifo[4];
      A[d0 + 0][d1 + 0 + 5] = tmp_fifo[5];
      A[d0 + 0][d1 + 0 + 6] = tmp_fifo[6];
      A[d0 + 0][d1 + 0 + 7] = tmp_fifo[7];
      A[d0 + 0][d1 + 0 + 8] = tmp_fifo[8];
      A[d0 + 0][d1 + 0 + 9] = tmp_fifo[9];
      A[d0 + 0][d1 + 0 + 10] = tmp_fifo[10];
      A[d0 + 0][d1 + 0 + 11] = tmp_fifo[11];
      A[d0 + 0][d1 + 0 + 12] = tmp_fifo[12];
      A[d0 + 0][d1 + 0 + 13] = tmp_fifo[13];
      A[d0 + 0][d1 + 0 + 14] = tmp_fifo[14];
      A[d0 + 0][d1 + 0 + 15] = tmp_fifo[15];
    }
  }
}

void read_C_FT0(float C[40][16],
                hls::stream<float16> &fifo_C_from_off_chip_to_S0, int j0,
                int i0) {
#pragma HLS inline off
  if (i0 >= 5 || j0 >= 14) {
    return;
  }
  for (int d0 = 0; d0 < 40; d0++) {
    for (int d1 = 0; d1 < 16; d1 += 16) {
#pragma HLS pipeline II = 1
      float16 tmp_fifo = fifo_C_from_off_chip_to_S0.read();
      C[d0 + 0][d1 + 0 + 0] = tmp_fifo[0];
      C[d0 + 0][d1 + 0 + 1] = tmp_fifo[1];
      C[d0 + 0][d1 + 0 + 2] = tmp_fifo[2];
      C[d0 + 0][d1 + 0 + 3] = tmp_fifo[3];
      C[d0 + 0][d1 + 0 + 4] = tmp_fifo[4];
      C[d0 + 0][d1 + 0 + 5] = tmp_fifo[5];
      C[d0 + 0][d1 + 0 + 6] = tmp_fifo[6];
      C[d0 + 0][d1 + 0 + 7] = tmp_fifo[7];
      C[d0 + 0][d1 + 0 + 8] = tmp_fifo[8];
      C[d0 + 0][d1 + 0 + 9] = tmp_fifo[9];
      C[d0 + 0][d1 + 0 + 10] = tmp_fifo[10];
      C[d0 + 0][d1 + 0 + 11] = tmp_fifo[11];
      C[d0 + 0][d1 + 0 + 12] = tmp_fifo[12];
      C[d0 + 0][d1 + 0 + 13] = tmp_fifo[13];
      C[d0 + 0][d1 + 0 + 14] = tmp_fifo[14];
      C[d0 + 0][d1 + 0 + 15] = tmp_fifo[15];
    }
  }
}

void read_B_FT0(float B[240][224],
                hls::stream<float16> &fifo_B_from_off_chip_to_S1, int j0,
                int i0) {
#pragma HLS inline off
  if (i0 > 0 || j0 >= 14) {
    return;
  }
  for (int d0 = 0; d0 < 240; d0++) {
    for (int d1 = 0; d1 < 16; d1 += 16) {
#pragma HLS pipeline II = 1
      float16 tmp_fifo = fifo_B_from_off_chip_to_S1.read();
      B[d0 + 0][d1 + j0 * 16 + 0] = tmp_fifo[0];
      B[d0 + 0][d1 + j0 * 16 + 1] = tmp_fifo[1];
      B[d0 + 0][d1 + j0 * 16 + 2] = tmp_fifo[2];
      B[d0 + 0][d1 + j0 * 16 + 3] = tmp_fifo[3];
      B[d0 + 0][d1 + j0 * 16 + 4] = tmp_fifo[4];
      B[d0 + 0][d1 + j0 * 16 + 5] = tmp_fifo[5];
      B[d0 + 0][d1 + j0 * 16 + 6] = tmp_fifo[6];
      B[d0 + 0][d1 + j0 * 16 + 7] = tmp_fifo[7];
      B[d0 + 0][d1 + j0 * 16 + 8] = tmp_fifo[8];
      B[d0 + 0][d1 + j0 * 16 + 9] = tmp_fifo[9];
      B[d0 + 0][d1 + j0 * 16 + 10] = tmp_fifo[10];
      B[d0 + 0][d1 + j0 * 16 + 11] = tmp_fifo[11];
      B[d0 + 0][d1 + j0 * 16 + 12] = tmp_fifo[12];
      B[d0 + 0][d1 + j0 * 16 + 13] = tmp_fifo[13];
      B[d0 + 0][d1 + j0 * 16 + 14] = tmp_fifo[14];
      B[d0 + 0][d1 + j0 * 16 + 15] = tmp_fifo[15];
    }
  }
}

void write_C_FT0(float C[40][16], hls::stream<float16> &fifo_C_to_off_chip,
                 int j0, int i0) {
#pragma HLS inline off
  if (j0 < 0 || i0 < 0) {
    return;
  }
  for (int d0 = 0; d0 < 40; d0++) {
    for (int d1 = 0; d1 < 16; d1 += 16) {
#pragma HLS pipeline II = 1
      float16 tmp_fifo;
      tmp_fifo[0] = C[d0 + 0][d1 + 0 + 0];
      tmp_fifo[1] = C[d0 + 0][d1 + 0 + 1];
      tmp_fifo[2] = C[d0 + 0][d1 + 0 + 2];
      tmp_fifo[3] = C[d0 + 0][d1 + 0 + 3];
      tmp_fifo[4] = C[d0 + 0][d1 + 0 + 4];
      tmp_fifo[5] = C[d0 + 0][d1 + 0 + 5];
      tmp_fifo[6] = C[d0 + 0][d1 + 0 + 6];
      tmp_fifo[7] = C[d0 + 0][d1 + 0 + 7];
      tmp_fifo[8] = C[d0 + 0][d1 + 0 + 8];
      tmp_fifo[9] = C[d0 + 0][d1 + 0 + 9];
      tmp_fifo[10] = C[d0 + 0][d1 + 0 + 10];
      tmp_fifo[11] = C[d0 + 0][d1 + 0 + 11];
      tmp_fifo[12] = C[d0 + 0][d1 + 0 + 12];
      tmp_fifo[13] = C[d0 + 0][d1 + 0 + 13];
      tmp_fifo[14] = C[d0 + 0][d1 + 0 + 14];
      tmp_fifo[15] = C[d0 + 0][d1 + 0 + 15];
      fifo_C_to_off_chip.write(tmp_fifo);
    }
  }
}

// extern "C"{
void kernel_nlp(float alpha, float beta, float16 vC_for_task0[2800],
                float16 vA_for_task1[3000], float16 vB_for_task1[3360]) {

#pragma HLS INTERFACE m_axi port = alpha offset = slave bundle = kernel_alpha
#pragma HLS INTERFACE m_axi port = beta offset = slave bundle = kernel_beta
#pragma HLS INTERFACE m_axi port = vC_for_task0 offset = slave bundle =        \
    kernel_vC_for_task0
#pragma HLS INTERFACE m_axi port = vA_for_task1 offset = slave bundle =        \
    kernel_vA_for_task1
#pragma HLS INTERFACE m_axi port = vB_for_task1 offset = slave bundle =        \
    kernel_vB_for_task1
#pragma HLS INTERFACE s_axilite port = alpha bundle = control
#pragma HLS INTERFACE s_axilite port = beta bundle = control
#pragma HLS INTERFACE s_axilite port = vC_for_task0 bundle = control
#pragma HLS INTERFACE s_axilite port = vA_for_task1 bundle = control
#pragma HLS INTERFACE s_axilite port = vB_for_task1 bundle = control
#pragma HLS DATA_PACK VARIABLE = alpha
#pragma HLS DATA_PACK VARIABLE = beta
#pragma HLS DATA_PACK VARIABLE = vC_for_task0
#pragma HLS DATA_PACK VARIABLE = vA_for_task1
#pragma HLS DATA_PACK VARIABLE = vB_for_task1
#pragma HLS INTERFACE s_axilite port = return bundle = control

#pragma HLS dataflow

  hls::stream<float16> fifo_A_from_off_chip_to_S1;
#pragma HLS stream variable = fifo_A_from_off_chip_to_S1 depth = 512
  hls::stream<float16> fifo_B_from_off_chip_to_S1;
#pragma HLS stream variable = fifo_B_from_off_chip_to_S1 depth = 512
  hls::stream<float16> fifo_C_from_off_chip_to_S0;
#pragma HLS stream variable = fifo_C_from_off_chip_to_S0 depth = 512
  hls::stream<float16> fifo_C_to_off_chip;
#pragma HLS stream variable = fifo_C_to_off_chip depth = 512

  load_vA_for_task1(fifo_A_from_off_chip_to_S1, vA_for_task1);
  load_vB_for_task1(fifo_B_from_off_chip_to_S1, vB_for_task1);
  load_vC_for_task0(fifo_C_from_off_chip_to_S0, vC_for_task0);

  FT0_level0(alpha, beta, fifo_A_from_off_chip_to_S1,
             fifo_B_from_off_chip_to_S1, fifo_C_from_off_chip_to_S0,
             fifo_C_to_off_chip);

  store_vC_for_task0(fifo_C_to_off_chip, vC_for_task0);
}
//}
