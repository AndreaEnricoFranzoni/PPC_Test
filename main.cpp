#include <iostream>
#include <variant>
#include <type_traits>


#include "KO_Traits.hpp"
#include "PPC_KO.hpp"
#include "KO_factory.hpp"
#include "error_function.hpp"

using namespace std;



int main()
{
    int status(0);

    //int nrow=4;
    //int ncol=3;

    int nrow=4; 
    int ncol=5;

        KO_Traits::StoringMatrix m(nrow,ncol);
    double k = 1.0;

    for (int i = 0; i < nrow; ++i)
    {
        for (int j = 0; j < ncol; ++j)
        {   
            if (j%2==0){
               m(i,j) = k; 
            }

            
            else
            {
                m(i,j) = k + static_cast<double>(4);
            }
            k ++ ;
        }
        
    }

    cout << "Data: " << endl;
    cout << m<< endl;

    double alpha = 0.34;
    std::size_t h = 100;

    constexpr string id = "CV";
    //using KO_T = std::conditional<false,KO_Type::NoCV,KO_Type::CV>; //it will be 0 or 1

//NEL COSTRUTTORE DEVO METTERE std::move(m)
    //std::unique_ptr<PPC::PPC_KO_base> ko = PPCfactory<KO_Type::CV>(std::move(m));
    //std::unique_ptr<PPC::PPC_KO_base> ko = PPCfactory<KO_Type::NoCV>(id,std::move(m),alpha);

    std::unique_ptr<PPC::PPC_KO_base> ko = KO_Solver(id,std::move(m));
    



    ko->solve();

    cout << "1-step ahead prediction: " << endl;
    cout << ko->prediction() << endl;

    cout << "Alpha is " << ko->alpha() << endl;


    /*
            KO_Traits::StoringMatrix m2(nrow,ncol);
    double k2 = 1.0;

    for (int i = 0; i < nrow; ++i)
    {
        for (int j = 0; j < ncol; ++j)
        {   
            if (j%2==0){
               m2(i,j) = k2; 
            }

            
            else
            {
                m2(i,j) = k2 + static_cast<double>(4);
            }
            k2 ++ ;
        }
        
    }

    cout << "M: " << endl;
    cout << m << endl;

    cout << "M2:" << endl;
    cout << m2 << endl;


    std::unique_ptr<PPC::PPC_KO_base> ko_2 = KO_Factory::KO_solver(id,std::move(m2),alpha);

    ko_2->solve();

    cout << "Solution:" << endl;
    cout << ko_2->prediction() << endl;

*/

/*
    cout<<"Valid err"<<endl;
    for (size_t i = 0; i < ko_2->ValidErr().size(); ++i)
    {
        cout << ko_2->ValidErr()[i] << endl;
    }
*/

    




    return status;
}