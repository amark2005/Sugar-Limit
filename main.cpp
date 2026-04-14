#include <iostream>
#include <string>
#include "raygui.h"

struct Body{
  float height=0;
  float weight=0;
  float age=0;
  std::string gender="";
  bool ismale=true;
  Body(){
    std::cout<<"Enter Age: ";
    std::cin>>age;
    std::cout<<"Enter Height: ";
    std::cin>>height;
    std::cout<<"Enter Weight: ";
    std::cin>>weight;
    std::cout<<"Are You a Male or Female(type m for male and f for female): ";
    std::cin>>gender;
    if(gender=="f")ismale=false;
  }
  float const BMR(){
    float bmr=0;
    if(ismale)bmr=(10*weight)+(6.25*height)-(5*age)+5;
    else bmr=(10*weight)+(6.25*height)-(5*age)-161;
    return bmr;
  }
  float const TDEE(){
    return BMR()*1.4;   //TODO: Need to add activity levels
  }
  float const dailycalorie(){return TDEE();}
  float const sugarlimit(){return (dailycalorie()*0.05)/4;}
  float const sugarlimit_teaspoon(){return sugarlimit()/4;}
};

int main(){
  Body amar;
  std::cout<<"Daily Calorie: "<<amar.dailycalorie()<<"\n";
  std::cout<<"Daily Sugar Limit: "<<amar.sugarlimit()<<"\n";
  std::cout<<"Daily Sugar Limit in Teaspoons: "<<amar.sugarlimit_teaspoon()<<"\n";
  return 0;
  
}