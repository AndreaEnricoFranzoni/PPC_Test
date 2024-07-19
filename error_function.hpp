#ifndef ERROR_FUNC_HPP
#define ERROR_FUNC_HPP

#include <Eigen/Dense>

#include <algorithm>
#include <numeric>

namespace EF_PPC
{
template<typename T>
double mse(const Eigen::Matrix<T,Eigen::Dynamic,1> &diff)
{

    double mse = std::transform_reduce(
        diff.begin(),
        diff.end(),
        0.0,
        std::plus{},
        [] (T const &x) {return std::pow(x,2);}
    );
    
    return mse/static_cast<double>(diff.size());
};


/*
template<typename T>
double mse(const Eigen::Matrix<T,Eigen::Dynamic,1> &v1, const Eigen::Matrix<T,Eigen::Dynamic,1> &v2)
{
    Eigen::Matrix<T,Eigen::Dynamic,1> diff = v1.array() - v2.array();

    double mse = std::transform_reduce(
        diff.begin(),
        diff.end(),
        0.0,
        std::plus{},
        [] (double const &x) {return std::pow(x,2);}
    );

    return mse;
};
*/

}   //end namespace EF_PPC

#endif /*ERROR_FUNC_HPP*/