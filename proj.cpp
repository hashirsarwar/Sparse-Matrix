#include<iostream>
#include<fstream>
#include<string>
using namespace std;
const int maxrow=250,maxcol=26; //for multiplication, listToMatrix and addition function
struct node
{
    int value;
    int row;
    int col;
    node* next;
};
node* readFile();
bool insert(node *& head, node *& tail);
void displayMatrix(const node* head);
bool listToMatrix (node * head);
node * addTwoMatrix(const node * node1, const node * node2);
node * getAllValues(const node * head, int value);
bool Delete (node *& head);
int main()
{
    node* head=readFile();
    node* tail=head;
    displayMatrix(head);
    insert(head,tail);
    //displayMatrix(head);
    listToMatrix(head);
    //initializing 2nd matrix for addition
    node* head2=new node;
    node* tail2=head2;
    tail2->col=6;
    tail2->row=1;
    tail2->value=15;
    tail2->next=new node;
    tail2=tail2->next;
    tail2->col=13;
    tail2->row=2;
    tail2->value=10;
    tail2->next=new node;
    tail2=tail2->next;
    tail2->col=1;
    tail2->row=4;
    tail2->value=13;
    tail2->next=new node;
    tail2=tail2->next;
    tail2->col=14;
    tail2->row=12;
    tail2->value=17;
    tail2->next=NULL;
    node* sum=addTwoMatrix(head,head2);
    cout<<"after sum of two matrices\n";
    displayMatrix(sum);
    node* values=getAllValues(head,1);
    cout<<"list with value 1 is \n";
    displayMatrix(values);
    Delete(head);
    Delete(head2);
    //system("pause");
}
node* readFile()
{
    node* head=new node;
    node* tail=head;
    int x,c=0,r=0,count=0;
    string line,num;
    ifstream fin,fin1,fin2;
    ofstream fout,fout1;
    fin.open("input.txt",ios::app);
    if(fin.is_open())
    {
        while(!fin.eof())
        {
            fin1.close();
            getline(fin,line);
            r++;
            c=0;
            fout.open("tmp.txt");
            fout<<line;
            fout.close();
            fin1.open("tmp.txt");
            while(!fin1.eof())
            {
                getline(fin1,num,',');
                fout1.open("tmp1.txt");
                fout1<<num;
                fout1.close();
                fin2.open("tmp1.txt");
                fin2>>x;
                fin2.close();
                c++;
                if(x!=0)
                {
                    if (count!=0)
                    {
                        tail->next=new node;
                        tail=tail->next;
                    }
                    tail->col=c;
                    tail->row=r;
                    tail->value=x;
                    count++;
                }
            }
        }
        tail->next=NULL;
        fin1.close();
        remove("tmp.txt");
        remove("tmp1.txt");
        return head;
    }
    else
        cout<<"unable to open file\n";
}
void displayMatrix(const node* head)
{
    const node* tmp=head;
    cout<<"value\trow\tcolumn\n";
    while(tmp!=NULL)
    {
        cout<<tmp->value<<"\t"<<tmp->row<<"\t"<<tmp->col<<endl;
        tmp=tmp->next;
    }
}
bool insert(node *& head, node *& tail)
{
    if(tail!=NULL)
    {
        if(tail->next==NULL)
        {
            tail->next=new node;
            tail->value=0;
            tail->row=0;
            tail->col=0;
            tail->next=NULL;
        }
        else
        {
            while(tail->next!=NULL)
                tail=tail->next;
            tail->next=new node;
            tail=tail->next;
            tail->value=0;
            tail->row=0;
            tail->col=0;
            tail->next=NULL;
            return true;
        }
    }
    else
        return false;
}
bool listToMatrix (node * head)
{
    ofstream fout;
    fout.open("output.txt");
    if(fout.is_open())
    {
        node* tmp=head;
        int row=tmp->row,col=tmp->col;
        for(int a=1; a<=maxrow; a++)
        {
            for(int b=1; b<=maxcol; b++)
            {
                if(a==row && b==col)
                {
                    fout<<tmp->value;
                    if(b!=maxcol)
                        fout<<", ";
                    tmp=tmp->next;
                    row=tmp->row;
                    col=tmp->col;
                }
                else
                {
                    fout<<0;
                    if(b!=maxcol)
                        fout<<", ";
                }
            }
            fout<<endl;
        }
        return true;
    }
    else
        return false;
}
node * addTwoMatrix(const node * node1, const node * node2)
{
    const node* tmp1=node1;
    const node* tmp2=node2;
    node* sum=new node;
    node* tmps=sum;
    int a=0,b=0,row,col,value,count=0;
    while(tmp2!=NULL)
    {
        if(tmp2->row>maxrow || tmp2->col>maxcol)
        {
            cout<<"sum is not possible\n";
            return NULL;
        }
        tmp2=tmp2->next;
    }
    while(a<maxrow)
    {
        b=0;
        a++;
        while(tmp1!=NULL)
        {
            if(tmp1->row==a)
            {
                row=tmp1->row;
                break;
            }
            tmp1=tmp1->next;
        }
        while(tmp2!=NULL)
        {
            if(tmp2->row==a)
            {
                row=tmp2->row;
                break;
            }
            tmp2=tmp2->next;
        }
        while(b<maxcol)
        {
            col=0;
            tmp1=node1;
            tmp2=node2;
            b++;
            while(tmp1!=NULL)
            {
                if(tmp1->col==b && tmp1->row==a)
                {
                    col=tmp1->col;
                    value=tmp1->value;
                    break;
                }
                tmp1=tmp1->next;
            }
            while(tmp2!=NULL)
            {
                if(tmp2->col==b && tmp2->row==a && col!=b)
                {
                    col=tmp2->col;
                    value=tmp2->value;
                    break;
                }
                else if(tmp2->col==b && tmp2->row==a && col==b)
                {
                    col=tmp2->col;
                    value=tmp2->value+tmp1->value;
                    break;
                }
                tmp2=tmp2->next;
            }
            if(row!=0 && col!=0)
            {
                if(count==0)
                {
                    tmps->row=row;
                    tmps->col=col;
                    tmps->value=value;
                    count=1;
                }
                else
                {
                    tmps->next=new node;
                    tmps=tmps->next;
                    tmps->row=row;
                    tmps->col=col;
                    tmps->value=value;
                }
            }
        }
        tmp1=node1;
        tmp2=node2;
    }
    tmps->next=NULL;
    return sum;
}
node * getAllValues(const node * head, int value)
{
    const node* tmp=head;
    node* values=new node;
    node* tmpv=values;
    int c=0;
    while(tmp!=NULL)
    {
        if(tmp->value==value)
        {
            if(c==0)
            {
                tmpv->row=tmp->row;
                tmpv->col=tmp->col;
                tmpv->value=tmp->value;
                c=1;
            }
            else
            {
                tmpv->next=new node;
                tmpv=tmpv->next;
                tmpv->row=tmp->row;
                tmpv->col=tmp->col;
                tmpv->value=tmp->value;
            }
        }
        tmp=tmp->next;
    }
    tmpv->next=NULL;
    return values;
}
bool Delete (node *& head)
{
    if(head==NULL)
        return false;
    node* tmp=head;
    node* tmp1=head->next;
    while(head!=NULL)
    {
        delete tmp;
        head=tmp1;
        if (head!=NULL)
            tmp1=tmp1->next;
        tmp=head;
    }
    return true;
}
