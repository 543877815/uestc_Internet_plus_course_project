#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#include "check.h"

#define SOFTENING 1e-9f
#define BLOCK_SIZE 256
/*
 * Each body contains x, y, and z coordinate positions,
 * as well as velocities in the x, y, and z directions.
 */

typedef struct { float4 *pos, *vel; } BodySystem;

/*
 * Do not modify this function. A constraint of this exercise is
 * that it remain a host function.
 */

void randomizeBodies(float *data, int n) {
  for (int i = 0; i < n; i++) {
    data[i] = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;
  }
}

/*
 * This function calculates the gravitational impact of all bodies in the system
 * on all others, but does not update their positions.
 */

__global__ void bodyForce(float4 *p, float4 *v, float dt, int n) {

  int index = threadIdx.x + blockIdx.x * blockDim.x;
  int stride = blockDim.x * gridDim.x;

  for (int i = index; i < n; i += stride) {
    float Fx = 0.0f; float Fy = 0.0f; float Fz = 0.0f;

    for (int j = 0; j < n; j++) {
      float dx = p[j].x - p[i].x;
      float dy = p[j].y - p[i].y;
      float dz = p[j].z - p[i].z;
      float distSqr = dx*dx + dy*dy + dz*dz + SOFTENING;
      float invDist = rsqrtf(distSqr);
      float invDist3 = invDist * invDist * invDist;

      Fx += dx * invDist3; Fy += dy * invDist3; Fz += dz * invDist3;
    }

     v[i].x += dt*Fx; v[i].y += dt*Fy; v[i].z += dt*Fz;
  }
}

int main(const int argc, const char** argv) {

  /*
   * Do not change the value for `nBodies` here. If you would like to modify it,
   * pass values into the command line.
   */

  int nBodies = 2<<11;
  int salt = 0;
  if (argc > 1) nBodies = 2<<atoi(argv[1]);

  /*
   * This salt is for assessment reasons. Tampering with it will result in automatic failure.
   */

  if (argc > 2) salt = atoi(argv[2]);

  const float dt = 0.01f; // time step
  const int nIters = 10;  // simulation iterations

  int bytes = 2*nBodies*sizeof(float4);
  float *buf;

  buf = (float *)malloc(bytes);

  BodySystem p = { (float4*)buf, ((float4*)buf) + nBodies };

  /*
   * As a constraint of this exercise, `randomizeBodies` must remain a host function.
   */

  randomizeBodies(buf, 8 * nBodies); // Init pos / vel data

  double totalTime = 0.0;

  float *d_buf;
  cudaMalloc(&d_buf, bytes);
  BodySystem d_p = { (float4*)d_buf, ((float4*)d_buf) + nBodies };

  int nBlocks = (nBodies + BLOCK_SIZE - 1) / BLOCK_SIZE;
  /*
   * This simulation will run for 10 cycles of time, calculating gravitational
   * interaction amongst bodies, and adjusting their positions to reflect.
   */

  /*******************************************************************/
  // Do not modify these 2 lines of code.
  for (int iter = 0; iter < nIters; iter++) {
    StartTimer();
  /*******************************************************************/

  /*
   * You will likely wish to refactor the work being done in `bodyForce`,
   * as well as the work to integrate the positions.
   */

    cudaMemcpy(d_buf, buf, bytes, cudaMemcpyHostToDevice);
    bodyForce<<<nBlocks, BLOCK_SIZE>>>(d_p.pos, d_p.vel, dt, nBodies);
   cudaMemcpy(buf, d_buf, bytes, cudaMemcpyDeviceToHost);

  /*
   * This position integration cannot occur until this round of `bodyForce` has completed.
   * Also, the next round of `bodyForce` cannot begin until the integration is complete.
   */

    for (int i = 0 ; i < nBodies; i++) { // integrate position
      p.pos[i].x += p.vel[i].x*dt;
      p.pos[i].y += p.vel[i].y*dt;
      p.pos[i].z += p.vel[i].z*dt;
    }

  /*******************************************************************/
  // Do not modify the code in this section.
    const double tElapsed = GetTimer() / 1000.0;
    totalTime += tElapsed;
}

double avgTime = totalTime / (double)(nIters);
float billionsOfOpsPerSecond = 1e-9 * nBodies * nBodies / avgTime;

#ifdef ASSESS
checkPerformance(buf, billionsOfOpsPerSecond, salt);
#else
checkAccuracy(buf, nBodies);
printf("%d Bodies: average %0.3f Billion Interactions / second\n", nBodies, billionsOfOpsPerSecond);
salt += 1;
#endif
  /*******************************************************************/

  /*
   * Feel free to modify code below.
   */

free(buf);
cudaFree(d_buf);
}