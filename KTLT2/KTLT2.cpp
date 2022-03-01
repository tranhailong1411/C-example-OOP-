#include<iostream>
#include<fstream>
#include<iomanip>
#include <vector>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include <algorithm>
using namespace std;
class student
{
public:
	int idnum;
	char name[50];
	int physics, chemistry, mathematics, english, comscience;
	double per;
	char grade;
public:
//	int getidnum();
//	char getname();
//	int getphysics();
//	int getchemistry();
//	int getmathematics();
//	int getenglish();
//	int getcomscience();
	void getdata();	
	float calculate();		
	void showdata() const;	
	void show_tabular() const;
	int getIDNum() const;
}; 
//	int student::getidnum() return idnum;
//	char student::getname();
//	int student::getphysics();
//	int student::getchemistry();
//	int student::getmathematics();
//	int student::getenglish();
//int student::getcomscience(); 

float student::calculate()
{
	per=(physics+chemistry+mathematics+english+comscience)/5.0;
	 if(per>=8.5)
		grade='A';
	else if(per>=7.0)
		grade='B';
	else if(per>=5.5)
		grade='C';
	else if(per>=4)
		grade='D';				
	else
		grade='F';
	return per;
} 
void student::getdata()
{
	cout<<"\nID cua hoc sinh:  ";
	cin>>idnum;
	cout<<"\n\nNhap ten: ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nDiem Vat Ly: ";
	cin>>physics;
	cout<<"\nDiem Hoa: ";
	cin>>chemistry;
	cout<<"\nDiem Toan: ";
	cin>>mathematics;
	cout<<"\nDiem Anh: ";
	cin>>english;
	cout<<"\nDiem Tin: ";
	cin>>comscience;
	calculate();
}
 
void student::showdata() const
{
	cout<<"\nID Number: "<<idnum;
	cout<<"\nTen: "<<name;
	cout<<"\nDiem Ly: "<<physics;
	cout<<"\nDiem Hoa: "<<chemistry;
	cout<<"\nDiem Toan: "<<mathematics;
	cout<<"\nDiem Anh: "<<english;
	cout<<"\nDiem Tin hoc: "<<comscience;
	cout<<"\nDiem trung binh: "<<per;
	cout<<"\nXep loai: "<<grade;
}
 
void student::show_tabular() const
{
	cout<<idnum<<setw(6)<<name<<setw(10)<<physics<<setw(12)<<chemistry<<setw(12)<<mathematics<<setw(12)
		<<english<<setw(12)<<comscience<<setw(10)<<per<<setw(5)<<grade<<endl;
}
 
int  student::getIDNum() const
{
	return idnum;
}
void SaveStudent();	
void displayAll();	
void Searchdisplay(int);	
void modifyStudent(int);	
void deleteStudent(int);	
void DisplayClassResult();	
void DisplayResult();			
void write_student()
{
	student st;
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	st.getdata();
	outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
	outFile.close();
    	cout<<"\n\nThong tin cua hoc sinh da duoc ghi lai ";
	cin.ignore();
	cin.get();
}
void display_all()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\n\t\tThong tin ca lop !!!\n\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.showdata();
		cout<<"\n\n====================================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}
struct less_than_key
{
    inline bool operator() (student* Sv1,student* Sv2)
    {
        return (Sv1->calculate() < Sv2->calculate());
    }
};
void sort1()
{	
	vector<student*> vec;
	student st;
	student st1[30];
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
student* p;
vector<student*>::iterator j; 
int i=0;
		while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{	
		st1[i] =st;
		vec.push_back(&st1[i]);
		i=i+1;	
	}
	sort(vec.begin(), vec.end(), less_than_key());
		for (j = vec.begin(); j != vec.end(); j++) {
		p=*j;
		p->showdata();
		cout<<"\n\n====================================\n";
		}	
	inFile.close();
	cin.ignore();
	cin.get();
}
void printftxt()
{
	student st;
	student st1[30];
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
int i=0;
		while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{	
		st1[i] =st;
		i=i+1;	
	}
	inFile.close();
	ofstream outfile; 
    outfile.open("student1.txt");
    for(int j=0;j<i;j++){
	outfile << st1[j].name<<","<<st1[j].idnum<<","<<st1[j].grade<< endl;
	}  
    outfile.close();  
    cout<<"Du lieu da duoc in ra file student1.txt";
	cin.ignore();
	cin.get();
}
void display_sp(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.getIDNum()==n)
		{
	  		 st.showdata();
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nKhong co du lieu";
	cin.ignore();
	cin.get();
}
void modify_student(int n)
{
	bool found=false;
	student st;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
    	while(!File.eof() && found==false)
	{
 
		File.read(reinterpret_cast<char *> (&st), sizeof(student));
		if(st.getIDNum()==n)
		{
			st.showdata();
			cout<<"\n\nXin hay nhap thong tin moi cua hoc sinh"<<endl;
			st.getdata();
		    	int pos=(-1)*static_cast<int>(sizeof(st));
		    	File.seekp(pos,ios::cur);
		    	File.write(reinterpret_cast<char *> (&st), sizeof(student));
		    	cout<<"\n\n\t Cap nhat thanh cong";
		    	found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n Khong ton tai du lieu ";
	cin.ignore();
	cin.get();
}
void delete_student(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.getIDNum()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	cout<<"\n\n\tRecord Deleted ..";
	cin.ignore();
	cin.get();
}
void class_result()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\tToan bo danh sach sinh vien  \n\n";
	cout<<"==========================================================\n";
	cout<<"R.No       Name        DiemLy   DiemHoa   DiemToan   DiemAnh   DiemTin     DiemTb   Xeploai"<<endl;
	cout<<"==========================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student))) //dung de doc file kieu nhi phan
	{
		st.show_tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}
 
int main()
{
	char ch;
	int num;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2); //in ra tat ca cac so deu co dang .xx
	do
	{
	system("cls");
	cout<<"\t|*****************Chuong trinh quan ly hoc sinh****************|";
	cout<<"\n\n\t|------------|1.Tao ho so hoc sinh                |------------|";
	cout<<"\n\n\t|------------|2.In ra ho so cua toan bo hoc sinh  |------------|";
	cout<<"\n\n\t|------------|3.Tim kiem ho so hoc sinh           |------------|";
	cout<<"\n\n\t|------------|4.Chinh sua ho so                   |------------|";
	cout<<"\n\n\t|------------|5.Xoa ho so                         |------------|";
	cout<<"\n\n\t|------------|6.In ra ket qua cua ca lop          |------------|";
	cout<<"\n\n\t|------------|7.Sap xep theo diem trung binh      |------------|";
	cout<<"\n\n\t|------------|8.Xuat du lieu hoc sinh ra file text|------------|";
	cout<<"\n\n\t|------------|9.Thoat chuong trinh                |------------|";
	cout<<"\n\n\t|**************************************************************|";
	cout<<"\n\n\tLua chon cua ban (1-9):? ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1':	write_student(); break;
	case '2':	display_all(); break;
	case '3':	cout<<"\n\n\tID cua hoc sinh: "; cin>>num;
				display_sp(num); break;
	case '4':	cout<<"\n\n\tID cua hoc sinh: "; cin>>num;
			modify_student(num);break;
	case '5':	cout<<"\n\n\tID cua hoc sinh: "; cin>>num;
			delete_student(num);break;
	case '6' :	class_result(); break;
	case '7' :	sort1(); break;
	case '8' :	printftxt(); break;
	case '9':	exit(0);
	default:	cout<<"\a"; 
		
    }
	}while(ch!='9');
 
	return 0;
}
