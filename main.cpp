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

    //toy example
    cout << "Data: " << endl;
    cout << m<< endl;

    double alpha = 0.34;
    std::size_t h = 100;

//NEL COSTRUTTORE DEVO METTERE std::move(m)
    //queste due linee di codice funzionano, ma hanno necessità che il template parameter sia già noto
    //std::unique_ptr<PPC::PPC_KO_base> ko = PPCfactory<KO_Type::CV>(std::move(m));
    //std::unique_ptr<PPC::PPC_KO_base> ko = PPCfactory<KO_Type::NoCV>(id,std::move(m),alpha);

    //quello che vorrei avere è una cosa del genere
    const string id = "CV";
    //std::unique_ptr<PPC::PPC_KO_base> ko = KO_Solver(id,std::move(m));  //non funziona
    

    //oppure
    using KO_T = std::conditional(string_id(id),KO_Type::NoCV, KO_Type::CV);
    std::unique_ptr<PPC::PPC_KO_base> ko = PPCfactory<KO_T>(std::move(m));
    //in entrambi i casi però bisognerebbe capire come passare il secondo parametro


    ko->solve();

    cout << "1-step ahead prediction: " << endl;
    cout << ko->prediction() << endl;

    cout << "Alpha is " << ko->alpha() << endl;


    return status;
}