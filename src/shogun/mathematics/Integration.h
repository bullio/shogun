/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2013 Roman Votyakov
 */

#ifndef _INTEGRATION_H_
#define _INTEGRATION_H_

#include <shogun/lib/config.h>

#ifdef HAVE_EIGEN3

#include <shogun/base/SGObject.h>
#include <shogun/lib/DynamicArray.h>
#include <shogun/mathematics/Math.h>
#include <shogun/mathematics/Function.h>

namespace shogun
{

/** @brief Class that contains certain methods related to numerical
 * integration
 */
class CIntegration : public CSGObject
{
public:
	/** numerically evaluate definite integral \f$\int_a^b f(x) dx\f$,
	 * where \f$f(x)\f$ - function of one variable, using adaptive
	 * Gauss-Kronrod quadrature formula
	 *
	 * \f[
	 * \int_a^b f(x)\dx \approx \sum_{i=1}^n w_i f(x_i)
	 * \f]
	 *
	 * where x_i and w_i - Gauss-Kronrod nodes and weights
	 * respectively.
	 *
	 * This function applies the Gauss-Kronrod 21-point integration
	 * rule for finite bounds \f$[a, b]\f$ and 15-point rule for
	 * infinite ones.
	 *
	 * @param f integrable function of one variable
	 * @param a lower bound of the domain of integration
	 * @param b upper bound of the domain of integration
	 * @param abs_tol absolute tolerance of the quadrature
	 * @param rel_tol relative tolerance of the quadrature
	 * @param max_iter maximum number of iterations of the method
	 * @param sn initial number of subintervals
	 *
	 * @return approximate value of definite integral of the function
	 * on given domain
	 */
	static float64_t integrate_quadgk(CFunction* f, float64_t a,
			float64_t b, float64_t abs_tol=1e-10, float64_t rel_tol=1e-5,
			uint32_t max_iter=1000, index_t sn=10);

	/** numerically evaluate integral of the following kind
	 *
	 * \f[
	 * \int_{-\infty}^{\infty}e^{-x^2}f(x)dx
	 * \f]
	 *
	 * using 64-point Gauss-Hermite rule
	 *
	 * \f[
	 * \int_{-\infty}^{\infty}e^{-x^2}f(x)dx \approx
	 * \sum_{i=1}^{64} w_if(x_i)
	 * \f]
	 *
	 * where x_i and w_i - ith node and weight for the 64-point
	 * Gauss-Hermite formula respectively.
	 *
	 * @param f integrable function of one variable
	 *
	 * @return approximate value of the
	 * integral \f$\int_{-\infty}^{\infty}e^{-x^2}f(x)dx\f$
	 */
	static float64_t integrate_quadgh(CFunction* f);

	/** get object name
	 *
	 * @return name Integration
	 */
	virtual const char* get_name() const { return "Integration"; }

private:
	/** evaluate definite integral of a function and error on each
	 * subinterval using Gauss-Kronrod quadrature formula of order n
	 *
	 * @param f integrable function of one variable
	 * @param subs subintervals of integration
	 * @param q approximate value of definite integral of the function
	 * on each subinterval
	 * @param err error on each subinterval
	 * @param n order of the Gauss-Kronrod rule
	 * @param xgk Gauss-Kronrod nodes
	 * @param wg Gauss weights
	 * @param wgk Gauss-Kronrod weights
	 */
	static void evaluate_quadgk(CFunction* f, CDynamicArray<float64_t>* subs,
			CDynamicArray<float64_t>* q, CDynamicArray<float64_t>* err, index_t n,
			float64_t* xgk, float64_t* wg, float64_t* wgk);

	/** evaluate definite integral of a function and error on each
	 * subinterval using Gauss-Kronrod quadrature formula of order 15.
	 *
	 * Gauss-Kronrod nodes, Gauss weights and Gauss-Kronrod weights
	 * are precomuted.
	 *
	 * @param f integrable function of one variable
	 * @param subs subintervals of integration
	 * @param q approximate value of definite integral of the function
	 * on each subinterval
	 * @param err error on each subinterval
	 */
	static void evaluate_quadgk15(CFunction* f, CDynamicArray<float64_t>* subs,
			CDynamicArray<float64_t>* q, CDynamicArray<float64_t>* err);

	/** evaluate definite integral of a function and error on each
	 * subinterval using Gauss-Kronrod quadrature formula of order 21.
	 *
	 * Gauss-Kronrod nodes, Gauss weights and Gauss-Kronrod weights
	 * are precomuted.
	 *
	 * @param f integrable function of one variable
	 * @param subs subintervals of integration
	 * @param q approximate value of definite integral of the function
	 * on each subinterval
	 * @param err error on each subinterval
	 */
	static void evaluate_quadgk21(CFunction* f, CDynamicArray<float64_t>* subs,
			CDynamicArray<float64_t>* q, CDynamicArray<float64_t>* err);

	/** evaluate integral \f$\int_{-\infty}^{\infty}e^{-x^2}f(x)dx\f$
	 * using Gauss-Hermite quadrature formula of order n
	 *
	 * @param f integrable function of one variable
	 * @param n order of the Gauss-Hermite rule
	 * @param xh Gauss-Hermite nodes
	 * @param wh Gauss-Hermite weights
	 *
	 * @return approximate value of the integral
	 * \f$\int_{-\infty}^{\infty}e^{-x^2}f(x)dx\f$
	 */
	static float64_t evaluate_quadgh(CFunction* f, index_t n, float64_t* xh,
			float64_t* wh);

	/** evaluate integral \f$\int_{-\infty}^{\infty}e^{-x^2}f(x)dx\f$
	 * using Gauss-Hermite quadrature formula of order 64.
	 *
	 * Gauss-Hermite nodes and Gauss-Hermite weights are precomuted.
	 *
	 * @param f integrable function of one variable
	 *
	 * @return approximate value of the integral
	 * \f$\int_{-\infty}^{\infty}e^{-x^2}f(x)dx\f$
	 */
	static float64_t evaluate_quadgh64(CFunction* f);
};
}
#endif /* HAVE_EIGEN3 */
#endif /* _INTEGRATION_H_ */