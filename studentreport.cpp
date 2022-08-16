#include<iostream>
#include<fstream>
using namespace std;

// the class that stores data of each student;
class student
{
int rollno;
char name[50];
int english_marks, math_marks, chemistry_marks, physics_marks, CS_marks;
int average;
char grade;

public:
void calculate_grade()
{
average=(english_marks + math_marks + chemistry_marks + physics_marks + CS_marks)/5;
if(average>=90)
grade='A';
else if(average>=75)
grade='B';
else if(average>=50)
grade='C';
else
grade='F';
}

void get_data()   // getting data of each students
{
cout<<"\nEnter student's roll number: ";
cin>>rollno;
cout<<"\nEnter student name:          ";
cin.ignore();
cin.getline(name,50);
cout<<"\n\n\t* All marks should be out of 100";
cout<<"\n\nEnter marks in English:         ";
cin>>english_marks;
cout<<"\nEnter marks in Math:              ";
cin>>math_marks;
cout<<"\nEnter marks in Chemistry:         ";
cin>>chemistry_marks;
cout<<"\nEnter marks in Physics:           ";
cin>>physics_marks;
cout<<"\nEnter marks in Computer science:  ";
cin>>CS_marks;
calculate_grade();
}
void show_data() const
{
cout<<"\n\n\t---------------------------";
cout<<"\n\t|  Name        : "<<name;
cout<<"\n\t|  Roll number : "<<rollno;
cout<<"\n\t---------------------------";
cout<<"\n\t---------------------------";
cout<<"\n\t|  English   ||       "<<english_marks<<"  |";
cout<<"\n\t|  Maths     ||       "<<math_marks<<"  |";
cout<<"\n\t|  Chemistry ||       "<<chemistry_marks<<"  |";
cout<<"\n\t|  Physics   ||       "<<physics_marks<<"  |";
cout<<"\n\t|  CS        ||       "<<CS_marks<<"  |";
cout<<"\n\t---------------------------";
cout<<"\n\t|\t  Average  :  "<<average<<"  |";
cout<<"\n\t|\t  Grade    :   "<<grade<<"  |";
cout<<"\n\t---------------------------\n";
}
int return_rollno() const
{
return rollno;
}
}; //class ends here


//write student details to file
void create_student()
{
student s1;
ofstream f1;
f1.open("student.dat",ios::binary|ios::app);
s1.get_data();
f1.write((char*)&s1, sizeof(s1));
f1.close();
cout<<"\n\nStudent record Has Been Created ";
cin.ignore();
cin.get();
}
// read file records
void display_all()
{
student s1;
ifstream f1;
f1.open("student.dat",ios::binary);
if(f1)
{
system("cls");
cout<<"\n\n\n\t\tDISPLAYING ALL RECORDS\n\n";
while(f1.read((char*)&s1, sizeof(s1)))
{
s1.show_data();
cout<<"\n\n====================================\n";
}
}
else{
  cout<<"\n\nFile is empty\n";
}
f1.close();
cin.ignore();
cin.get();
}
//read specific record based on roll number
void display_sp(int n)
{
student s1;
ifstream f1;
bool f=false;
f1.open("student.dat",ios::binary);
if(f1)
{
while(f1.read((char*)&s1, sizeof(s1)) )
{
if(s1.return_rollno()==n)
{
 system("cls");
 s1.show_data();
 f=true;
 break;
}
}
}
else{
  cout<<"\n\nFile is empty\n";
}
f1.close();
if(f==false)
cout<<"\n\nrecord does not exist";
cin.ignore();
cin.get();
}
// modify record for specified roll number
void change_student(int n)
{
bool f=false;
student s1;
fstream f1;
f1.open("student.dat",ios::binary|ios::in|ios::out);
if(!f1)
{
cout<<"File could not be opened. Press any Key to exit...";
cin.ignore();
cin.get();
return;
}
while(!f1.eof() && f==false)
{
f1.read((char*)&s1, sizeof(s1));
if(s1.return_rollno()==n)
{
s1.show_data();
cout<<"\nEnter new student details:"<<endl;
s1.get_data();
    int pos=(-1)*(sizeof(s1));
    f1.seekp(pos,ios::cur);
    f1.write((char*)&s1, sizeof(s1));
    cout<<"\n\n\t Record Updated";
    f=true;
}
}
f1.close();
if(f==false)
cout<<"\n\n Record Not Found ";
cin.ignore();
cin.get();
}
//delete record with particular roll number
void delete_student(int n)
{
student s1;
ifstream f1;
f1.open("student.dat",ios::binary);
if(!f1)
{
cout<<"File could not be opened... Press any Key to exit...";
cin.ignore();
cin.get();
return;
}
ofstream f2;
f2.open("Temp.dat",ios::out);
f1.seekg(0,ios::beg);
while(f1.read((char*)&s1, sizeof(s1)))
{
if(s1.return_rollno()!=n)
{
f2.write((char*)&s1, sizeof(s1));
}
}
f2.close();
f1.close();
remove("student.dat");
rename("Temp.dat","student.dat");
cout<<"\n\n\tRecord Deleted ..";
cin.ignore();
cin.get();
}
//MAIN
int main()
{
char ch;
do
{
char ch;
int num;
system("cls");
cout<<"\n\n\n\tMENU";
cout<<"\n\n\t1.Create student record";
cout<<"\n\n\t2.Search student record";
cout<<"\n\n\t3.Display all students records ";
cout<<"\n\n\t4.Delete student record";
cout<<"\n\n\t5.Modify student record";
cout<<"\n\n\t6.Exit";
cout<<"\n\nEnter your Choice (1/2/3/4/5/6) ";
cin>>ch;
system("cls");
switch(ch)
{
case '1': create_student(); 
          break;
case '2': cout<<"\n\n\tEnter The roll number "; 
          cin>>num;
          display_sp(num); 
          break;
case '3': display_all(); 
          break;
case '4': cout<<"\n\n\tEnter The roll number: "; 
          cin>>num;
          delete_student(num);
          break;
case '5': cout<<"\n\n\tEnter The roll number "; 
          cin>>num;
          change_student(num);
          break;
case '6': cout<<"Exiting, Thank you!";
          exit(0);

}
}while(ch!='6');
return 0;
}
