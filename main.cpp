#include "biblio.hh"
#include <iostream>

using namespace std;

int main()
{
    video vid1("bardella victory" , "BFMTV" , support::DVD) ;
    std::cout<<vid1<<"\n";
    std::cout<<"-------------------"<<"\n";
    periodique ped1("élections européennes" , "jack lang" , 15 , 10);
    std::cout<<ped1<<"\n";
    return 0;
}
