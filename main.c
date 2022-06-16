/* 		Student Record System (pw: es105)
	Made By:
				Amisha Shyam Sakhare
											*/
				
#include <stdio.h>                  //Standard Input Output header file
#include <string.h>                 //contains all string functions 
#include <conio.h>                  //provides console input/output
#include <stdlib.h>                 //General Purpose Standard Library
#include <windows.h>                //Windows-specific  header file
#define size 1000					
typedef struct student              //typedef is used to provide alternative names
{
    char name[30];
    char ID[20];					//name,ID etc. are public variable
    char e_mail[30];
    char phone_no[20];
} std;								//std - object variable
std info[size];						//store details of student in array
int l=0;							//initially record system is empty ie. 0

void SetColor(int ForgC)	                           	//for font colour
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

void ClearConsoleToColors(int ForgC, int BackC)			//for font and background colour
{
    WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};                               //set coordinate to left corner initially
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SetConsoleTextAttribute(hStdOut, wColor);
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
        FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
        SetConsoleCursorPosition(hStdOut, coord);
    }
    return;
}

void SetColorAndBackground(int ForgC, int BackC)		//for font color and highlighting sentences 
{
    WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
    return;
}

COORD coord = {0,0};	                             	//set coordinate to left corner initially
void xy_coordinates(int x, int y)		                //to set cursor position
{
	coord.X = x; coord.Y = y;	                    	//coordinate name x and y
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawing_rectangle()
{
	int i, j;
	SetColor (5);
	xy_coordinates (0,0);	                        	//left corner
	printf ("%c", 201);		                        	//print left corner
	for (i=1; i<78; i++)
	{
		xy_coordinates (i,0);
		printf ("%c", 205);	                         	//print double line horizontal
	}
	xy_coordinates (78,0);	                        	//because i<78 so start again with the x coordinate
	printf ("%c", 187);	                            	//print right corner
	for (i=1; i<25; i++)
	{
		xy_coordinates (78,i);	                    	//cursor at left corner
		if (i==6)
		{
			printf ("%c", 185);	                       	//splitting line
		}
		else
		{
			printf ("%c", 186);	                    	//print double vertical line
		}
	}
	xy_coordinates (78,25);	                         	// cursor at right bottom 		
	printf ("%c", 188);	                            	//print bottom right corner
	for (i=77; i>0; i--)	
	{
		xy_coordinates (i, 25);
		if (i==35)
		{
			printf ("%c", 202);	                       	//splitting bottom line
		}
		else 
		{
			printf ("%c", 205);	                    	//print bottom double line
		}
	}
	xy_coordinates (0,25);	                        	//cursor at left bottom corner
	printf ("%c", 200); 	                        	//print right bottom corner
	for (i=24; i>0; i--)
	{
		xy_coordinates (0,i);
		if (i==6)
		{
			printf ("%c", 204);	                       	//splitting left vertical line
		}
		else
		{
			printf ("%c", 186);	                    	//print veritcal double line
		}
	}
	for (i=1; i<78; i++)
	{
		xy_coordinates (i,6);
		if (i==35)
		{
			printf ("%c", 203);	                    	//middle splitting line
		}
		else 
		{
			printf ("%c", 205);	                    	//print middle horizontal line 
		}
	}
	for (i=7; i<25; i++)
	{
		xy_coordinates (35,i);
		printf ("%c", 186);	                         	//print middle vertical line
	}		
}

void clear_window()                                     //clears second block of right side
{
	int i, j;
	for (i=37; i<78; i++)
	{
		for (j=7; j<25; j++)
		{
			xy_coordinates (i,j);
			printf (" ");
		}
	}
	return;
}

void window()		                                 	//heading in upper block
{
	drawing_rectangle();
	xy_coordinates (28,2);
	SetColor(2);
	printf ("STUDENT RECORD SYSTEM");
	xy_coordinates (22,3);
	printf ("BVM Engineering College, V V Nagar");
	xy_coordinates (33,4);
	printf ("Estd.: 1948");
	xy_coordinates (25,24);
	SetColor (4);
}

void print_heading (const char st[])	            	//st[] title for second block
{
	SetColorAndBackground (31,28);
	xy_coordinates (45,8);
	printf ("SRS: %s", st);                             //SRS: Student Record System
	SetColorAndBackground (17,14);
}

void add()                                              //for adding students detail
{
	clear_window ();                                    //clears the console screen 
	print_heading ("Add Student Record");
	int coord = 37;
    std st;
    fflush(stdin);                                      //flush output buffer of stream
    xy_coordinates (coord, 10);
    printf("Student Name: ");
    gets(st.name);                                      //get student's name
    xy_coordinates (coord, 12);
    printf("Student ID: ");
    gets(st.ID);                                        //get student's ID
    xy_coordinates (coord, 14);
    printf("Student E-Mail: ");			
    gets(st.e_mail);                                    //get students email
    xy_coordinates (coord, 16);
    printf("Phone Number: ");
    gets(st.phone_no);                                  //get student's phone number
    info[l]=st;
    l++;                                                //for record counting
	xy_coordinates (coord,22);
	printf ("The student record is successfully added");	
	SetColor (4);
	return;
}

void modify()                                           //for modifying students detail
{
	clear_window();                                     //clears the console screen 
    print_heading ("Modify Student Record");
    SetColor (1);
    int i,j,k=0, x=37;
    char ch[20];
    xy_coordinates (x,10);
    printf("Enter ID to Modify: ");
    fflush(stdin);                                      //flush output buffer of stream
    xy_coordinates (x,11);
    gets(ch);                                         //get student ID
    if((ch[0]>='a'&&ch[0]<='z')||(ch[0]>='A'&&ch[0]<='Z')||((ch[0]>='0'&&ch[0]<='9')))
    {
        for(i=0; i<l; i++)
        {
            if(strcmp(ch,info[i].ID)==0)                //strcmp: Compares ID
            {
            	xy_coordinates (x,14);
                printf("Student Name: ");
                fflush(stdin);                          //flush output buffer of stream
                gets(info[i].name);                     //get student Name
                xy_coordinates (x,16);
                printf("Student ID: ");
                gets(info[i].ID);                       //get student ID
                xy_coordinates (x,18);
                printf("Student E-Mail: ");
                gets(info[i].e_mail);                   //get students Email
                xy_coordinates (x,20);
                printf("Phone Number: ");
                gets(info[i].phone_no);                 //get students phone no
                k=1;
                break;
            }
        }


        if(k==1)
        {
        	xy_coordinates (x,22);
            printf("Details has been Modified.",ch);
        }
        else
        {
        	xy_coordinates (x,18);
            printf("Sorry! No record found.") ;
        }
    }
    else
    {
    	xy_coordinates (x,18);
        printf("Invalid Input!.");
    }
    SetColor(4);
    return;	
}

void delete_record()                                    //for Deleting student detail
{
	clear_window();                                     //clears the console screen 
    print_heading ("Delete Student Record");
    SetColor (1);
    int i,j,k=0, coord=37;
    char ch[20];
    xy_coordinates (coord, 10);
    printf("Enter ID to delete: ");
    fflush(stdin);                                       //flush output buffer of the screen
    gets(ch);                                            //get student ID                             
    if((ch[0]>='a'&&ch[0]<='z')||(ch[0]>='A'&&ch[0]<='Z')||((ch[0]>='0'&&ch[0]<='9')))
    {
        for(i=0; i<l; i++)
        {
            if(strcmp(ch,info[i].ID)==0)                        //strcmp compares ID
            {
                for(j=i; j<l; j++)		
                {
                    strcpy(info[j].name,info[j+1].name);           //strcpy copies string details
                    strcpy(info[j].ID,info[j+1].ID);
                    strcpy(info[j].e_mail,info[j+1].e_mail);
                    strcpy(info[j].phone_no,info[j+1].phone_no);

                }
                l--;
                k=1;
                break;
            }
        }


        if(k==1)
        {
        	xy_coordinates (coord, 18);
            printf("The record of %s is deleted",ch);
        }
        else
        {
        	xy_coordinates (coord, 18);
            printf("Sorry ! No record found.") ;
        }
    }
    else
    {
    	xy_coordinates (coord, 18);
        printf("Invalid Search!");
    }
    SetColor (4);
    return;

}

void search()                                   //for searching particular student detail
{
	clear_window();                             //clears the console screen 
    print_heading ("Search Student Record");
    SetColor (1);
    int i,j=0, coord=37;
    char ch[20];
    xy_coordinates (coord, 10);
    printf("Enter ID to search: ");
    fflush(stdin);                              //flush output bufer of the stream
    gets(ch);                                   //get student ID

    if((ch[0]>='a'&&ch[0]<='z')||(ch[0]>='A'&&ch[0]<='Z')||((ch[0]>='0'&&ch[0]<='9')))
    {
        for(i=0; i<l; i++)
        {
            if(strcmp(ch,info[i].ID)==0)                     //compares ID
            {
            	xy_coordinates (coord, 12);
                printf("%d  Student Information:",i+1);
                xy_coordinates (coord, 16);
				printf("Student Name: %s",info[i].name);                    //get students name
				xy_coordinates (coord, 18);
                printf("Student ID: %s",info[i].ID);                        //get students ID
                xy_coordinates (coord, 20);
                printf("Student E-Mail: %s",info[i].e_mail);                // get students email
                xy_coordinates (coord, 22);
                printf("Phone Number: %s",info[i].phone_no);         		//get students phone number
                j=1;
                break;
            }
        }
        if(j==0)
        {
        	xy_coordinates (coord, 18);
            printf("Sorry! No record found.");
        }
    }
    else
    {
    	xy_coordinates (coord, 18);
        printf("Invalid Search!");
    }
    SetColor(4);
	return;
}

void display()                                 //displays lists of students
{
	clear_window();                            //clears the console screen 
    print_heading ("All Student Record");
    SetColor (1);	
    int i, coord=37, y=10;
    for(i=0; i<l; i++)
    {
        xy_coordinates (coord, y);
        printf("%d %s : %s",i+1, info[i].ID ,info[i].name);            //displays ID and name of student
        y++;
    }
    fflush(stdin);                                        //flush output buffer of the stream
    SetColor (4);
    return;

}

void main_window()                                        //for displaying left side block
{
    char ch;
    int y=2, x=37;
    while(1)
    {
    	xy_coordinates (y,8);
        printf("Enter your choice:");
        xy_coordinates (y,10);
		printf("1. Add Student Details");
        xy_coordinates (y,12);
		printf("2. List Of All Students");
        xy_coordinates (y,14);
		printf("3. Search Student Details");
        xy_coordinates (y,16);
		printf("4. Delete Student Details");
        xy_coordinates (y,18);
		printf("5. Modify Student Details");
        xy_coordinates (y,20);
        printf("0. Exit.");
        fflush(stdin);                                    //flush output buffer of the stream
        xy_coordinates (y,22);
        scanf("%c",&ch);
        switch(ch)
        {
        case '1':
            if(l==size)
            {
            	xy_coordinates (x,18);
                printf("STORAGE FULL");
                break;
            }
            add();
            break;
        case '2':
            if(l==0)
            {
            	xy_coordinates (x,18);
                printf("The Rocord List is Empty!");
                break;
            }
            display();
            break;
        case '3':
            if(l==0)
            {
            	xy_coordinates (x,18);
                printf("The Rocord List is Empty!");
                break;
            }
            search();
            break;
        case '4':
            if(l==0)
            {
            	xy_coordinates (x,18);
                printf("The Rocord List is Empty!");
                break;
            }
            delete_record();
            break;
        case '5':
            if(l==0)
            {
            	xy_coordinates (x,18);
                printf("The Rocord List is Empty!");
                break;
            }
            modify();
            break;
        case '0':
        	xy_coordinates (x,30);
            exit(0);
        default:
        	xy_coordinates (x,18);
            printf("Invalid Input!. Please Try Again.");
            break;
        }
    }
}

void Password(void)                        //for password option
{
	char password[10]="es105";
	char d[20]=" Password Protected";
	char ch,pass[10];
	int i=0,j;
	SetColor (5);
	ClearConsoleToColors (5,14);
	xy_coordinates (10,4);
	for(j=0;j<20;j++)
	{
		Sleep(50);                         //holds the screen
		printf("*");
	}
	for(j=0;j<20;j++)
	{
		Sleep(50);                         //holds the screen
		printf("%c",d[j]);
	}
	for(j=0;j<20;j++)
	{
		Sleep(50);                         //holds the screen
		printf("*");
	}
	xy_coordinates(15,7);
	SetColor (0);
	printf("Enter Password: ");
	SetColor (4);
	while(ch!=13)
	{
		ch=getch();                        //accepts character without displaying on screen
		if(ch!=13 && ch!=8)
		{
			putch('*');
			pass[i] = ch;
			i++;
		}
	}
	pass[i] = '\0';
	if(strcmp(pass,password)==0)			//compare password
	{
		SetColor (2);
		xy_coordinates(17,14);
		printf("Password match");
		xy_coordinates(17,16);
		printf("Press any key to countinue.....");
		getch();
	}
	else
	{
		xy_coordinates (15,16);
		printf("Warning!! Incorrect Password. Try Again");
		getch();
		Password();
	}
	SetColor (4);
	return;
}

int main()                                      //main function
{
    ClearConsoleToColors(5,15);
    SetConsoleTitle("Made By: Amisha sakhare");       	//set console title
    Password ();
    system("cls");                                             		//clear full screen
    window();
    main_window();
    return 0;
}
