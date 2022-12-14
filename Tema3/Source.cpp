#include<iostream>
#include <cstring>
#include<memory>
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
     bool isLocked;
    public:
    Cars(  const string name , const int numberOfDoors  ,const string carOwner, const string color, const bool &isLocked ):
        name(name),
numberOfDoors(numberOfDoors),
carOwner(carOwner),
color(color),
isLocked(isLocked)
{};
    ~Cars(){
    cout<<"destructor"<<endl; //just to see how it works
    }


    void showDetails(){
        cout<<"name: "<<name<<endl<<"Number of doors: "<<numberOfDoors<<endl<<"owner: "<<carOwner<<endl<<"color: "<<color<<endl<<"locked: "<<isLocked<<endl;
        cout<<endl;
    }

   Cars(const Cars& c){
       name = c.name;
       numberOfDoors = c.numberOfDoors;
       carOwner = c.carOwner;
       color = c.color;
       isLocked = c.isLocked;
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
                this->isLocked = t.isLocked;
            }
        std::cout << "Copied Object"; //just to see that it works
        return *this; //return the left-hand object
    }
    bool getCarIsLocked(){
       return isLocked;
    }
    void setCarLocked( bool isLocked){
       this->isLocked = isLocked;
    }
    void setNumberOfDoors( int numberOfDoors){
       this->numberOfDoors = numberOfDoors;
    }
    int getNumberOfDoors(){
       return numberOfDoors;
    }
    string getCarOwner(){
       return carOwner;
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
    ExpensiveCars(const string name,const int numberOfDoors, const string carOwner, const string color,const bool &isLocked, const int price):
         Cars(name,numberOfDoors,carOwner,color,isLocked),price(price){};
    //copy constr superclasei se copiaza si el
    ExpensiveCars(const  ExpensiveCars& e): Cars(e),price(e.price){};
    ~ExpensiveCars(){
      cout<<"destructor expensive cars"<<endl;
    }
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

  Cars* createCars(const string name,const int numberOfDoors, const string carOwner, const string color,const bool &isLocked ){
      return new Cars(name,numberOfDoors,carOwner,color,isLocked);
  }

  void lock(Cars& car) {
    car.setCarLocked(true);
    cout<<"Car locked"<<endl;
  };

  void unlock(Cars& car) {
    car.setCarLocked(false);
    cout<<"Car unlocked"<<endl;
  };
  class Lock: private Uncopyable{

   private: Cars& carPtr;
   public:
    Lock(Cars& ptr): carPtr(ptr){
        lock(carPtr);
    }
    ~Lock(){
      unlock(carPtr);
    }

};
 // item 4member initialization list



int main(){

   /* Cars* car1 = new Cars("Audi",2,"Mihai Popescu","red");
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
   */
   /* item 13*/
   auto_ptr<Cars>car1(createCars("Audi",2,"Mihai Popescu","red",false));

   cout<<car1->getCarOwner()<<endl;
   cout<<car1->getNumberOfDoors()<<endl;

   auto_ptr<Cars>car2(car1);

   cout<<car2->getCarOwner()<<endl;
   cout<<car2->getNumberOfDoors()<<endl;

   /*cout<<car1->getCarOwner()<<endl;
   cout<<car1->getNumberOfDoors()<<endl;
   */
   /* segmentation fault, car1 a fost distrus */

   shared_ptr<Cars>car3(createCars("BMW",4,"Maria Ionescu","black",false));

   cout<<car3->getCarOwner()<<endl;
   cout<<car3->getNumberOfDoors()<<endl;

   shared_ptr<Cars>car4(car3); //arata spre ac obiect creat mai sus

   cout<<car4->getCarOwner()<<endl;
   cout<<car4->getCarIsLocked()<<endl;
   cout<<"car3 "<<car3->getCarOwner()<<endl; //acum functioneaza
   cout<<"car3 "<<car3->getNumberOfDoors()<<endl;

   /* item 14 */
   Cars car5("Hyundai",4,"Ion Ionescu","black",false);
   cout<<car5.getCarOwner()<<" "<<car5.getNumberOfDoors()<<" "<<car5.getCarIsLocked()<<endl;
   Lock car6(car5);
   car5.setCarLocked(true);
   car5.setNumberOfDoors(7);
   cout<<car5.getCarOwner()<<" "<<car5.getNumberOfDoors()<<" "<<car5.getCarIsLocked()<<endl;




   return 0;


}
