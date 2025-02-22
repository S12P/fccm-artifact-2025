#include "output.h"

#define READ_RANGE(Arr, data_size, l)                                          \
  (Arr.data.range((data_size) * (l) + (data_size) - 1, (data_size) * (l)))

/****************************************************
 This file was automatically generated by Prometheus
****************************************************/
void compute_FT0_level0(
    hls::stream<ap_axiu<512, 0, 0, 0>> &fifo_r_from_off_chip_to_S1,
    hls::stream<ap_axiu<512, 0, 0, 0>> &fifo_A_from_off_chip_to_S1,
    hls::stream<ap_axiu<512, 0, 0, 0>> &fifo_s_to_off_chip, int j0,
    float s_0[16], float s_1[16], float A_0[416][16], float A_1[416][16],
    float r[416]) {
#pragma HLS inline off
#pragma HLS dataflow
  read_A_FT0(A_1, fifo_A_from_off_chip_to_S1, j0 + 1);
  task0_intra(s_0, A_0, r, j0);
  task1_intra(s_0, A_0, r, j0);
  write_s_FT0(s_1, fifo_s_to_off_chip, j0 - 1);
}
void FT0_level0(hls::stream<ap_axiu<512, 0, 0, 0>> &fifo_r_from_off_chip_to_S1,
                hls::stream<ap_axiu<512, 0, 0, 0>> &fifo_A_from_off_chip_to_S1,
                hls::stream<ap_axiu<512, 0, 0, 0>> &fifo_s_to_off_chip) {
#pragma HLS inline off
  float s_0[16];
  // FT0
#pragma HLS array_partition variable = s_0 cyclic factor = 16 dim = 1
  float s_1[16];
  // FT0
#pragma HLS array_partition variable = s_1 cyclic factor = 16 dim = 1
  float A_0[416][16];
  // FT0
#pragma HLS array_partition variable = A_0 cyclic factor = 32 dim = 1
#pragma HLS array_partition variable = A_0 cyclic factor = 16 dim = 2
  float A_1[416][16];
  // FT0
#pragma HLS array_partition variable = A_1 cyclic factor = 32 dim = 1
#pragma HLS array_partition variable = A_1 cyclic factor = 16 dim = 2
  float r[416];
#pragma HLS array_partition variable = r cyclic factor = 32 dim = 1
  read_r_FT0(r, fifo_r_from_off_chip_to_S1);
  read_A_FT0(A_0, fifo_A_from_off_chip_to_S1, 0);
  for (int j0 = 0; j0 < 25; j0++) {

    if (j0 % 2 == 0) {
      //     read_A_FT0(A_1, fifo_A_from_off_chip_to_S1, j0+1);
      //     task0_intra(s_0, A_0, r, j0);
      //     task1_intra(s_0, A_0, r, j0);
      //     write_s_FT0(s_1, fifo_s_to_off_chip, j0-1);
      compute_FT0_level0(fifo_r_from_off_chip_to_S1, fifo_A_from_off_chip_to_S1,
                         fifo_s_to_off_chip, j0, s_0, s_1, A_0, A_1, r);
    } else if (j0 % 2 == 1) {
      //     read_A_FT0(A_0, fifo_A_from_off_chip_to_S1, j0+1);
      //     task0_intra(s_1, A_1, r, j0);
      //     task1_intra(s_1, A_1, r, j0);
      //     write_s_FT0(s_0, fifo_s_to_off_chip, j0-1);
      compute_FT0_level0(fifo_r_from_off_chip_to_S1, fifo_A_from_off_chip_to_S1,
                         fifo_s_to_off_chip, j0, s_1, s_0, A_1, A_0, r);
    }
  }
  write_s_FT0(s_0, fifo_s_to_off_chip, 24);
}
void task0_intra(float s[16], float A[416][16], float r[416], int j0) {
#pragma HLS inline off
  int j;
  for (int j1 = 0; j1 < 16; j1++) {
#pragma HLS unroll
    j = j0 * 16 + j1;
    s[j1] = 0.0;
  }
}
void task1_intra(float s[16], float A[416][16], float r[416], int j0) {
#pragma HLS inline off
  int j;
  int i;
  for (int i0 = 0; i0 < 13; i0++) {
#pragma HLS pipeline II = 2
    for (int j1 = 0; j1 < 16; j1++) {
#pragma HLS unroll
      for (int i1 = 0; i1 < 32; i1++) {
#pragma HLS unroll
        j = j0 * 16 + j1;
        i = i0 * 32 + i1;
        s[j1] = s[j1] + r[i] * A[i][j1];
      }
    }
  }
}
void read_r_FT0(float r[416],
                hls::stream<float16> &fifo_r_from_off_chip_to_S1) {
#pragma HLS inline off
  for (int d0 = 0; d0 < 416; d0 += 16) {
#pragma HLS pipeline II = 1
    float16 tmp_fifo = fifo_r_from_off_chip_to_S1.read();
    r[d0 + 0 + 0] = tmp_fifo[0];
    r[d0 + 0 + 1] = tmp_fifo[1];
    r[d0 + 0 + 2] = tmp_fifo[2];
    r[d0 + 0 + 3] = tmp_fifo[3];
    r[d0 + 0 + 4] = tmp_fifo[4];
    r[d0 + 0 + 5] = tmp_fifo[5];
    r[d0 + 0 + 6] = tmp_fifo[6];
    r[d0 + 0 + 7] = tmp_fifo[7];
    r[d0 + 0 + 8] = tmp_fifo[8];
    r[d0 + 0 + 9] = tmp_fifo[9];
    r[d0 + 0 + 10] = tmp_fifo[10];
    r[d0 + 0 + 11] = tmp_fifo[11];
    r[d0 + 0 + 12] = tmp_fifo[12];
    r[d0 + 0 + 13] = tmp_fifo[13];
    r[d0 + 0 + 14] = tmp_fifo[14];
    r[d0 + 0 + 15] = tmp_fifo[15];
  }
}
void read_r_FT0(
    float r[416],
    hls::stream<ap_axiu<512, 0, 0, 0>> &fifo_r_from_off_chip_to_S1) {
#pragma HLS inline off
  for (int d0 = 0; d0 < 416; d0 += 16) {
#pragma HLS pipeline II = 1
    ap_axiu<512, 0, 0, 0> tmp_fifo = fifo_r_from_off_chip_to_S1.read();
    uint32_t tmp_0 = tmp_fifo.data.range(31, 0);
    r[d0 + 0 + 0] = *(float *)(&tmp_0);
    uint32_t tmp_1 = tmp_fifo.data.range(63, 32);
    r[d0 + 0 + 1] = *(float *)(&tmp_1);
    uint32_t tmp_2 = tmp_fifo.data.range(95, 64);
    r[d0 + 0 + 2] = *(float *)(&tmp_2);
    uint32_t tmp_3 = tmp_fifo.data.range(127, 96);
    r[d0 + 0 + 3] = *(float *)(&tmp_3);
    uint32_t tmp_4 = tmp_fifo.data.range(159, 128);
    r[d0 + 0 + 4] = *(float *)(&tmp_4);
    uint32_t tmp_5 = tmp_fifo.data.range(191, 160);
    r[d0 + 0 + 5] = *(float *)(&tmp_5);
    uint32_t tmp_6 = tmp_fifo.data.range(223, 192);
    r[d0 + 0 + 6] = *(float *)(&tmp_6);
    uint32_t tmp_7 = tmp_fifo.data.range(255, 224);
    r[d0 + 0 + 7] = *(float *)(&tmp_7);
    uint32_t tmp_8 = tmp_fifo.data.range(287, 256);
    r[d0 + 0 + 8] = *(float *)(&tmp_8);
    uint32_t tmp_9 = tmp_fifo.data.range(319, 288);
    r[d0 + 0 + 9] = *(float *)(&tmp_9);
    uint32_t tmp_10 = tmp_fifo.data.range(351, 320);
    r[d0 + 0 + 10] = *(float *)(&tmp_10);
    uint32_t tmp_11 = tmp_fifo.data.range(383, 352);
    r[d0 + 0 + 11] = *(float *)(&tmp_11);
    uint32_t tmp_12 = tmp_fifo.data.range(415, 384);
    r[d0 + 0 + 12] = *(float *)(&tmp_12);
    uint32_t tmp_13 = tmp_fifo.data.range(447, 416);
    r[d0 + 0 + 13] = *(float *)(&tmp_13);
    uint32_t tmp_14 = tmp_fifo.data.range(479, 448);
    r[d0 + 0 + 14] = *(float *)(&tmp_14);
    uint32_t tmp_15 = tmp_fifo.data.range(511, 480);
    r[d0 + 0 + 15] = *(float *)(&tmp_15);
  }
}
void read_A_FT0(float A[416][16],
                hls::stream<float16> &fifo_A_from_off_chip_to_S1, int j0) {
#pragma HLS inline off
  if (j0 >= 25) {
    return;
  }
  for (int d0 = 0; d0 < 416; d0++) {
    for (int d1 = 0; d1 < 16; d1 += 16) {
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
void read_A_FT0(float A[416][16],
                hls::stream<ap_axiu<512, 0, 0, 0>> &fifo_A_from_off_chip_to_S1,
                int j0) {
#pragma HLS inline off
  if (j0 >= 25) {
    return;
  }
  for (int d0 = 0; d0 < 416; d0++) {
    for (int d1 = 0; d1 < 16; d1 += 16) {
#pragma HLS pipeline II = 1
      ap_axiu<512, 0, 0, 0> tmp_fifo = fifo_A_from_off_chip_to_S1.read();
      uint32_t tmp_0 = tmp_fifo.data.range(31, 0);
      A[d0 + 0][d1 + 0 + 0] = *(float *)(&tmp_0);
      uint32_t tmp_1 = tmp_fifo.data.range(63, 32);
      A[d0 + 0][d1 + 0 + 1] = *(float *)(&tmp_1);
      uint32_t tmp_2 = tmp_fifo.data.range(95, 64);
      A[d0 + 0][d1 + 0 + 2] = *(float *)(&tmp_2);
      uint32_t tmp_3 = tmp_fifo.data.range(127, 96);
      A[d0 + 0][d1 + 0 + 3] = *(float *)(&tmp_3);
      uint32_t tmp_4 = tmp_fifo.data.range(159, 128);
      A[d0 + 0][d1 + 0 + 4] = *(float *)(&tmp_4);
      uint32_t tmp_5 = tmp_fifo.data.range(191, 160);
      A[d0 + 0][d1 + 0 + 5] = *(float *)(&tmp_5);
      uint32_t tmp_6 = tmp_fifo.data.range(223, 192);
      A[d0 + 0][d1 + 0 + 6] = *(float *)(&tmp_6);
      uint32_t tmp_7 = tmp_fifo.data.range(255, 224);
      A[d0 + 0][d1 + 0 + 7] = *(float *)(&tmp_7);
      uint32_t tmp_8 = tmp_fifo.data.range(287, 256);
      A[d0 + 0][d1 + 0 + 8] = *(float *)(&tmp_8);
      uint32_t tmp_9 = tmp_fifo.data.range(319, 288);
      A[d0 + 0][d1 + 0 + 9] = *(float *)(&tmp_9);
      uint32_t tmp_10 = tmp_fifo.data.range(351, 320);
      A[d0 + 0][d1 + 0 + 10] = *(float *)(&tmp_10);
      uint32_t tmp_11 = tmp_fifo.data.range(383, 352);
      A[d0 + 0][d1 + 0 + 11] = *(float *)(&tmp_11);
      uint32_t tmp_12 = tmp_fifo.data.range(415, 384);
      A[d0 + 0][d1 + 0 + 12] = *(float *)(&tmp_12);
      uint32_t tmp_13 = tmp_fifo.data.range(447, 416);
      A[d0 + 0][d1 + 0 + 13] = *(float *)(&tmp_13);
      uint32_t tmp_14 = tmp_fifo.data.range(479, 448);
      A[d0 + 0][d1 + 0 + 14] = *(float *)(&tmp_14);
      uint32_t tmp_15 = tmp_fifo.data.range(511, 480);
      A[d0 + 0][d1 + 0 + 15] = *(float *)(&tmp_15);
    }
  }
}
void write_s_FT0(float s[16], hls::stream<float16> &fifo_s_to_off_chip,
                 int j0) {
#pragma HLS inline off
  if (j0 < 0) {
    return;
  }
  for (int d0 = 0; d0 < 16; d0 += 16) {
#pragma HLS pipeline II = 1
    float16 tmp_fifo;
    tmp_fifo[0] = s[d0 + 0 + 0];
    tmp_fifo[1] = s[d0 + 0 + 1];
    tmp_fifo[2] = s[d0 + 0 + 2];
    tmp_fifo[3] = s[d0 + 0 + 3];
    tmp_fifo[4] = s[d0 + 0 + 4];
    tmp_fifo[5] = s[d0 + 0 + 5];
    tmp_fifo[6] = s[d0 + 0 + 6];
    tmp_fifo[7] = s[d0 + 0 + 7];
    tmp_fifo[8] = s[d0 + 0 + 8];
    tmp_fifo[9] = s[d0 + 0 + 9];
    tmp_fifo[10] = s[d0 + 0 + 10];
    tmp_fifo[11] = s[d0 + 0 + 11];
    tmp_fifo[12] = s[d0 + 0 + 12];
    tmp_fifo[13] = s[d0 + 0 + 13];
    tmp_fifo[14] = s[d0 + 0 + 14];
    tmp_fifo[15] = s[d0 + 0 + 15];
    fifo_s_to_off_chip.write(tmp_fifo);
  }
}
void write_s_FT0(float s[16],
                 hls::stream<ap_axiu<512, 0, 0, 0>> &fifo_s_to_off_chip,
                 int j0) {
#pragma HLS inline off
  if (j0 < 0) {
    return;
  }
  for (int d0 = 0; d0 < 16; d0 += 16) {
#pragma HLS pipeline II = 1
    ap_axiu<512, 0, 0, 0> tmp_fifo;
    float tmp_0 = s[d0 + 0 + 0];
    tmp_fifo.data.range(31, 0) = *(uint32_t *)(&tmp_0);
    float tmp_1 = s[d0 + 0 + 1];
    tmp_fifo.data.range(63, 32) = *(uint32_t *)(&tmp_1);
    float tmp_2 = s[d0 + 0 + 2];
    tmp_fifo.data.range(95, 64) = *(uint32_t *)(&tmp_2);
    float tmp_3 = s[d0 + 0 + 3];
    tmp_fifo.data.range(127, 96) = *(uint32_t *)(&tmp_3);
    float tmp_4 = s[d0 + 0 + 4];
    tmp_fifo.data.range(159, 128) = *(uint32_t *)(&tmp_4);
    float tmp_5 = s[d0 + 0 + 5];
    tmp_fifo.data.range(191, 160) = *(uint32_t *)(&tmp_5);
    float tmp_6 = s[d0 + 0 + 6];
    tmp_fifo.data.range(223, 192) = *(uint32_t *)(&tmp_6);
    float tmp_7 = s[d0 + 0 + 7];
    tmp_fifo.data.range(255, 224) = *(uint32_t *)(&tmp_7);
    float tmp_8 = s[d0 + 0 + 8];
    tmp_fifo.data.range(287, 256) = *(uint32_t *)(&tmp_8);
    float tmp_9 = s[d0 + 0 + 9];
    tmp_fifo.data.range(319, 288) = *(uint32_t *)(&tmp_9);
    float tmp_10 = s[d0 + 0 + 10];
    tmp_fifo.data.range(351, 320) = *(uint32_t *)(&tmp_10);
    float tmp_11 = s[d0 + 0 + 11];
    tmp_fifo.data.range(383, 352) = *(uint32_t *)(&tmp_11);
    float tmp_12 = s[d0 + 0 + 12];
    tmp_fifo.data.range(415, 384) = *(uint32_t *)(&tmp_12);
    float tmp_13 = s[d0 + 0 + 13];
    tmp_fifo.data.range(447, 416) = *(uint32_t *)(&tmp_13);
    float tmp_14 = s[d0 + 0 + 14];
    tmp_fifo.data.range(479, 448) = *(uint32_t *)(&tmp_14);
    float tmp_15 = s[d0 + 0 + 15];
    tmp_fifo.data.range(511, 480) = *(uint32_t *)(&tmp_15);
    fifo_s_to_off_chip.write(tmp_fifo);
  }
}

void kernel_nlp_slr2(
    hls::stream<ap_axiu<512, 0, 0, 0>> &fifo_r_from_off_chip_to_S1,
    hls::stream<ap_axiu<512, 0, 0, 0>> &fifo_A_from_off_chip_to_S1,
    hls::stream<ap_axiu<512, 0, 0, 0>> &fifo_s_to_off_chip) {
#pragma HLS interface ap_ctrl_none port = return
#pragma HLS inline off
#pragma HLS INTERFACE axis port = fifo_r_from_off_chip_to_S1
#pragma HLS INTERFACE axis port = fifo_A_from_off_chip_to_S1
#pragma HLS INTERFACE axis port = fifo_s_to_off_chip
  FT0_level0(fifo_r_from_off_chip_to_S1, fifo_A_from_off_chip_to_S1,
             fifo_s_to_off_chip);
}
