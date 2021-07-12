//SOURCE C++ CODE

//RESTAURANT MANAGEMENT
#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<process.h>
#include<ctype.h>
int y=1,z=1,stype=1,o=1,ch2,disp=0,rec2=0,x=1;
/***********************************************
 CLASS TO CONTROL ALL FUNCTIONS RELATED TO OWNER
 ***********************************************/
class OWNER
{
	int code,price,rec;
	char iname[20];
	public:
		void getdata();
		void showdata();
		void show();
		int retcode();
		void getnewprice();
		int retrec();
		int retprice();
		char* retname();
}O;
/**************************************************
 CLASS TO CONTROL ALL FUNCTIONS RELATED TO CUSTOMER
 **************************************************/
class CUSTOMER
{
	int cd,qty,rec1,ono,price1;
	char miname[20],cname[20],cadd[20],styp[20],ostatus[20],mno[20];
	public:
		void getdata1();
		void showdata1();
		void showdata2();
		int retrec1();
		void getnewqty(int q);
		int retcd();
		int retqty();
		void servicetype(int stype);
		int retprice1();
		int retono();
		void modqty();
		void ostat();
		char* retminame();
		char* retcname();
		char* retcadd();
		char* retostatus();
		char* retmno();
		char* retstyp();
}C;
/**********************************************
 CLASS TO CONTROL ALL FUNCTIONS RELATED TO BILL
 **********************************************/
class BILL
{
	int sum;
	float tax,amount;
	public:
		void calculate();
		int retsum();
		float rettax();
		float retamount();
}B;
/*******************************************************
 CLASS TO CONTROL ALL FUNCTIONS RELATED TO ORDER HISTORY
 *******************************************************/
class OHISTORY
{
	int hcd,hqty,hono,hprice,hsum,rec3;
	float htax,hamount;
	char hname[20],hcname[20],hcadd[20],hstyp[20],hostatus[20],hmno[20];
	public:
		void hwrite();
		int rethono();
		void show1();
		int retrec3();
}H;
/**************************************************
 CLASS TO CONTROL ALL FUNCTIONS RELATED TO PASSWORD
 **************************************************/
class PASSWORD
{
	char B[50];
	public:
		void password();
		int passcomp(char A[]);
		int pass(char c);
}P;
/*******************************
 FUNCTION TO INPUT DATA FOR MENU
 *******************************/
void OWNER::getdata()
{
	code=z;
	cout<<"Code: "<<code<<endl;
	cout<<"Enter item name: ";
	gets(iname);
	fflush(stdin);
	cout<<"Enter price: ";
	cin>>price;
	z++;
}
/*******************************
 FUNCTION TO OUTPUT DATA OF MENU
 *******************************/
void OWNER::showdata()
{
	gotoxy(x,y);
	cout<<code;
	x+=20;
	gotoxy(x,y);
	puts(iname);
	x+=20;
	gotoxy(x,y);
	cout<<price;
	x=1;
	y+=1;
}
/***********************************
 FUNCTION TO OUTPUT HEADINGS OF MENU
 ***********************************/
void OWNER::show()
{
	gotoxy(x,y);
	cout<<"Code";
	x+=20;
	gotoxy(x,y);
	cout<<"Item name";
	x+=20;
	gotoxy(x,y);
	cout<<"Price";
	x=1;
	y+=1;
}
/**************************************
 FUNCTION TO RETURN ITEM CODE FROM MENU
 **************************************/
int OWNER::retcode()
{
	return code;
}
/*******************************************
 FUNCTION TO MODIFY PRICE OF AN ITEM IN MENU
 *******************************************/
void OWNER::getnewprice()
{
	cout<<"\nOld price of item is: "<<price<<endl;
	cout<<"Enter new price of item: ";
	cin>>price;
}
/***********************************************
 FUNCTION TO COUNT THE NUMBER OF RECORDS IN MENU
 ***********************************************/
int OWNER::retrec()
{
	fstream f;
	rec=0;
	f.open("MENU.dat",ios::in|ios::binary);
	f.seekg(0,ios::end);
	rec=f.tellg()/sizeof(O);
	f.close();
	return rec;
}
/*********************************************
 FUNCTION TO RETURN PRICE OF AN ITEM FROM MENU
 *********************************************/
int OWNER::retprice()
{
	return price;
}
/********************************************
 FUNCTION TO RETURN NAME OF AN ITEM FROM MENU
 ********************************************/
char* OWNER::retname()
{
	return iname;
}
/***********************
 FUNCTION TO PLACE ORDER
 ***********************/
void CUSTOMER::getdata1()
{
	int flag=0,q,flagc=0,price2;
	char miname2[20];
	fstream f;
	cout<<"\nEnter item code: ";
	cin>>q;
	f.open("MENU.dat",ios::in|ios::binary);
	while(f.read((char*)&O,sizeof(O)))
	{
		if(O.retcode()==q)
		{
			flag=1;
			break;
		}
	}
	f.close();
	if(flag==0)
		cout<<"Item not in menu..."<<endl;
	else
	{
		if(C.retrec1()>0)
		{
			f.open("CUSTOMER.dat",ios::in|ios::binary);
			while(f.read((char*)&C,sizeof(C)))
			{
				if(C.retcd()==q)
				{
					flagc=1;
					break;
				}
			}
			f.close();
			if(flagc==0)
			{
				f.open("MENU.dat",ios::in|ios::binary);
				while(f.read((char*)&O,sizeof(O)))
				{
					if(O.retcode()==q)
					{
						strcpy(miname2,O.retname());
						price2=O.retprice();
						break;
					}
				}
				f.close();
				cout<<"Enter quantity: ";
				cin>>qty;
				cd=q;
				strcpy(miname,miname2);
				price1=price2;
				f.open("CUSTOMER.dat",ios::app|ios::binary);
				f.write((char*)&C,sizeof(C));
				f.close();
				disp++;
			}
			else
				C.getnewqty(q);
		}
		else
		{
			f.open("MENU.dat",ios::in|ios::binary);
			while(f.read((char*)&O,sizeof(O)))
			{
				if(O.retcode()==q)
				{
					strcpy(miname2,O.retname());
					price2=O.retprice();
					break;
				}
			}
			f.close();
			cout<<"Enter quantity: ";
			cin>>qty;
			cd=q;
			strcpy(miname,miname2);
			price1=price2;
			f.open("CUSTOMER.dat",ios::out|ios::binary);
			f.write((char*)&C,sizeof(C));
			f.close();
			disp=5;
		}
	}
}
/****************************************************
 FUNCTION TO OUTPUT ALL THE DETAILS OF A PLACED ORDER
 ****************************************************/
void CUSTOMER::showdata1()
{
	fstream f;
	if(ch2==4||ch2==5)
	{
		clrscr();
		f.open("CUSTOMER.dat",ios::in|ios::binary);
		f.read((char*)&C,sizeof(C));
		cout<<"\t\t\t**********Order Number: "<<C.retono()<<"**********";
		cout<<"\n\t\t\t**********Bill Details**********";
		f.close();
		x=1;
		y=3;
		cout<<"\nItem Code";
		x+=24;
		gotoxy(x,y);
		cout<<"Item Name";
		x+=24;
		gotoxy(x,y);
		cout<<"Quantity";
		x+=24;
		gotoxy(x,y);
		cout<<"Price";
		x=1;
		y+=1;
		gotoxy(x,y);
		f.open("CUSTOMER.dat",ios::in|ios::binary);
		while(f.read((char*)&C,sizeof(C)))
		{
			cout<<cd;
			x+=24;
			gotoxy(x,y);
			puts(miname);
			x+=24;
			gotoxy(x,y);
			cout<<qty;
			x+=24;
			gotoxy(x,y);
			cout<<price1;
			x=1;
			y+=1;
			gotoxy(x,y);
		}
		f.close();
	}
	if(ch2==2||ch2==6||ch2==7)
	{
		clrscr();
		f.open("CUSTOMER.dat",ios::in|ios::binary);
		f.read((char*)&C,sizeof(C));
		cout<<"\t\t\t**********Order Number: "<<C.retono()<<"**********";
		cout<<"\n\t\t\t**********Service type: "<<C.retstyp()<<"**********";
		f.close();
		x=1;
		y=3;
		gotoxy(x,y);
		cout<<"Mob No.";
		x+=23;
		gotoxy(x,y);
		cout<<"Your Name";
		if(stype==3)
		{
			x+=23;
			gotoxy(x,y);
			cout<<"Address";
		}
		if(ch2==2)
		{
			x+=23;
			gotoxy(x,y);
			cout<<"Status";
		}
		x=1;
		y+=1;
		f.open("CUSTOMER.dat",ios::in|ios::binary);
		f.read((char*)&C,sizeof(C));
		gotoxy(x,y);
		cout<<mno;
		x+=23;
		gotoxy(x,y);
		puts(cname);
		if(stype==3)
		{
			x+=23;
			gotoxy(x,y);
			puts(cadd);
		}
		if(ch2==2)
		{
			x+=23;
			gotoxy(x,y);
			puts(ostatus);
		}
		f.close();
		getch();
		if(C.retrec1()!=0)
		{
			x=1;
			y+=1;
			clrscr();
			f.open("CUSTOMER.dat",ios::in|ios::binary);
			f.read((char*)&C,sizeof(C));
			cout<<"\t\t\t**********Order Number: "<<C.retono()<<"**********";
			cout<<"\n\t\t\t**********Bill Details**********";
			f.close();
			x=1;
			y=3;
			cout<<"\nItem Code";
			x+=24;
			gotoxy(x,y);
			cout<<"Item Name";
			x+=24;
			gotoxy(x,y);
			cout<<"Quantity";
			x+=24;
			gotoxy(x,y);
			cout<<"Price";
			x=1;
			y+=1;
			gotoxy(x,y);
			f.open("CUSTOMER.dat",ios::in|ios::binary);
			while(f.read((char*)&C,sizeof(C)))
			{
				cout<<cd;
				x+=24;
				gotoxy(x,y);
				puts(miname);
				x+=24;
				gotoxy(x,y);
				cout<<qty;
				x+=24;
				gotoxy(x,y);
				cout<<price1;
				x=1;
				y+=1;
				gotoxy(x,y);
			}
			f.close();
			x=49;
			y=disp;
			gotoxy(x,y);
			cout<<"--------------------------------";
			y+=1;
			gotoxy(x,y);
			cout<<"Total: ";
			y+=1;
			gotoxy(x,y);
			cout<<"CGST: ";
			y+=1;
			gotoxy(x,y);
			cout<<"SGST: ";
			y+=1;
			gotoxy(x,y);
			f.open("BILL.dat",ios::in|ios::binary);
			f.read((char*)&B,sizeof(B));
			if(stype==3&&B.retsum()<300)
			{
				cout<<"Home Delivery Charges:  30";
				y+=1;
				gotoxy(x,y);
			}
			cout<<"Amount: ";
			if(stype==3&&B.retsum()<300)
				y-=4;
			else
				y-=3;
			x=73;
			gotoxy(x,y);
			cout<<B.retsum();
			y+=1;
			gotoxy(x,y);
			cout<<B.rettax();
			y+=1;
			gotoxy(x,y);
			cout<<B.rettax();
			y+=1;
			gotoxy(x,y);
			if(stype==3&&B.retsum()<300)
			{
				y+=1;
				gotoxy(x,y);
			}
			cout<<B.retamount();
			f.close();
		}
		else
			cout<<"\nNo items in your cart, Please add items in your cart first...";
	}
}
/******************************************************************************************************
 FUNCTION TO OUTPUT DETAILS OF A SEARCHED ITEM IN ORDER (USED FOR ADDING ITEMS AND MODIFYING QUANTITY)
 ******************************************************************************************************/
void CUSTOMER::showdata2()
{
	clrscr();
	cout<<"\t\t\t**********Order Number: "<<C.retono()<<"**********";
	x=1;
	y=2;
	cout<<"\nItem Code";
	x+=24;
	gotoxy(x,y);
	cout<<"Item Name";
	x+=24;
	gotoxy(x,y);
	cout<<"Quantity";
	x+=24;
	gotoxy(x,y);
	cout<<"Price";
	x=1;
	y+=1;
	gotoxy(x,y);
	cout<<cd;
	x+=24;
	gotoxy(x,y);
	puts(miname);
	x+=24;
	gotoxy(x,y);
	cout<<qty;
	x+=24;
	gotoxy(x,y);
	cout<<price1;
	x=1;
	y+=1;
	gotoxy(x,y);
}
/********************************************************
 FUNCTION TO COUNT THE NUMBER OF RECORDS IN CUSTOMER FILE
 ********************************************************/
int CUSTOMER::retrec1()
{
	fstream f;
	rec1=0;
	f.open("CUSTOMER.dat",ios::in|ios::binary);
	f.seekg(0,ios::end);
	rec1=f.tellg()/sizeof(C);
	f.close();
	return rec1;
}
/******************************************************
 FUNCTION TO SUM UP QUANTITY OF A SAME ITEM IN AN ORDER
 *******************************************************/
void CUSTOMER::getnewqty(int q)
{
	fstream f;
	int qtynew,qtyret,rec1=0;
	cout<<"Enter quantity: ";
	cin>>qtynew;
	f.open("CUSTOMER.dat",ios::in|ios::out|ios::binary);
	while(f.read((char*)&C,sizeof(C)))
	{
		if(C.retcd()==q)
		{
			qtyret=C.retqty();
			qty=(qtynew+qtyret);
			cd=q;
			f.seekp((rec1)*sizeof(C),ios::beg);
			f.write((char*)&C,sizeof(C));
			f.close();
			break;
		}
		else
			rec1++;
	}
}
/*****************************************************
 FUNCTION TO RETURN CODE OF AN ITEM FROM CUSTOMER FILE
 *****************************************************/
int CUSTOMER::retcd()
{
	return cd;
}
/*********************************************************************
 FUNCTION TO RETURN QUANTITY OF AN ITEM IN AN ORDER FROM CUSTOMER FILE
 *********************************************************************/
int CUSTOMER::retqty()
{
	return qty;
}
/************************************************************
 FUNCTION TO INPUT DETAILS OF A CUSTOMER AND THE SERVICE TYPE
 ************************************************************/
void CUSTOMER::servicetype(int stype)
{
	int tono=0,u=0;
	fstream f;
	if(H.retrec3()>0)
	{
		f.open("HISTORY.dat",ios::in|ios::binary);
		while(f.read((char*)&H,sizeof(H)))
			tono=H.rethono();
		f.close();
		tono++;
		o=tono;
	}
	ono=o;
	o++;
	strcpy(ostatus,"Saved");
	if(stype==1)
	{
		cout<<"Enter Your Name: ";
		gets(cname);
		fflush(stdin);
		u=0;
		while(cname[u]!='\0')
		{
			if((toupper(cname[u])<'A'&&cname[u]!=' ')||(toupper(cname[u])>'Z'&&cname[u]!=' '))
			{
				cout<<"Please enter a valid name...";
				cout<<"\nEnter your name: ";
				gets(cname);
				fflush(stdin);
				u=0;
			}
			else
				u++;
		}
		cout<<"Enter your Mobile No.: ";
		gets(mno);
		fflush(stdin);
		u=0;
		while(mno[u]!='\0')
		{
			if(mno[0]=='0'||mno[u]<'0'||mno[u]>'9'||strlen(mno)!=10)
			{
				cout<<"Please enter a valid mobile number...";
				cout<<"\nEnter your Mobile No.: ";
				gets(mno);
				fflush(stdin);
				u=0;
			}
			else
				u++;
		}
		strcpy(styp,"Dine In");
		strcpy(cadd,"N/A");
	}
	else if(stype==2)
	{
		cout<<"Enter Your Name: ";
		gets(cname);
		fflush(stdin);
		u=0;
		while(cname[u]!='\0')
		{
			if((toupper(cname[u])<'A'&&cname[u]!=' ')||(toupper(cname[u])>'Z'&&cname[u]!=' '))
			{
				cout<<"Please enter a valid name...";
				cout<<"\nEnter your name: ";
				gets(cname);
				fflush(stdin);
				u=0;
			}
			else
				u++;
		}
		cout<<"Enter your Mobile No.: ";
		gets(mno);
		fflush(stdin);
		u=0;
		while(mno[u]!='\0')
		{
			if(mno[0]=='0'||mno[u]<'0'||mno[u]>'9'||strlen(mno)!=10)
			{
				cout<<"Please enter a valid mobile number...";
				cout<<"\nEnter your Mobile No.: ";
				gets(mno);
				fflush(stdin);
				u=0;
			}
			else
				u++;
		}
		strcpy(styp,"Take Away");
		strcpy(cadd,"N/A");
	}
	else
	{
		cout<<"Enter Your Name: ";
		gets(cname);
		fflush(stdin);
		u=0;
		while(cname[u]!='\0')
		{
			if((toupper(cname[u])<'A'&&cname[u]!=' ')||(toupper(cname[u])>'Z'&&cname[u]!=' '))
			{
				cout<<"Please enter a valid name...";
				cout<<"\nEnter your name: ";
				gets(cname);
				fflush(stdin);
				u=0;
			}
			else
				u++;
		}
		cout<<"Enter your Mobile No.: ";
		gets(mno);
		fflush(stdin);
		u=0;
		while(mno[u]!='\0')
		{
			if(mno[0]=='0'||mno[u]<'0'||mno[u]>'9'||strlen(mno)!=10)
			{
				cout<<"Please enter a valid mobile number...";
				cout<<"\nEnter your Mobile No.: ";
				gets(mno);
				fflush(stdin);
				u=0;
			}
			else
				u++;
		}
		strcpy(styp,"Home Delivery");
		cout<<"Enter your Address: ";
		gets(cadd);
	}
}
/******************************************************************
 FUNCTION TO RETURN PRICE OF AN ITEM IN AN ORDER FROM CUSTOMER FILE
 ******************************************************************/
int CUSTOMER::retprice1()
{
	return price1;
}
/**************************************************
 FUNCTION TO RETURN ORDER NUMBER FROM CUSTOMER FILE
 **************************************************/
int CUSTOMER::retono()
{
	return ono;
}
/**************************************************
 FUNCTION TO MODIFY QUANTITY OF AN ITEM IN AN ORDER
 **************************************************/
void CUSTOMER::modqty()
{
	cout<<"Old quantity is: "<<qty<<endl;
	cout<<"Enter new quantity: ";
	cin>>qty;
}
/*******************************************
 FUNCTION TO MAINTAIN THE STATUS OF AN ORDER
 *******************************************/
void CUSTOMER::ostat()
{
	fstream f;
	int rec6=0,order;
	f.open("CUSTOMER.dat",ios::in|ios::out|ios::binary);
	if(ch2==6)
	{
		order=C.retono();
		while(f.read((char*)&C,sizeof(C)))
		{
			if(order==C.retono())
			{
				strcpy(ostatus,"Completed");
				f.seekp((rec1)*sizeof(C),ios::beg);
				f.write((char*)&C,sizeof(C));
				f.close();
				break;
			}
			else
				rec6++;
		}
	}
	if(ch2==7)
	{
		order=C.retono();
		while(f.read((char*)&C,sizeof(C)))
		{
			if(order==C.retono())
			{
				strcpy(ostatus,"Cancelled");
				f.seekp((rec1)*sizeof(C),ios::beg);
				f.write((char*)&C,sizeof(C));
				f.close();
				break;
			}
			else
				rec6++;
		}
	}
	f.close();
}
/***********************************************************
 FUNCTION TO RETURN ITEM NAME IN AN ORDER FROM CUSTOMER FILE
 ***********************************************************/
char* CUSTOMER::retminame()
{
	return miname;
}
/*****************************************************
 FUNCTION TO RETURN CUSTOMER'S NAME FROM CUSTOMER FILE
 *****************************************************/
char* CUSTOMER::retcname()
{
	return cname;
}
/********************************************************
 FUNCTION TO RETURN CUSTOMER'S ADDRESS FROM CUSTOMER FILE
 ********************************************************/
char* CUSTOMER::retcadd()
{
	return cadd;
}
/**************************************************
 FUNCTION TO RETURN ORDER STATUS FROM CUSTOMER FILE
 **************************************************/
char* CUSTOMER::retostatus()
{
	return ostatus;
}
/**************************************************************
 FUNCTION TO RETURN CUSTOMER'S MOBILE NUMBER FROM CUSTOMER FILE
 **************************************************************/
char* CUSTOMER::retmno()
{
	return mno;
}
/**************************************************************
 FUNCTION TO RETURN SERVICE TYPE OF AN ORDER FROM CUSTOMER FILE
 **************************************************************/
char* CUSTOMER::retstyp()
{
	return styp;
}
/**************************************
 FUNCTION TO CALCULATE BILL OF AN ORDER
 **************************************/
void BILL::calculate()
{
	sum=0;
	amount=0;
	tax=0;
	int D[50],l=0;
	fstream f;
	f.open("CUSTOMER.dat",ios::in|ios::binary);
	while(f.read((char*)&C,sizeof(C)))
	{
		D[l]=C.retcd();
		l++;
	}
	f.close();
	l=0;
	f.open("CUSTOMER.dat",ios::in|ios::binary);
	while(f.read((char*)&C,sizeof(C)))
	{
		if(C.retcd()==D[l])
		{
			sum+=(C.retqty()*C.retprice1());
			l++;
		}
	}
	f.close();
	tax=((10*sum)/100.0);
	if(sum<300&&stype==3)
		amount=(30+sum+(2*tax));
	else
		amount=(sum+(2*tax));
	remove("BILL.dat");
	f.open("BILL.dat",ios::out|ios::binary);
	f.write((char*)&B,sizeof(B));
	f.close();
}
/******************************************************************
 FUNCTION TO RETURN SUM OF ITEMS PRESENT IN AN ORDER FROM BILL FILE
 ******************************************************************/
int BILL::retsum()
{
	return sum;
}
/***************************************************
 FUNCTION TO RETURN THE AMOUNT OF TAX FROM BILL FILE
 ***************************************************/
float BILL::rettax()
{
	return tax;
}
/************************************************************************
 FUNCTION TO RETURN FINAL AMOUNT INCLUDING TAX OF AN ORDER FROM BILL FILE
 ************************************************************************/
float BILL::retamount()
{
	return amount;
}
/**************************************************************
 FUNCTION TO WRITE THE DETAILS OF ORDERS PLACED IN HISTORY FILE
 **************************************************************/
void OHISTORY::hwrite()
{
	fstream f,f1,f2;
	int rec5=0;
	if(ch2==6)
	{
		f1.open("BILL.dat",ios::in|ios::binary);
		f1.read((char*)&B,sizeof(B));
		hsum=B.retsum();
		htax=B.rettax();
		hamount=B.retamount();
		f1.close();
		f.open("CUSTOMER.dat",ios::in|ios::binary);
		f.read((char*)&C,sizeof(C));
		hono=C.retono();
		strcpy(hcname,C.retcname());
		strcpy(hcadd,C.retcadd());
		strcpy(hstyp,C.retstyp());
		strcpy(hostatus,C.retostatus());
		strcpy(hmno,C.retmno());
		f.close();
		f.open("CUSTOMER.dat",ios::in|ios::binary);
		while(f.read((char*)&C,sizeof(C)))
		{
			hcd=C.retcd();
			hprice=C.retprice1();
			hqty=C.retqty();
			strcpy(hname,C.retminame());
			if(H.retrec3()==0)
			{
				f2.open("HISTORY.dat",ios::out|ios::binary);
				f2.write((char*)&H,sizeof(H));
				f2.close();
			}
			else
			{
				f2.open("HISTORY.dat",ios::app|ios::binary);
				f2.write((char*)&H,sizeof(H));
				f2.close();
			}
		}
		f.close();
	}
	if(ch2==7)
	{
		f.open("CUSTOMER.dat",ios::in|ios::binary);
		f2.open("HISTORY.dat",ios::in|ios::out|ios::binary);
		f.read((char*)&C,sizeof(C));
		while(f2.read((char*)&H,sizeof(H)))
		{
			if(hono==C.retono())
			{
				strcpy(hostatus,C.retostatus());
				f2.seekp((rec5)*sizeof(H),ios::beg);
				f2.write((char*)&H,sizeof(H));
				f2.close();
				break;
			}
			else
				rec5++;
		}
		f.close();
	}
}
/*************************************************
 FUNCTION TO RETURN ORDER NUMBER FROM HISTORY FILE
 **************************************************/
int OHISTORY::rethono()
{
	return hono;
}
/*****************************************************************
 FUNCTION TO OUTPUT DETAILS OF ALL ORDERS PLACED FROM HISTORY FILE
 *****************************************************************/
void OHISTORY::show1()
{
	clrscr();
	fstream f1,f2;
	int rec4=0,temp,temp1=0,flags=0,flagy;
	if(H.retrec3()>0)
	{
		f1.open("HISTORY.dat",ios::in|ios::binary);
		while(f1.read((char*)&H,sizeof(H)))
		{
			clrscr();
			temp=hono;
			temp1=0;
			flagy=0;
			x=1;
			y=1;
			gotoxy(x,y);
			f2.open("HISTORY.dat",ios::in|ios::binary);
			while(f2.read((char*)&H,sizeof(H)))
			{
				if(flags==0)
				{
					if(temp==hono)
					{
						cout<<"\t\t\t**********Order Number: "<<hono<<"**********"<<endl;
						cout<<"\t\t\t**********Service Type: "<<hstyp<<"**********"<<endl;
						cout<<"\t\t\t**********Order Status: "<<hostatus<<"**********"<<endl;
						flags=1;
					}
				}
			}
			f2.close();
			flags=0;
			x=1;
			y=4;
			gotoxy(x,y);						cout<<"Mob No.";
			x+=24;
			gotoxy(x,y);
			cout<<"Customer Name";
			x+=24;
			gotoxy(x,y);
			cout<<"Address";
			x=1;
			y+=1;
			gotoxy(x,y);
			f2.open("HISTORY.dat",ios::in|ios::binary);
			while(f2.read((char*)&H,sizeof(H)))
			{
				if(flags==0)
				{
					if(temp==hono)
					{
						puts(hmno);
						x+=24;
						gotoxy(x,y);
						puts(hcname);
						x+=24;
						gotoxy(x,y);
						puts(hcadd);
						flags=1;
					}
				}
			}
			f2.close();
			flags=0;
			x=1;
			y+=3;
			gotoxy(x,y);
			cout<<"\t\t\t**********Bill Details**********";
			x=1;
			y+=1;
			gotoxy(x,y);
			cout<<"Item Code";
			x+=24;
			gotoxy(x,y);
			cout<<"Item Name";
			x+=24;
			gotoxy(x,y);
			cout<<"Quantity";
			x+=24;
			gotoxy(x,y);
			cout<<"Price";
			x=1;
			y+=1;
			f2.open("HISTORY.dat",ios::in|ios::binary);
			while(f2.read((char*)&H,sizeof(H)))
			{
				if(temp==hono)
				{
					gotoxy(x,y);
					cout<<hcd;
					x+=24;
					gotoxy(x,y);
					puts(hname);
					x+=24;
					gotoxy(x,y);
					cout<<hqty;
					x+=24;
					gotoxy(x,y);
					cout<<hprice;
					x=1;
					y+=1;
					rec4+=1;
					flagy+=1;
				}
			}
			f2.close();
			x=49;
			y=10+flagy;
			gotoxy(x,y);
			cout<<"--------------------------------";
			y+=1;
			gotoxy(x,y);
			cout<<"Total: ";
			y+=1;
			gotoxy(x,y);
			cout<<"CGST: ";
			y+=1;
			gotoxy(x,y);
			cout<<"SGST: ";
			y+=1;
			gotoxy(x,y);
			f2.open("HISTORY.dat",ios::in|ios::binary);
			while(f2.read((char*)&H,sizeof(H)))
			{
				if(flags==0)
				{
					if(temp==hono)
					{
						if(hsum<300&&strcmpi(hstyp,"Home Delivery")==0)
						{
							cout<<"Home Delivery:          30";
							y+=1;
							temp1=1;
							flags=1;
							gotoxy(x,y);
						}
					}
				}
			}
			f2.close();
			flags=0;
			cout<<"Amount: ";
			if(temp1==1)
				y-=4;
			else
				y-=3;
			x=73;
			gotoxy(x,y);
			f2.open("HISTORY.dat",ios::in|ios::binary);
			while(f2.read((char*)&H,sizeof(H)))
			{
				if(flags==0)
				{
					if(temp==hono)
					{
						cout<<hsum;
						y+=1;
						gotoxy(x,y);
						cout<<htax;
						y+=1;
						gotoxy(x,y);
						cout<<htax;
						y+=1;
						gotoxy(x,y);
						if(temp1==1)
						{
							y+=1;
							gotoxy(x,y);
						}
						cout<<hamount;
						flags=1;
					}
				}
			}
			f2.close();
			flags=0;
			getch();
			f1.seekg((rec4)*sizeof(H),ios::beg);
		}
		f1.close();
	}
	else
		cout<<"No orders placed yet...";
}
/*******************************************************
 FUNCTION TO COUNT THE NUMBER OF RECORDS IN HISTORY FILE
 ********************************************************/
int OHISTORY::retrec3()
{
	fstream f;
	rec3=0;
	f.open("HISTORY.dat",ios::in|ios::binary);
	f.seekg(0,ios::end);
	rec3=f.tellg()/sizeof(H);
	f.close();
	return rec3;
}
/************************
 FUNCTION TO SET PASSWORD
 *************************/
void PASSWORD::password()
{
	char c;
	int i=0,ct=19,w;
	clrscr();
	cout<<"Set your password:";
	c=getch();
	w=P.pass(c);
	while(c!=13)
	{
		if(c!=8)
		{
			cout<<"*";
			B[i]=c;
			i++;
			c=getch();
			ct++;
		}
		else if(i>=1)
		{
			ct--;
			gotoxy(ct,1);
			cout<<(char)32;
			i--;
			gotoxy(ct,1);
			c=getch();
			if(i==0)
				w=P.pass(c);
		}
		else
		{
			c=getch();
			w=P.pass(c);
		}
	}
	if(w==1)
	{
		B[i]=NULL;
		cout<<"\nYour password is saved...";
		getch();
	}
}
/****************************
 FUNCTION TO COMPARE PASSWORD
 *****************************/
int PASSWORD::passcomp(char A[])
{
	if(strcmpi(A,B)==0)
		return 1;
	else
		return 0;
}
/****************************************
 FUNCTION TO CHECK CONDITIONS IN PASSWORD
 ****************************************/
int PASSWORD::pass(char c)
{
	int i=0,ct=19,v=1;
	if(c==13)
	{
		while(i==0)
		{
			cout<<"\nPlease enter a valid password...";
			getch();
			clrscr();
			cout<<"Set your password:";
			c=getch();
			while(c!=13)
			{
				if(c!=8)
				{
					cout<<"*";
					B[i]=c;
					i++;
					c=getch();
					ct++;
				}
				else if(i>=1)
				{
					ct--;
					gotoxy(ct,1);
					cout<<(char)32;
					i--;
					gotoxy(ct,1);
					c=getch();
				}
				else
					c=getch();
			}
		}
		v=0;
		B[i]=NULL;
		cout<<"\nYour password is saved...";
		getch();
	}
	return v;
}
void main()
{
	clrscr();
	char c,A[50],r,ans;
	int ch,ch1,ch3,i=0,ct=25,k,rec=0,n,tcode=0,flag=0,a,cd,rec1,pstatus=0,deli,cstatus=0,fstatus=0;
	fstream f,fd;
	cout<<"Do you want to enter a new password(Y/N)?: ";
	cin>>r;
	if(toupper(r)=='Y')
	{
		remove("PASSWORD.dat");
		f.open("PASSWORD.dat",ios::out|ios::binary);
		P.password();
		f.write((char*)&P,sizeof(P));
		f.close();
	}
	if(toupper(r)=='N')
	{
		f.open("PASSWORD.dat",ios::in|ios::binary);
		f.seekg(0,ios::end);
		rec=f.tellg()/sizeof(P);
		f.close();
		if(rec==0)
		{
			cout<<"Password is not saved, please re-enter password...";
			getch();
			remove("PASSWORD.dat");
			f.open("PASSWORD.dat",ios::out|ios::binary);
			P.password();
			f.write((char*)&P,sizeof(P));
			f.close();
		}
	}
	while(1)
	{
		clrscr();
		cout<<"\n\t\t\t**********WELCOME**********"
		    <<"\n\t\tLogin as:"
		    <<"\n\t\t1.Owner"
		    <<"\n\t\t2.Customer"
		    <<"\n\t\t3.Or want to exit"
		    <<"\n\t\tEnter your choice: ";
		cin>>ch;
		switch(ch)
		{
			case 1:k=0;
			       while(k<3)
			       {
					clrscr();
					cout<<"\t\t\t**********OWNER**********"
					    <<"\nEnter password to access"
					    <<"\nPassword:";
					c=getch();
					ct=10;
					i=0;
					while(c!=13)
					{
						if(c!=8)
						{
							cout<<"*";
							A[i]=c;
							i++;
							c=getch();
							ct++;
						}
						else if(i>=1)
						{
							ct--;
							gotoxy(ct,3);
							cout<<(char)32;
							i--;
							gotoxy(ct,3);
							c=getch();
						}
						else
							c=getch();
					}
					A[i]=NULL;
					fd.open("PASSWORD.dat",ios::in|ios::binary);
					fd.read((char*)&P,sizeof(P));
					if(P.passcomp(A)==1)
					{
						fd.close();
						k=3;
						cout<<"\nCorrect,now you can access the account...";
						getch();
						do
						{
							clrscr();
							cout<<"\n\t\t1.Decide Menu"
							    <<"\n\t\t2.Show Menu"
							    <<"\n\t\t3.Add more items"
							    <<"\n\t\t4.Modify rates"
							    <<"\n\t\t5.Delete items"
							    <<"\n\t\t6.View placed orders history"
							    <<"\n\t\t7.Back to main menu"
							    <<"\n\t\tEnter your choice: ";
							cin>>ch1;
							switch(ch1)
							{
								case 1: z=1;
									cout<<"Enter number of items: ";
									cin>>n;
									remove("MENU.dat");
									f.open("MENU.dat",ios::out|ios::binary);
									for(int j=1;j<=n;j++)
									{
										O.getdata();
										f.write((char*)&O,sizeof(O));
									}
									f.close();
									break;
								case 2: y=2;
									if(O.retrec()>0)
									{
										clrscr();
										f.open("MENU.dat",ios::in|ios::binary);
										cout<<"\t\t\t**********MENU**********";
										O.show();
										while(f.read((char*)&O,sizeof(O)))
										{
											O.showdata();
										}
										f.close();
									}
									else
										cout<<"No items in menu...";
									x=1;
									y=1;
									break;
								case 3: if(O.retrec()>0)
									{
										cout<<"Enter number of items to add: ";
										cin>>n;
										f.open("MENU.dat",ios::in|ios::binary);
										while(f.read((char*)&O,sizeof(O)))
											tcode=O.retcode();
										f.close();
										tcode++;
										z=tcode;
										f.open("MENU.dat",ios::app|ios::binary);
										for(j=1;j<=n;j++)
										{
											O.getdata();
											f.write((char*)&O,sizeof(O));
										}
										f.close();
									}
									else
										cout<<"Please add items in menu first...";
									break;
								case 4: y=1;
									if(O.retrec()>0)
									{
										f.open("MENU.dat",ios::in|ios::binary);
										clrscr();
										O.show();
										while(f.read((char*)&O,sizeof(O)))
										{
											O.showdata();
										}
										f.close();
										x=1;
										y=1;
										cout<<"\nEnter the item code whose rate is to be modified: ";
										cin>>a;
										rec=0;
										f.open("MENU.dat",ios::in|ios::out|ios::binary);
										while(f.read((char*)&O,sizeof(O)))
										{
											if(O.retcode()==a)
											{
												cout<<"Item found...";
												getch();
												clrscr();
												O.show();
												O.showdata();
												f.seekp((rec)*sizeof(O),ios::beg);
												O.getnewprice();
												f.write((char*)&O,sizeof(O));
												cout<<"Rate modified...";
												f.close();
												flag=1;
											}
											else
												rec++;
										}
										if(flag==0)
										{
											cout<<"Item not found...";
											f.close();
										}
										x=1;
										y=1;
									}
									else
										cout<<"Please add items in menu first...";
									break;
								case 5: y=1;
									flag=0;
									if(O.retrec()>0)
									{
										f.open("MENU.dat",ios::in|ios::binary);
										clrscr();
										O.show();
										while(f.read((char*)&O,sizeof(O)))
										{
											O.showdata();
										}
										f.close();
										x=1;
										y=1;
										cout<<"\nEnter the item code which is to be deleted from menu: ";
										cin>>a;
										f.open("MENU.dat",ios::in|ios::binary);
										while(f.read((char*)&O,sizeof(O)))
										{
											if(O.retcode()==a)
											{
												cout<<"Item found...";
												getch();
												flag=1;
												break;
											}
										}
										f.close();
										if(flag==0)
											cout<<"Item not found...";
										else
										{
											f.open("MENU.dat",ios::in|ios::binary);
											fd.open("TEMP.dat",ios::out|ios::binary);
											while(f.read((char*)&O,sizeof(O)))
											{
												if(O.retcode()!=a)
													fd.write((char*)&O,sizeof(O));
												else
												{
													clrscr();
													O.show();
													O.showdata();
													cout<<"\nDo you want to delete this item(Y/N)? ";
													cin>>ans;
													if(toupper(ans)=='N')
													{
														fd.write((char*)&O,sizeof(O));
														cout<<"Item is not deleted...";
														getch();
													}
													if(toupper(ans)=='Y')
														cout<<"Item deleted from menu...";
												}
											}
											fd.close();
											f.close();
											remove("MENU.dat");
											rename("TEMP.dat","MENU.dat");
										}
										x=1;
										y=1;
									}
									else
										cout<<"Please add items in menu first...";
									break;
								case 6:	H.show1();
									x=1;
									y=1;
									break;
								case 7:	break;
								default:cout<<"Invalid choice...";
							}
							getch();
						}while(ch1!=7);
					}
					else
					{
						fd.close();
						k++;
						if(k!=3)
							cout<<"\nIncorrect password,try again...";
						if(k==3)
							cout<<"\nYou've reached maximum limit of attempts, please try again later...";
						getch();
					}
			       }
			       break;
			case 2:do
				{
					clrscr();
					cout<<"\n\t\t\t**********CUSTOMER**********"
					    <<"\n\t\t1.Place your order"
					    <<"\n\t\t2.View your cart"
					    <<"\n\t\t3.Add more items"
					    <<"\n\t\t4.Delete items"
					    <<"\n\t\t5.Modify Quantity of an item"
					    <<"\n\t\t6.Finalise your order"
					    <<"\n\t\t7.Cancel your order"
					    <<"\n\t\t8.Back to main menu"
					    <<"\n\t\tEnter your choice: ";
					cin>>ch2;
					switch(ch2)
					{
						case 1: if(O.retrec()>0)
							{
								y=2;
								pstatus=1;
								cstatus=0;
								fstatus=0;
								ch1=0;
								do
								{
									clrscr();
									cout<<"\n\t\t1.Dine-In"
									    <<"\n\t\t2.Take Away"
									    <<"\n\t\t3.Home Delivery"
									    <<"\n\t\tEnter your Choice: ";
									cin>>ch1;
									switch(ch1)
									{
										case 1:stype=1;
											C.servicetype(stype);
											break;
										case 2:stype=2;
											C.servicetype(stype);
											break;
										case 3:stype=3;
											C.servicetype(stype);
											break;
										default:cout<<"Invalid Choice";
									}
									getch();
								}while(ch1!=1&&ch1!=2&&ch1!=3);
								clrscr();
								f.open("MENU.dat",ios::in|ios::binary);
								cout<<"\t\t\t**********MENU**********";
								O.show();
								while(f.read((char*)&O,sizeof(O)))
								{
									O.showdata();
								}
								f.close();
								x=1;
								y=1;
								remove("CUSTOMER.dat");
								cout<<"\nPlease place your order...";
								C.getdata1();
								cout<<"Do you want to add more items(Y/N)? ";
								cin>>ans;
								while(toupper(ans)=='Y')
								{
									C.getdata1();
									cout<<"Do you want to add more items(Y/N)? ";
									cin>>ans;
								}
								if(toupper(ans)=='N')
								{
									B.calculate();
									cout<<"Your order has been saved in the cart...";
									getch();
								}
							}
							else
								cout<<"Server down, inconvenience regretted...";
							break;
						case 2:if(cstatus==0)
						       {
								if(pstatus==1)
									C.showdata1();
								else
									cout<<"No order placed yet...";
						       }
						       else
								cout<<"Order has been cancelled";
						       x=1;
						       y=1;
						       break;
						case 3:y=2;
						       if(cstatus==0)
						       {
								if(fstatus==0)
								{
									if(pstatus==1)
									{
										clrscr();
										f.open("MENU.dat",ios::in|ios::binary);
										cout<<"\t\t\t**********MENU**********";
										O.show();
										while(f.read((char*)&O,sizeof(O)))
										{
											O.showdata();
										}
										f.close();
										x=1;
										y=1;
										C.getdata1();
										cout<<"Do you want to add more items(Y/N)? ";
										cin>>ans;
										while(toupper(ans)=='Y')
										{
											C.getdata1();
											cout<<"Do you want to add more items(Y/N)? ";
											cin>>ans;
										}
										if(toupper(ans)=='N')
										{
											B.calculate();
											cout<<"Your order has been saved in the cart...";
											getch();
										}
									}
									else
										cout<<"Please place your order first...";
								}
								else
									cout<<"Order has been finalized and cannot be modified now...";
						       }
						       else
								cout<<"Order has been cancelled";
						       break;
						case 4:if(cstatus==0)
						       {
								if(fstatus==0)
								{
									if(pstatus==1)
									{
										if(C.retrec1()!=0)
										{
											flag=0;
											C.showdata1();
											cout<<"Enter the item code which is to be deleted: ";
											cin>>deli;
											f.open("CUSTOMER.dat",ios::in|ios::binary);
											while(f.read((char*)&C,sizeof(C)))
											{
												if(C.retcd()==deli)
												{
													cout<<"Item found...";
													getch();
													flag=1;
													break;
												}
											}
											f.close();
											if(flag==0)
												cout<<"Item code not found...";
											else
											{
												f.open("CUSTOMER.dat",ios::in|ios::binary);
												fd.open("TEMP1.dat",ios::out|ios::binary);
												while(f.read((char*)&C,sizeof(C)))
												{
													if(C.retcd()!=deli)
														fd.write((char*)&C,sizeof(C));
													else
													{
														C.showdata2();
														cout<<"Do you want to delete this item(Y/N)? ";
														cin>>ans;
														if(toupper(ans)=='N')
														{
															fd.write((char*)&C,sizeof(C));
															cout<<"Item is not deleted...";
															getch();
														}
														if(toupper(ans)=='Y')
														{
															disp--;
															cout<<"Item deleted from order...";
														}
													}
												}
												fd.close();
												f.close();
												remove("CUSTOMER.dat");
												rename("TEMP1.dat","CUSTOMER.dat");
												B.calculate();
											}
											x=1;
											y=1;
										}
										else
											cout<<"No items in your cart, Please add items in your cart first...";
									}
									else
										cout<<"Please place your order first...";
								}
								else
									cout<<"Order has been finalized and cannot be modified now...";
						       }
						       else
								cout<<"Order has been cancelled";
						       break;
						case 5:if(cstatus==0)
						       {
								if(fstatus==0)
								{
									if(pstatus==1)
									{
										if(C.retrec1()!=0)
										{
											flag=0;
											rec2=0;
											C.showdata1();
											cout<<"Enter the item code for which quantity needs to be modified: ";
											cin>>deli;
											f.open("CUSTOMER.dat",ios::in|ios::out|ios::binary);
											while(f.read((char*)&C,sizeof(C)))
											{
												if(C.retcd()==deli)
												{
													cout<<"Item found...";
													getch();
													clrscr();
													C.showdata2();
													f.seekp((rec2)*sizeof(C),ios::beg);
													C.modqty();
													f.write((char*)&C,sizeof(C));
													cout<<"Quantity modified...";
													flag=1;
													f.close();
													B.calculate();
												}
												else
													rec2++;
											}
											if(flag==0)
											{
												cout<<"Item code not found...";
												f.close();
											}
											x=1;
											y=1;
										}
										else
											cout<<"No items in your cart, Please add items in your cart first...";
									}
									else
										cout<<"Please place your order first...";
								}
								else
									cout<<"Order has been finalized and cannot be modified now...";
						       }
						       else
								cout<<"Order has been cancelled...";
							break;
						case 6:if(pstatus==1)
							{
								if(fstatus==0)
								{
									if(C.retrec1()!=0)
									{
										C.showdata1();
										cout<<"\nDo you want to finalise your order(Y/N)?: ";
										cin>>ans;
										if(toupper(ans)=='N')
										{
											cout<<"Order is not finalised...";
											break;
										}
										if(toupper(ans)=='Y')
										{
											C.ostat();
											H.hwrite();
											fstatus=1;
											cout<<"Your order has been finalised...";
										}
									}
									else
										cout<<"No items in your cart, Please add items in your cart first...";
								}
								else
									cout<<"Your order has already been finalised...";
							}
							else
								cout<<"Please place your order first...";
							break;
						case 7:if(pstatus==1)
							{
								if(fstatus==1)
								{
									C.showdata1();
									cout<<"\nDo you want to cancel your order(Y/N)?: ";
									cin>>ans;
									if(toupper(ans)=='N')
									{
										cout<<"Order is not cancelled...";
										break;
									}
									if(toupper(ans)=='Y')
									{
										C.ostat();
										H.hwrite();
										pstatus=0;
										fstatus=0;
										cstatus=1;
										remove("CUSTOMER.dat");
										cout<<"Your order has been cancelled...";
									}
								}
								else
									cout<<"Your order is not finalised yet...";
							}

							else
								cout<<"Please place your order first...";
						       break;
						case 8:break;
					}
					getch();
				}while(ch2!=8);
				break;
			case 3:exit(0);
			default:cout<<"Invalid choice...";
		}
		getch();
	}
}







