#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Seats	/*estrutura dos lugares*/
{
char occupied;
char name [100];
char checked_in;
int id_luggage;
int id_reservation_code;
}SEAT;


void menu()
{
	printf("		Aircraft Business\n");
	printf("	0 - Exit\n");
	printf("	1 - Show the structure of a plane\n");
	printf("	2 - Show the occupancy of a flight\n");
	printf("	3 - Show the passenger names with a reservation for this flight\n"); printf("\n");
	printf("	4 - Reserve a flight with seat number\n");
	printf("	5 - Change the seat of a reservation\n");
	printf("	6 - Assign a plane to a specific flight (opening of a flight)\n"); printf("\n");
	printf("	7 - Fill in a flight with random passengers\n"); printf("\n");
	printf("	8 - Histogram of flight occupancy per type of seat\n");
	printf("	9 - Generation of the files \"names\" and \"surnames\"\n");
}
int Random(int max)												
{	
	int rd;
	int min = 0 ;
	rd = (rand () % (max - min + 1)) + min;

	return rd;
}

void Question(char name[])
{
	printf("Please select the aircraft type: Ex(a318)  ");
	scanf(" %s",name);
	name[0] = (name[0]+32)*(name[0]=='A') + name[0]*(name[0]=='a');  /*aceita imputs do tipo A318 por exemplo*/
}
void TranslateChar(char name[],char filename[]) /*traduz ficheiros do tipo a318 para Airbus318 por exemplo*/
{
	if (!strcmp(name, "a318"))
		strcpy(filename ,"Airbus318");
	if (!strcmp(name, "a319"))
		strcpy(filename,"Airbus319");
	if (!strcmp(name, "a320"))
		strcpy(filename, "Airbus320");
	if (!strcmp(name, "a321"))
		strcpy(filename, "Airbus321");			
}
void TranslateInt(int type,char name[]) /* traduz 318 para a318 por exemplo */
{
	sprintf(name ,"a%d",type);
}

void ChooseFile(char filename[])
{
	printf("\nSelect a flight code  ");
	scanf("%s",filename);
	printf("\n");
}	
void ChooseFile2(char Fcode[],char Atype[])
{
	printf("\nWrite a flight code without blank spaces (Ex. TP2040  ");
	scanf("%s",Fcode);
	printf("\nWrite the aircraft type (Ex: a321):  ");
	scanf(" %s",Atype); 
	Atype[0] = (Atype[0]+32)*(Atype[0]=='A') + Atype[0]*(Atype[0]=='a');
	
	
}
int ReadPlaneStructFile(char name[],int *Executive_Rows,int *Turistic_Rows)
{
	/* conta as filas executivas e turisticas */
	char filename[256];
	char line [256];
	TranslateChar(name,filename);
	
	FILE *fp;
		
	
		fp = fopen(filename,"r"); /* lê ficheiro de texto*/
		
		if(fp != NULL)
		{
			while (fgets(line, 256, fp)!= NULL) /* leitura linha a linha do ficheiro */
			{
				if (strlen(line) == 5)  /* conta com \n*/
					{
						(*Executive_Rows)++;
					}
				if (strlen(line) == 7)  /* conta com \n*/
					{
						(*Turistic_Rows)++;
					}
			}
		return 1;	
		}	
		else
		{
			printf("\nUnable to open file\n\n");
			return 0;
		}
		fclose(fp);
}	
void ShowSeats(int Executive_Rows,int Turistic_Rows, SEAT seats[][35]) /* leitura dos lugares */
{
	printf("	\".\"represents the reserved seats\n\n");
	for (int i = 0;i < 6;i++)	
		{
				for ( int j = 0; j < Executive_Rows+Turistic_Rows; ++j)
				{
					if (j < Executive_Rows)
					{
						if ((i == 0) || (i == 5))
						{
							printf("  ");
							continue;
						}
						if(seats[i][j].occupied)
						{	
							printf(" .");
						}
						else
						{
							printf(" %c",'a' + i - 1); 
						}
						
					}
					else
					{
						if(seats[i][j].occupied)
						{	
							printf(" .");
						}
						else	
						{
							printf(" %c",'a' + i);
						}
					}	
				}
			printf("\n");	
		}
		printf("\n\n");
		printf("Press Enter to continue\n\n\n");
		getchar();
		getchar();
}
void ReadSeats(int Executive_Rows,int Turistic_Rows,SEAT seats[6][35], FILE *fp)
{
		
	for (int i = 0;i < Executive_Rows ;i++)	
		{	
					for ( int j = 1; j < 5 ; ++j)
					{						
						fread(&seats[j][i], sizeof(SEAT),1,fp);						
					}
		}
		
	for (int i=Executive_Rows ; i < Turistic_Rows+Executive_Rows ;i++)	
		{	
					for (int j = 0 ; j < 6 ; ++j)
					{								
						fread(&seats[j][i],sizeof(SEAT),1,fp);		
					}	
		}
}
void WriteSeats(int Executive_Rows,int Turistic_Rows,SEAT seats[6][35], FILE *fp)
{
		
	for (int i = 0;i < Executive_Rows ;i++)	
		{	
					for ( int j = 1; j < 5 ; ++j)
					{						
						fwrite(&seats[j][i], sizeof(SEAT),1,fp);						
					}
		}
		
	for (int i=Executive_Rows ; i < Turistic_Rows+Executive_Rows ;i++)	
		{	
					for (int j = 0 ; j < 6 ; ++j)
					{								
						fwrite(&seats[j][i],sizeof(SEAT),1,fp);		
					}	
		}
}
void ShowPassengers(int Executive_Rows,int Turistic_Rows,SEAT seats[6][35])
{
	printf("Passengers\n");	
	printf("  Executive:\n");	
	for (int i = 0;i < Executive_Rows ;i++)	
		{	
					for ( int j = 1; j < 5 ; ++j)
					{						
						if (seats[j][i].occupied)
							printf("	Row %d, seat %c: name =  %s\n",i+1,'a'+j-1,seats[j][i].name);					
					}
		}
	printf("\n  Turistic:\n");	
	for (int i=Executive_Rows ; i < Turistic_Rows+Executive_Rows ;i++)	
		{	
					for (int j = 0 ; j < 6 ; ++j)
					{								
						if(seats[j][i].occupied)
							printf("	Row %d, seat %c: name =  %s\n",i+1,'a'+j,seats[j][i].name);
					}	
		}
		printf("\n\n");
		printf("Press Enter to continue\n\n\n");
		getchar();
		getchar();		
}	
void SeatConvert(int j, int *i, char c, int Executive_Rows)
{
	
	if(j<=Executive_Rows)
		{
			if(c =='a')
				*i =	1;
			if(c =='b')
				*i =	2;
			if(c =='c')
				*i =	3;
			if(c =='d')
				*i =	4;	
		}
		else
		{
			if(c =='a')
				*i =	0;
			if(c =='b')
				*i =	1;
			if(c =='c')
				*i =	2;
			if(c =='d')
				*i =	3;	
			if(c =='e')
				*i =	4;
			if(c =='f')
				*i =	5;			
		}

}
void MakeReserve(int Executive_Rows,SEAT seats[6][35])
{
	int i=0; int j,id, rc;
	char c; char name[100]; 
		
	if (Executive_Rows == 0)
	{
		return;
	}
			
	while(1)
	{		
			
		printf("	\nSelect the row number for the reservation:  ");
		scanf(" %d",&j);
			
		printf("	\nChoose the desired seat in this row (ex: b):  ");
		scanf(" %c",&c);	
			
		SeatConvert(j,&i,c,Executive_Rows); /* converte carateres em posições i da matriz seats*/
	
	
		if(!(seats[i][j-1].occupied))
		{	
					printf("  \nPlease write a name and surname:    ");
			scanf(" %99[^\n]",name); 		
			
			printf("  \nPlease write a number for the identifier of the luggage:    ");
			scanf(" %d", &id);
			
			printf("  \nPlease write a number for the reservation code:    ");
			scanf(" %d", &rc);
		
			
			if(j<=Executive_Rows)
			{		
				seats[i][j-1].id_luggage = id;
				strcpy(seats[i][j-1].name, name);	
				seats[i][j-1].id_reservation_code = rc;	
				seats[i][j-1].occupied = 1;	
				break;
			}
			else
			{	
				seats[i][j-1].id_luggage = id;
				strcpy(seats[i][j-1].name, name);	
				seats[i][j-1].id_reservation_code = rc;		
				seats[i][j-1].occupied = 1;	
				break;	
			}
		}
		else
		{
			printf("\n  Seat already taken, Choose again");
			continue;
		}
	}			
		printf("\n\n");
		printf("Done. Press Enter to continue\n\n\n");
		getchar();
		getchar();		
}
void ChangeReserve(int Executive_Rows,SEAT seats[6][35])
{
	int j,rc,id; int i=0;
	char c; char name[100];
	
	if (Executive_Rows == 0)
	{
		return;
	}
	
	while(1)
	{	
		printf("\n\n	What is your original row?  ");
		scanf(" %d",&j);
		
		printf("\n	What is your original seat in this row(a, b, c, etc)?  ");
		scanf(" %c",&c);
		
		SeatConvert(j,&i,c,Executive_Rows);
		
		if(seats[i][j-1].occupied)
		{
			printf("\n	Just for testing ----> The reservation name is: %s \n",seats[i][j-1].name);
			printf("\n	Write your name and surname:  ");
			scanf(" %99[^\n]",name); 
			
			if(!strcmp(name,seats[i][j-1].name ))
			{
				seats[i][j-1].occupied = 0;
				rc = seats[i][j-1].id_reservation_code;
				id = seats[i][j-1].id_luggage;
				
				
				printf("\n\n	What is the row for the reservation?:   ");
				scanf(" %d",&j);
				
				printf("\n	Select the seat in this row (ex: b):   ");
				scanf(" %c",&c);
				
				SeatConvert(j,&i,c,Executive_Rows); /* converte carateres em posições i da matriz seats*/
				
				seats[i][j-1].id_luggage = id;	
				seats[i][j-1].id_reservation_code = rc;	
				strcpy(seats[i][j-1].name, name);	
				seats[i][j-1].occupied = 1;	
							
			}
			else
			{
				printf("Wrong name choose again\n");
				continue;
			}
			
			
			break;
		}
		else
		{
			printf("That seat is empty, choose again\n");
			continue;
		}
	}
}
void CreateNewPlane(int Executive_Rows,int Turistic_Rows,SEAT seats[6][35])
{	
	if (Executive_Rows == 0)
	{
		return;
	}	
	
	for (int i = 0;i < Executive_Rows ;i++)	
		{	
					for ( int j = 1; j < 5 ; ++j)
					{						
						seats[j][i].occupied = 0;								
					}
		}
		
	for (int i=Executive_Rows ; i < Turistic_Rows+Executive_Rows ;i++)	
		{	
					for (int j = 0 ; j < 6 ; ++j)
					{								
						seats[j][i].occupied = 0;	
					}	
		}
}
int ReadNames(char name[])
{
	/* abre o ficheiro dos nomes */
	int x; int i = 0;
	char line [256];
	
	x = Random(818);
	
	FILE *fp;
		
	
		fp = fopen("names","r"); /* lê ficheiro de texto*/
		
		if(fp != NULL)
		{
			while (fgets(line, 256, fp)!= NULL) /* leitura linha a linha do ficheiro */
			{
				if(i < x)
				{	
					i++;
				}
				else
				{
					strcpy(name ,line);
					name[strlen(name)-1] = '\0';
					break;
				}	
			}
		}	
		else
		{
			printf("Unable to open file");
			return -1;
		}
		fclose(fp);
}
int ReadSurnames(char surname[])
{
	/* abre o ficheiro dos nomes */
	int x; int i = 0;
	char line [256];
	
	x = Random(751);
	
	FILE *fp;
		
	
		fp = fopen("surnames","r"); /* lê ficheiro de texto*/
		
		if(fp != NULL)
		{
			while (fgets(line, 256, fp)!= NULL) /* leitura linha a linha do ficheiro */
			{
				if(i < x)
				{	
					i++;
				}
				else
				{
					strcpy(surname ,line);
					surname[strlen(surname)-1] = '\0';
					break;
				}	
			}
		}	
		else
		{
			printf("Unable to open file");
			return -1;
		}
		fclose(fp);
}			
void CreateRandomFlight(int Executive_Rows,int Turistic_Rows,SEAT seats[6][35])
{	
	int SeatNumber; int try=0;
	float Percent,TotalSeats;
	char name[30];
	char surname[30];
	char FullName[61];
	
	if (Executive_Rows == 3)
	{
		TotalSeats = 108;
	}
	if (Executive_Rows == 4)
	{
		TotalSeats = 124;
	}
	if (Executive_Rows == 5)
	{
		TotalSeats = 152;
	}
	if (Executive_Rows == 6)
	{
		TotalSeats = 186;
	}
	
	SeatNumber = Random(TotalSeats);
	
	Percent = (SeatNumber / TotalSeats)*100;
	
	printf("\n 	The aircraft has %.0f seats and %d seats will be reserved (%.2f)%%								\n",TotalSeats,SeatNumber,Percent);
	
	printf("\n\n");
	printf("  Press Enter to continue\n\n\n");
	getchar();
	getchar();
	
	
	
	while (try < SeatNumber)
	{
		int j = Executive_Rows+Turistic_Rows-1;
		int i = 5;
		
		i = Random(i);
		j = Random(j);
		
		
		if((j < Executive_Rows) && (i == 0))
			continue;
		if((j < Executive_Rows) && (i == 5))
			continue;
		if (seats[i][j].occupied )
			continue;	
			
		
		ReadNames(name);
		ReadSurnames(surname);	
			
		strcpy(FullName, name);	
		
		strcat(FullName, " ");
		
		strcat(FullName, surname);
			
		seats[i][j].id_luggage = Random(10000);	
		seats[i][j].id_reservation_code = Random(10000);	
		strcpy(seats[i][j].name, FullName);	
		seats[i][j].occupied = 1;		
		try++;
					
	}	
	
}
void WriteBinaryFile(char filename[],int type,int Executive_Rows,int Turistic_Rows,SEAT seats[6][35])
{
	if (Executive_Rows == 0)
	{
		return;
	}
	
	FILE *fp;
	
	fp = fopen(filename,"wb");
	
	if(fp != NULL)
	{
		fwrite(&type, sizeof(type), 1 ,fp);	
		
		WriteSeats(Executive_Rows,Turistic_Rows,seats, fp); /* introduz informação da estrutura SEAT na matriz seats*/
	}
	else
	{
		printf("Unable to open file");
		return;
	}
	fclose(fp);
}
int ReadBinaryFile(char filename[],int *Executive_Rows,int *Turistic_Rows,SEAT seats[6][35])  /*[6][35] dimensão maxima possivel de cada avião */
{
	char name[20];
	
	ChooseFile(filename);

	FILE *fp;
	
	int type;
	
	
	fp = fopen(filename,"rb");
	
	if(fp != NULL)
	{
		fread(&type, sizeof(type), 1 ,fp); /* Tipo de avião*/	
		
		TranslateInt(type,name);
		
		ReadPlaneStructFile(name,Executive_Rows,Turistic_Rows);  /*numero de filas exec ou turist*/
		
		ReadSeats(*Executive_Rows,*Turistic_Rows,seats, fp); /*leitura com base na estrutura SEAT*/
		
	}	
	else
	{
		printf("Unable to open file\n\n");
		return 1;
	}
	fclose(fp);
	return type;

}
void asteriscos(int Percent)
{
	int ast,i;
	
	ast = (Percent*70)/100;
	printf("\n");
	
	for (i =0; i < ast;i++)
		printf("*");
		
	printf("\n");
		
	
	
	
}
void PercentRead(int Executive_Rows,int Turistic_Rows,SEAT seats[6][35])
{
	int count = 0; float TotalSeats = 0.0; float TotalSeats2 = 0.0;
	float result; int TotalExec;
	int window=0; int Cr = 0; int Md = 0;
	
	if (Executive_Rows == 0)
	{
		return;
	}		
	
	for (int i = 0;i < Executive_Rows ;i++)	
		{	
					for ( int j = 1; j < 5 ; ++j)
					{						
						if (seats[j][i].occupied)	
							count++;
						TotalSeats++;
						TotalSeats2++;
						
						if(((seats[j][i].occupied)&&(j == 1))||((seats[j][i].occupied)&&(j == 4)))
							window++;	
						if(((seats[j][i].occupied)&&(j == 2))||((seats[j][i].occupied)&&(j == 3)))
							Cr++;	
												
					}
		}
		
	TotalExec = (count/TotalSeats);
	result = (count/TotalSeats)*100;	
	
	printf("\n\nThe executive percent is : %.2f%% \n",result);
	
	asteriscos(result);
	
	TotalSeats = 0.0;
	count = 0;
	
	for (int i=Executive_Rows ; i < Turistic_Rows+Executive_Rows ;i++)	
		{	
					for (int j = 0 ; j < 6 ; ++j)
					{								
						
						if (seats[j][i].occupied)	
							count++;
						TotalSeats++;
						TotalSeats2++;
						
						if(((seats[j][i].occupied)&&(j == 0))||((seats[j][i].occupied)&&(j == 5)))
							window++;
						if(((seats[j][i].occupied)&&(j == 2))||((seats[j][i].occupied)&&(j == 3)))
							Cr++;	
						if(((seats[j][i].occupied)&&(j == 1))||((seats[j][i].occupied)&&(j == 4)))
							Md++;			
							
					}	
		}
	
	result = (count/TotalSeats)*100;
		
	printf("The turistic percent is: %.2f%% \n",result);	
	
	asteriscos(result);
	
	result = (TotalExec + (count/TotalSeats))*100;
	
	printf("The total occupation percent is: %.2f%% \n",result);	
	
	asteriscos(result);
	
	result = (window/TotalSeats2)*100;
	
	printf("The window occupation percent is: %.2f%% \n",result);	
	
	asteriscos(result);
	
	result = (Cr/TotalSeats2)*100;
	
	printf("The corridor occupation percent is: %.2f%% \n",result);	
	
	asteriscos(result);
	
	result = (Md/TotalSeats2)*100;
	
	printf("The middle occupation percent is: %.2f%% \n",result);
	
	asteriscos(result);
	
	printf("\n\n");
	printf("  Press Enter to continue\n\n\n");
	getchar();
	getchar();
		
}

/********************                 FUNÇÕES PRINCIPAIS              ************************/
void ShowPlaneStructure() /*1*/ 
{	
	char name[256];
	int Executive_Rows=0; int Turistic_Rows=0; int true;

	Question(name);
	true = ReadPlaneStructFile(name,&Executive_Rows,&Turistic_Rows);
	if(true)
		printf("\nNumber of executive Rows: %d    Number of Turistic Rows: %d    \n\n\n",Executive_Rows,Turistic_Rows);     
}
void  ShowOccupancy()	/*2*/
{
	char filename[20];
	int Executive_Rows=0; int Turistic_Rows=0;
	
	SEAT seats[6][35];
	ReadBinaryFile(filename,&Executive_Rows,&Turistic_Rows,seats);
	ShowSeats(Executive_Rows,Turistic_Rows,seats); 	 
}
void ShowNames()		/*3*/
{
	char filename[20];
	int Executive_Rows=0; int Turistic_Rows=0;
	
	SEAT seats[6][35];
	ReadBinaryFile(filename,&Executive_Rows,&Turistic_Rows,seats);
	ShowPassengers(Executive_Rows,Turistic_Rows,seats);

}
void ReserveFlight() /*4*/
{
	char filename[20];
	int Executive_Rows=0; int Turistic_Rows=0;
	int type;
	
	SEAT seats[6][35];
	type = ReadBinaryFile(filename,&Executive_Rows,&Turistic_Rows,seats);
	ShowSeats(Executive_Rows,Turistic_Rows,seats); 	 

	MakeReserve(Executive_Rows,seats); /* Efetuar a reserva */
	WriteBinaryFile(filename,type,Executive_Rows,Turistic_Rows,seats); /* Aplica alterações ao ficheiro */
}

void ChangeReservedSeat()  /*5*/
{ 
	char filename[20];
	int Executive_Rows=0; int Turistic_Rows=0;
	int type;
	
	SEAT seats[6][35];
	type = ReadBinaryFile(filename,&Executive_Rows,&Turistic_Rows,seats);
	ShowSeats(Executive_Rows,Turistic_Rows,seats); 	 
	
	ChangeReserve(Executive_Rows,seats); /*muda a posição da reserva existente*/
	WriteBinaryFile(filename,type,Executive_Rows,Turistic_Rows,seats); /* Aplica alterações ao ficheiro */  
}

void AssignPlane()	/*6*/
{
	char Fcode[20]; char Atype[20];
	int Executive_Rows=0; int Turistic_Rows=0;
	int type;
	
	SEAT seats[6][35];	 
	
	ChooseFile2(Fcode,Atype);
	sscanf(Atype,"a%d",&type);
	
	ReadPlaneStructFile(Atype, &Executive_Rows,&Turistic_Rows);
	
	CreateNewPlane(Executive_Rows,Turistic_Rows,seats);
	
	WriteBinaryFile(Fcode,type,Executive_Rows,Turistic_Rows,seats); /* Aplica alterações ao ficheiro */  
}
void FillFlight() /*7*/
{
	char Fcode[20]; char Atype[20];
	int Executive_Rows=0; int Turistic_Rows=0;
	int type;
	
	SEAT seats[6][35];	 
			
	
	ChooseFile2(Fcode,Atype);
	sscanf(Atype,"a%d",&type);
	
	ReadPlaneStructFile(Atype, &Executive_Rows,&Turistic_Rows);
	
	CreateNewPlane(Executive_Rows,Turistic_Rows,seats);
	CreateRandomFlight(Executive_Rows,Turistic_Rows,seats);
	
	WriteBinaryFile(Fcode,type,Executive_Rows,Turistic_Rows,seats);
}

void Histogram() /*8*/
{
	char filename[20];
	int Executive_Rows=0; int Turistic_Rows=0;
	
	SEAT seats[6][35];
	ReadBinaryFile(filename,&Executive_Rows,&Turistic_Rows,seats);
	
	PercentRead(Executive_Rows,Turistic_Rows,seats);
}
int GenerateFiles()  /*9*/
{

}
int main(int argc,char *argv[])  /**********************    MAIN  *************************/     
{
	int op;   
	int Executive_Rows=0, Turistic_Rows=0;
	
	if (argc == 2) 
	{	
		if (!strcmp(argv[1], "-h"))        /* -help (contem a sintax do programa)*/
		{
			printf("\n");
			printf(" Sintax: ./FinalPm   flight_name  aircraft_type\n"); 
			printf("     or: ./FinalPm   aircraftType\n");	
			printf("\n");
			printf("Example: ./FinalPm   TP107    a318\n");	
			printf("     or: ./FinalPm   a319\n");	
			exit(1);	
		}
		else
		{
			ReadPlaneStructFile(argv[1],&Executive_Rows,&Turistic_Rows);
			printf("Number of executive Rows: %d    Number of Turistic Rows: %d    \n",Executive_Rows,Turistic_Rows);  
		}
	}
	if (argc == 3)
	{
	int Executive_Rows=0; int Turistic_Rows=0;
	int type;
	
	SEAT seats[6][35];	 
	
	ReadPlaneStructFile(argv[2], &Executive_Rows,&Turistic_Rows);
	sscanf(argv[2],"a%d",&type);
	
	CreateNewPlane(Executive_Rows,Turistic_Rows,seats);
	
	WriteBinaryFile(argv[1],type,Executive_Rows,Turistic_Rows,seats); /* Aplica alterações ao ficheiro */  
	
	} 
	
	srand (time(NULL));
	/* MENU */
	while (1)	
	{	
	menu();
	scanf(" %d", &op);
	switch(op)
		{
			case 0 : exit(1);
			case 1 : ShowPlaneStructure(); break;  /*donne*/
			case 2 : ShowOccupancy(); break;  /* donne*/
			case 3 : ShowNames(); break; /*donne */
			case 4 : ReserveFlight(); break;/* donne*/
			case 5 : ChangeReservedSeat(); break; /* donne*/	
			case 6 : AssignPlane(); break; /* donne */
			case 7 : FillFlight(); break; /* donne */
			case 8 : Histogram(); break; /* donne */
			case 9 : GenerateFiles(); break; /* to do*/
		}
	}	
	return 1;
}
