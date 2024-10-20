
#include "osqp_interface.h"

namespace IAU {
namespace common {
namespace math {
MpcOsqp::MpcOsqp(const Eigen::MatrixXd &matrix_a,
                 const Eigen::MatrixXd &matrix_b,
                 const Eigen::MatrixXd &matrix_c,
                 const Eigen::MatrixXd &matrix_q,
                 const Eigen::MatrixXd &matrix_r,
                 const Eigen::MatrixXd &matrix_initial_x,
                 const Eigen::MatrixXd &matrix_u_lower,
                 const Eigen::MatrixXd &matrix_u_upper,
                 const Eigen::MatrixXd &matrix_x_lower,
                 const Eigen::MatrixXd &matrix_x_upper,
                 const Eigen::MatrixXd &matrix_x_ref, const int max_iter,
                 const int horizon, const double eps_abs)
    : matrix_a_(matrix_a),
      matrix_b_(matrix_b),
      matrix_c_(matrix_c),
      matrix_q_(matrix_q),
      matrix_r_(matrix_r),
      matrix_initial_x_(matrix_initial_x),
      matrix_u_lower_(matrix_u_lower),
      matrix_u_upper_(matrix_u_upper),
      matrix_x_lower_(matrix_x_lower),
      matrix_x_upper_(matrix_x_upper),
      matrix_x_ref_(matrix_x_ref),
      max_iteration_(max_iter),
      horizon_(horizon),
      eps_abs_(eps_abs) {
  state_dim_ = matrix_b.rows();
  control_dim_ = matrix_b.cols();
  std::cout << "      " << std::endl;
  std::cout << "state_dim " << state_dim_ << std::endl;
  std::cout << "control_dim_ " << control_dim_ << std::endl;
  std::cout << "horizon_ " << horizon_ << std::endl;
  num_param_ = state_dim_ * (horizon_ + 1) + control_dim_ * horizon_;
  std::cout << "test 37 good" << std::endl;
}


void MpcOsqp::castMPCToQPHessian()
{

    //P矩阵不在是原来标准二次规划的权重矩阵，而是根据MPC理论，推导后的一个矩阵
    //P=K.tans()QK+R

    //先求K
    /**
     * A 4x4 B 4x1
     * K=[B 0 0 0
     *    AB B 0 0
     *    A^2B AB B 0
     *    A^n-1B ****  AB B]
     * K的维度 [state_dim_ * horizon_ , control_dim_ * horizon_]
     * 
     */
    Eigen::MatrixXd Q = Eigen::MatrixXd::Identity(state_dim_ * horizon_ ,state_dim_ * horizon_);
    Eigen::MatrixXd R = Eigen::MatrixXd::Identity(control_dim_ * horizon_ ,control_dim_ * horizon_);
    Eigen::MatrixXd K = Eigen::MatrixXd::Zero(state_dim_ * horizon_ , control_dim_ * horizon_);
    K.block(0 * state_dim_, 0, state_dim_, control_dim_) = matrix_b_;

    K.block(1 * state_dim_, 0, state_dim_, control_dim_) = matrix_a_ * matrix_b_;
    K.block(1 * state_dim_, 1, state_dim_, control_dim_) = matrix_b_;

    K.block(2 * state_dim_, 0, state_dim_, control_dim_) = matrix_a_* matrix_a_ * matrix_b_;
    K.block(2 * state_dim_, 1, state_dim_, control_dim_) = matrix_a_ * matrix_b_;
    K.block(2 * state_dim_, 2, state_dim_, control_dim_) = matrix_b_;

    K.block(3 * state_dim_, 0, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_ * matrix_b_;
    K.block(3 * state_dim_, 1, state_dim_, control_dim_) = matrix_a_* matrix_a_ * matrix_b_;
    K.block(3 * state_dim_, 2, state_dim_, control_dim_) = matrix_a_ * matrix_b_;
    K.block(3 * state_dim_, 3, state_dim_, control_dim_) = matrix_b_;

    
    K.block(4 * state_dim_, 0, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_b_;   
    K.block(4 * state_dim_, 1, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_ * matrix_b_;
    K.block(4 * state_dim_, 2, state_dim_, control_dim_) = matrix_a_* matrix_a_ * matrix_b_;
    K.block(4 * state_dim_, 3, state_dim_, control_dim_) = matrix_a_ * matrix_b_;
    K.block(4 * state_dim_, 4, state_dim_, control_dim_) = matrix_b_;

    K.block(5 * state_dim_, 0, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_b_;     
    K.block(5 * state_dim_, 1, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_b_;   
    K.block(5 * state_dim_, 2, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_ * matrix_b_;
    K.block(5 * state_dim_, 3, state_dim_, control_dim_) = matrix_a_* matrix_a_ * matrix_b_;
    K.block(5 * state_dim_, 4, state_dim_, control_dim_) = matrix_a_ * matrix_b_;
    K.block(5 * state_dim_, 5, state_dim_, control_dim_) = matrix_b_;   

    K.block(6 * state_dim_, 0, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_b_;     
    K.block(6 * state_dim_, 1, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_b_;     
    K.block(6 * state_dim_, 2, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_b_;   
    K.block(6 * state_dim_, 3, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_ * matrix_b_;
    K.block(6 * state_dim_, 4, state_dim_, control_dim_) = matrix_a_* matrix_a_ * matrix_b_;
    K.block(6 * state_dim_, 5, state_dim_, control_dim_) = matrix_a_ * matrix_b_;
    K.block(6 * state_dim_, 6, state_dim_, control_dim_) = matrix_b_;

    K.block(7 * state_dim_, 0, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_b_;     
    K.block(7 * state_dim_, 1, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_b_;     
    K.block(7 * state_dim_, 2, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_b_;     
    K.block(7 * state_dim_, 3, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_b_;   
    K.block(7 * state_dim_, 4, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_ * matrix_b_;
    K.block(7 * state_dim_, 5, state_dim_, control_dim_) = matrix_a_* matrix_a_ * matrix_b_;
    K.block(7 * state_dim_, 6, state_dim_, control_dim_) = matrix_a_ * matrix_b_;
    K.block(7 * state_dim_, 7, state_dim_, control_dim_) = matrix_b_;

    K.block(8 * state_dim_, 0, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_b_;     
    K.block(8 * state_dim_, 1, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_b_;     
    K.block(8 * state_dim_, 2, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_b_;     
    K.block(8 * state_dim_, 3, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_b_;     
    K.block(8 * state_dim_, 4, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_b_;   
    K.block(8 * state_dim_, 5, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_ * matrix_b_;
    K.block(8 * state_dim_, 6, state_dim_, control_dim_) = matrix_a_* matrix_a_ * matrix_b_;
    K.block(8 * state_dim_, 7, state_dim_, control_dim_) = matrix_a_ * matrix_b_;
    K.block(8 * state_dim_, 8, state_dim_, control_dim_) = matrix_b_;

    K.block(9 * state_dim_, 0, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_b_;     
    K.block(9 * state_dim_, 1, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_b_;     
    K.block(9 * state_dim_, 2, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_b_;     
    K.block(9 * state_dim_, 3, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_b_;     
    K.block(9 * state_dim_, 4, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_b_;     
    K.block(9 * state_dim_, 5, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_b_;   
    K.block(9 * state_dim_, 6, state_dim_, control_dim_) = matrix_a_* matrix_a_* matrix_a_ * matrix_b_;
    K.block(9 * state_dim_, 7, state_dim_, control_dim_) = matrix_a_* matrix_a_ * matrix_b_;
    K.block(9 * state_dim_, 8, state_dim_, control_dim_) = matrix_a_ * matrix_b_;
    K.block(9 * state_dim_, 9, state_dim_, control_dim_) = matrix_b_;  


    Eigen::MatrixXd P = Eigen::MatrixXd::Zero(control_dim_ * horizon_, control_dim_ * horizon_);
    // P.resize(control_dim_ * horizon_, control_dim_ * horizon_) ;
    
    P = (K.transpose() * Q * K + R).block(0,0, control_dim_ * horizon_, control_dim_ * horizon_);
    std::cout << P << std::endl;

    hessian_.resize( control_dim_ * horizon_, control_dim_ * horizon_ );

    for(int i = 0; i < control_dim_ * horizon_; i++){
        for(int j=0; j <control_dim_*horizon_; j++){
            float value = P(i,j);
            if(value != 0)
            hessian_.insert(i,j) = value;   //稀疏矩阵不能直接赋值，只将非零部分赋值
        }   
    }
    // std::cout << hessian_ << std::endl;

    //q的转置 = (M + CC)的转置 * Q *K
    //先求M
    Eigen::MatrixXd M = Eigen::MatrixXd::Zero(state_dim_ * horizon_, 1);
    Eigen::MatrixXd CC = Eigen::MatrixXd::Zero(state_dim_*horizon_, 1);
    M.block(0 * state_dim_, 0 , state_dim_, 1) = matrix_a_ * matrix_initial_x_;
    M.block(1 * state_dim_, 0 , state_dim_, 1) = matrix_a_* matrix_a_ * matrix_initial_x_;
    M.block(2 * state_dim_, 0 , state_dim_, 1) = matrix_a_* matrix_a_* matrix_a_ * matrix_initial_x_;
    M.block(3 * state_dim_, 0 , state_dim_, 1) = matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_initial_x_;
    M.block(4 * state_dim_, 0 , state_dim_, 1) = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_initial_x_;
    M.block(5 * state_dim_, 0 , state_dim_, 1) = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_initial_x_;
    M.block(6 * state_dim_, 0 , state_dim_, 1) = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_initial_x_;
    M.block(7 * state_dim_, 0 , state_dim_, 1) = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_initial_x_;
    M.block(8 * state_dim_, 0 , state_dim_, 1) = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_initial_x_;
    M.block(9 * state_dim_, 0 , state_dim_, 1) = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_initial_x_;



    Eigen::MatrixXd test1 = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_c_;     
    Eigen::MatrixXd test2 = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_c_;     
    Eigen::MatrixXd test3 = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_c_;     
    Eigen::MatrixXd test4 = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_c_;     
    Eigen::MatrixXd test5 = matrix_a_* matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_c_;     
    Eigen::MatrixXd test6 = matrix_a_* matrix_a_* matrix_a_* matrix_a_ * matrix_c_;   
    Eigen::MatrixXd test7 = matrix_a_* matrix_a_* matrix_a_ * matrix_c_;
    Eigen::MatrixXd test8 = matrix_a_* matrix_a_ * matrix_c_;
    Eigen::MatrixXd test9 = matrix_a_ * matrix_c_;
    Eigen::MatrixXd test10 = matrix_c_;

    CC.block(0 * state_dim_, 0 , state_dim_, 1) =   test10;
    CC.block(1 * state_dim_, 0 , state_dim_, 1) =   test9 + test10;
    CC.block(2 * state_dim_, 0 , state_dim_, 1) =   test8+ test9 + test10;  
    CC.block(3 * state_dim_, 0 , state_dim_, 1) =   test7 + test8+ test9 + test10;     
    CC.block(4 * state_dim_, 0 , state_dim_, 1) =   test6 + test7 + test8+ test9 + test10;
    CC.block(5 * state_dim_, 0 , state_dim_, 1) =   test5 + test6 + test7 + test8+ test9 + test10;
    CC.block(6 * state_dim_, 0 , state_dim_, 1) =   test4 +test5 + test6 + test7 + test8+ test9 + test10;
    CC.block(7 * state_dim_, 0 , state_dim_, 1) =   test3 + test4 +test5 + test6 + test7 + test8+ test9 + test10;
    CC.block(8 * state_dim_, 0 , state_dim_, 1) =   test2 + test3 + test4 +test5 + test6 + test7 + test8+ test9 + test10;
    CC.block(9 * state_dim_, 0 , state_dim_, 1) =   test1 + test2 + test3 + test4 +test5 + test6 + test7 + test8+ test9 + test10;

    gradient_ = Eigen::VectorXd::Zero(control_dim_*horizon_, 1);
    gradient_ =  ((M + CC).transpose() * Q * K).transpose();


    // hessian_.resize( state_dim_*(horizon_+1) + control_dim_ * horizon_, state_dim_*(horizon_+1) + control_dim_ * horizon_ );

    // //populate hessian matrix
    // for(int i = 0; i < state_dim_*(horizon_+1) + control_dim_ * horizon_; i++){
    //     if(i < state_dim_*(horizon_+1)){
    //         int posQ = i%state_dim_;
    //         float value = matrix_q_.diagonal()[posQ];
    //         if(value != 0)
    //             hessian_.insert(i,i) = value;
    //     }
    //     else{
    //         int posR = i%control_dim_;
    //         float value = matrix_r_.diagonal()[posR];
    //         if(value != 0)
    //             hessian_.insert(i,i) = value;
    //     }
    // }
}

void MpcOsqp::castMPCToQPGradient()
{

    Eigen::Matrix<double,4,1> Qx_ref;
    Qx_ref = matrix_q_ * (-matrix_x_ref_);

    // populate the gradient vector
    gradient_ = Eigen::VectorXd::Zero(state_dim_*(horizon_+1) +  control_dim_*horizon_, 1);
    for(int i = 0; i < state_dim_*(horizon_+1); i++){
        int posQ = i%state_dim_;
        float value = Qx_ref(posQ,0);
        gradient_(i,0) = value;
    }
}

void MpcOsqp::castMPCToQPConstraintMatrix()
{
    constraintMatrix_.resize(1 * horizon_, 1 * horizon_);

    for(int i = 0; i<1*horizon_; i++){
        constraintMatrix_.insert(i,i) = 1;
    }
}

void MpcOsqp::castMPCToQPConstraintVectors()
{
    // evaluate the lower and the upper inequality vectors
    Eigen::VectorXd lowerInequality = Eigen::MatrixXd::Zero(1 * horizon_, 1);
    Eigen::VectorXd upperInequality = Eigen::MatrixXd::Zero(1 * horizon_, 1);

    for(int i=0; i< horizon_; i++){
        lowerInequality.block(i * control_dim_ , 0, 1, 1) = matrix_u_lower_;
        upperInequality.block(i * control_dim_ , 0, 1, 1) = matrix_u_upper_;
    }

    // evaluate the lower and the upper equality vectors
    // Eigen::VectorXd lowerEquality = Eigen::MatrixXd::Zero(4*(horizon_+1),1 );
    // Eigen::VectorXd upperEquality;
    // lowerEquality.block(0,0,4,1) = -matrix_initial_x_;
    // upperEquality = lowerEquality;
    // lowerEquality = lowerEquality;

    // merge inequality and equality vectors
    lowerBound_ = Eigen::MatrixXd::Zero(1*horizon_,1 );
    lowerBound_ << 
        lowerInequality;

    upperBound_ = Eigen::MatrixXd::Zero(1*horizon_,1 );
    upperBound_ << 
        upperInequality;
}

bool MpcOsqp::Solve(std::vector<double> *control_cmd){

    castMPCToQPHessian();
    std::cout << "to Hessian finsh" << std::endl;
    // castMPCToQPGradient();
    std::cout << "to Gradient finsh" << std::endl;
    castMPCToQPConstraintMatrix();
    std::cout << "to ConstraintMatrix finsh" << std::endl;
    castMPCToQPConstraintVectors();
    std::cout << "to ConstraintVectors finsh" << std::endl;

    // instantiate the solver
    OsqpEigen::Solver solver;
    // settings
    //solver.settings()->setVerbosity(false);
    solver.settings()->setWarmStart(true);
    solver.settings()->setMaxIteration(150);

    // set the initial data of the QP solver
    solver.data()->setNumberOfVariables(10); // osqp A矩阵的列数
    solver.data()->setNumberOfConstraints(10);    // oaqp A矩阵的行数
    if(!solver.data()->setHessianMatrix(hessian_)) return 1;
    std::cout <<"set hessian success" << std::endl;
    if(!solver.data()->setGradient(gradient_)) return 1;
    std::cout <<"set Gradient success" << std::endl;
    if(!solver.data()->setLinearConstraintsMatrix(constraintMatrix_)) return 1;
    std::cout <<"set LinearConstraintsMatrix success" << std::endl;
    if(!solver.data()->setLowerBound(lowerBound_)) return 1;
    if(!solver.data()->setUpperBound(upperBound_)) return 1;
    std::cout <<"set Bound success" << std::endl;
    

    // instantiate the solver
    if(!solver.initSolver()) return 1;

    // controller input and QPSolution vector
    Eigen::VectorXd ctr;
    Eigen::VectorXd QPSolution;

    // solve the QP problem
    if(!solver.solve()) return 1;   

    // get the controller input
    QPSolution = solver.getSolution();
    ctr = QPSolution.block(0, 0, 1, 1);
    std::cout << "cmd " << ctr[0] <<std::endl;
    control_cmd->at(0) = ctr[0];

    return 0;

}

}  // namespace math
}  // namespace common
}  // namespace IAU
