#include<iostream>
#include <cstring>
using namespace std;
//item 5
//Compilers may implicitly generate a class’s default constructor, copy
//constructor, copy assignment operator, and destructor.
//item 6
//To disallow functionality automatically provided by compilers, de-
//clare the corresponding member functions private and give no imple-
//mentations. Using a base class like Uncopyable is one way to do this.
class Uncopyable {   //base class specifically designed to prevent copying
protected: // allow construction
Uncopyable() {} // and destruction of
~Uncopyable() {} // derived objects...

private: //ca sa nu se foloseasca cel default l am facut private
Uncopyable(const Uncopyable&); // ...but prevent copying //copy constructor
Uncopyable& operator=(const Uncopyable&); //copy assignment operator



};
//daca nu as fi scris eu copy contr si copy ass nu m-ar fi lasat sa copiez
// so that Cars objects would not be copied, we inherit from Uncopyable
class Cars:private Uncopyable{
   private:
     string name;
     int numberOfDoors;
     string carOwner;
     string color;
    public:
    Cars(  const string name , const int numberOfDoors  ,const string carOwner, const string color ):
        name(name),
numberOfDoors(numberOfDoors),
carOwner(carOwner),
color(color){
};
    ~Cars(){
    cout<<"destructor"<<endl; //just to see how it works
    }


    void showDetails(){
        cout<<"name: "<<name<<endl<<"Number of doors: "<<numberOfDoors<<endl<<"owner: "<<carOwner<<endl<<"color: "<<color<<endl;
        cout<<endl;
    }

   Cars(const Cars& c){
       name = c.name;
       numberOfDoors = c.numberOfDoors;
       carOwner = c.carOwner;
       color = c.color;
        std::cout << "Copied Object"; //just to see that it works

    }
//item 10
   Cars& operator=(const Cars& t){ //overwriting assignement operator
        if(this!=&t)
            {
                this->name = t.name;
                this->numberOfDoors = t.numberOfDoors;
                this->carOwner = t.carOwner;
                this->color = t.color;
            }
        std::cout << "Copied Object"; //just to see that it works
        return *this; //return the left-hand object
    }






};
class CarsElectric{

private:
    Cars *pb;


public:
    CarsElectric(Cars *pb):

pb(pb){
}
          CarsElectric& operator=(const CarsElectric& rhs)
    {
        Cars *pOrig = pb;
        pb = new Cars(*rhs.pb);
        delete pOrig;
        std::cout<<"deleted"<<endl;
        cout<<endl;
        return *this;

    }
};
class ExpensiveCars: public Cars{
  private:
      int price;
  public:
    ExpensiveCars(const string name,const int numberOfDoors, const string carOwner, const string color, const int price):
         Cars(name,numberOfDoors,carOwner,color),price(price){};
    //copy constr superclasei se copiaza si el
    ExpensiveCars(const  ExpensiveCars& e): Cars(e),price(e.price){};

   void display2(){
       Cars::showDetails();
       cout<<"price:"<<price<<endl;
    }
    ExpensiveCars& operator=(const ExpensiveCars& rhs){
       Cars::operator=(rhs);
       price= rhs.price;
       return *this;
    }
};
 // item 4member initialization list



int main(){

    Cars* car1 = new Cars("Audi",2,"Mihai Popescu","red");
    CarsElectric car5(car1);
    car1->showDetails();

    Cars car3("Hyundai",4,"Ion Ionescu","black");
    car3.showDetails();
    Cars car4 = car3;
    car4.showDetails();
    car4 = car4;
    car4.showDetails();
      car5 = car5;
      //item 12
      ExpensiveCars e1("Audi",5,"Maria Popescu","black",1000);
      e1.display2();
      ExpensiveCars e2("BMW",4,"Maria Ionescu","black",10300);
      e2.display2();
      e2 = e1;
      e2.display2();

   return 0;


}
