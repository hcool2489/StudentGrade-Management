/*
--Binary Files (Working with structure and classes)

Q. Write a menu driven prog using binary files to achieve the following
1. Insert
2. Display all
3. Search
	1. Rno
	2. Name
4. Delete
5. Modify
*/

#include<iostream.h>
#include<conio.h>
#include<process.h>
#include<stdio.h>
#include<fstream.h>
#include<string.h>

class student
{
	int rno;
	char name[20];
	float marks;
	char grade;

public:
	char grade_assign(float marks)
	{
		if(marks>80)
			return 'A';
		else if (marks>60)
			return 'B';
		else if (marks>40)
			return 'C';
		else
			return 'D';
	}

	void readdata()
	{
		cout<<"RNo: ";
		cin>>rno;
		cout<<"Name: ";
		gets(name);
		cout<<"Marks: ";
		cin>>marks;
		grade = grade_assign(marks);
	}

	void displaydata()
	{
		cout<<"RNo:\t"<<rno<<"\nName:\t"<<name<<"\nMarks:\t"<<marks<<"\nGrade:\t"<<grade;
	}

	int ret_rno()
	{
		return rno;
	}

	char* ret_name()
	{
		return name;
	}

	void modify_c()
	{
		cout<<"RNo:\t"<<rno<<"\nName:\t"<<name<<"\nMarks:\t"<<marks<<"\nGrade:\t"<<grade<<endl;
		cout<<"\n--Enter New Details--\n: ";
		char n[20];
		float m;
		cout<<"Name(or enter \'.\' to retain old one): ";
		cin>>n;
		cout<<"Marks(or enter \'-1\' to retain old one): ";
		cin>>m;
		if (strcmp(n,".")!=0)
			strcpy(name,n);
		if (m!=-1)
		{
			marks=m;
			grade=grade_assign(m);
		}
	}
};

void insert();
void display();
void search_rno();
void search_name();
void modify();
void Delete();
void exit_mod();

void main()
{
	int choice;
	char ans;
	do
	{
		menu:
		clrscr();
		cout<<"--Menu--\n\n0 - Exit\n1 - Insert Record\n2 - Display Record\n3 - Search *\n4 - Modify\n5 - Delete\nAns: ";
		cin>>choice;

		switch(int(choice))
		{
			case 0:
				exit_mod();

			case 1:
				clrscr();
				insert();
				break;

			case 2:
				clrscr();
				display();
				break;

			case 3:
				clrscr();
				int choice1;
				char ans1;
				do
				{
					clrscr();
					cout<<"--Search--\n\n0 - Back\n1 - Search by Rno\n2 - Search by Name\nAns: ";
					cin>>choice1;

					switch(int(choice1))
					{
						case 0:
							goto menu;

						case 1:
							search_rno();
							break;

						case 2:
							search_name();
							break;
							
						default:
							cout<<"\nError: Wrong choice entered...";
					}
					cout<<"\n\nWant to Continue in Same menu(y/n)?: ";
					cin>>ans1;
				}while(ans1=='y'||ans1=='Y');
				break;

			case 4:
				clrscr();
				modify();
				break;

			case 5:
				clrscr();
				Delete();
				break;
			
			default:
				cout<<"\nError: Wrong choice Entered...";
		}
		cout<<"\n\nWant to Continue?(y/n): ";
		cin>>ans;
	}while(ans=='y'||ans=='Y');
	exit_mod();
}

void insert()
{
	student s;
	s.readdata();
	ofstream fout("st.dat",ios::binary|ios::app);
	fout.write((char*)&s,sizeof(s));
/*
fout.write((char*)&s,sizeof(s));
  1		2	  3	   4	5
  
1. It is an Object of ofstream class to write into the file "st.dat".
2. It is a Function to write a complete object in one go to the file "st.dat".
3. It is type casting to convert the data of different type in 's' to characters.
4. It is an address of the object where the data is present in memory.
5. It tells that how many bytes are to be written to the "st.dat".
*/
	fout.close();
}

void Delete()
{
	student s;
	ifstream fin("st.dat",ios::binary);
	ofstream fout("temp.dat",ios::binary);
	int r;
	char flag='n';
	cout<<"--Delete--\nEnter Rno: ";
	cin>>r;
	while(!fin.eof())
	{
		fin.read((char*)&s,sizeof(s));
		if (s.ret_rno()==r)
		{
			flag='f';
			break;
		}
		else
			fout.write((char*)&s,sizeof(s));
	}
	if (!fin.eof())
	{
		while(!fin.eof())
		{
			fin.read((char*)&s,sizeof(s));
			fout.write((char*)&s,sizeof(s));
		}
	}
	if (flag=='n')
		cout<<"\n--Record not Found--";
	else
		cout<<"\n--Successful--";
	fin.close();
	fout.close();
	remove("st.dat");
	rename("temp.dat","st.dat");
}

void modify()
{
	student s;
	fstream fio;
	fio.open("st.dat",ios::in|ios::out|ios::binary);
	int r;
	cout<<"--Modify--\nRno: ";
	cin>>r;
	char flag='n';
	int pos;
	while(!fio.eof())
	{
		pos=fio.tellg();
		fio.read((char*)&s,sizeof(s));
		if (s.ret_rno()==r)
		{
			s.modify_c();
			fio.seekg(pos,ios::beg);
			fio.write((char*)&s,sizeof(s));
			flag='f';
		}
	}
	if(flag=='n')
		cout<<"\n--Record not Found--";
	else
		cout<<"\n--Successful--";
	fio.close();
}

void search_name()
{
	student s;
	char n[20], flag='n';
	cout<<"--Search--\nEnter Name: ";
	gets(n);
	ifstream fin("st.dat",ios::binary);
	while(!fin.eof())
	{
		fin.read((char*)&s,sizeof(s));
		if (strcmpi(s.ret_name(),n)==0)
		{
			s.displaydata();
			flag='f';
		}
	}
	if (flag=='n')
		cout<<"\n--Record not Found--";
	fin.close();
}

void search_rno()
{
	student s;
	ifstream fin;
	fin.open("st.dat",ios::binary);
	int r;
	char flag='n';
	cout<<"--Search--\nEnter Rno: ";
	cin>>r;
	while(!fin.eof())
	{
		fin.read((char*)&s,sizeof(s));
		if(s.ret_rno()==r)
		{
			s.displaydata();
			flag='f';
			break;
		}
	}
	if(flag=='n')
		cout<<"\n--Record not Found--";
	fin.close();
}

void display()
{
	cout<<endl;
	student s;
	ifstream fin("st.dat",ios::binary);
	while(!fin.eof())
	{
		break;
	}
	s.displaydata();
	fin.close();
}

//Insertion of record in sorted order
/*
ifstream fin("st.dat",ios::binary);
ofstream fin("temp.dat",ios::binary);
char last='y';
student s1,s2;
cout<<"Enter details to be inserted...";
s1.readdata();
while(!fin.eof())
{
	fin.read((char*)&s2,sizeof(s2));
	if(s1.ret_rno()<s2.retrno())
	{
		fout.write((char*)&s1,sizeof(s1));
		last='n';
		break;
	}
	else
		fout.write((char*)&s2,sizeof(s2));
}
if (flag=='y')
	fout.write((char*)&s1,sizeof(s1));
else if (!fin.eof())
{
	while(!fin.eof())
	{
		fin.read((char*)&s2,sizeof(s2));
		fin.read((char*)&s2,sizeof(s2));
	}
}
fin.close();
fout.close();
remove("st.dat");
rename("temp.dat","st.dat")
*/

void exit_mod()
{
	clrscr();
	cout<<"\t\tMade BY\n\n";
	cout<<"##      ##        ###         ####      # # # #   ##      ##  ######  ########\n";
	for(long int i=0;i<2000000;i++){}
	cout<<"##      ##       ## ##        ##  ##   #          ##      ##    ##       ##\n";
	for(i=0;i<2000000;i++){}
	cout<<"##      ##      ##   ##       ##   ##  #          ##      ##    ##       ##\n";
	for(i=0;i<2000000;i++){}
	cout<<"##########     ##     ##      ##  ##     # # #    ##########    ##       ##\n";
	for(i=0;i<2000000;i++){}
	cout<<"##      ##    ###########     ####             #  ##      ##    ##       ##\n";
	for(i=0;i<2000000;i++){}
	cout<<"##      ##   ##         ##    ##  #            #  ##      ##    ##       ##\n";
	for(i=0;i<2000000;i++){}
	cout<<"##      ##  ##           ##   ##    #   # # # #   ##      ##  ######     ##";
	cout<<"\n\n\n\t\tPress any Key to exit...";
	getch();
	exit(0);
}