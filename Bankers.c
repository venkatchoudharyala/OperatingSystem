#include<stdio.h>
int mon;
struct process
{
        char name[37];
        int res_count[35];
        int max_res_count[35];
        int req_res[35];
        int call_id;
};
void alloc();
void alloc2();
void next();
void cover();
int main()
{
        struct process Arr[35];
        int n,r,i,j;
        int tot_res[35];
        int ps_res[35];
        printf("ENTER TOTAL NO OF PROCESS :");
        scanf("%d",&n);
        printf("ENTER NO OF RESOURCES :");
        scanf("%d",&r);
        for(i=0;i<r;i++)
        {
                printf("ENTER %d TH RESOURCE AVAILABLE :",i+1);
                scanf("%d",&tot_res[i]);
                ps_res[i]=tot_res[i];
        }
        for(i=0;i<n;i++)
        {
                printf("FOR THE %dTH PROCESS :",i+1);
                printf("ENTER NAME :");
                scanf("%s",Arr[i].name);
                for(j=0;j<r;j++)
                {
                        printf("ENTER %dTH RESOURCE COUNT :",j+1);
                        scanf("%d",&Arr[i].res_count[j]);
                        printf("MAX %dTH RESOURCE REQUIRED :",j+1);
                        scanf("%d",&Arr[i].max_res_count[j]);
                        Arr[i].req_res[j]=Arr[i].max_res_count[j]-Arr[i].res_count[j];
                }
        }
        printf("THE PROCESS SEQUENCE :");
        alloc(Arr,n,r,tot_res);
        cover(n,mon);
        mon=0;
        next(Arr,n,r,ps_res);
        return 0;
}
void alloc(struct process Arr[],int n,int r,int tot_res[])
{
        int i,j;
        int flag=0;
        int final[35];
        for(i=0;i<n;i++)
        {
                for(j=0;j<r;j++)
                {
                        if(tot_res[j]>=Arr[i].req_res[j] && Arr[i].call_id!=1)
                        {
                                flag=flag+1;
                        }
                        else
                        {
                                break;
                        }
                }
                if(flag==r)
                {
                        printf("\n%s\n",Arr[i].name);
                        mon=mon+1;
                        alloc2(Arr,i,n,r,tot_res);
                        break;
                }
                if(i==n-1)
                {
                        return;
                }
        }
}
void alloc2(struct process Arr[],int v,int n,int r,int tot_res[])
{
        int k;
        for(k=0;k<r;k++)
        {
                tot_res[k]=Arr[v].res_count[k]+tot_res[k];
                Arr[v].call_id=1;
        }
        alloc(Arr,n,r,tot_res);
}
void next(struct process Arr[],int n,int r,int ps_res[])
{
        int z,i,x,init[35],init2[35];
        printf("ENTER 1 TO CHOOSE");
        printf("\nENTER 0 TO EXIT");
        scanf("%d",&x);
        for(i=0;i<n;i++)
        {
                Arr[i].call_id=0;
        }
        switch(x)
        {
                case 1:
                        printf("ENTER WHICH PROCESS TO CHANGE :");
                        scanf("%d",&z);
                        for(i=0;i<r;i++)
                        {
                                init[i]=Arr[z-1].req_res[i];
                                init2[i]=ps_res[i];
                                printf("ENTER %dTH NEW REQUIRED REOSURCE :",i+1);
                                scanf("%d",&Arr[z-1].req_res[i]);
                        }
                        alloc(Arr,n,r,ps_res);
                        cover(n,mon);
                        for(i=0;i<r;i++)
                        {
                                Arr[z-1].req_res[i]=init[i];
                                ps_res[i]=init2[i];
                        }
                        next(Arr,n,r,ps_res);
                        break;
                case 2:
                        return;
                        break;
        }
}
void cover(int n,int mon)
{
        if(mon==n)
        {
                printf("Safe\n");
        }
        else
        {
                printf("Unsafe,after the above process deadlock has occured...\n");
        }

}

