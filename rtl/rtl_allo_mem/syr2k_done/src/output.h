#ifndef PROMETHEUS_H
#define PROMETHEUS_H

#include <ap_int.h>
#include <hls_stream.h>
#include <hls_vector.h>

#include <algorithm>
#include <cstring>
#include <iostream>

typedef hls::vector<float, 16> float16;
typedef hls::vector<float, 8> float8;
typedef hls::vector<float, 4> float4;
typedef hls::vector<float, 2> float2;
typedef hls::vector<float, 1> float1;

void kernel_nlp(
  float vv35[240 * 208 / 16],
  float vv36[240 * 208 / 16],
  float vv37[240 * 208 / 16],
  float vv38[240 * 208 / 16],
  float vv39[240 * 240 / 16],
  float vv40[240 * 240 / 16]
);
#endif  // PROMETHEUS_H
