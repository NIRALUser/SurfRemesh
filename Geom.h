﻿#ifndef GEOM_HH_
#define GEOM_HH_

#include <math.h>
#include <stdio.h>
#include "string.h"
#define PI 3.141592653589793238462643

class MathVector
{
public:
	MathVector(void)
	{
		m_vector[0] = m_vector[1] = m_vector[2] = 0;
	}

	MathVector(const float *v)
	{
		m_vector[0] = v[0];
		m_vector[1] = v[1];
		m_vector[2] = v[2];
	}

	MathVector(const float *v1, const float *v2)
	{
		m_vector[0] = v2[0] - v1[0];
		m_vector[1] = v2[1] - v1[1];
		m_vector[2] = v2[2] - v1[2];
	}

	MathVector(const float v1, const float v2, const float v3)
	{
		m_vector[0] = v1;
		m_vector[1] = v2;
		m_vector[2] = v3;
	}

	MathVector(const int v1, const int v2, const int v3)
	{
		m_vector[0] = (const float)v1;
		m_vector[1] = (const float)v2;
		m_vector[2] = (const float)v3;
	}

	MathVector(const MathVector &v)
	{
		m_vector[0] = v.m_vector[0];
		m_vector[1] = v.m_vector[1];
		m_vector[2] = v.m_vector[2];
	}

	~MathVector(void)
	{
	}

	MathVector cross(const MathVector v)
	{
		MathVector p;
		p.m_vector[0] = m_vector[1] * v.m_vector[2] - m_vector[2] * v.m_vector[1];
		p.m_vector[1] = m_vector[2] * v.m_vector[0] - m_vector[0] * v.m_vector[2];
		p.m_vector[2] = m_vector[0] * v.m_vector[1] - m_vector[1] * v.m_vector[0];
		return p;
	}

	float norm(void)
	{
		return sqrt(m_vector[0] * m_vector[0] + m_vector[1] * m_vector[1] + m_vector[2] * m_vector[2]);
	}

	MathVector unit(void)
	{
		float s = norm();
		if (s > 0)
		{
			m_vector[0] /= s;
			m_vector[1] /= s;
			m_vector[2] /= s;
		}
		return *this;
	}

	MathVector trunc()
	{
		m_vector[0] = floor(m_vector[0]);
		m_vector[1] = floor(m_vector[1]);
		m_vector[2] = floor(m_vector[2]);

		return *this;
	}

	const float * fv(void)
	{
		return m_vector;
	}

	MathVector operator +(const MathVector &v)
	{
		return MathVector(m_vector[0] + v.m_vector[0], m_vector[1] + v.m_vector[1], m_vector[2] + v.m_vector[2]);
	}

	MathVector operator -(const MathVector &v)
	{
		return MathVector(m_vector[0] - v.m_vector[0], m_vector[1] - v.m_vector[1], m_vector[2] - v.m_vector[2]);
	}

	MathVector operator *(const float v)
	{
		return MathVector(m_vector[0] * v, m_vector[1] * v, m_vector[2] * v);
	}

	float operator *(const MathVector &v)
	{
		return m_vector[0] * v.m_vector[0] + m_vector[1] * v.m_vector[1] + m_vector[2] * v.m_vector[2];
	}

	MathVector operator /(const float v)
	{
		return MathVector(m_vector[0] / v, m_vector[1] / v, m_vector[2] / v);
	}

	MathVector operator =(const float *v)
	{
		m_vector[0] = v[0];
		m_vector[1] = v[1];
		m_vector[2] = v[2];
		return *this;
	}

	float operator[] (int id)
	{
		return m_vector[id];
    }

	const MathVector & operator +=(const MathVector &v)
	{
		m_vector[0] += v.m_vector[0];
		m_vector[1] += v.m_vector[1];
		m_vector[2] += v.m_vector[2];
		return *this;
	}

	const MathVector & operator -=(const MathVector &v)
	{
		m_vector[0] -= v.m_vector[0];
		m_vector[1] -= v.m_vector[1];
		m_vector[2] -= v.m_vector[2];
		return *this;
	}

	const MathVector & operator *=(const float v)
	{
		m_vector[0] *= v; m_vector[1] *= v; m_vector[2] *= v;
		return *this;
	}

	const MathVector & operator /=(const float v)
	{
		m_vector[0] /= v; m_vector[1] /= v; m_vector[2] /= v;
		return *this;
	}

	bool operator ==(const MathVector &v) const
	{
		return (m_vector[0] == v.m_vector[0]) && (m_vector[1] == v.m_vector[1]) && (m_vector[2] == v.m_vector[2]);
	}

	bool operator !=(const MathVector &v) const
	{
		return !(m_vector[0] == v.m_vector[0]) && (m_vector[1] == v.m_vector[1]) && (m_vector[2] == v.m_vector[2]);
	}

	bool operator <(const MathVector &v) const
	{
		if (m_vector[0] == v.m_vector[0])
			if (m_vector[1] == v.m_vector[1])
				return m_vector[2] < v.m_vector[2];
			else
				return m_vector[1] < v.m_vector[1];
		else
			return m_vector[0] < v.m_vector[0];
	}

	bool operator >(const MathVector &v) const
	{
		if (m_vector[0] == v.m_vector[0])
			if (m_vector[1] == v.m_vector[1])
				return m_vector[2] > v.m_vector[2];
			else
				return m_vector[1] > v.m_vector[1];
		else
			return m_vector[0] > v.m_vector[0];
	}

private:
	float m_vector[3];
};

class Coordinate
{
public:
	static void cart2sph(float *v, float *phi, float *theta)
	{
		// phi: azimuth, theta: elevation
		float d = v[0] * v[0] + v[1] * v[1];
		*phi = (d == 0) ? 0: atan2(v[1], v[0]);
		*theta = (v[2] == 0) ? 0: atan2(v[2], sqrt(d));
	}

	static void sph2cart(float phi, float theta, float *v)
	{
		// phi: azimuth, theta: elevation
		v[2] = sin(theta);
		float coselev = cos(theta);
		v[0] = coselev * cos(phi);
		v[1] = coselev * sin(phi);
	}

	static void cart2bary(float *a, float *b, float *c, float *p, float *coeff)
	{
		// test dataset for debug
		/*float a[3] = {-0.6498,0.3743,0.6616};
		float b[3] = {-0.6571,0.3837,0.6488};
		float c[3] = {-0.6646,0.3675,0.6506};
		float p[3] = {-0.6572,0.3752,0.6537};
		float coeff[3];*/

		// a counter clockwise order
		MathVector A(a), B(b), C(c), P(p);
		MathVector N((B-A).cross(C-A));

		float ABC = N * N / N.norm();
		N.unit();
		coeff[0] = (B-P).cross(C-P) * N / ABC;
		coeff[1] = (C-P).cross(A-P) * N / ABC;
		coeff[2] = 1 - coeff[0] - coeff[1];

		// debug
		/*printf("coeff: %f %f %f\n",coeff[0],coeff[1],coeff[2]);
		MathVector PP = A * coeff[0] + B * coeff[1] + C * coeff[2];
		printf("recons: %f %f %f\n", PP.fv()[0],PP.fv()[1],PP.fv()[2]);*/
	}
	static void rotPoint(const float *p0, const float *mat, float *p1)
	{
		for (int i = 0; i < 3; i++)
			p1[i] = mat[i * 3 + 0] * p0[0] + mat[i * 3 + 1] * p0[1] + mat[i * 3 + 2] * p0[2];
	}
	static void rotPointInv(const float *p0, const float *mat, float *p1)
	{
		for (int i = 0; i < 3; i++)
			p1[i] = mat[i] * p0[0] + mat[i + 3] * p0[1] + mat[i + 6] * p0[2];
	}
	static void rotation(const float *axis, const float theta, float *mat)
	{
		memset(mat, 0, sizeof(float) * 9);

		mat[0] = 1; mat[4] = 1; mat[8] = 1;

		MathVector RAxis(axis);
		if (RAxis.norm() == 0) return;
		RAxis.unit();

		float A[9] = {0, -RAxis[2], RAxis[1], RAxis[2], 0, -RAxis[0], -RAxis[1], RAxis[0], 0};

		// A * sin(-theta)
		for (int i = 0; i < 9; i++)
			mat[i] += A[i] * sin(theta);
		// A * A * (1 - cos(-theta))
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 3; j++)
				mat[i] += A[j + (i / 3) * 3] * A[j * 3 + i % 3] * (1 - cos(theta));
	}
	static void rotation2equator(float *v, float *mat, float *pole)
	{
		MathVector p0(pole), axis;
		float dot;

		// fit to the equator
		float rot[9];
		MathVector v0(v);
		axis = p0.cross(v0);
		if (axis.norm() == 0) axis = p0;
		dot = p0 * v0;
		dot = (dot > 1) ? 1: dot;
		dot = (dot < -1) ? -1: dot;
		float theta = PI / 2 - acos(dot);
		Coordinate::rotation(axis.fv(), theta, rot);
		float u[3];
		rotPoint(v, rot, u);

		// rotation btw v and u
		MathVector v1(u);
		axis = v0.cross(v1);
		if (axis.norm() == 0) axis = p0;
		dot = v0 * v1;
		dot = (dot > 1) ? 1: dot;
		dot = (dot < -1) ? -1: dot;
		theta = acos(dot);
		rotation(axis.fv(), theta, rot);

		// fit the new pole to the original
		float rot2[9];
		MathVector p1(0, 0, 1);
		axis = p0.cross(p1);
		if (axis.norm() == 0) axis = p0;
		dot = p0 * p1;
		dot = (dot > 1) ? 1: dot;
		dot = (dot < -1) ? -1: dot;
		theta = acos(dot);
		rotation(axis.fv(), theta, rot2);

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				MathVector col(rot[j], rot[j + 3], rot[j + 6]);
				MathVector row(rot2[i * 3], rot2[i * 3 + 1], rot2[i * 3 + 2]);
				mat[i * 3 + j] = row * col;
			}
		}

		// debug
		/*printf("Vertex: %f %f %f\n", v[0], v[1], v[2]);
		printf("sph: %f %f\n", phi, theta);
		for (int i = 0; i < 9; i++)
		{
			if (i % 3 == 0) printf("\n");
			printf("%f ", mat[i]);
		}
		printf("\n");*/
	}
	static void proj2plane(float a, float b, float c, float d, float *p0, float *p1)
	{
		float portion = (a * p0[0] + b * p0[1] + c * p0[2] + d) / (a * a + b * b + c * c);
		p1[0] = p0[0] - a * portion;
		p1[1] = p0[1] - b * portion;
		p1[2] = p0[2] - c * portion;
	}
	static float dpoint2tri(const float *t0, const float *t1, const float *t2, float *p0)
	{
		MathVector B(t0), P(p0);
		MathVector E0 = MathVector(t1) - B;
		MathVector E1 = MathVector(t2) - B;

		MathVector D = B - P;
		float a = E0 * E0;
		float b = E0 * E1;
		float c = E1 * E1;
		float d = E0 * D;
		float e = E1 * D;
		float f = D * D;

		float det = a * c - b * b; // do we have to use abs here?
		float s = b * e - c * d;
		float t = b * d - a * e;

		float sqrDistance;

		// Terible tree of conditionals to determine in which region of the diagram
		// shown above the projection of the point into the triangle-plane lies.
		if ((s + t) <= det)
		{
			if (s < 0)
			{
				if (t < 0)
				{
					// region4
					if (d < 0)
					{
						t = 0;
						if (-d >= a)
						{
							s = 1;
							sqrDistance = a + 2 * d + f;
						}
						else
						{
							s = -d / a;
							sqrDistance = d * s + f;
						}
					}
					else
					{
						s = 0;
						if (e >= 0)
						{
							t = 0;
							sqrDistance = f;
						}
						else
						{
							if (-e >= c)
							{
								t = 1;
								sqrDistance = c + 2 * e + f;
							}
							else
							{
								t = -e / c;
								sqrDistance = e * t + f;
							}
						}
					} // end of region 4
				}
				else
				{
					// region 3
					s = 0;
					if (e >= 0)
					{
						t = 0;
						sqrDistance = f;
					}
					else
					{
						if (-e >= c)
						{
							t = 1;
							sqrDistance = c + 2 * e + f;
						}
						else
						{
							t = -e / c;
							sqrDistance = e * t + f;
						}
					}
				} // end of region 3
			}
			else
			{
				if (t < 0)
				{
					// region 5
					t = 0;
					if (d >= 0)
					{
						s = 0;
						sqrDistance = f;
					}
					else
					{
						if (-d >= a)
						{
							s = 1;
							sqrDistance = a + 2 * d + f;
						}
						else
						{
							s = -d / a;
							sqrDistance = d * s + f;
						}
					}
				}
				else
				{
					// region 0
					float invDet = 1 / det;
					s = s * invDet;
					t = t * invDet;
					sqrDistance = s * (a * s + b * t + 2 * d) + t * (b * s + c * t + 2 * e) + f;
				}
			}
		}
		else
		{
			if (s < 0)
			{
				// region 2
				float tmp0 = b + d;
				float tmp1 = c + e;
				if (tmp1 > tmp0) // minimum on edge s+t=1
				{
					float numer = tmp1 - tmp0;
					float denom = a - 2 * b + c;
					if (numer >= denom)
					{
						s = 1;
						t = 0;
						sqrDistance = a + 2 * d + f;
					}
					else
					{
						s = numer / denom;
						t = 1 - s;
						sqrDistance = s * (a * s + b * t + 2 * d) + t * (b * s + c * t + 2 * e) + f;
					}
				}
				else          // minimum on edge s=0
				{
					s = 0;
					if (tmp1 <= 0)
					{
						t = 1;
						sqrDistance = c + 2 * e + f;
					}
					else
					{
						if (e >= 0)
						{
							t = 0;
							sqrDistance = f;
						}
						else
						{
							t = -e / c;
							sqrDistance = e * t + f;
						}
					}
				} // end of region 2
			}
			else
			{
				if (t < 0)
				{
					// region6 
					float tmp0 = b + e;
					float tmp1 = a + d;
					if (tmp1 > tmp0)
					{
						float numer = tmp1 - tmp0;
						float denom = a - 2 * b + c;
						if (numer >= denom)
						{
							t = 1;
							s = 0;
							sqrDistance = c + 2 * e + f;
						}
						else
						{
							t = numer / denom;
							s = 1 - t;
							sqrDistance = s * (a * s + b * t + 2 * d) + t * (b * s + c * t + 2 * e) + f;
						}
					}
					else
					{
						t = 0;
						if (tmp1 <= 0)
						{
							s = 1;
							sqrDistance = a + 2 * d + f;
						}
						else
						{
							if (d >= 0)
							{
								s = 0;
								sqrDistance = f;
							}
							else
							{
								s = -d / a;
								sqrDistance = d * s + f;
							}
						}
					}
				}	// end of region 6
				else
				{
					// region 1
					float numer = c + e - b - d;
					if (numer <= 0)
					{
						s = 0;
						t = 1;
						sqrDistance = c + 2 * e + f;
					}
					else
					{
						float denom = a - 2 * b + c;
						if (numer >= denom)
						{
						  s = 1;
						  t = 0;
						  sqrDistance = a + 2 * d + f;
						}
						else
						{
						  s = numer / denom;
						  t = 1 - s;
						  sqrDistance = s * (a * s + b * t + 2 * d) + t * (b * s + c * t + 2 * e) + f;
						}
					} // end of region 1
				}
			}
		}

		// account for numerical round-off error
		if (sqrDistance < 0) sqrDistance = 0;

		float dist = sqrt(sqrDistance);

		return dist;
	}
};

class Series
{
public:
	static double factorial(int x)
	{
		if (x == 0) return 1;
		return x * factorial(x - 1);
	}

	static double factorial(int x, int stopx)
	{
		if (x == stopx) return stopx;
		return x * factorial(x - 1);
	}

	static void legendre(int n, float x, float *Y)
	{
		if (n < 0) return;

		float **P = new float*[n + 1];
		for (int i = 0; i <= n; i++) P[i] = new float[n + 1];
		float factor = -sqrt(1.0 - pow(x,2));
 
		// Init legendre
		P[0][0] = 1.0;        // P_0,0(x) = 1
		if (n == 0)
		{
			Y[0] = P[0][0];
			return;
		}

		// Easy values
		P[1][0] = x;      // P_1,0(x) = x
		P[1][1] = factor;     // P_1,1(x) = −sqrt(1 − x^2)
		if (n == 1)
		{
			Y[0] = P[1][0];
			Y[1] = P[1][1];
			return;
		}
 
		for (int l = 2; l <= n; l++)
		{
			for (int m = 0; m < l - 1 ; m++)
			{
				// P_l,m = (2l-1)*x*P_l-1,m - (l+m-1)*x*P_l-2,m / (l-k)
				P[l][m] = ((float)(2 * l - 1) * x * P[l - 1][m] - (float)(l + m - 1) * P[l - 2][m]) / (float)(l - m);
			}
			// P_l,l-1 = (2l-1)*x*P_l-1,l-1
			P[l][l-1] = (float)(2 * l - 1) * x * P[l-1][l-1];
			// P_l,l = (2l-1)*factor*P_l-1,l-1
			P[l][l] = (float)(2 * l - 1) * factor * P[l-1][l-1];
		}

		for (int i = 0; i <= n; i++) Y[i] = P[n][i];

		// release memory
		for (int i = 0; i <= n; i++) delete [] P[i];
		delete [] P;
	}
};

class Statistics
{
public:
	static float sum(float *A, int n)
	{
		float res = 0;
		for (int i = 0; i < n; i++) res += A[i];
		return res;
	}
	static float mean(float *A, int n)
	{
		return sum(A, n) / (float)n;
	}
	static float min(float *A, int n)
	{
		float res = A[0];
		for (int i = 1; i < n; i++)
			if (res > A[i]) res = A[i];
		return res;
	}
	static float max(float *A, int n)
	{
		float res = A[0];
		for (int i = 1; i < n; i++)
			if (res < A[i]) res = A[i];
		return res;
	}
	static void sum(float *A, int n, int dim, float *res)
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < dim; j++)
				res[j] += A[i * dim + j];
	}
	static void mean(float *A, int n, int dim, float *res)
	{
		sum(A, n, dim, res);
		for (int i = 0; i < dim; i++)
			res[i] /= (float)n;
	}
	static float correlation(float *A, float *B, int n)
	{
		float res = 0;
		float meanA = mean(A, n);
		float meanB = mean(B, n);

		for (int i = 0; i < n; i++)
			res += (A[i] - meanA) * (B[i] - meanB);

		return res;
	}
	static float var(float *A, int n)
	{
		float m = mean(A, n);
		float res = 0;
		for (int i = 0; i < n; i++) res += (A[i] - m) * (A[i] - m) / n;
		return res;
	}
	static void cov(float *p, int n, int dim, float *M)
	{
		float *x;
		float *m = new float[dim];

		memset(m, 0, sizeof(float) * dim);

		// mean
		mean(p, n, dim, m);

		// covariance matrix (spd)
		for (int i = 0; i < n; i++)
		{
			x = &p[i * dim];
			for (int j = 0; j < dim; j++)
			{
				for (int k = j; k < dim; k++)
				{
					M[j * dim + k] += (x[j] - m[j]) * (x[k] - m[k]) / (float)(n - 1);
					M[k * dim + j] = M[j * dim + k];
				}
			}
		}

		delete m;
	}
	static void cov_trans(float *p, int n, int dim, float *M)
	{
		float *x, *y;
		float *m = new float[dim];

		memset(m, 0, sizeof(float) * dim);

		// mean
		mean(p, n, dim, m);

		// covariance matrix (spd)
		for (int i = 0; i < n; i++)
		{
			for (int j = i; j < n; j++)
			{
				x = &p[i * dim];
				y = &p[j * dim];
				for (int k = 0; k < dim; k++)
				{
					M[i * n + j] += (x[k] - m[k]) * (y[k] - m[k]) / (float)(n - 1);
				}
				M[j * n + i] = M[i * n + j];
			}
		}

		delete m;
	}
	static void wcov_trans(float *p, int n, int dim, float *M, float *w)
	{
		float *x, *y;
		float *m = new float[dim];

		memset(m, 0, sizeof(float) * dim);

		// mean
		mean(p, n, dim, m);

		// covariance matrix (spd)
		for (int i = 0; i < n; i++)
		{
			for (int j = i; j < n; j++)
			{
				x = &p[i * dim];
				y = &p[j * dim];
				for (int k = 0; k < dim; k++)
				{
					M[i * n + j] += (x[k] - m[k]) * (y[k] - m[k]) * w[k] * w[k] / (float)(n - 1);
				}
				M[j * n + i] = M[i * n + j];
			}
		}

		delete m;
	}
	static float NCC(float *A, float *B, int n)
	{
		return correlation(A, B, n) / sqrt(correlation(A, A, n)) / sqrt(correlation(B, B, n));
	}
	static float normal_pdf(float x, float u, float sigma)
	{
		return exp( -1 * (x - u) * (x - u) / (2 * sigma * sigma)) / (sigma * sqrt(2 * PI));
	}
	static float normal_cdf_approx(float x, float u, float sigma)
	{
		const double ninf = u - 10 * sigma;
		double sum = 0;
		double n = 1e3; // tune for speed/accuracy
		double c = (x - ninf) / n;

		for (int k = 1; k < n - 1; k++)
			sum += normal_pdf(ninf + (float)k * c, u, sigma);

		return c * ((normal_pdf(x, u, sigma) + normal_pdf(ninf, u, sigma)) / 2 + sum);
	}
	static float erf(float x)
	{
		float sign = (x > 0) ? 1: -1;
		x *= sign;
		float y = 1.0 / ( 1.0 + 0.3275911 * x);
		float e = 1 - (((((
				+ 1.061405429  * y
				- 1.453152027) * y
				+ 1.421413741) * y
				- 0.284496736) * y
				+ 0.254829592) * y)
				* exp (-x * x);
		return e * sign;
	}
	static float normal_cdf(float x, float u, float sigma)
	{
		return 0.5 * (1 + erf((x - u) / (sigma * sqrt(2.))));
	}
	static float median(float *v, int n)
	{
		// copy to tmp
		float *tmp = new float[n];
		memcpy(tmp, v, sizeof(float) * n);
		// sort
		std::sort(tmp, tmp + n);
		//median
		float med;
		if (n % 2 == 1) med = tmp[n / 2];
		else med = (tmp[n / 2 - 1] + tmp[n / 2]) * 0.5f;

		delete [] tmp;

		return med;
	}
};

#endif