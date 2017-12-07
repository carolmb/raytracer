#ifndef PERLIN__
#define PERLIN__

#include <cmath>
#include <random>

#include "util/vec3.h"

class Perlin {
	static std::knuth_b randomGenerator;
	Vec3 *rand;
	int *permX;
	int *permY;
	int *permZ;
public:
	Perlin() {
		permX = perlinGeneratePerm();
		permY = perlinGeneratePerm();
		permZ = perlinGeneratePerm();
		rand = perlinGenerator();
	}

	float noise(Vec3 p) {
		int i = std::floor(p.x);
		int j = std::floor(p.y);
		int k = std::floor(p.z);
		Vec3 c[2][2][2];
		for(int di = 0; di < 2; di++) {
			for(int dj = 0; dj < 2; dj++) {
				for(int dk = 0; dk < 2; dk++) {
					c[di][dj][dk] = rand[permX[(i+di) & 255] ^ 
										permY[(j+dj) & 255] ^ 
										permZ[(k+dk) & 255]];
				}
			}
		}
		return trillinearInterpolation(c, p);
	}

	Vec3* perlinGenerator() {
		Vec3 *p = new Vec3[256];
		for(int i = 0; i < 256; i++) {
			float r1 = std::generate_canonical<double, 9> (randomGenerator);
			float r2 = std::generate_canonical<double, 9> (randomGenerator);
			float r3 = std::generate_canonical<double, 9> (randomGenerator);
			p[i] = Vec3(-1 + 2*r1, -1 + 2*r2, -1 + 2*r3).norm();
		}
		return p;
	}

	void permute(int *p, int n) {
		for(int i = n-1; i > 0; i--) {
			double random = std::generate_canonical<double, 9> (randomGenerator);
			int target = int(random*(i+1));
			int temp = p[i];
			p[i] = p[target];
			p[target] = temp;	
		}
	}

	int* perlinGeneratePerm() {
		int *p = new int[256];
		for(int i = 0; i < 256; i++) {
			p[i] = i;
		}
		permute(p, 256);
		return p;
	}

	float trillinearInterpolation(Vec3 c[2][2][2], Vec3 p) {
		float u = p.x - std::floor(p.x);
        float v = p.y - std::floor(p.y);
		float w = p.z - std::floor(p.z);
		float uu = u*u*(3-2*u);
		float vv = v*v*(3-2*v);
		float ww = w*w*(3-2*w);
		
		float accum = 0;
		for(int i = 0; i < 2; i++) {
			for(int j = 0; j < 2; j++) {
				for(int k = 0; k < 2; k++) {
					Vec3 weight(u-i, v-j, w-k);
					accum += (i*uu + (1-i)*(1-uu))*
							(j*vv + (1-j)*(1-vv))*
							(k*ww + (1-k)*(1-ww))*
							weight.dot(c[i][j][k]);

				}
			}
		}
		return accum;
	}

	float turb(Vec3 p, int depth = 7) {
		float accum = 0;
		Vec3 temp = p;
		float weight = 1;
		for(int i = 0; i < depth; i++) {
			accum += weight*noise(temp);
			weight *= 0.5;
			temp = temp*2;
		}
		return std::fabs(accum);
	}
};

#endif