#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<math.h>
#include<ctype.h>

char pass[]="123";
char DB_pointer;
char *N_DB[30];
char DDL_pointer[100];
char DML_pointer[100];
void clear_(){
		system("cls");
}
//Password check module.
int pass_check(){
	char check[3];
	printf("Enter the password:");
	scanf("%s",check);
	if (strcmp(check,pass)==0)
		return 0;
	else
		exit(0);
}
void help_(){
	printf("This DBMS is case-sensitive.\n");
	printf("Press 1 for DDL commands to initiate.\npress 2 for DML commands to initiate.\nType 'C' to clear current screen.\nType 'E' to exit.\n");
	printf("To use DML commands. Database have to be imported with the help of *Use Database commmand in DDL.\n");
	printf("Each command section are seperated so as to make it less complex.\n");
	printf("To properly use the DBMS. One must shuffle between DDL and DML commands section.\n");
	printf("Commands of one section cannot be accessed, when other section is opened first.\n");
	printf("Commands 'H', 'E' and 'C' are universal and can be accessed from anywhere except at the run-time of DDL or DML commands.\n");
	printf("Field name must be unique in a particular table.\n");
	printf("Trying to make table or Database with already existing name will result to overwrite.\n");
}
void DDL_help(){
	printf("\n");
	printf("Following commands can be used : \n\n1)*Create Database\n<Name>\n\n2)*Use Database\n<Name>\n\n3)*Close Database\n<Name>\n\n4)*Drop Database\n<Name>\n\n5)*Rename Database\n<Old name><New name\n\n6)*Create table\n<\\\\Name>\n\n7)*Drop table\n<\\\\Name>\n\n");
}
void func_help(){
	printf("Arithmetic functions:\n\n1)add\n2)sub\n3)mul\n4)div\n5)mod\n6)round\n7)pow\n\n");
	printf("String function:\n\n1)cat\n2)cmp\n3)rev\n4)len\n5)upper\n6)lower\n\n");
}
void DML_help(){
	char ch[1];
	printf("\n");
	printf("Following commands can be used : \n\n1)Insert into table\n<\\\\Name>\n\n2)Select ALL from\n<\\\\Table name>\n\n3)Select\n<Field name>\nfrom\n<\\\\Table name>\n\n4)Select in\n<Field>\nfrom\n<\\\\Table>\n<Function>\n<parameter>\n\n");
	printf("Type 3 to see all provided functions.\n\n");
	gets(ch);
	if (strcmp(ch,"3")==0)
		func_help();
}
void pointer_(){
		printf("MyVBDBMS>>>");
}
void intro_(){
	printf("Welcome to MyVBDMBS.\n");
	printf("Created by aj.s.\n");
	printf("Version 7.4.20(Beta)");
	printf("\n\n");
	printf("Copyleft (C) 2022, Procrast and/or its affiliates(dank meme corporation).\n");
	printf("This is a Very Basic DBMS. So go easy on it.");
	printf("\n\n");
	printf("Type 'H' for Help. Type 'C' to clear current screen. Type 'E' to exit.\n");
}
void Creat_DB(){
	int check;
	char n_DB[30];
	scanf("%s",n_DB);
	check=mkdir(n_DB);
	if (check==0)
		printf("Database created successfully.\n");
	else
		printf("Error : Database was not created due to some error or database of same name exits already.\n");
}
DIR* Use_DB(char *n_DB[30]){
	DIR *db;
	scanf("%s",n_DB);
	db=opendir(n_DB);
	if (db!=NULL){
		printf("Database is ready to use.\n");
		return db;
	}
	else
		printf("Error : No database found named : %s \n",n_DB);
}
void Close_DB(DIR *DB){
	int check;
	check=closedir(DB);
	if (check==0)
		printf("Database has been closed successfully.\n");
	else
		printf("Error : Unable to close database or no database found of entered name.\n");
}
void Drop_db(){
	char n_DB[30];
	scanf("%s",n_DB);
	remove(n_DB);
}
void Rename_db(){
	char n_DB[30],N_db[30];
	scanf("%s%s",n_DB,N_db);
	rename(n_DB,N_db);
}

FILE* Creat_table(char *N_db[30]){
	char n_tb[30];
	char dn_tb[40];
	FILE *fp,*fq;
	char N_tb[30];
	char Ds_tb[30]="DB";
	if (strcmp(N_tb,"")==0){
		printf("Error : no database is in use. refer to DDL sections' help desk for suitable command.\n");
		return 0;
	}
	strcpy(N_tb,N_db);
	printf("%s",N_tb);
	scanf("%s",n_tb);
	strcpy(dn_tb,n_tb);
	strcat(dn_tb,"_Ds.txt");
	strcat(Ds_tb,dn_tb);
	strcat(n_tb,".txt");
	strcat(N_tb,n_tb);
	fp=fopen(N_tb,"w+");
	fq=fopen(Ds_tb,"w+");
	if (fp!=NULL && fq!=NULL){
		printf("Table has been created fully.\n");
		char n_tb1[30];
		char size[3];
		char sizetemp[3]="0";
		int s,ln;
		printf("Keep entering the names and size of the fields in order\n<Name>\n<size>\nSize must be in two digit format(02,20).\nType ; then enter when done.\n");
		while (1)
		{
			scanf("%s",n_tb1);
			if (strcmp(n_tb1,";")==0)
				break;
			ln=strlen(n_tb1);
			fputs(n_tb1,fp);
			scanf("%s",size);
			s=atoi(size);
			if (s<ln && s!=0){
				itoa(ln,size,10);
				strcat(sizetemp,size);
				fputs(sizetemp,fq);
				goto K;
			}
			fputs(size,fq);
			for (int c = 0; c < (s-ln); c++)
				fputc(' ',fp);
			K:
			fputc('|',fp);
		}
		fclose(fp);
		fclose(fq);
		}
	else
		printf("Error : Table was unable to form or unable to open metadata.\n");
}
int Insert_tb(char *N_db[30]){
	char n_tb[30];
	char dn_tb[40];
	FILE *fp,*fq;
	char N_tb[30];
	char Ds_tb[30]="DB";
	strcpy(N_tb,N_db);
	if (strcmp(N_tb,"")==0){
		printf("Error : no database is in use. refer to DDL sections' help desk for suitable command.\n");
		return 0;
	}
	printf("%s",N_tb);
	scanf("%s",n_tb);
	strcpy(dn_tb,n_tb);
	strcat(dn_tb,"_Ds.txt");
	strcat(Ds_tb,dn_tb);
	strcat(n_tb,".txt");
	strcat(N_tb,n_tb);
	fp=fopen(N_tb,"a");
	fq=fopen(Ds_tb,"r+");
	if (fp!=NULL && fq!=NULL){
		char n_tb1[30];
		char size[3];
		int ln,s;
		/*while (fgets(size,3,fq)!=NULL)
    	{
			 s=atoi(size);
       		 printf("%d\n",s);
    	}*/
		printf("Keep entering the data of the fields.Type ; then enter when done.\n");
		while (1){
			printf(">\n");
			fputc('\n',fp);
			while (fgets(size,3,fq)!=NULL){
				s=atoi(size);
				scanf("%s",n_tb1);
				ln=strlen(n_tb1);
				if (ln>s){
					printf("Error : Exceeded the specified Size.\n");
					break;
				}
				if (strcmp(n_tb1,";")==0)
					goto C;
				fputs(n_tb1,fp);
				for (int c = 0; c < (s-ln); c++)
					fputc(' ',fp);
				fputc('|',fp);
			}
			rewind(fq);
		}
		C:
		fclose(fp);
		fclose(fq);
	}
	else
		printf("Error : Table was unable to open or no table found of entered name.\n");
}
int Select_All(char *N_db[30]){
	char N_tb[30];
	FILE *fp;
	char n_tb[30];
	char temp[1];
	strcpy(N_tb,N_db);
	if (strcmp(N_tb,"")==0){
		printf("Error : no database is in use. refer to DDL sections' help desk for suitable command.\n");
		return 0;
	}
	printf("%s",N_tb);
	scanf("%s",n_tb);
	strcat(n_tb,".txt");
	strcat(N_tb,n_tb);
	fp=fopen(N_tb,"r");
	if (fp!=NULL){
		char n_tb1[100];
		printf("Below are the contents of the table <%s>.\n",n_tb);
		while (fgets(n_tb1,99,fp)!=NULL)
		{
			printf("%s",n_tb1);
		}
		printf("\n");
		fclose(fp);
		}
	else
		printf("Error : Table was unable to display or no table found of entered name.\n");
}
int Select_part(char *N_db[30]){
	char N_tb[30];
	FILE *fp;
	char n_tb[30];
	char n_tb1[30];
	strcpy(N_tb,N_db);
	if (strcmp(N_tb,"")==0){
		printf("Error : no database is in use. refer to DDL sections' help desk for suitable command.\n");
		return 0;
	}
	scanf("%s",n_tb1);
	printf("from\n");
	printf("%s",N_tb);
	scanf("%s",n_tb);
	strcat(n_tb,".txt");
	strcat(N_tb,n_tb);
	fp=fopen(N_tb,"r");
	if (fp!=NULL){
		char n_tb2[100];
		printf("Below are the contents of the field <%s> from table <%s> : \n\n",n_tb1,n_tb);
		fgets(n_tb2,99,fp);
   		int i=0,j=0,k=0,l;
    	for (l = 0; n_tb2[l]!='\0'; l++)
    	{
			k=strlen(n_tb1);
        	j=l;
        	i=0;
        	A:
        	if (k==0){
            	break;
        	}
        	if (n_tb1[i]==n_tb2[j] && k>0){
            	i++;
            	j++;
            	--k;
            	goto A;
        	}
       	 	else
            	continue;
    	}
		while (fgets(n_tb2,99,fp)!=NULL)
		{
			for (int c = l; n_tb2[c]!='|'; c++)
			{
				printf("%c",n_tb2[c]);
			}
			printf("\n");
		}
		printf("\n");
		fclose(fp);
		}
	else
		printf("Error : Table was unable to display or no table found of entered name.\n");
}
void Field_arithmetic(int num,int num1,char F_n[10]){
	if (strcmp(F_n,"add")==0)
		printf("%d",num+num1);
	if (strcmp(F_n,"sub")==0)
		printf("%d",num-num1);
	if (strcmp(F_n,"mul")==0)
		printf("%d",num*num1);
	if (strcmp(F_n,"div")==0)
		printf("%d",num/num1);
	if (strcmp(F_n,"mod")==0)
		printf("%d",num%num1);
	if (strcmp(F_n,"round")==0){
		double temp;
		temp=round(num);
		printf("%lf",temp);
	}
	if (strcmp(F_n,"pow")==0){
		int temp1;
		temp1=pow(num,num1);
		printf("%d",temp1);
	}
}
void Field_string(char field[99],char arges[100],char F_n[10]){
	char temp1[99];
	if (strcmp(F_n,"cat")==0){
		strcat(temp1,field);
		strcat(temp1,arges);
		printf("%s",temp1);
	}
	if (strcmp(F_n,"cmp")==0)
		printf("%d",strcmp(field,arges));
	if (strcmp(F_n,"rev")==0){
		strcpy(temp1,field);
		strrev(temp1);
		printf("%s",temp1);
	}
	if (strcmp(F_n,"len")==0){
		int ln;
		ln=strlen(field);
		printf("%d",ln);
	}
	if (strcmp(F_n,"upper")==0){
		strcpy(temp1,field);
		for (int i = 0; temp1[i]!='\0'; i++)
			printf("%c",toupper(temp1[i]));
	}
	if (strcmp(F_n,"lower")==0){
		strcpy(temp1,field);
		for (int i = 0; temp1[i]!='\0'; i++)
			printf("%c",tolower(temp1[i]));
	}
}
int Field_functions(char *N_db[30]){
	char N_tb[30];
	FILE *fp;
	char n_tb[30];
	char n_tb1[30];
	char f_n[10];
	char para[100];
	strcpy(N_tb,N_db);
	if (strcmp(N_tb,"")==0){
		printf("Error : no database is in use. refer to DDL sections' help desk for suitable command.\n");
		return 0;
	}
	scanf("%s",n_tb1);
	printf("from\n");
	printf("%s",N_tb);
	scanf("%s",n_tb);
	strcat(n_tb,".txt");
	strcat(N_tb,n_tb);
	fp=fopen(N_tb,"r");
	if (fp!=NULL){
		char n_tb2[100];
		fgets(n_tb2,99,fp);
   		int i=0,j=0,k=0,l;
    	for (l = 0; n_tb2[l]!='\0'; l++)
    	{
			k=strlen(n_tb1);
        	j=l;
        	i=0;
        	A:
        	if (k==0){
            	break;
        	}
        	if (n_tb1[i]==n_tb2[j] && k>0){
            	i++;
            	j++;
            	--k;
            	goto A;
        	}
       	 	else
            	continue;
    	}
		scanf("%s",f_n);
		if (strcmp(f_n,"round")==0)
			goto R;
		if (strcmp(f_n,"rev")==0)
			goto R;
		if (strcmp(f_n,"len")==0)
			goto R;
		if (strcmp(f_n,"upper")==0)
			goto R;
		if (strcmp(f_n,"lower")==0)
			goto R;
		scanf("%s",para);
		R:
		if (strcmp(f_n,"add")==0){
			printf("Below is the result of <add(%s,%s)>:\n",n_tb1,para);
			int n,n1;
			char temp[99];
			n=atoi(para);
			while (fgets(n_tb2,99,fp)!=NULL){
				for (int c = l,j=0; n_tb2[c]!='|'; c++,j++)
					{
						temp[j]=n_tb2[c];
					}
				n1=atoi(temp);
				Field_arithmetic(n1,n,f_n);
				printf("\n");
			}
		}
		else if (strcmp(f_n,"sub")==0){
			printf("Below is the result of <sub(%s,%s)>:\n",n_tb1,para);
			int n,n1;
			char temp[99];
			n=atoi(para);
			while (fgets(n_tb2,99,fp)!=NULL){
				for (int c = l,j=0; n_tb2[c]!='|'; c++,j++)
					{
						temp[j]=n_tb2[c];
					}
				n1=atoi(temp);
				Field_arithmetic(n1,n,f_n);
				printf("\n");
			}
		}
		else if (strcmp(f_n,"mul")==0){
			printf("Below is the result of <mul(%s,%s)>:\n",n_tb1,para);
			int n,n1;
			char temp[99];
			n=atoi(para);
			while (fgets(n_tb2,99,fp)!=NULL){
				for (int c = l,j=0; n_tb2[c]!='|'; c++,j++)
					{
						temp[j]=n_tb2[c];
					}
				n1=atoi(temp);
				Field_arithmetic(n1,n,f_n);
				printf("\n");
			}
		}
		else if (strcmp(f_n,"div")==0){
			printf("Below is the result of <div(%s,%s)>:\n",n_tb1,para);
			int n,n1;
			char temp[99];
			n=atoi(para);
			while (fgets(n_tb2,99,fp)!=NULL){
				for (int c = l,j=0; n_tb2[c]!='|'; c++,j++)
					{
						temp[j]=n_tb2[c];
					}
				n1=atoi(temp);
				Field_arithmetic(n1,n,f_n);
				printf("\n");
			}
		}
		else if (strcmp(f_n,"mod")==0){
			printf("Below is the result of <mod(%s,%s)>:\n",n_tb1,para);
			int n,n1;
			char temp[99];
			n=atoi(para);
			while (fgets(n_tb2,99,fp)!=NULL){
				for (int c = l,j=0; n_tb2[c]!='|'; c++,j++)
					{
						temp[j]=n_tb2[c];
					}
				n1=atoi(temp);
				Field_arithmetic(n1,n,f_n);
				printf("\n");
			}
		}
		else if (strcmp(f_n,"round")==0){
			printf("Below is the result of <round(%s)>:\n",n_tb1);
			int n,n1;
			char temp[99];
			n=atoi(para);
			while (fgets(n_tb2,99,fp)!=NULL){
				for (int c = l,j=0; n_tb2[c]!='|'; c++,j++)
					{
						temp[j]=n_tb2[c];
					}
				n1=atof(temp);
				Field_arithmetic(n1,n,f_n);
				printf("\n");
			}
		}
		else if (strcmp(f_n,"pow")==0){
			printf("Below is the result of <pow(%s,%s)>:\n",n_tb1,para);
			int n,n1;
			char temp[99];
			n=atoi(para);
			while (fgets(n_tb2,99,fp)!=NULL){
				for (int c = l,j=0; n_tb2[c]!='|'; c++,j++)
					{
						temp[j]=n_tb2[c];
					}
				n1=atoi(temp);
				Field_arithmetic(n1,n,f_n);
				printf("\n");
			}
		}
		else if (strcmp(f_n,"cat")==0){
			printf("Below is the result of <cat(%s,%s)>:\n",n_tb1,para);
			char temp[99];
			while (fgets(n_tb2,99,fp)!=NULL){
				for (int c = l,j=0; n_tb2[c]!=' '; c++,j++)
					{
						temp[j]=n_tb2[c];
					}
				Field_string(temp,para,f_n);
				printf("\n");
			}
		}
		else if (strcmp(f_n,"cmp")==0){
			printf("Below is the result of <cmp(%s,%s)>:\n",n_tb1,para);
			char temp[99];
			while (fgets(n_tb2,99,fp)!=NULL){
				for (int c = l,j=0; n_tb2[c]!=' '; c++,j++)
					{
						temp[j]=n_tb2[c];
					}
				Field_string(temp,para,f_n);
				printf("\n");
			}
		}
		else if (strcmp(f_n,"rev")==0){
			printf("Below is the result of <rev(%s)>:\n",n_tb1);
			char temp[99];
			while (fgets(n_tb2,99,fp)!=NULL){
				for (int c = l,j=0; n_tb2[c]!=' '; c++,j++)
					{
						temp[j]=n_tb2[c];
					}
				Field_string(temp,para,f_n);
				printf("\n");
			}
		}
		else if (strcmp(f_n,"len")==0){
			printf("Below is the result of <len(%s)>:\n",n_tb1);
			char temp[99];
			while (fgets(n_tb2,99,fp)!=NULL){
				for (int c = l,j=0; n_tb2[c]!=' '; c++,j++)
					{
						temp[j]=n_tb2[c];
					}
				Field_string(temp,para,f_n);
				printf("\n");
			}
		}
		else if (strcmp(f_n,"upper")==0){
			printf("Below is the result of <upper(%s)>:\n",n_tb1);
			char temp[99];
			while (fgets(n_tb2,99,fp)!=NULL){
				for (int c = l,j=0; n_tb2[c]!=' '; c++,j++)
					{
						temp[j]=n_tb2[c];
					}
				Field_string(temp,para,f_n);
				printf("\n");
			}
		}
		else if (strcmp(f_n,"lower")==0){
			printf("Below is the result of <lower(%s)>:\n",n_tb1);
			char temp[99];
			while (fgets(n_tb2,99,fp)!=NULL){
				for (int c = l,j=0; n_tb2[c]!=' '; c++,j++)
					{
						temp[j]=n_tb2[c];
					}
				Field_string(temp,para,f_n);
				printf("\n");
			}
		}
		else
			printf("Error : Invalid Function.\n");
		printf("\n");
		fclose(fp);
		}

	else
		printf("Error : Table was unable to display or no table found of entered name.\n");
}
int Drop_tb(char *N_db[30]){
	char n_tb[30];
	char N_tb[30];
	char dn_tb[40];
	char Ds_tb[30]="DB";
	int check,check1;
	if (strcmp(N_tb,"")==0){
		printf("Error : no database is in use. refer to DDL sections' help desk for suitable command.\n");
		return 0;
	}
	strcpy(N_tb,N_db);
	printf("%s",N_tb);
	scanf("%s",n_tb);
	strcpy(dn_tb,n_tb);
	strcat(dn_tb,"_Ds.txt");
	strcat(Ds_tb,dn_tb);
	strcat(n_tb,".txt");
	strcat(N_tb,n_tb);
	check=remove(N_tb);
	check1=remove(Ds_tb);
	if (check==0 && check==0)
		printf("The table and all its internal data has been successfuly removed.\n");
	else
		printf("Error : The table was unable to be removed or no table found of entered name.\n");
}
//DDL section module.
int DDL(){
	DIR *DB;
	printf("Type H>DDL to see all possible commands. Type EXIT>DDL to exit DDL command section.\n");
	while(1){
		gets(DDL_pointer);
		if (strcmp(DDL_pointer,"H>DDL")==0)
			DDL_help();
		if (strcmp(DDL_pointer,"Create Database")==0)
			Creat_DB();
		if (strcmp(DDL_pointer,"Use Database")==0)
			DB=Use_DB(N_DB);
		if (strcmp(DDL_pointer,"Close Database")==0)
			Close_DB(DB);
		if (strcmp(DDL_pointer,"Drop Database")==0)
			Drop_db();
		if (strcmp(DDL_pointer,"Rename Database")==0)
			Rename_db();
		if (strcmp(DDL_pointer,"Create table")==0)
			Creat_table(N_DB);
		if (strcmp(DDL_pointer,"Drop table")==0)
			Drop_tb(N_DB);
		if (strcmp(DDL_pointer,"C")==0)
			clear_();
		if (strcmp(DDL_pointer,"H")==0)
			help_();
		if (strcmp(DDL_pointer,"E")==0)
			exit(0);
		if (strcmp(DDL_pointer,"EXIT>DDL")==0)
			return 0;
		pointer_();
	}
}
//DML section module
int DML(){
	printf("Type H>DML to see all possible commands. Type EXIT>DML to exit DML command section.\n");
	while(1){
		gets(DML_pointer);
		if (strcmp(DML_pointer,"Insert into table")==0)
			Insert_tb(N_DB);
		if (strcmp(DML_pointer,"Select ALL from")==0)
			Select_All(N_DB);
		if (strcmp(DML_pointer,"Select")==0)
			Select_part(N_DB);
		if (strcmp(DML_pointer,"Select in")==0)
			Field_functions(N_DB);
		if (strcmp(DML_pointer,"H>DML")==0)
			DML_help();
		if (strcmp(DML_pointer,"C")==0)
			clear_();
		if (strcmp(DML_pointer,"H")==0)
			help_();
		if (strcmp(DML_pointer,"E")==0)
			exit(0);
		if (strcmp(DML_pointer,"EXIT>DML")==0)
			return 0;
		pointer_();
	}
}
void main(){
	pass_check();
	intro_();
	while (1)
	{
		scanf("%c",&DB_pointer);
		if (DB_pointer==10)
			pointer_();
		if (DB_pointer=='C')
			clear_();
		if (DB_pointer=='H')
			help_();
		if (DB_pointer=='E')
			exit(0);
		if (DB_pointer==49)
			DDL();
		if (DB_pointer==50)
			DML();
	}
}