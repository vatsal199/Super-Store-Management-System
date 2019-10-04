/*

Author: Dhameliya Vatsalkumar
Email: vatsal17137@gmail.com

*/

#include<cstdio>
#include<fstream>
#include<iostream>
#include<string.h>
#include<cstdlib>
#include<iomanip>
#include<vector>
#include "conio.h"
#include<stdlib.h>
using namespace std;
//---------------------------------------product area----------------------------------------------------------------
typedef struct tree{
	long long tp;
	long long int batch_no;
	char product_name[20];
	int QTY;
    char mfg_dt[12];
	char exp_dt[12];
	float price;
	struct tree *lc,*rc;
}node;
ofstream fout;
int total_product=0;
node *search(node *root,char key[])
{
	node *temp;
	temp=root;
		while(temp!=NULL)
		{
			if(strcmp(temp->product_name,key)==0)
				return temp;
			else if(strcmp(temp->product_name,key)==1)
				temp=temp->lc;
			else
				temp=temp->rc;
		}
	return NULL;
}
node *getnode()
{
	node *new1;
	new1=new node[sizeof(node)];
	printf("\nEnter Batch_no:");
	cin>>new1->batch_no;
	printf("\nEnter Product Name:");
	cin>>new1->product_name;
	printf("\nEnter Price:");
	cin>>new1->price;
	printf("\nEnter Quntity:");
	cin>>new1->QTY;
	printf("\nEnter Manufacture Date:");
	cin>>new1->mfg_dt;
	printf("\nEnter Expiry Date:");
	cin>>new1->exp_dt;
    new1->lc=NULL;
	new1->rc=NULL;
	return new1;
}

node *insert(node *root,node *new1)
{
	if(root==NULL)
		root=new1;
	else
	{
		if(strcmp(new1->product_name,root->product_name) == -1)
		{
			if(root->lc==NULL)
				root->lc=new1;
			else
				insert(root->lc,new1);
		}
		else
		{

			if(root->rc==NULL)
				root->rc=new1;
			else
				insert(root->rc,new1);
		}
	}
	return root;
}
void inorder(node *root)
{
	if(root->lc!=NULL)
		inorder(root->lc);
	cout<<setw(10)<<root->batch_no<<" ";
	cout<<setw(14)<<root->product_name<<" ";
	cout<<setw(6)<<root->price<<" ";
	cout<<setw(8)<<root->QTY<<" ";
	cout<<setw(13)<<root->mfg_dt<<" ";
	cout<<setw(13)<<root->exp_dt<<endl;
	if(root->rc!=NULL)
		inorder(root->rc);
	return ;
}

node *proinitialize(node *root)
{
	node *new1;
	ifstream fio("data.txt");
	fio>>total_product;
	int temp=total_product;
	while(temp--)
	{
		new1=new node[sizeof(node)];
		fio>>new1->batch_no;
		fio>>new1->product_name;
		fio>>new1->price;
		fio>>new1->QTY;
		fio>>new1->mfg_dt;
		fio>>new1->exp_dt;
		new1->lc=NULL;
		new1->rc=NULL;
		root=insert(root,new1);
	}
	fio.close();
	return root;
}
node *delete1(node *root,char key[])
{
	node *temp,*parent,*succesor;
	if(root==NULL)
		printf("No product!");
	else
	{
		temp=search(root,key);
		if(temp==NULL)
			printf("Product not found!");
		else
		{
			if(temp->lc!=NULL && temp->rc!=NULL)
			{
				succesor=temp->rc;
				if(succesor->lc==NULL)
				{
					temp->batch_no=succesor->batch_no;
					strcpy(temp->product_name,succesor->product_name);
					temp->price=succesor->price;
					temp->QTY=succesor->QTY;
					strcpy(temp->mfg_dt,succesor->mfg_dt);
					strcpy(temp->exp_dt,succesor->exp_dt);
					temp->rc=NULL;
					return root;
				}
				while(succesor->lc!=NULL)
				{
					parent=succesor;
					succesor=succesor->lc;
				}
				temp->batch_no=succesor->batch_no;
				strcpy(temp->product_name,succesor->product_name);
				temp->price=succesor->price;
				temp->QTY=succesor->QTY;
				strcpy(temp->mfg_dt,succesor->mfg_dt);
                strcpy(temp->exp_dt,succesor->exp_dt);
				parent->lc=succesor->rc;
			}
			else if(temp->lc!=NULL)
			{
				if(temp == root)
					root=root->lc;
				else
				{
					parent=root;
					while(parent->lc!=temp && parent->rc!=temp)
					{
						if(strcmp(key,parent->product_name) == -1)
							parent=parent->lc;
						else
							parent=parent->rc;
					}
					if(parent->lc==temp)
						parent->lc=temp->lc;
					else
						parent->rc=temp->lc;
				}
				free(temp);
			}
			else if(temp->rc!=NULL)
			{
				if(temp == root)
					root=root->rc;
				else
				{
					parent=root;
					while(parent->lc!=temp && parent->rc!=temp)
					{
						if(strcmp(key,parent->product_name) == -1)
						{
							parent=parent->lc;
						}
						else
						{
							parent=parent->rc;
						}
					}

					if(parent->lc==temp)
						parent->lc=temp->rc;
					else
						parent->rc=temp->rc;
				}
				free(temp);
			}
			else
			{
				if(temp == root)
					root=NULL;
				else
				{
					parent=root;
					while(parent->lc!=temp && parent->rc!=temp)
					{
						if(strcmp(key,parent->product_name) == -1)
							parent=parent->lc;
						else
							parent=parent->rc;
					}
					if(parent->lc==temp)
						parent->lc=NULL;
					else
						parent->rc=NULL;
				}
				free(temp);
			}
		}
	}
	return root;
}
void update(node *root,char key[])
{
	if(root==NULL)
		printf("No product!");
	else
	{
	    node *temp;
		temp=search(root,key);
		if(temp==NULL)
			printf("Product not found!");
		else
		{
			printf("\nEnter Batch_No:");
			cin>>temp->batch_no;
			printf("\nEnter Price:");
			cin>>temp->price;
			printf("\nEnter Quntity:");
			cin>>temp->QTY;
			printf("\nEnter Manufacture Date:");
			cin>>temp->mfg_dt;
			printf("\nEnter Expiry Date:");
			cin>>temp->exp_dt;
		}
	}
}
void printline()
{
    printf("\n");
	for(int i=0;i<40;i++)
		printf("-");
	printf("\n");
}
void filepreorder(node *root)
{
	fout<<root->batch_no<<" ";
	fout<<root->product_name<<" ";
	fout<<root->price<<" ";
	fout<<root->QTY<<" ";
	fout<<root->mfg_dt<<" ";
	fout<<root->exp_dt<<" "<<endl;
	if(root->lc!=NULL)
		filepreorder(root->lc);
	if(root->rc!=NULL)
		filepreorder(root->rc);
	return ;
}
void writedata(node *root)
{
	fout.open("data.txt",ios::out|ios::trunc);
	fout<<total_product<<endl;
    filepreorder(root);
	fout.close();
}
//----------------------------------------customer area-------------------------------------------------------------------
typedef struct tree1{
	char cust_id[8];
	char cust_name[20];
	long long int Mo_no;
	char address[20];
	char city[10];
	char state[10];
	long long int pincode;
	int card_point;
	struct tree1 *lc,*rc;
}custnode;
int total_customer=0;
custnode *search_c(custnode *root,char key[])
{
	custnode *temp;
	temp=root;
		while(temp!=NULL)
		{
			if(strcmp(temp->cust_id,key)==0)
				return temp;
			else if(strcmp(temp->cust_id,key)==1)
				temp=temp->lc;
			else
				temp=temp->rc;
		}
	return NULL;
}
void show_cust(custnode *root)
{
	if(root->lc!=NULL)
		show_cust(root->lc);
	cout<<setw(9)<<root->cust_id<<" ";
	cout<<setw(19)<<root->cust_name<<" ";
	cout<<setw(11)<<root->Mo_no<<" ";
	cout<<setw(19)<<root->address<<" ";
	cout<<setw(9)<<root->city<<" ";
	cout<<setw(9)<<root->state<<" ";
	cout<<setw(7)<<root->pincode<<" ";
	cout<<setw(12)<<root->card_point<<endl;
	if(root->rc!=NULL)
		show_cust(root->rc);
	return ;
}
custnode *getcustnode(custnode *root)
{
	custnode *new1;
	new1=new custnode[sizeof(custnode)];
	rt:
	printf("\nEnter Customer_ID(5-digit):");
	cin>>new1->cust_id;
	if(root != NULL)
	{
		custnode *xtemp;
		xtemp=search_c(root,new1->cust_id);
		if(xtemp != NULL)
		{
			cout<<"\nID already taken by "<<xtemp->cust_name;
			cout<<"Choose another ID...";
			goto rt;
		}
	}
	printf("\nEnter Customer Name:");
	cin>>new1->cust_name;
	printf("\nEnter Mobile No.:");
	cin>>new1->Mo_no;
	printf("\nEnter Address:");
	cin>>new1->address;
	printf("\nEnter City:");
	cin>>new1->city;
	printf("\nEnter State:");
	cin>>new1->state;
	printf("\nEnter Pincode:");
	cin>>new1->pincode;
	new1->card_point=0;
    new1->lc=NULL;
	new1->rc=NULL;
	return new1;
}
custnode *insert_c(custnode *root,custnode *new1)
{
	if(root==NULL)
		root=new1;
	else
	{
		if(strcmp(new1->cust_id,root->cust_id) == -1)
		{
			if(root->lc==NULL)
				root->lc=new1;
			else
				insert_c(root->lc,new1);
		}
		else
		{

			if(root->rc==NULL)
				root->rc=new1;
			else
				insert_c(root->rc,new1);
		}
	}
	return root;
}
custnode *custinitialize(custnode *cust_root)
{
	custnode *new1;
	ifstream fio("cust.txt");
	fio>>total_customer;
	int temp=total_customer;
	while(temp--)
	{
	new1=new custnode[sizeof(custnode)];
	fio>>new1->cust_id;
	fio>>new1->cust_name;
	fio>>new1->Mo_no;
	fio>>new1->address;
	fio>>new1->city;
	fio>>new1->state;
	fio>>new1->pincode;
	fio>>new1->card_point;
	new1->lc=NULL;
	new1->rc=NULL;
	cust_root=insert_c(cust_root,new1);
	}
	fio.close();
	return cust_root;
}

void custpreorder(custnode *root)
{
	fout<<root->cust_id<<" ";
	fout<<root->cust_name<<" ";
	fout<<root->Mo_no<<" ";
	fout<<root->address<<" ";
	fout<<root->city<<" ";
	fout<<root->state<<" ";
	fout<<root->pincode<<" ";
	fout<<root->card_point<<endl;
	if(root->lc!=NULL)
		custpreorder(root->lc);
	if(root->rc!=NULL)
		custpreorder(root->rc);
	return ;
}
void write(custnode *cust_root)
	{
		fout.open("cust.txt",ios::out|ios::trunc);
		fout<<total_customer<<endl;
		custpreorder(cust_root);
		fout.close();
	}
custnode* delete_c(custnode *root,char key[])
{
	custnode *temp,*parent,*succesor;
	if(root==NULL)
		printf("No Customer!");
	else
	{
		temp=search_c(root,key);
		if(temp==NULL)
			printf("Customer not found!");
		else
		{
			if(temp->lc!=NULL && temp->rc!=NULL)
			{
				succesor=temp->rc;
				if(succesor->lc==NULL)
				{
					strcpy(temp->cust_id,succesor->cust_id);
					strcpy(temp->cust_name,succesor->cust_name);
					temp->Mo_no=succesor->Mo_no;
					temp->pincode=succesor->pincode;
					strcpy(temp->address,succesor->address);
					strcpy(temp->city,succesor->city);
					strcpy(temp->state,succesor->state);
					temp->card_point=succesor->card_point;
					temp->rc=NULL;
					return root;
				}
				while(succesor->lc!=NULL)
				{
					parent=succesor;
					succesor=succesor->lc;
				}
				strcpy(temp->cust_id,succesor->cust_id);
				strcpy(temp->cust_name,succesor->cust_name);
				temp->Mo_no=succesor->Mo_no;
				temp->pincode=succesor->pincode;
				strcpy(temp->address,succesor->address);
				strcpy(temp->city,succesor->city);
				strcpy(temp->state,succesor->state);
				temp->card_point=succesor->card_point;
				parent->lc=succesor->rc;
			}
			else if(temp->lc!=NULL)
			{
				if(temp == root)
				{
					root=root->lc;
				}
				else
				{
					parent=root;
					while(parent->lc!=temp && parent->rc!=temp)
					{
						if(strcmp(key,parent->cust_id) == -1)
							parent=parent->lc;
						else
							parent=parent->rc;
					}
					if(parent->lc==temp)
						parent->lc=temp->lc;
					else
						parent->rc=temp->lc;
				}
				free(temp);
			}
			else if(temp->rc!=NULL)
			{
				if(temp==root)
				{
					root=root->rc;
				}
				else
				{
					parent=root;
					while(parent->lc!=temp && parent->rc!=temp)
					{
						if(strcmp(key,parent->cust_id) == -1)
						{
							parent=parent->lc;
						}
						else
						{
							parent=parent->rc;
						}
					}
					if(parent->lc==temp)
						parent->lc=temp->rc;
					else
						parent->rc=temp->rc;
				}
				free(temp);
			}
			else
			{
				if(temp == root)
				{
					root=NULL;
				}
				else
				{
					parent=root;
					while(parent->lc!=temp && parent->rc!=temp)
					{
						if(strcmp(key,parent->cust_id) == -1)
							parent=parent->lc;
						else
							parent=parent->rc;
					}
					if(parent->lc==temp)
						parent->lc=NULL;
					else
						parent->rc=NULL;
				}
				free(temp);
			}
		}
	}
	return root;
}

void update_c(custnode *root,char key[])
{
	if(root==NULL)
		printf("No Customer!");
	else
	{
	    custnode *temp;
		temp=search_c(root,key);
		if(temp==NULL)
			printf("Customer not found!");
		else
		{
			printf("\nEnter Customer Name:");
			cin>>temp->cust_name;
			printf("\nEnter Mobile No.:");
			cin>>temp->Mo_no;
			printf("\nEnter Address:");
			cin>>temp->address;
			printf("\nEnter City:");
			cin>>temp->city;
			printf("\nEnter State:");
			cin>>temp->state;
			printf("\nEnter Pincode:");
			cin>>temp->pincode;
		}
	}
}
void preline(int n)
{
	for(int i=0;i<n;i++)
		cout<<"-";
	cout<<endl;
}
//---------------------------------------shopping area---------------------------------------------------------------
typedef struct bill1{
	char product_name[20];
	float price;
	int QTY;
	float total;
	struct bill1 *next;
}bill;
class shopping{

	int total_bill;
	float total_bill_amount;
	float pay_amount[2];
	int total_item[2];
	bill *new1;
	bill *start[2],*trv,*temp;
	bill *getbillnode();
	bill *insertbillnode(bill *start,bill *node);
	public:
	shopping()
	{
		total_bill=0;
		total_bill_amount=0.0;
		start[0]=NULL;
		start[1]=NULL;
		total_item[0]=0;
		total_item[1]=0;
	}
	void shop(char SID[],char Sname[],node *root,custnode *cust_root);
	void prebill(char SID[],char Sname[],custnode *cust_root);
};
void shopping::prebill(char SID[],char Sname[],custnode *cust_root)
{
		custnode *temp1;
		temp1=search_c(cust_root,SID);
		if(temp1 == NULL)
		{
			printf("\nYou need to first register your name and ID!!");
			cout<<"\nGo to  Customer_info-->Register";
			return;
		}
		if(strcmp(temp1->cust_name,Sname)!=0)
		{
			printf("\nYou need to first register your name and ID!!");
			cout<<"\nGo to  Customer_info-->Register";
			return;
		}
	char filename[10];
	strcpy(filename,SID);
	strcat(filename,".txt");
	ifstream sfin(filename);
	if(sfin)
	{
		sfin>>total_bill;
		sfin>>total_item[0];
		sfin>>total_item[1];
		printf("\n");
		for(int j=0;j<total_bill;j++)
		{
			total_bill_amount = 0;
			printf("\n\n");
			cout<<setw(15)<<"Product Name"<<setw(7)<<"Price"<<setw(10)<<"Quantity"<<setw(7)<<"Total"<<endl;
			preline(40);
			for(int i=0;i<total_item[j];i++)
			{
				new1=getbillnode();
				sfin>>new1->product_name;
				cout<<setw(15)<<new1->product_name<<" ";
				sfin>>new1->price;
				cout<<setw(6)<<new1->price<<" ";
				sfin>>new1->QTY;
				cout<<setw(9)<<new1->QTY<<" ";
				cout<<setw(6)<<new1->price*new1->QTY<<endl;
				total_bill_amount += new1->price*new1->QTY;
				free(new1);
			}
			sfin>>pay_amount[j];
			cout<<"Total bill amount is:"<<total_bill_amount;
			cout<<"  Amount which customer pay is:"<<pay_amount[j]<<endl;
		}
	}
	else
	{
		cout<<"\nYou need to buy something!!"<<endl;
	}
}
void shopping::shop(char SID[],char Sname[],node *root,custnode *cust_root)
	{
		custnode *temp1;
		temp1=search_c(cust_root,SID);
		if(temp1 == NULL)
		{
			printf("\nYou need to first register your name and ID!!");
			cout<<"\nGo to  Customer_info-->Register";
			return;
		}
		if(strcmp(temp1->cust_name,Sname)!=0)
		{
			printf("\nYou need to first register your name and ID!!");
			cout<<"\nGo to  Customer_info-->Register";
			return;
		}
		char filename[10];
		strcpy(filename,SID);
		strcat(filename,".txt");
		ifstream sfin(filename);
		if(sfin)
		{
			sfin>>total_bill;
			sfin>>total_item[0];
			sfin>>total_item[1];
				free(start[1]);
				start[1]=NULL;
				for(int i=0;i<total_item[0];i++)
				{
					new1=getbillnode();
					sfin>>new1->product_name;
					sfin>>new1->price;
					sfin>>new1->QTY;
					new1->total=new1->price*new1->QTY;
					start[1]=insertbillnode(start[1],new1);
				}
				sfin>>pay_amount[1];
				total_item[1]=total_item[0];
			sfin.close();
		}
		else
		{
			sfin.close();
		}
		printf("\nEnter how many item you buy?");
		cin>>total_item[0];
		node *temp;
		total_bill_amount=0;
		if(total_bill<2)
			total_bill++;
		free(start[0]);
		start[0]=NULL;
		for(int i=0;i<total_item[0];i++)
		{
			rlist:
			new1=getbillnode();
			cout<<"\nEnter Product Name:";
			cin>>new1->product_name;
			temp=search(root,new1->product_name);
			if(temp==NULL)
			{
				cout<<"\nItem record does not exist";
				cout<<"\nPlease...Re-enter last item details!!";
				free(new1);
				goto rlist;
			}
			new1->price=temp->price;
			cout<<"\nEnter Quantities:";
			cin>>new1->QTY;
			if(new1->QTY>temp->QTY)
			{
				cout<<"\nWe not have "<<new1->QTY<<" quantities of "<<new1->product_name;
				cout<<"\nPlease...Re-enter details!!";
				free(new1);
				goto rlist;
			}
			temp->QTY-=new1->QTY;
			if(temp->QTY == 0)
			{
				printline();
				cout<<"Warning: "<<temp->product_name<<" stock = "<<temp->QTY;
				printline();
			}
			new1->total=new1->price*new1->QTY;
			total_bill_amount += new1->total;
			start[0]=insertbillnode(start[0],new1);
		}
		cout<<"\nTotal Bill Amount is: "<<total_bill_amount<<endl;
		pay_amount[0]=total_bill_amount;
		int getpoint=total_bill_amount * 0.01;
		temp1->card_point += getpoint;
		if(temp1->card_point == 100)
		{
			cout<<"\nYour card points is 100 ,so you get 20% discount on your bill amount";
			pay_amount[0]=total_bill_amount*0.8;
			cout<<"\nTotal Bill Amount is:"<<pay_amount[0];
			temp1->card_point = 0;
		}
		fstream sfo;
		sfo.open(filename,ios::out | ios::trunc);
		sfo<<total_bill<<endl;
		sfo<<total_item[0]<<" "<<total_item[1]<<endl;
		for(int i=0;i<total_bill;i++)
		{
			bill *trv=start[i];
			for(int j=0;j<total_item[i];j++)
			{
				sfo<<trv->product_name<<" ";
				sfo<<trv->price<<" ";
				sfo<<trv->QTY<<" ";
				trv=trv->next;
			}
			sfo<<pay_amount[i]<<endl;
		}
	}
bill *shopping::insertbillnode(bill *start,bill *node)
{
	bill *trv;
	if(start==NULL)
		start=node;
	else
	{
		trv=start;
		while(trv->next != NULL)
			trv=trv->next;
		trv->next=node;
	}
	return start;
}
bill *shopping::getbillnode()
{
	bill *new1;
	new1=new bill[sizeof(bill)];
	new1->next=NULL;
	return new1;
}
//---------------------------------------------------Staff_Entry-----------------------------------------------------------
typedef struct staf_entry1{
	char name[20];
	char username[20];
	char password[20];
}SFE;
class staf_entry{
		vector<SFE> emp;
		SFE temp;
		int total_staf;
	public:
		staf_entry()
		{
			ifstream fin("staf.txt");
			fin>>total_staf;
			int tp;
			tp=total_staf;
			while(tp--)
			{
				fin>>temp.name;
				fin>>temp.username;
				fin>>temp.password;
				emp.push_back(temp);
			}
			fin.close();
		}
		bool check();
		bool admin();
		bool delete1(char []);
		void Register();
		void show();
		void writestaf();
};
bool staf_entry::admin()
{
    bool flag=false;
    char username[20],password[20];
    char au[20]="vatsal";
    char pass[20]="17137";
    cout<<"\nEnter Admin Username:";
    cin>>username;
    cout<<"\nEnter Admin Password:";
	char ch;
	int j=0;
	ch=getch();
	ch=getch();
	do{
		password[j++]=ch;
		cout<<"*";
		ch=getch();
		if(ch == 127)
		{
			cout<<"\nRe-enter Admin Password:";
			j=0;
			ch=getch();
		}
	}while(ch != 10);
	password[j]='\0';	
    if(strcmp(au,username)==0)
    {
        if(strcmp(pass,password)==0)
        {
            flag=true;
        }
    }
    return flag;
}
bool staf_entry::check()
{
	bool flag = false;
	char username[20],password[20];
	cout<<"\nEnter Username:";
	cin>>username;
	cout<<"\nEnter Password:";
	char ch;
	int j=0;
	ch=getch();
	ch=getch();
	do{
		password[j++]=ch;
		cout<<"*";
		ch=getch();
		if(ch == 127)
		{
			cout<<"\nRe-enter Password:";
			j=0;
			ch=getch();
		}
	}while(ch != 10);
	password[j]='\0';
	for(int i=0;i<total_staf;i++)
	{
		if(strcmp(emp[i].username,username) == 0)
		{
			if(strcmp(emp[i].password,password)==0)
			{
				flag=true;
				break;
			}
		}
	}
	return flag;
}
bool staf_entry::delete1(char username[])
{
    bool flag = false;
	if(total_staf == 0)
	{
		cout<<"\nNo staff!";
		return flag;
	}
	for(int i=0;i<total_staf;i++)
	{
		if(strcmp(emp[i].username,username) == 0)
		{
			for(int j=i+1;j<total_staf;j++)
			{
				strcpy(emp[j-1].name,emp[j].name);
				strcpy(emp[j-1].username,emp[j].username);
				strcpy(emp[j-1].password,emp[j].password);
			}
			total_staf--;
			flag=true;
			break;
		}
	}
	return flag;
}
void staf_entry::Register()
{
	char ch;
	int i=0;
	cout<<"\n\n\nEnter New Member Details";
	cout<<"\nEnter Name:";
	cin>>temp.name;
	cout<<"\nEnter Username:";
	cin>>temp.username;
	for(int i=0;i<total_staf;i++)
	{
		if(strcmp(emp[i].username,temp.username) == 0)
		{
			printline();
			cout<<"\nUsername already exist!";
			cout<<"\nPlease... Register with different username!";
			printline();
			return;
		}
	}
	cout<<"\nEnter Password:";
	ch=getch();
	ch=getch();
	do{
		temp.password[i++]=ch;
		cout<<"*";
		ch=getch();
		if(ch == 127)
		{
			cout<<"\nRe-enter Password:";
			i=0;
			ch=getch();
		}
	}while(ch != 10);
	temp.password[i]='\0';
	emp.push_back(temp);
	total_staf++;
}
void staf_entry::show()
{
	printf("\n\n");
	if(total_staf == 0)
	{
		cout<<"No staff!";
		return;
	}
	cout<<setw(15)<<"Name"<<setw(15)<<"UserName"<<endl;
	preline(32);
	for(int i=0;i<total_staf;i++)
	{
		cout<<setw(15)<<emp[i].name<<" ";
		cout<<setw(14)<<emp[i].username<<endl;
	}
}
void staf_entry::writestaf()
{
	fout.open("staf.txt",ios::out | ios::trunc);
	fout<<total_staf<<endl;
	for(int i=0;i<total_staf;i++)
	{
		fout<<emp[i].name<<" ";
		fout<<emp[i].username<<" ";
		fout<<emp[i].password<<endl;
	}
	fout.close();
}
//------------------------------------------------------main---------------------------------------------------------------
int main()
{

	node *root;
	root=NULL;
	custnode *cust_root;
	cust_root=NULL;
	shopping s1;
	root=proinitialize(root);
	printf("WEL COME");
	cust_root=custinitialize(cust_root);
	int ch,ch1,ch2;
	staf_entry st1;
	char username[20];
	bool flag;
	while(1)
	{
		logout:
		printline();
		printf("\n1.Login \n2.Register \n3.Delete \n4.Show\n5.Exit\n");
		cout<<"\nEnter your choice:";
		cin>>ch2;
		switch(ch2)
		{
			case 1:
				flag=st1.check();
				if(flag == false)
				{
					printline();
					printf("\nIncorrect Username or Password");
				}
				else
				{
					system("clear");
					back:
						while(1)
						{
							printf("\n");
						printline();
						char SID[8],Sname[20];
						printf("1.Product Info\n2.Customer Info \n3.Shopping \n4.Previous Bill\n5.LogOut \n6.Exit\n");
						cout<<"Enter your choice:";
						cin>>ch;
						switch(ch)
						{
							case 1:
								while(1)
								{
								printline();
								printf("\n1.insert \n2.delete \n3.update \n4.show \n5.Search_By_Name\n6.back \n7.Exit");
								cout<<"\nEnter your choice:";
								cin>>ch1;
								switch(ch1)
								{
									case 1:
										node *new1;
										new1=getnode();
										node *xtemp;
										xtemp=search(root,new1->product_name);
										if(xtemp==NULL)
										{
											total_product++;
											root=insert(root,new1);
										}
										else
										{
											cout<<"\nItem already exist";
										}
										writedata(root);
										break;
									case 2:
									if(root==NULL)
										cout<<"Product data not found!";
									else
									{
										cout<<"Enter product_name:";
										char PN[20];
										cin>>PN;
										total_product--;
										root=delete1(root,PN);
										writedata(root);
									}
										break;
									case 3:
										if(root==NULL)
											cout<<"No product!";
										else
										{
										cout<<"Enter product_name:";
										char pronm[20];
										cin>>pronm;
										update(root,pronm);
										writedata(root);
										}
										break;
									case 4:
										printf("\n");
										if(root==NULL)
											printf("\nNo Product Found!");
										else
											{
											cout<<setw(10)<<"Betch_No"<<setw(15)<<"Product Name"<<setw(7)<<"Price"<<setw(9)<<"Quantity";
											cout<<setw(14)<<"MFG_Date"<<setw(14)<<"EXP_Date"<<endl;
											preline(70);
											inorder(root);
										}											
										break;
									case 5:
										cout<<"Enter Product Name:";
										char pn[20];
										cin>>pn;
										node *temp;
										temp=search(root,pn);
										if(temp==NULL)
											cout<<"Product Not Found!";
										else
										{
											cout<<setw(10)<<"Betch_No"<<setw(15)<<"Product Name"<<setw(7)<<"Price"<<setw(9)<<"Quantity";
											cout<<setw(14)<<"MFG_Date"<<setw(14)<<"EXP_Date"<<endl;
											cout<<setw(10)<<temp->batch_no<<" ";
											cout<<setw(14)<<temp->product_name<<" ";
											cout<<setw(6)<<temp->price<<" ";
											cout<<setw(8)<<temp->QTY<<" ";
											cout<<setw(13)<<temp->mfg_dt<<" ";
											cout<<setw(13)<<temp->exp_dt<<endl;
										}
										break;
									case 6:

										goto back;
										break;
									case 7:
										exit(0);
										break;
									default:
										cout<<"Enter proper choice!";
										break;
								}
								}
								break;
							case 2:
								while(1)
								{
									printline();
									printf("\n1.Register \n2.Delete \n3.Update \n4.show\n5.Search_By_ID \n6.back \n7.Exit");
									cout<<"\nEnter your choice:";
									cin>>ch1;
									switch(ch1)
									{
										case 1:
											custnode *custnew;
											custnew=getcustnode(cust_root);
											total_customer++;
											cust_root=insert_c(cust_root,custnew);
											write(cust_root);
											break;
										case 2:
											if(cust_root==NULL)
												cout<<"Customer data not found!";
											else
											{
											cout<<"Enter Customer_ID:";
											char CI[20];
											cin>>CI;
											total_customer--;
											cust_root=delete_c(cust_root,CI);
											write(cust_root);
											}
											break;
										case 3:
											if(cust_root == NULL)
												cout<<"Customer data not found!";
											else
											{
												cout<<"Enter Customer_ID:";
												char CID[8];
												cin>>CID;
												update_c(cust_root,CID);
												write(cust_root);
											}
											break;
										case 4:
											printf("\n");
											if(cust_root==NULL)
												printf("There are no customer");
											else
											{
												cout<<setw(9)<<"ID"<<setw(20)<<"Customer Name"<<setw(12)<<"Mo_no"<<setw(20)<<"Address"<<setw(10)<<"City";
												cout<<setw(10)<<"State"<<setw(8)<<"Pincod"<<setw(13)<<"Card_points"<<endl;
												preline(104);
												show_cust(cust_root);
											}
											break;
										case 5:
											char I[8];
											cout<<"Enter Customer ID:";
											cin>>I;
											custnode *ctp;
											ctp=search_c(cust_root,I);
											if(ctp==NULL)
												cout<<"Customer Not Found!";
											else
											{
												cout<<setw(9)<<"ID"<<setw(20)<<"Customer Name"<<setw(12)<<"Mo_no"<<setw(20)<<"Address"<<setw(10)<<"City";
												cout<<setw(10)<<"State"<<setw(8)<<"Pincod"<<setw(13)<<"Card_points"<<endl;
												cout<<setw(9)<<ctp->cust_id<<" ";
												cout<<setw(19)<<ctp->cust_name<<" ";
												cout<<setw(11)<<ctp->Mo_no<<" ";
												cout<<setw(19)<<ctp->address<<" ";
												cout<<setw(9)<<ctp->city<<" ";
												cout<<setw(9)<<ctp->state<<" ";
												cout<<setw(7)<<ctp->pincode<<" ";
												cout<<setw(12)<<ctp->card_point<<endl;
											}
											break;
										case 6:
											goto back;
											break;
										case 7:
											exit(0);
											break;
										default:
											cout<<"Enter proper choice!";
											break;
									}
								}
							case 3:
								printf("\nEnter Customer_ID:");
								cin>>SID;
								printf("\nEnter Customer Name:");
								cin>>Sname;
								s1.shop(SID,Sname,root,cust_root);
								writedata(root);
								write(cust_root);
								break;
							case 4:
								printf("\nEnter Customer_ID:");
								cin>>SID;
								printf("\nEnter Customer Name:");
								cin>>Sname;
								s1.prebill(SID,Sname,cust_root);
								break;
							case 5:
								goto logout;
								break;
							case 6:
								exit(0);
								break;
							default:
								cout<<"Enter proper choice!";
								break;
						}
						}
				}
				break;
			case 2:
				flag=st1.admin();
				if(flag == false)
				{
					printline();
					cout<<"\nIncorrect Username or Password!";
					printline();
				}
				else{
					st1.Register();
					st1.writestaf();
				}
				break;
			case 3:
				flag=st1.admin();
				if(flag == false)
				{
					printline();
					cout<<"\nIncorrect Username or Password!";
				}
				else{
					cout<<"\nEnter Username:";
					cin>>username;
					flag=st1.delete1(username);
					if(flag == false)
					{
						printline();
						cout<<"\nUsername not found!";
					}
					else
					{
						st1.writestaf();
					}
				}
				break;
			case 4:
				st1.show();
				break;
			case 5:
				exit(0);
				break;
			default:
				cout<<"\nEnter Proper choice!\n";
				break;
		}

	}
	return 0;
}
