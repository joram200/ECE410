/**
* Implementation of KalmanFilter class.
*
* @author: Hayk Martirosyan
* @date: 2014.11.15
*/

#include <iostream>
#include <stdexcept>

#include "kalman.hpp"
#include "kalman_hw.h"

KalmanFilter::KalmanFilter(
    double dt,
    const Eigen::MatrixXd& A,
    const Eigen::MatrixXd& C,
    const Eigen::MatrixXd& Q,
    const Eigen::MatrixXd& R,
    const Eigen::MatrixXd& P)
  : A(A), C(C), Q(Q), R(R), P0(P),
    m(C.rows()), n(A.rows()), dt(dt), initialized(false),
    I(n, n), x_hat(n), x_hat_new(n)
{
  I.setIdentity();
}

KalmanFilter::KalmanFilter() {}

void KalmanFilter::init(double t0, const Eigen::VectorXd& x0) {
  x_hat = x0;
  P = P0;
  this->t0 = t0;
  t = t0;
  initialized = true;
}

void KalmanFilter::init() {
  x_hat.setZero();
  P = P0;
  t0 = 0;
  t = t0;
  initialized = true;
}

void KalmanFilter::update(const Eigen::VectorXd& y) {

  if(!initialized)
    throw std::runtime_error("Filter is not initialized!");

  x_hat_new = A * x_hat;
  P = A*P*A.transpose() + Q;
  K = P*C.transpose()*(C*P*C.transpose() + R).inverse();
  x_hat_new += K * (y - C*x_hat_new);
  P = (I - K*C)*P;
  x_hat = x_hat_new;

  t += dt;
}

void KalmanFilter::update(const Eigen::VectorXd& y, double dt, const Eigen::MatrixXd A) {

  this->A = A;
  this->dt = dt;
  update(y);
}

void KalmanFilter::update_hw(const Eigen::VectorXd& y) {

  if (!initialized)
    throw std::runtime_error("Filter is not initialized!");

  // Predict (Eigen): x_hat_new = A*x_hat,  P = A*P*A' + Q
  x_hat_new = A * x_hat;
  P = A * P * A.transpose() + Q;

  // Marshal predicted state and covariance to C arrays (row-major)
  double x_pred[3], P_pred[9], x_out[3], P_out[9];
  for (int i = 0; i < n; i++)
    x_pred[i] = x_hat_new(i);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      P_pred[i * n + j] = P(i, j);

  // Correct (MMIO accelerator)
  kalman_hw_update(y(0), x_pred, P_pred, x_out, P_out);

  // Unmarshal HW outputs back to Eigen state
  for (int i = 0; i < n; i++)
    x_hat(i) = x_out[i];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      P(i, j) = P_out[i * n + j];

  t += dt;
}
