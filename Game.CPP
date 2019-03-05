#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<dos.h>
#include<string.h>
#include<graphics.h>
#include<process.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<bios.h>
#include<time.h>
//ctype.h for toupper

//*/*/*/*/*/*/*/---VARIABLE INITIALISATIONS---*/*/*/*/*/*/*/*/*/

int xo,yo,K,lk,pp=0,key=0,HL=0;

//Initial Co-ordinates:
float H1x=340,H1y=220; //human player 1
float H2x=420,H2y=80;  //human player 2
float H3x=420,H3y=360; //human player 3
float H4x=475,H4y=220; //human player 4
float H5x=590,H5y=220; //human player 5
float C1x=290,C1y=220; //PC player 1
float C2x=210,C2y=80;  //PC player 2
float C3x=210,C3y=360; //PC player 3
float C4x=155,C4y=220; //PC player 4
float C5x=40,C5y=220;  //PC player 5
float Bx=330,By=250; //Ball
int h=307,k=100; //Aim
int h1,k1,r; //centre and radius of the circle for PENSHO
int swing=1;
int go=0;

float gx=307,gy=140,gr=10;      //////// GOAL KEEPER COORDINATES
//int sx=180,sy=340,sr=10;      //////// SHOOTER COORDINATES
float bx=307,by=400,lbs=15;  //////// BALL2 COORDINATES

int filflg=0;

float H1co=4,H2co=4,H3co=4,H4co=4,H5co=4;
float C1co=4,C2co=4,C3co=4,C4co=4,C5co=4;

int H1co1=4,H2co1=4,H3co1=4,H4co1=4,H5co1=4;
int C1co1=4,C2co1=4,C3co1=4,C4co1=4,C5co1=4;

int conx1,conx2,conx3,conx4,conx5;
int cony1,cony2,cony3,cony4,cony5;

int NE;   //Nearest enemy

int chooseflag=0;     //To eliminate the rectangle from various screens(helpscreen,credits,etc...)

int FLAG=0,shotflag=0;
int KEEPFLAG=0;        //1 for alternate keeper

int aimsp=0;

int pbu=42,pbd=50;          // POWER SELECTOR COORDINATES
int powflg=0;
int power=0;
float no=0;

int MM=0;

double tm=0,scr=0;

//SELECTION
 int HPARR[6]={1,0,0,0,0,0};
 int strthl=0;

//WINSCRNSEL
 int WIN[2]={1,0};
 int LOS[2]={1,0};

//*/*/*/*/*/*/*/*/*/---GRAPHICS---*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/

void GRAPHICS()
{
/* request auto detection */
int gdriver = DETECT, gmode, errorcode;
int xmax, ymax;

/* initialize graphics and local variables */
initgraph(&gdriver, &gmode, "c:\\turboc3\\bgi");

/* read result of initialization */
errorcode = graphresult();
/* an error occurred */
if (errorcode != grOk)
{
   printf("Graphics error: %s\n", grapherrormsg(errorcode));
   printf("Press any key to halt:");
   getch();
   exit(1);
}
}

//*/*/*/*/*/*/*/*/*/*---GAME LOGIC---*/*/*/*/*/*/*/*/*/*/*/*/*

void FIELD_LAYOUT()
{
 setcolor(2);
 line(315,10,315,450);
 rectangle(30,10,600,450);
 rectangle(30,55,144,405);
 rectangle(30,230-70,80,230+70);           //left kick d
 rectangle(600-50,230-70,600,230+70);      //right kick d
 rectangle(600-114,55,600,405);
 circle(315,230,70);
 arc(52,230,320,40,120);                   //left outer d
 arc(578,230,140,220,120); 		    //right outer d
 circle(110,230,1.5);
 circle(110,230,2);
 circle(518,230,1.5);
 circle(518,230,2);
 setcolor(getmaxcolor());
 rectangle(30,175,18,285);
 setfillstyle(7,getmaxcolor());
 floodfill(29,176,getmaxcolor());
 rectangle(600,175,612,285);
 setfillstyle(7,getmaxcolor());
 floodfill(605,176,getmaxcolor());
}

void BALL()
{
 setcolor(14);
 circle(Bx,By,7);
 setfillstyle(1,14);
 floodfill(Bx,By,14);
}

void HP(int x,int y,int s,float &co,int &co1,int fl)
{
setcolor(getmaxcolor());

switch(co1)
{
 case 0:
  circle(x,y,s);
  line(x,y+s,x,y+(5*s));
  line(x,y+(2*s),x+(co/10*s),y+(4*s));
  line(x,y+(2*s),x-(co/10*s),y+(4*s));
  line(x,y+(5*s),x+(co/10*s),y+(7*s));
  line(x,y+(5*s),x-(co/10*s),y+(7*s));
  if (fl==1)
  {co++;co1++;}
  break;

 case 1:
  co=1;
  circle(x,y,s);
  line(x,y+s,x,y+(5*s));
  line(x,y+(2*s),x+(co/5*s),y+(4*s));
  line(x,y+(2*s),x-(co/5*s),y+(4*s));
  line(x,y+(5*s),x+(co/5*s),y+(7*s));
  line(x,y+(5*s),x-(co/5*s),y+(7*s));
  if (fl==1)
  {co++;co1++;}
  break;

 case 2:
  co=2;
  circle(x,y,s);
  line(x,y+s,x,y+(5*s));
  line(x,y+(2*s),x+(co*3/10*s),y+(4*s));
  line(x,y+(2*s),x-(co*3/10*s),y+(4*s));
  line(x,y+(5*s),x+(co*3/10*s),y+(7*s));
  line(x,y+(5*s),x-(co*3/10*s),y+(7*s));
  if (fl==1)
  {co++;co1++;}
  break;

 case 3:
  co=3;
  circle(x,y,s);
  line(x,y+s,x,y+(5*s));
  line(x,y+(2*s),x+(co*2/5*s),y+(4*s));
  line(x,y+(2*s),x-(co*2/5*s),y+(4*s));
  line(x,y+(5*s),x+(co*2/5*s),y+(7*s));
  line(x,y+(5*s),x-(co*2/5*s),y+(7*s));
  if (fl==1)
  {co++;co1++;}
  break;

 case 4:
  circle(x,y,s);
  line(x,y+s,x,y+(5*s));
  line(x,y+(2*s),x+(co/2*s),y+(4*s));
  line(x,y+(2*s),x-(co/2*s),y+(4*s));
  line(x,y+(5*s),x+(co/2*s),y+(7*s));
  line(x,y+(5*s),x-(co/2*s),y+(7*s));
  if (fl==1)
  {co=0;co1=0;}
  break;
}
}

void CP(int x,int y,int s,float &co,int &co1,int fl)
{
setcolor(YELLOW);

switch(co1)
{
 case 0:
  circle(x,y,s);
  line(x,y+s,x,y+(5*s));
  line(x,y+(2*s),x+(co/10*s),y+(4*s));
  line(x,y+(2*s),x-(co/10*s),y+(4*s));
  line(x,y+(5*s),x+(co/10*s),y+(7*s));
  line(x,y+(5*s),x-(co/10*s),y+(7*s));
  if (fl==1)
  {co++;co1++;}
  break;

 case 1:
  co=1;
  circle(x,y,s);
  line(x,y+s,x,y+(5*s));
  line(x,y+(2*s),x+(co/5*s),y+(4*s));
  line(x,y+(2*s),x-(co/5*s),y+(4*s));
  line(x,y+(5*s),x+(co/5*s),y+(7*s));
  line(x,y+(5*s),x-(co/5*s),y+(7*s));
  if (fl==1)
  {co++;co1++;}
  break;

 case 2:
  co=2;
  circle(x,y,s);
  line(x,y+s,x,y+(5*s));
  line(x,y+(2*s),x+(co*3/10*s),y+(4*s));
  line(x,y+(2*s),x-(co*3/10*s),y+(4*s));
  line(x,y+(5*s),x+(co*3/10*s),y+(7*s));
  line(x,y+(5*s),x-(co*3/10*s),y+(7*s));
  if (fl==1)
  {co++;co1++;}
  break;

 case 3:
  co=3;
  circle(x,y,s);
  line(x,y+s,x,y+(5*s));
  line(x,y+(2*s),x+(co*2/5*s),y+(4*s));
  line(x,y+(2*s),x-(co*2/5*s),y+(4*s));
  line(x,y+(5*s),x+(co*2/5*s),y+(7*s));
  line(x,y+(5*s),x-(co*2/5*s),y+(7*s));
  if (fl==1)
  {co++;co1++;}
  break;

 case 4:
  circle(x,y,s);
  line(x,y+s,x,y+(5*s));
  line(x,y+(2*s),x+(co/2*s),y+(4*s));
  line(x,y+(2*s),x-(co/2*s),y+(4*s));
  line(x,y+(5*s),x+(co/2*s),y+(7*s));
  line(x,y+(5*s),x-(co/2*s),y+(7*s));
  if (fl==1)
  {co=0;co1=0;}
  break;
}
}

void DISPLAYI()
{
FIELD_LAYOUT();
BALL();
H1co=4;H1co1=4;
HP(H1x,H1y,4,H1co,H1co1,0);
H2co=4;H2co1=4;
HP(H2x,H2y,4,H2co,H2co1,0);
H3co=4;H3co1=4;
HP(H3x,H3y,4,H3co,H3co1,0);
H4co=4;H4co1=4;
HP(H4x,H4y,4,H4co,H4co1,0);
H5co=4;H5co1=4;
HP(H5x,H5y,4,H5co,H5co1,0);
C1co=4;C1co1=4;
CP(C1x,C1y,4,C1co,C1co1,0);
C2co=4;C2co1=4;
CP(C2x,C2y,4,C2co,C2co1,0);
C3co=4;C3co1=4;
CP(C3x,C3y,4,C3co,C3co1,0);
C4co=4;C4co1=4;
CP(C4x,C4y,4,C4co,C4co1,0);
C5co=4;C5co1=4;
CP(C5x,C5y,4,C5co,C5co1,0);
}

void DISPLAYC(int pl)
{
switch(pl)
{
 case 6:
  CP(C1x,C1y,4,C1co,C1co1,0);
  CP(C2x,C2y,4,C2co,C2co1,0);
  CP(C3x,C3y,4,C3co,C3co1,0);
  CP(C4x,C4y,4,C4co,C4co1,0);
  CP(C5x,C5y,4,C5co,C5co1,1);
  break;
 case 7:
  CP(C1x,C1y,4,C1co,C1co1,0);
  CP(C2x,C2y,4,C2co,C2co1,0);
  CP(C3x,C3y,4,C3co,C3co1,0);
  CP(C4x,C4y,4,C4co,C4co1,1);
  CP(C5x,C5y,4,C5co,C5co1,0);
  break;
 case 8:
  CP(C1x,C1y,4,C1co,C1co1,0);
  CP(C2x,C2y,4,C2co,C2co1,0);
  CP(C3x,C3y,4,C3co,C3co1,1);
  CP(C4x,C4y,4,C4co,C4co1,0);
  CP(C5x,C5y,4,C5co,C5co1,0);
  break;
 case 9:
  CP(C1x,C1y,4,C1co,C1co1,0);
  CP(C2x,C2y,4,C2co,C2co1,1);
  CP(C3x,C3y,4,C3co,C3co1,0);
  CP(C4x,C4y,4,C4co,C4co1,0);
  CP(C5x,C5y,4,C5co,C5co1,0);
  break;
 case 10:
  CP(C1x,C1y,4,C1co,C1co1,1);
  CP(C2x,C2y,4,C2co,C2co1,0);
  CP(C3x,C3y,4,C3co,C3co1,0);
  CP(C4x,C4y,4,C4co,C4co1,0);
  CP(C5x,C5y,4,C5co,C5co1,0);
  break;
 default:
  CP(C1x,C1y,4,C1co,C1co1,0);
  CP(C2x,C2y,4,C2co,C2co1,0);
  CP(C3x,C3y,4,C3co,C3co1,0);
  CP(C4x,C4y,4,C4co,C4co1,0);
  CP(C5x,C5y,4,C5co,C5co1,0);
}
}

void DISPLAY(int pl)
{
FIELD_LAYOUT();
BALL();
switch(pl)
{
 case 1:
  HP(H1x,H1y,4,H1co,H1co1,1);
  HP(H2x,H2y,4,H2co,H2co1,0);
  HP(H3x,H3y,4,H3co,H3co1,0);
  HP(H4x,H4y,4,H4co,H4co1,0);
  HP(H5x,H5y,4,H5co,H5co1,0);
  break;
 case 2:
  HP(H1x,H1y,4,H1co,H1co1,0);
  HP(H2x,H2y,4,H2co,H2co1,1);
  HP(H3x,H3y,4,H3co,H3co1,0);
  HP(H4x,H4y,4,H4co,H4co1,0);
  HP(H5x,H5y,4,H5co,H5co1,0);
  break;
 case 3:
  HP(H1x,H1y,4,H1co,H1co1,0);
  HP(H2x,H2y,4,H2co,H2co1,0);
  HP(H3x,H3y,4,H3co,H3co1,1);
  HP(H4x,H4y,4,H4co,H4co1,0);
  HP(H5x,H5y,4,H5co,H5co1,0);
  break;
 case 4:
  HP(H1x,H1y,4,H1co,H1co1,0);
  HP(H2x,H2y,4,H2co,H2co1,0);
  HP(H3x,H3y,4,H3co,H3co1,0);
  HP(H4x,H4y,4,H4co,H4co1,1);
  HP(H5x,H5y,4,H5co,H5co1,0);
  break;
 case 5:
  HP(H1x,H1y,4,H1co,H1co1,0);
  HP(H2x,H2y,4,H2co,H2co1,0);
  HP(H3x,H3y,4,H3co,H3co1,0);
  HP(H4x,H4y,4,H4co,H4co1,0);
  HP(H5x,H5y,4,H5co,H5co1,1);
  break;
 default:
  HP(H1x,H1y,4,H1co,H1co1,0);
  HP(H2x,H2y,4,H2co,H2co1,0);
  HP(H3x,H3y,4,H3co,H3co1,0);
  HP(H4x,H4y,4,H4co,H4co1,0);
  HP(H5x,H5y,4,H5co,H5co1,0);
}
}

float ANGLE(float x1,float y1,float x2,float y2,float x3,float y3)
{
float m1,m2,m,Q,q;
if(x1!=x2 && x2!=x3)
 {
  m1=((y2-y1)/(x2-x1));
  m2=((y2-y3)/(x2-x3));
  m=(m1-m2)/(1+(m1*m2));
  Q=atan(m);
  if(Q<0)
   Q=-Q;
  return Q;
 }
else if(x1==x2 && x2!=x3)
 {
  m1=((y2-y3)/(x2-x3));
  m2=0;
  m=(m1-m2)/(1+(m1*m2));
  q=atan(m);
  if(q<0)
   q=-q;
  Q=(3.14/2)-q;
  return Q;
 }
else if(x1!=x2 && x2==x3)
 {
  m1=((y2-y1)/(x2-x1));
  m2=0;
  m=(m1-m2)/(1+(m1*m2));
  q=atan(m);
  if(q<0)
   q=-q;
  Q=(3.14/2)-q;
  return Q;
 }
else
 {
  Q=0;
  return Q;
 }
}

void XLESS(float zx,float zy,float mx,float my)
{
if(conx1==2)  //i.e equality scenario: H1x=xo
 conx1=0;     //because here case 0 is rejected i.e we dont want to consider equality scenario
if(conx2==2)
 conx2=0;
if(conx3==2)
 conx3=0;
if(conx4==2)
 conx4=0;
if(conx5==2)
 conx5=0;

switch(conx1)
{
 case 1: switch(conx2)
	   {
	    case 1: if(ANGLE(H1x,H1y,zx,zy,mx,my)<=ANGLE(H2x,H2y,zx,zy,mx,my))
		      {
		       lacde:
		       switch(conx3)
			{
			 case 1:  if(ANGLE(H1x,H1y,zx,zy,mx,my)<=ANGLE(H3x,H3y,zx,zy,mx,my))
				   {
				    lade:
				    switch(conx4)
				     {
				      case 1: if(ANGLE(H1x,H1y,zx,zy,mx,my)<=ANGLE(H4x,H4y,zx,zy,mx,my))
						{
						 lae:
						 switch(conx5)
						  {
						   case 1: if(ANGLE(H1x,H1y,zx,zy,mx,my)<=ANGLE(H5x,H5y,zx,zy,mx,my))
							     pp=1;
							   else
							     pp=5;
							   break;
						   case 0: pp=1;
						  }
						}
					      else
						{
						 lde:
						 switch(conx5)
						  {
						   case 1: if(ANGLE(H4x,H4y,zx,zy,mx,my)<=ANGLE(H5x,H5y,zx,zy,mx,my))
							     pp=4;
							   else
							     pp=5;
							   break;
						   case 0: pp=4;
						  }
						}
					      break;
				       case 0: goto lae;
				     }
				   }
				  else
				   {
				    lcde:
				    switch(conx4)
				     {
				      case 1: if(ANGLE(H3x,H3y,zx,zy,mx,my)<=ANGLE(H4x,H4y,zx,zy,mx,my))
						{
						 lce:
						 switch(conx5)
						  {
						   case 1:  if(ANGLE(H3x,H3y,zx,zy,mx,my)<=ANGLE(H5x,H5y,zx,zy,mx,my))
							     pp=3;
							    else
							     pp=5;
							   break;
						   case 0: pp=3;
						  }
						}
					      else
						goto lde;
					      break;
				      case 0: goto lce;
				     }
				   }
				 break;
			 case 0: goto lade;
			}
		      }
		     else
		      {
		       lbcde:
		       switch(conx3)
			{
			 case 1:  if(ANGLE(H2x,H2y,zx,zy,mx,my)<=ANGLE(H3x,H3y,zx,zy,mx,my))
				   {
				    lbde:
				    switch(conx4)
				     {
				      case 1: if(ANGLE(H2x,H2y,zx,zy,mx,my)<=ANGLE(H4x,H4y,zx,zy,mx,my))
						{
						 lbe:
						 switch(conx5)
						  {
						   case 1: if(ANGLE(H2x,H2y,zx,zy,mx,my)<=ANGLE(H5x,H5y,zx,zy,mx,my))
							     pp=2;
							    else
							     pp=5;
							   break;
						   case 0: pp=2;
							   break;
						  }
						}
					      else
						goto lde;
					      break;
				      case 0: goto lbe;
				     }
				   }
				  else
				   goto lcde;
				 break;
			 case 0: goto lbde;
			}
		      }
		    break;
	    case 0: goto lacde;
	   }
	 break;
 case 0: switch(conx2)
	   {
	    case 1: goto lbcde;
	    case 0: switch(conx3)
		    {
		      case 1: goto lcde;
		      case 0: switch(conx4)
			       {
				case 1: goto lde;
				case 0: switch(conx5)
					 {
					  case 1: pp=5;
					 }
			       }
		    }
	   }
}
}

void XMORE(float zx,float zy,float mx,float my)
{
if(conx1==2)  //i.e equality scenario: H1x=xo
 conx1=1;
if(conx2==2)
 conx2=1;
if(conx3==2)
 conx3=1;
if(conx4==2)
 conx4=1;
if(conx5==2)
 conx5=1;

switch(conx1)
{
 case 0: switch(conx2)
	   {
	    case 0:  if(ANGLE(H1x,H1y,zx,zy,mx,my)<=ANGLE(H2x,H2y,zx,zy,mx,my))
		      {
		       lacde:
		       switch(conx3)
			{
			 case 0:  if(ANGLE(H1x,H1y,zx,zy,mx,my)<=ANGLE(H3x,H3y,zx,zy,mx,my))
				   {
				    lade:
				    switch(conx4)
				     {
				      case 0: if(ANGLE(H1x,H1y,zx,zy,mx,my)<=ANGLE(H4x,H4y,zx,zy,mx,my))
						{
						 lae:
						 switch(conx5)
						  {
						   case 0: if(ANGLE(H1x,H1y,zx,zy,mx,my)<=ANGLE(H5x,H5y,zx,zy,mx,my))
							     pp=1;
							   else
							     pp=5;
							   break;
						   case 1: pp=1;
						  }
						}
					      else
						{
						 lde:
						 switch(conx5)
						  {
						   case 0: if(ANGLE(H4x,H4y,zx,zy,mx,my)<=ANGLE(H5x,H5y,zx,zy,mx,my))
							     pp=4;
							   else
							     pp=5;
							   break;
						   case 1: pp=4;
						  }
						}
					      break;
				       case 1: goto lae;
				     }
				   }
				  else
				   {
				    lcde:
				    switch(conx4)
				     {
				      case 0: if(ANGLE(H3x,H3y,zx,zy,mx,my)<=ANGLE(H4x,H4y,zx,zy,mx,my))
						{
						 lce:
						 switch(conx5)
						  {
						   case 0:  if(ANGLE(H3x,H3y,zx,zy,mx,my)<=ANGLE(H5x,H5y,zx,zy,mx,my))
							     pp=3;
							    else
							     pp=5;
							   break;
						   case 1: pp=3;
						  }
						}
					      else
						goto lde;
					      break;
				      case 1: goto lce;
				     }
				   }
				 break;
			 case 1: goto lade;
			}
		      }
		     else
		      {
		       lbcde:
		       switch(conx3)
			{
			 case 0:  if(ANGLE(H2x,H2y,zx,zy,mx,my)<=ANGLE(H3x,H3y,zx,zy,mx,my))
				   {
				    lbde:
				    switch(conx4)
				     {
				      case 0: if(ANGLE(H2x,H2y,zx,zy,mx,my)<=ANGLE(H4x,H4y,zx,zy,mx,my))
						{
						 lbe:
						 switch(conx5)
						  {
						   case 0: if(ANGLE(H2x,H2y,zx,zy,mx,my)<=ANGLE(H5x,H5y,zx,zy,mx,my))
							     pp=2;
							    else
							     pp=5;
							   break;
						   case 1: pp=2;
							   break;
						  }
						}
					      else
						goto lde;
					      break;
				      case 1: goto lbe;
				     }
				   }
				  else
				   goto lcde;
				 break;
			 case 1: goto lbde;
			}
		      }
		    break;
	    case 1: goto lacde;
	   }
	 break;
 case 1:  switch(conx2)
	   {
	    case 0: goto lbcde;
	    case 1: switch(conx3)
		    {
		      case 0: goto lcde;
		      case 1: switch(conx4)
			       {
				case 0: goto lde;
				case 1: switch(conx5)
					 {
					  case 0: pp=5;
					 }
			       }
		    }
	   }
}
}

int dis[6];
void ENEIDEN(float &xo,float &yo)
{
//xo yo are coordinates of ball

dis[1]=sqrt(pow((xo-C1x),2)+pow((yo-C1y),2));
dis[2]=sqrt(pow((xo-C2x),2)+pow((yo-C2y),2));
dis[3]=sqrt(pow((xo-C3x),2)+pow((yo-C3y),2));
dis[4]=sqrt(pow((xo-C4x),2)+pow((yo-C4y),2));
dis[5]=sqrt(pow((xo-C5x),2)+pow((yo-C5y),2));
NE=1;
if(dis[2]<dis[NE]) NE=2;
if(dis[3]<dis[NE]) NE=3;
if(dis[4]<dis[NE]) NE=4;
if(dis[5]<dis[NE]) NE=5;
}

void ENE1ITE(float &ex,float &ey,float sp)
{
int xfl=0,yfl=0;
float xdis,ydis;
float drs,xfr,yfr;
float tbx,tby;    //temporary ball coordinates for calculations

tbx=Bx+10;
tby=By-30;

if(ex>tbx)
 xfl=1;          //flag is 1 if player is towards the right of the ball
if(ey>tby)
 yfl=1;          //flag is 1 if player is below the ball

xdis=fabs(tbx-ex);
ydis=fabs(tby-ey);

drs=sqrt((xdis*xdis)+(ydis*ydis));

xfr=xdis/drs;
yfr=ydis/drs;

ex+=(xfl==1)?(-sp*xfr):(sp*xfr);
ey+=(yfl==1)?(-sp*yfr):(sp*yfr);

if(xdis<=xfr && ydis<=yfr)
  FLAG=1;
}

void ENE1CHRG(float sp=1.0)
{
ENEIDEN(Bx,By);
switch(NE)
 {
  case 1:
   ENE1ITE(C1x,C1y,sp);
   break;
  case 2:
   ENE1ITE(C2x,C2y,sp);
   break;
  case 3:
   ENE1ITE(C3x,C3y,sp);
   break;
  case 4:
   ENE1ITE(C4x,C4y,sp);
   break;
  case 5:
   ENE1ITE(C5x,C5y,sp);
   break;
 }
}

void BALLPASS(float kx,float ky)
{
int idx,idy;
float Do,dx,dy,fx,fy;

kx=kx-10; //so that ball goes at leg of player
ky=ky+30;

if(kx>=Bx)
 idx=1;
else
 idx=0;

if(ky>=By)
 idy=1;
else
 idy=0;

dx=(kx-Bx);
 if(dx<0)
  dx=-dx;
dy=(ky-By);
 if(dy<0)
  dy=-dy;

Do=pow((pow(dx,2)+pow(dy,2)),0.5);

fx=dx/Do;
fy=dy/Do;

for(int j1=0;;j1++)
 {
  if(idx==1)
   Bx=Bx+fx;
  else
   Bx=Bx-fx;
  if(idy==1)
   By=By+fy;
  else
   By=By-fy;
  ENE1CHRG(0.7);
  if(FLAG==1)
   break;
  cleardevice();
  DISPLAYI();
  delay(10);
  tm+=0.01;
  if(fabs(Bx-kx)<fx)
   break;
 }
}

void MOVEMENT(float &xo,float &yo,int pl)
{
int i1;

a:
K=bioskey(0);

if(K!=6512) //i.e player has not pressed 'p' key
{
switch(K)
{
 case 19200: for(i1=0;;i1++) //key 4 on nums pad for LEFT
	      {
	      lk=4;
	       cleardevice();
	       xo--;
	       Bx--;
	       ENE1CHRG(1.3);
	       DISPLAY(pl);
	       DISPLAYC(pl);
	       delay(30);
	       tm+=0.03;
	       if(Bx>30 && Bx<80 && By>160 && By<300)
		{
		 shotflag=1;
		 break;  // breaks from for loop
		}
	       if(Bx<30 || Bx>600 || By<10 || By>450)
		FLAG=1;
	       if(FLAG==1) //As we have to also include that case where flag becomes 1 in ENE1CHRG
		break;
	       if (bioskey(1)!=0)
		{
		 cleardevice();
		 DISPLAYI();
		 goto a;
		}
	      }
	     break;

 case 19712: for(i1=0;;i1++)//key 6 on nums pad for RIGHT
	      {
	       lk=6;
	       cleardevice();
	       xo++;
	       Bx++;
	       ENE1CHRG(1.3);
	       DISPLAY(pl);
	       DISPLAYC(pl);
	       delay(30);
	       tm+=0.03;
	       if(Bx>30 && Bx<80 && By>160 && By<300)
		{
		 shotflag=1;
		 break;
		}
	       if(Bx<30 || Bx>600 || By<10 || By>450)
		FLAG=1;
	       if(FLAG==1)
		break;
	       if (bioskey(1)!=0)
		{
		 cleardevice();
		 DISPLAYI();
		 goto a;
		}
	      }
	     break;

 case 20480: for(i1=0;;i1++)//key 2 on nums pad for DOWN
	      {
	       lk=2;
	       cleardevice();
	       yo++;
	       By++;
	       ENE1CHRG(1.3);
	       DISPLAY(pl);
	       DISPLAYC(pl);
	       delay(30);
	       tm+=0.03;
	       if(Bx>30 && Bx<80 && By>160 && By<300)
		{
		 shotflag=1;
		 break;
		}
	       if(Bx<30 || Bx>600 || By<10 || By>450)
		FLAG=1;
	       if(FLAG==1)
		break;
	       if (bioskey(1)!=0)
		{
		 cleardevice();
		 DISPLAYI();
		 goto a;
		}
	      }
	     break;

 case 18432: for(i1=0;;i1++)//key 8 on nums pad for UP
	      {
	       lk=8;
	       cleardevice();
	       yo--;
	       By--;
	       ENE1CHRG(1.3);
	       DISPLAY(pl);
	       DISPLAYC(pl);
	       delay(30);
	       tm+=0.03;
	       if(Bx>30 && Bx<80 && By>160 && By<300)
		{
		 shotflag=1;
		 break;
		}
	       if(Bx<30 || Bx>600 || By<10 || By>450)
		FLAG=1;
	       if(FLAG==1)
		break;
	       if (bioskey(1)!=0)
		{
		 cleardevice();
		 DISPLAYI();
		 goto a;
		}
	      }
	     break;

 case 18176: for(i1=0;;i1++)//key 7 on nums pad for DIAGONAL UP-LEFT
	      {
	       lk=7;
	       cleardevice();
	       xo--;
	       yo--;
	       Bx--;
	       By--;
	       ENE1CHRG(1.5);
	       DISPLAY(pl);
	       DISPLAYC(pl);
	       delay(35);
	       tm+=0.035;
	       if(Bx>30 && Bx<80 && By>160 && By<300)
		{
		 shotflag=1;
		 break;
		}
	       if(Bx<30 || Bx>600 || By<10 || By>450)
		FLAG=1;
	       if(FLAG==1)
		break;
	       if (bioskey(1)!=0)
		{
		 cleardevice();
		 DISPLAYI();
		 goto a;
		}
	      }
	     break;

 case 18688: for(i1=0;;i1++)//key 9 on nums pad for DIAGONAL UP-RIGHT
	      {
	       lk=9;
	       cleardevice();
	       xo++;
	       yo--;
	       Bx++;
	       By--;
	       ENE1CHRG(1.5);
	       DISPLAY(pl);
	       DISPLAYC(pl);
	       delay(35);
	       tm+=0.035;
	       if(Bx>30 && Bx<80 && By>160 && By<300)
		{
		 shotflag=1;
		 break;
		}
	       if(Bx<30 || Bx>600 || By<10 || By>450)
		FLAG=1;
	       if(FLAG==1)
		break;
	       if (bioskey(1)!=0)
		{
		 cleardevice();
		 DISPLAYI();
		 goto a;
		}
	      }
	     break;

 case 20224: for(i1=0;;i1++)//key 1 on nums pad for DIAGONAL DOWN-LEFT
	      {
	       lk=1;
	       cleardevice();
	       xo--;
	       yo++;
	       Bx--;
	       By++;
	       ENE1CHRG(1.5);
	       DISPLAY(pl);
	       DISPLAYC(pl);
	       delay(35);
	       tm+=0.035;
	       if(Bx>30 && Bx<80 && By>160 && By<300)
		{
		 shotflag=1;
		 break;
		}
	       if(Bx<30 || Bx>600 || By<10 || By>450)
		FLAG=1;
	       if(FLAG==1)
		break;
	       if (bioskey(1)!=0)
		{
		 cleardevice();
		 DISPLAYI();
		 goto a;
		}
	      }
	     break;

 case 20736: for(i1=0;;i1++)//key 3 on nums pad for DIAGONAL DOWN-RIGHT
	      {
	       lk=3;
	       cleardevice();
	       xo++;
	       yo++;
	       Bx++;
	       By++;
	       ENE1CHRG(1.5);
	       DISPLAY(pl);
	       DISPLAYC(pl);
	       delay(35);
	       tm+=0.035;
	       if(Bx>30 && Bx<80 && By>160 && By<300)
		{
		 shotflag=1;
		 break;
		}
	       if(Bx<30 || Bx>600 || By<10 || By>450)
		FLAG=1;
	       if(FLAG==1)
		break;
	       if (bioskey(1)!=0)
		{
		 cleardevice();
		 DISPLAYI();
		 goto a;
		}
	      }
	     break;

 default: goto a;
}
}

if(shotflag!=1 && FLAG!=1)
{
conx1=2;conx2=2;conx3=2;conx4=2;conx5=2;
cony1=2;cony2=2;cony3=2;cony4=2;cony5=2;

if(H1x<xo)
 conx1=1;
if(H1x>xo)
 conx1=0;
if(H2x<xo)
 conx2=1;
if(H2x>xo)
 conx2=0;
if(H3x<xo)
 conx3=1;
if(H3x>xo)
 conx3=0;
if(H4x<xo)
 conx4=1;
if(H4x>xo)
 conx4=0;
if(H5x<xo)
 conx5=1;
if(H5x>xo)
 conx5=0;

if(H1y<yo)
 cony1=1;
if(H1y>yo)
 cony1=0;
if(H2y<yo)
 cony2=1;
if(H2y>yo)
 cony2=0;
if(H3y<yo)
 cony3=1;
cout<<"H3y: "<<H3y;
cout<<"yo: "<<yo;
if(H3y>yo)
 cony3=0;
if(H4y<yo)
 cony4=1;
if(H4y>yo)
 cony4=0;
if(H5y<yo)
 cony5=1;
if(H5y>yo)
 cony5=0;

float refx1=0.0,refx2=0.0,refy1=0.0,refy2=0.0;

int select;
select=0;

switch(lk)
{
case 4: XLESS(xo,yo,0,yo);
	break;

case 6: XMORE(xo,yo,1000,yo);
	break;

case 7: XLESS(xo,yo,xo-yo,0);
	break;

case 1: XLESS(xo,yo,0,xo+yo);
	break;

case 9: XMORE(xo,yo,xo+yo,0);
	break;

case 3: XMORE(xo,yo,xo+1000,yo+1000);
	break;

case 8: pp=0;
	if(cony1!=1)
	 conx1=0;     //so that it gets rejected in XLESS
	if(cony2!=1)
	 conx2=0;
	if(cony3!=1)
	 conx3=0;
	if(cony4!=1)
	 conx4=0;
	if(cony5!=1)
	 conx5=0;
	XLESS(xo,yo,xo,0);
	if(pp==1)
	 {refx1=H1x;
	 refy1=H1y;}
	else if(pp==2)
	 {refx1=H2x;
	 refy1=H2y;}
	else if(pp==3)
	 {refx1=H3x;
	 refy1=H3y;}
	else if(pp==4)
	 {refx1=H4x;
	 refy1=H4y;}
	else if(pp==5)
	 {refx1=H5x;
	 refy1=H5y;}

	if(cony1!=1)
	 conx1=1;     //so that it gets rejected in XMORE
	if(cony2!=1)
	 conx2=1;
	if(cony3!=1)
	 conx3=1;
	if(cony4!=1)
	 conx4=1;
	if(cony5!=1)
	 conx5=1;
	pp=0;
	XMORE(xo,yo,xo,0);
	if(pp==1)
	 {refx2=H1x;
	 refy2=H1y;}
	else if(pp==2)
	 {refx2=H2x;
	 refy2=H2y;}
	else if(pp==3)
	 {refx2=H3x;
	 refy2=H3y;}
	else if(pp==4)
	 {refx2=H4x;
	 refy2=H4y;}
	else if(pp==5)
	 {refx2=H5x;
	 refy2=H5y;}

	if(refx1==0.0)
	 {
	  if(refx2!=0.0)
	   {
	    BALLPASS(refx2,refy2);
	    select=2;
	   }
	 }
	else
	 {
	  if(refx2!=0.0)
	   {
	    if(ANGLE(refx1,refy1,xo,yo,xo,0)<=ANGLE(refx2,refy2,xo,yo,xo,0))
	     {
	      BALLPASS(refx1,refy1);
	      select=1;
	     }
	    else
	     {
	      BALLPASS(refx2,refy2);
	      select=2;
	     }
	   }
	  else
	   {
	    BALLPASS(refx1,refy1);
	    select=1;
	   }
	 }
	 break;

case 2: pp=0;
	if(cony1!=0)
	 conx1=0;     //so that it gets rejected in XLESS
	if(cony2!=0)
	 conx2=0;
	if(cony3!=0)
	 conx3=0;
	if(cony4!=0)
	 conx4=0;
	if(cony5!=0)
	 conx5=0;
	XLESS(xo,yo,xo,2000);
	cout<<"XLESS : "<<pp;
	if(pp==1)
	 {refx1=H1x;
	 refy1=H1y;}
	else if(pp==2)
	 {refx1=H2x;
	 refy1=H2y;}
	else if(pp==3)
	 {refx1=H3x;
	 refy1=H3y;}
	else if(pp==4)
	 {refx1=H4x;
	 refy1=H4y;}
	else if(pp==5)
	 {refx1=H5x;
	 refy1=H5y;}

	if(cony1!=0)
	 conx1=1;     //so that it gets rejected in XMORE
	if(cony2!=0)
	 conx2=1;
	if(cony3!=0)
	 conx3=1;
	if(cony4!=0)
	 conx4=1;
	if(cony5!=0)
	 conx5=1;
	pp=0;
	XMORE(xo,yo,xo,2000);
	cout<<"XMORE: "<<pp;
	if(pp==1)
	 {refx2=H1x;
	 refy2=H1y;}
	else if(pp==2)
	 {refx2=H2x;
	 refy2=H2y;}
	else if(pp==3)
	 {refx2=H3x;
	 refy2=H3y;}
	else if(pp==4)
	 {refx2=H4x;
	 refy2=H4y;}
	else if(pp==5)
	 {refx2=H5x;
	 refy2=H5y;}

	 cout<<"refx1: "<<refx1<<" refy1: "<<refy1;
	 cout<<"refx2: "<<refx2<<" refy2: "<<refy2;

	if(refx1==0.0)
	 {
	  if(refx2!=0.0)
	   {
	    BALLPASS(refx2,refy2);
	    select=2;
	   }
	 }
	else
	 {
	  if(refx2!=0.0)
	   {
	    if(ANGLE(refx1,refy1,xo,yo,xo,2000)<=ANGLE(refx2,refy2,xo,yo,xo,2000)) // > sign because we r passing down & magnitude of slope obtained will be opp to that in normal coordinate plane
	     {
	      BALLPASS(refx1,refy1);
	      select=1;
	     }
	    else
	     {
	      BALLPASS(refx2,refy2);
	      select=2;
	     }
	   }
	  else
	   {
	    BALLPASS(refx1,refy1);
	    select=1;
	   }
	 }
	 break;
}

if(select==0)
{
if (pp==1)
 BALLPASS(H1x,H1y);
else if (pp==2)
 BALLPASS(H2x,H2y);
else if(pp==3)
 BALLPASS(H3x,H3y);
else if(pp==4)
 BALLPASS(H4x,H4y);
else if(pp==5)
 BALLPASS(H5x,H5y);
}

else if(select==1)
{
if(refx1==H1x && refy1==H1y)
 pp=1;
else if(refx1==H2x && refy1==H2y)
 pp=2;
else if(refx1==H3x && refy1==H3y)
 pp=3;
else if(refx1==H4x && refy1==H4y)
 pp=4;
else if(refx1==H5x && refy1==H5y)
 pp=5;
}

else if(select==2)
{
if(refx2==H1x && refy2==H1y)
 pp=1;
else if(refx2==H2x && refy2==H2y)
 pp=2;
else if(refx2==H3x && refy2==H3y)
 pp=3;
else if(refx2==H4x && refy2==H4y)
 pp=4;
else if(refx2==H5x && refy2==H5y)
 pp=5;
}
}
}

void MOVREF(char Player[5])
{
if(strcmpi(Player,"hp1")==0)
 MOVEMENT(H1x,H1y,1);
else if(strcmpi(Player,"hp2")==0)
 MOVEMENT(H2x,H2y,2);
else if(strcmpi(Player,"hp3")==0)
 MOVEMENT(H3x,H3y,3);
else if(strcmpi(Player,"hp4")==0)
 MOVEMENT(H4x,H4y,4);
else if(strcmpi(Player,"hp5")==0)
 MOVEMENT(H5x,H5y,5);
else if(strcmpi(Player,"cp1")==0)
 MOVEMENT(C5x,C5y,6);
else if(strcmpi(Player,"cp2")==0)
 MOVEMENT(C5x,C5y,7);
else if(strcmpi(Player,"cp3")==0)
 MOVEMENT(C5x,C5y,8);
else if(strcmpi(Player,"cp4")==0)
 MOVEMENT(C5x,C5y,9);
else if(strcmpi(Player,"cp5")==0)
 MOVEMENT(C5x,C5y,10);
}

void GAMERUN()
{
MOVREF("hp1");

label:
cout<<"\nfinal pp: "<<pp;
if(pp==1)
 MOVREF("hp1");
else if(pp==2)
 MOVREF("hp2");
else if(pp==3)
 MOVREF("hp3");
else if(pp==4)
 MOVREF("hp4");
else if(pp==5)
 MOVREF("hp5");

if(shotflag!=1 && FLAG!=1)
 goto label;
}

void AIM(int h,int k)
{
int T1[6]={h,k-2,h-7,(k-2)-12,h+7,(k-2)-12};
setfillstyle(1,YELLOW);
fillpoly(3,T1);

int T2[6]={h,k+2,h-7,(k+2)+12,h+7,(k+2)+12};
setfillstyle(1,YELLOW);
fillpoly(3,T2);

int T3[6]={h-2,k,(h-2)-12,k-7,(h-2)-12,k+7};
setfillstyle(1,YELLOW);
fillpoly(3,T3);

int T4[6]={h+2,k,(h+2)+12,k-7,(h+2)+12,k+7};
setfillstyle(1,YELLOW);
fillpoly(3,T4);
}

void GOALPOST()
{
 //GOAL POST NET
 setcolor(7);
 rectangle(145,80,475,290);
 setfillstyle(8,7);     //////////CAN ALSO TRY 9 FOR PATTERN NO.
 floodfill(146,101,7);

 //GOAL POST BARS
 setcolor(WHITE);
 for(int fbar1=130;fbar1<=145;fbar1++)
 {
  line(fbar1,60,fbar1,290);
 }
 for(int fbar2=475;fbar2<=490;fbar2++)
 {
  line(fbar2,60,fbar2,290);
 }
 for(int bbar1=165;bbar1<=174;bbar1++)
 {
  line(bbar1,110,bbar1,290);
 }
 for(int bbar2=441;bbar2<=450;bbar2++)
 {
  line(bbar2,110,bbar2,290);
 }

 //UPPER BARS
 int UpRiBa[8]={473,60,488,60,450,110,441,110};
 setfillstyle(1,WHITE);
 fillpoly(4,UpRiBa);
 int UpLeBa[8]={130,60,150,60,174,110,165,110};
 fillpoly(4,UpLeBa);

 //CROSSBAR
 int crossbar;
 for(crossbar=60;crossbar<=80;crossbar++)
 {
  line(130,crossbar,490,crossbar);
 }

 //BACKBAR
 int backbar;
 for(backbar=109;backbar<=118;backbar++)
 {
  line(174,backbar,441,backbar);
 }
}

void OUTFIELD()
{
setcolor(GREEN);
rectangle(0,290,640,580);
setfillstyle(9,GREEN);
floodfill(25,335,GREEN);
}

void BALL2(float bx, float by, int lbs)
{
setcolor(getmaxcolor());

//BALL

circle(bx,by,lbs);

 //PATERN IN BALL
 int polyhex1[8]={bx-0.9*lbs,by+0.4*lbs,bx-0.5*lbs,by+0.2*lbs,bx-0.5*lbs,by-0.2*lbs,bx-0.9*lbs,by-0.4*lbs};
 drawpoly(4,polyhex1);

 int polyhex2[8]={bx-0.9*lbs,by-0.4*lbs,bx-0.5*lbs,by-0.2*lbs,bx,by-0.5*lbs,bx,by-lbs};
 drawpoly(4,polyhex2);

 int polyhex3[8]={bx,by-lbs,bx,by-0.5*lbs,bx+0.5*lbs,by-0.2*lbs,bx+0.9*lbs,by-0.4*lbs};
 drawpoly(4,polyhex3);

 int polyhex4[8]={bx+0.9*lbs,by+0.4*lbs,bx+0.5*lbs,by+0.2*lbs,bx+0.5*lbs,by-0.2*lbs,bx+0.9*lbs,by-0.4*lbs};
 drawpoly(4,polyhex4);

 int polyhex5[8]={bx,by+lbs,bx,by+0.5*lbs,bx+0.5*lbs,by+0.2*lbs,bx+0.9*lbs,by+0.4*lbs};
 drawpoly(4,polyhex5);

 int polyhex6[8]={bx-0.9*lbs,by+0.4*lbs,bx-0.5*lbs,by+0.2*lbs,bx,by+0.5*lbs,bx,by+lbs};
 drawpoly(4,polyhex6);

 if(filflg==0)
 {
  setcolor(WHITE);
  setfillstyle(1,WHITE);
  floodfill(bx-0.9*lbs,by,WHITE);
  floodfill(bx+1,by-0.5*lbs,WHITE);
  floodfill(bx+1,by+0.5*lbs,WHITE);
  filflg=21898;
 }

 else
 {
  setcolor(WHITE);
  setfillstyle(1,WHITE);
  floodfill(bx+0.9*lbs,by,WHITE);
  floodfill(bx-1,by-0.5*lbs,WHITE);
  floodfill(bx-1,by+0.5*lbs,WHITE);
  filflg=0;
 }
}

void KEEPER(int gx,int gy,int gr)
{
 //FACE
 setcolor(12);

 circle(gx,gy,gr);
 setfillstyle(1,12);
 floodfill(gx,gy,12);

 //NECK
 setcolor(LIGHTRED);

 rectangle(gx-5,gy+10,gx+5,gy+17);
 setfillstyle(1,LIGHTRED);
 floodfill(gx-4,gy+16,LIGHTRED);

 //TORSO
 setcolor(BLUE);

 int torso[8]={gx-25,gy+17,gx+25,gy+17,gx+10,gy+80,gx-10,gy+80};
 setfillstyle(11,BLUE);
 fillpoly(4,torso);

 setcolor(RED);

 int shrtptrn[8]={gx-21,gy+33,gx+21,gy+33,gx+17,gy+48,gx-17,gy+48};
 setfillstyle(1,RED);
 fillpoly(4,shrtptrn);

 if(KEEPFLAG!=1)
 {
 //SLEEVES
 setcolor(RED);

 int sl1[8]={gx-37,gy+24,gx-25,gy+17,gx-23,gy+30,gx-32,gy+34};
 setfillstyle(1,RED);
 fillpoly(4,sl1);

 int sl2[8]={gx+25,gy+17,gx+36,gy+24,gx+32,gy+34,gx+23,gy+30};
 setfillstyle(1,RED);
 fillpoly(4,sl2);

 //HANDS
 setcolor(12);

 int lefthand[8]={gx-48,gy+29,gx-38,gy+24,gx-34,gy+33,gx-44,gy+36};
 setfillstyle(1,LIGHTRED);
 fillpoly(4,lefthand);

 int righthand[8]={gx+37,gy+25,gx+47,gy+28,gx+44,gy+36,gx+32,gy+33};
 setfillstyle(1,LIGHTRED);
 fillpoly(4,righthand);

 int leftarm[8]={gx-57,gy+29,gx-48,gy+29,gx-44,gy+36,gx-57,gy+36};
 setfillstyle(1,LIGHTRED);
 fillpoly(4,leftarm);

 int rightarm[8]={gx+47,gy+28,gx+56,gy+28,gx+56,gy+35,gx+44,gy+35};
 setfillstyle(1,LIGHTRED);
 fillpoly(4,rightarm);

 //GLOVES
 setcolor(YELLOW);

 int lglove[10]={gx-57,gy+29,gx-57,gy+36,gx-61,gy+36,gx-68,gy+39,
		 gx-68,gy+29};
 setfillstyle(1,14);
 fillpoly(5,lglove);

 int rglove[10]={gx+56,gy+28,gx+67,gy+28,gx+67,gy+38,gx+63,gy+35,
		 gx+56,gy+35};
 setfillstyle(1,14);
 fillpoly(5,rglove);
 }

 else if(KEEPFLAG==1)
 {
  //SLEEVES
 setcolor(RED);

 int sl1[8]={gx-34,gy+10,gx-25,gy+17,gx-23,gy+30,gx-30,gy+24};
 setfillstyle(1,RED);
 fillpoly(4,sl1);

 int sl2[8]={gx+27,gy+17,gx+35,gy+9,gx+30,gy+24,gx+24,gy+30};
 setfillstyle(1,RED);
 fillpoly(4,sl2);

 //HANDS
 setcolor(12);

 int lefthand[8]={gx-38,gy+9,gx-35,gy+11,gx-32,gy+23,gx-48,gy+9};
 setfillstyle(1,LIGHTRED);
 fillpoly(4,lefthand);

 int righthand[8]={gx+35,gy+11,gx+38,gy+9,gx+48,gy+9,gx+32,gy+23};
 setfillstyle(1,LIGHTRED);
 fillpoly(4,righthand);

 int leftarm[8]={gx-30,gy-7,gx-27,gy-5,gx-38,gy+9,gx-48,gy+9};
 setfillstyle(1,LIGHTRED);
 fillpoly(4,leftarm);

 int rightarm[8]={gx+27,gy-5,gx+30,gy-7,gx+48,gy+9,gx+38,gy+9};
 setfillstyle(1,LIGHTRED);
 fillpoly(4,rightarm);

 //GLOVES
 setcolor(YELLOW);

 int lglove[10]={gx-30,gy-7,gx-12,gy-25,gx-9,gy-15,gx-22,gy-9,
		 gx-27,gy-5};
 setfillstyle(1,14);
 fillpoly(5,lglove);

 int rglove[10]={gx+27,gy-5,gx+22,gy-9,gx+9,gy-15,gx+12,gy-25,
		 gx+30,gy-7};
 setfillstyle(1,14);
 fillpoly(5,rglove);

 }

 //SHORTS
 setcolor(BLUE);

 int lshorts[8]={gx-10,gy+80,gx,gy+80,gx-5,gy+100,gx-25,gy+100};
 setfillstyle(10,BLUE);
 fillpoly(4,lshorts);

 int rshorts[8]={gx,gy+80,gx+10,gy+80,gx+25,gy+100,gx+5,gy+100};
 setfillstyle(10,BLUE);
 fillpoly(4,rshorts);

 setcolor(RED);

 int pline1[8]={gx-24,gy+97,gx-4,gy+97,gx-6,gy+100,gx-25,gy+100};
 setfillstyle(1,RED);
 fillpoly(4,pline1);

 int pline2[8]={gx+4,gy+97,gx+23,gy+97,gx+25,gy+100,gx+5,gy+100};
 setfillstyle(1,RED);
 fillpoly(4,pline2);

 //LEGS
 setcolor(LIGHTRED);

 int leftleg[8]={gx-23,gy+101,gx-8,gy+101,gx-13,gy+150,gx-18,gy+150};
 setfillstyle(1,LIGHTRED);
 fillpoly(4,leftleg);

 int rightleg[8]={gx+7,gy+101,gx+22,gy+101,gx+17,gy+150,gx+12,gy+150};
 setfillstyle(1,LIGHTRED);
 fillpoly(4,rightleg);

 //STUDS
 setcolor(4);

 int leftstud[12]={gx-18,gy+150,gx-13,gy+150,gx-10,gy+152,gx-14,gy+155,
		   gx-17,gy+155,gx-21,gy+152};
 setfillstyle(1,RED);
 fillpoly(6,leftstud);

 int rightstud[12]={gx+12,gy+150,gx+17,gy+150,gx+20,gy+152,gx+16,gy+155,
		    gx+13,gy+155,gx+9,gy+152};
 setfillstyle(1,RED);
 fillpoly(6,rightstud);

}

void SHOOTSCREEN()
{
cleardevice();
GOALPOST();
OUTFIELD();
KEEPER(gx,gy,gr);
BALL2(bx,by,15);
}

void AIMSP()
{
if(h<250 || h>363)
 aimsp=1;
else aimsp=0;
}

void AIMMOVE()
{
int i1,ke;

lab:
ke=bioskey(0);

if(ke!=7181) //i.e player has not pressed 'Enter' key
{
switch(ke)
{
case 19200 : for(i1=0;;i1++) //key 4 on nums pad for LEFT
	      {
	       cleardevice();
	       SHOOTSCREEN();
	       AIMSP();
	       if(aimsp==0)
	       {
	       h=h-2;
	       AIM(h,k);
	       delay(20);
	       }
	       else
	       {
	       h=h-8;
	       AIM(h,k);
	       delay(15);
	       }
	       if (bioskey(1)!=0)
		goto lab;
	      }     // No need for break since for loop is infinite

case 19712 : for(i1=0;;i1++) //key 6 on nums pad for RIGHT
	      {
	       cleardevice();
	       SHOOTSCREEN();
	       AIMSP();
	       if(aimsp==0)
	       {
	       h=h+2;
	       AIM(h,k);
	       delay(20);
	       }
	       else
	       {
	       h=h+8;
	       AIM(h,k);
	       delay(15);
	       }
	       if (bioskey(1)!=0)
		goto lab;
	      }

case 18432 : for(i1=0;;i1++) //key 8 on nums pad for TOP
	      {
	       cleardevice();
	       SHOOTSCREEN();
	       AIMSP();
	       if(aimsp==0)
	       {
	       k=k-2;
	       AIM(h,k);
	       delay(20);
	       }
	       else
	       {
	       k=k-8;
	       AIM(h,k);
	       delay(15);
	       }
	       if (bioskey(1)!=0)
		goto lab;
	      }

case 20480 : for(i1=0;;i1++) //key 2 on nums pad for BOTTOM
	      {
	       cleardevice();
	       SHOOTSCREEN();
	       AIMSP();
	       if(aimsp==0)
	       {
	       k=k+2;
	       AIM(h,k);
	       delay(20);
	       }
	       else
	       {
	       k=k+8;
	       AIM(h,k);
	       delay(15);
	       }
	       if (bioskey(1)!=0)
		goto lab;
	      }

default : goto lab;
}

}
}

void WINSCREEN()
{
key=0;
while(key!=7181)
{
cleardevice();
settextstyle(1,0,7);
setcolor(14);
outtextxy(160,40,"YOU WON!");
settextstyle(1,0,3);
setcolor(4);
outtextxy(10,120,"YOU HAVE SAVED YOUR GROUND AND YOUR RESPECT...");
settextstyle(0,0,5);
setcolor(CYAN);
outtextxy(50,200,"YOUR SCORE:");
settextstyle(1,0,4);
setcolor(GREEN);
outtextxy(60,280,"GO BACK TO");
outtextxy(62,310,"MAIN MENU");
settextstyle(2,0,5);
setcolor(YELLOW);
outtextxy(92,360,"(AND CHECK OUT");
outtextxy(88,380,"THE HIGH SCORES)");
settextstyle(1,0,6);
setcolor(GREEN);
outtextxy(440,285,"QUIT");
settextstyle(2,0,5);
setcolor(YELLOW);
outtextxy(450,360,"(LEAVE WITH");
outtextxy(430,380,"DIGNITY AND HONOR)");

BALL2(320,320,18);
settextstyle(4,0,6);
setcolor(7);
outtextxy(340,285,"R");

if(WIN[0]==1)
HL=1;
else
HL=0;

setcolor(GREEN);
if(HL==1)
rectangle(52,280,250,350);

else
rectangle(432,290,558,350);

key=bioskey(0);
key=bioskey(0);

if(key==19712 || key==19200)
 {
  if(HL==1)
   {
    WIN[0]=0;
    WIN[1]=1;
   }
  else
   {
    WIN[0]=1;
    WIN[1]=0;
   }
 }
}
if(WIN[0]==1)
 MM=1;
else if(WIN[0]==0)
 exit(0);
}

void LOSESCREEN()
{
key=0;
while(key!=7181)
{
cleardevice();
settextstyle(1,0,7);
setcolor(14);
outtextxy(160,40,"YOU LOST!");
settextstyle(1,0,3);
setcolor(4);
outtextxy(15,120,"NOW YOU DONT HAVE A GROUND NOR ANY RESPECT...");
settextstyle(1,0,8);
setcolor(BLUE);
outtextxy(100,170,"WHAT NOW?");
settextstyle(1,0,4);
setcolor(GREEN);
outtextxy(60,280,"GO BACK TO");
outtextxy(62,310,"MAIN MENU");
settextstyle(2,0,5);
setcolor(YELLOW);
outtextxy(72,360,"(AND TRY TO REGAIN");
outtextxy(70,380,"WHAT YOU HAVE LOST)");
settextstyle(1,0,6);
setcolor(GREEN);
outtextxy(440,285,"QUIT");
settextstyle(2,0,5);
setcolor(YELLOW);
outtextxy(427,360,"(ACCEPT DEFEAT AND");
outtextxy(425,380,"LEAVE LIKE A COWARD)");

BALL2(320,320,18);
settextstyle(4,0,6);
setcolor(7);
outtextxy(340,285,"R");

if(LOS[0]==1)
HL=1;
else
HL=0;

setcolor(GREEN);
if(HL==1)
rectangle(52,280,250,350);

else
rectangle(432,290,558,350);

key=bioskey(0);
key=bioskey(0);

if(key==19712 || key==19200)
 {
  if(HL==1)
   {
    LOS[0]=0;
    LOS[1]=1;
   }
  else
   {
    LOS[0]=1;
    LOS[1]=0;
   }
 }
}

if(LOS[0]==1)
 MM=1;
else if(LOS[0]==0)
 exit(0);
}


void BALLSHOOT(float hx,float hy)
{
int idx,idy;
float Do,dx,dy,fx,fy,Dog,dxg,dyg,fxg,fyg;
int kf=0;

if(hx>=bx)
 idx=1;
else
 idx=0;

if(hy>=by)
 idy=1;
else
 idy=0;

dx=(hx-bx);
 if(dx<0)
  dx=-dx;
dy=(hy-by);
 if(dy<0)
  dy=-dy;

Do=pow((pow(dx,2)+pow(dy,2)),0.5);

fx=dx/Do;
fy=dy/Do;

dxg=(hx-gx);
 if(dxg<0)
  dxg=-dxg;
dyg=(hy-gy);
 if(dyg<0)
  dyg=-dyg;

Dog=pow((pow(dxg,2)+pow(dyg,2)),0.5);

fxg=dxg/Dog;
fyg=dyg/Dog;

for(int j1=0;;j1++)
 {
  if(idx==1)
   bx=bx+no*fx;
  else
   bx=bx-no*fx;
  if(idy==1)
   by=by+no*fy;
  else
   by=by-no*fy;
  if(kf!=1)
  {
  if(KEEPFLAG!=1)
   {
    if(idx==1)
     gx++;
    else
     gx--;
   if(fabs(gx-hx)<=2)
    kf=1;
   }
  else
   {
    if(idx==1)
     {
      gx=gx+fxg;
      gy=gy-fyg;
     }
    else
     {
      gx=gx-fxg;
      gy=gy-fyg;
     }
    if(fabs(gx-hx)<fxg)
     kf=1;
   }
  }
  cleardevice();
  SHOOTSCREEN();
  delay(10);
  if(fabs(bx-hx)<no*fx)
   break;
 }
delay(1500);
}

void GOAL()
{
if(h>150 && h<200 && k>85 && k<290)
 go=1;
else if(h>200 && h<420 && k>85 && k<110)
 go=1;
else if(h>420 && h<470 && k>85 && k<290)
 go=1;
}

void SHOOTDISPLAY()
{
/*
int id=0;
if(h>=bx)
 id=1;

cout<<"\n"<<no<<" "<<id<<" "<<h<<" "<<k;
if(no==4.2)
 {
  if(id==1)
   h+=5;
  else
   h=h-5;
  k=k-5;
 }
else if(no==4.5)
 {
  if(id==1)
   h+=10;
  else
   h=h-10;
  k=k-10;
 }
else if(no==4.8)
 {
  cout<<"AAAAAAAAAAAAAAAAAA";
  if(id==1)
   h+=15;
  else
   h=h-15;
  k=k-15;
 }
cout<<"\n"<<h<<" "<<k;
delay(6000);    */
GOAL();
if(no<=3)
 go=0;
if(k<140)
 KEEPFLAG=1;
BALLSHOOT(h,k);
if(go==1)
 WINSCREEN();
else
 LOSESCREEN();
}

void POWERBAR()
{
setcolor(RED);
rectangle(50,40,80,202);

setcolor(RED);

rectangle(52,42,78,50);
setfillstyle(1,RED);
floodfill(55,43,RED);

rectangle(52,52,78,60);
setfillstyle(1,RED);
floodfill(55,53,RED);

rectangle(52,62,78,70);
setfillstyle(1,RED);
floodfill(55,63,RED);

setcolor(YELLOW);

rectangle(52,72,78,80);
setfillstyle(1,YELLOW);
floodfill(55,73,YELLOW);

rectangle(52,82,78,90);
setfillstyle(1,YELLOW);
floodfill(55,83,YELLOW);

rectangle(52,92,78,100);
setfillstyle(1,YELLOW);
floodfill(55,93,YELLOW);

rectangle(52,102,78,110);
setfillstyle(1,YELLOW);
floodfill(55,103,YELLOW);

rectangle(52,112,78,120);
setfillstyle(1,YELLOW);
floodfill(55,113,YELLOW);

setcolor(GREEN);

rectangle(52,122,78,130);
setfillstyle(1,GREEN);
floodfill(55,123,GREEN);

rectangle(52,132,78,140);
setfillstyle(1,GREEN);
floodfill(55,133,GREEN);

rectangle(52,142,78,150);
setfillstyle(1,GREEN);
floodfill(55,143,GREEN);

rectangle(52,152,78,160);
setfillstyle(1,GREEN);
floodfill(55,153,GREEN);

rectangle(52,162,78,170);
setfillstyle(1,GREEN);
floodfill(55,163,GREEN);

setcolor(LIGHTBLUE);

rectangle(52,172,78,180);
setfillstyle(1,LIGHTBLUE);
floodfill(55,173,LIGHTBLUE);

rectangle(52,182,78,190);
setfillstyle(1,LIGHTBLUE);
floodfill(55,183,LIGHTBLUE);

rectangle(52,192,78,200);
setfillstyle(1,LIGHTBLUE);
floodfill(55,193,LIGHTBLUE);
}

void POWERSELECT()
{
int key=0;
for(int i=1;i<=10;i++)
 {
  if(powflg!=1)
   {
    for(pbu=192,pbd=200;pbu>=42,pbd>=50;pbu-=10,pbd-=10)
     {
      delay(100);
      setcolor(BLACK);
      rectangle(48,pbu+10,82,pbd+10);
      POWERBAR();
      setcolor(WHITE);
      rectangle(48,pbu,82,pbd);

      key=bioskey(1);
      if(key==7181)
       {
	powflg=1;
	break;
       }
   }
 }
 if(powflg==1)
  {
   power=202-pbu;
   no=power*0.03;
   break;
  }
setcolor(BLACK);
rectangle(48,42,82,50);
setcolor(BLACK);
rectangle(48,192,82,200);
}
}

void SHOOT()
{
cleardevice();
settextstyle(1,0,7);
setcolor(14);
outtextxy(150,150,"S");
delay(1000);
outtextxy(185,150,"H");
delay(1000);
outtextxy(225,150,"O");
delay(1000);
outtextxy(265,150,"O");
delay(1000);
outtextxy(300,150,"T");
delay(1000);
cleardevice();
SHOOTSCREEN();
AIM(h,k);
AIMMOVE();
POWERSELECT();
}

void HELPSCREEN()
{
chooseflag=1;
cleardevice();
settextstyle(1,0,5);
setcolor(GREEN);
outtextxy(265,20,"HELP");

settextstyle(2,0,5);
setcolor(CYAN);
 outtextxy(0,90,"Soccer Redemption is the world's best third-person "
		 "soccer-arcade game.");
 outtextxy(0,105,"The objective is very staight-forward ........"
		  "TO SCORE A GOAL !! " );
 outtextxy(0,125,"\nHowever,unlike other games,here the player has "
		  "to score the goal without losing");
 outtextxy(0,140,"ball possession even ONCE, thus making it extremely "
		  "difficult to score.");
 outtextxy(0,155,"There are 5 players (by default) in each team."
		  " The CPU players are faster ");
 outtextxy(0,170,"and are extremely clever - they can spot any and every "
		  "movement of the ball,so");
 outtextxy(0,185,"beware of your passing. However,to help you, ball speed "
		  "when passed is more than");
 outtextxy(0,200,"that of CPU players. Once your player gets inside the "
		  "innermost rectangle of ");
 outtextxy(0,215,"the goal area, an alternate screen will appear showing the "
		  "opposion keeper ");
 outtextxy(0,230,"and your striker. The time taken taken by you to reach "
		  "this point will be noted. " );
 outtextxy(0,245,"This will account your score - faster you reach, higher "
		 "the score. But, this score");
 outtextxy(0,260,"will only be recorded if your player succeeds in scoring.");
 outtextxy(0,275,"In the shoot screen, an aim will be provided to you "
		  "to position your shot. ");
 outtextxy(0,290,"The aim will be controlled by the Nums Pad "
		  " keys:4,6,2,8, as mentioned below. ");
 outtextxy(0,305,"Power can be chosen from the power bar : RED-high "
		  "GREEN-low mid,YELLOW-high mid,");
 outtextxy(0,320,"BLUE-low (CAUTION: High power causes loss in accuracy)."
		  " To confirm your shot, ");
 outtextxy(0,335,"press enter. Your striker will shoot as per the "
		  "selected configuration.");

 settextstyle(8,0,1);
 setcolor(WHITE);
 outtextxy(0,365,"KEYPAD CONTROLS : ");
 settextstyle(8,0,1);
 outtextxy(230,360,"( Num Lock should be kept OFF )");
 setcolor(RED);
 settextstyle(2,0,5);
 outtextxy(0,395,"8-Up         2-Down       4-LEFT        6-RIGHT");
 outtextxy(0,420,"7-Left&Up    9-Right&Up    1-Left&Down    3-Right&Down "
		 "    P-Pass");
}

void CREDITS()
{
 chooseflag=1;
 cleardevice();
 settextstyle(3,0,7);
 setcolor(LIGHTBLUE);
 outtextxy(160,50,"This game ");
 delay(1000);
 outtextxy(155,140," has been ");
 delay(1000);
 outtextxy(100,220,"brought to you");
 delay(1000);
 outtextxy(250,300," by ...");
 delay(1000);
 cleardevice();
 delay(1000);

 settextstyle(2,0,20);

 setcolor(LIGHTBLUE);
 outtextxy(200,40,"Arkil Patel");
 delay(1000);

 getch();
 MM=1;
}

void HMPGSEL(int key1)
{
int HL=0;
 for(int i=0;i<=5;i++)
  {
   if(HPARR[HL]==1)
    break;
   else
    HL++;
  }
 if(key1==18432)
  {
   switch(HL)
    {
     case 0:
      HPARR[0]=0;
      HPARR[5]=1;
     default:
      HPARR[HL]=0;
      HPARR[HL-1]=1;
    }
  }
 else if(key1==20480)
  {
   switch(HL)
    {
     case 5:
      HPARR[0]=1;
      HPARR[5]=0;
     default:
      HPARR[HL]=0;
      HPARR[HL+1]=1;
    }
  }
 else if(key==7181)
  {
   if(HPARR[0]==1)
    {
     cleardevice();
     DISPLAYI();
     GAMERUN();
     cout<<"\n"<<FLAG;
     if(FLAG!=1)
      {
       SHOOT();
       SHOOTDISPLAY();
       cout<<'\n'<<'\t'<<tm;
       tm=int(tm);
       scr=1000-tm*10;
       cout<<'\n'<<'\t'<<scr;
      }
     else
      LOSESCREEN();
    }
   else if(HPARR[3]==1)
    {
     HELPSCREEN();
     getch();
     MM=1;
    }
   else if(HPARR[4]==1)
    {
     CREDITS();
     getch();
     MM=1;
    }
   else if(HPARR[5]==1)
    exit(0);
  }
}

void HOMEPAGE()
{
 settextstyle(4,0,7);
 setcolor(7);
 outtextxy(200,10,"S CCER");
 settextstyle(4,0,6);
 setcolor(14);
 outtextxy(110,75,"! REDEMPTION !");

 setcolor(14);
 circle(255,53,18);
 setfillstyle(9,BLACK);
 floodfill(255,53,14);
 setcolor(getmaxcolor());

 BALL2(255,53,18);

 settextstyle(1,0,4);
 setcolor(4);
 outtextxy(220,180,"Quick Match");
 settextstyle(1,0,4);
 setcolor(4);
 outtextxy(233,220,"Story Mode");
 settextstyle(1,0,4);
 setcolor(4);
 outtextxy(234,260,"High Score");
 settextstyle(1,0,4);
 setcolor(4);
 outtextxy(283,300,"Help");
 setcolor(4);
 outtextxy(265,340,"Credits");
 setcolor(4);
 outtextxy(283,380,"Quit");
 settextstyle(1,0,4);
 setcolor(getmaxcolor());

if(strthl==0)
 {
  setcolor(GREEN);
  rectangle(212,180,420,220);
  strthl=21;
 }

 key=bioskey(0);
 HMPGSEL(key);

if(FLAG!=1 && shotflag!=1 && chooseflag!=1)   // Otherwise rectangle is displayed in win screen,lost screen,helpscreen,etc...
 {
 //SELECTION RECTANGLE
 setcolor(BLACK);
 if(HPARR[0]==1)
 setcolor(GREEN);
 rectangle(212,180,420,220);

 setcolor(BLACK);
 if(HPARR[1]==1)
 setcolor(GREEN);
 rectangle(223,221,410,260);

 setcolor(BLACK);
 if(HPARR[2]==1)
 setcolor(GREEN);
 rectangle(225,261,407,300);

 setcolor(BLACK);
 if(HPARR[3]==1)
 setcolor(GREEN);
 rectangle(275,301,355,340);

 setcolor(BLACK);
 if(HPARR[4]==1)
 setcolor(GREEN);
 rectangle(258,341,375,380);

 setcolor(BLACK);
 if(HPARR[5]==1)
 setcolor(GREEN);
 rectangle(277,381,350,420);
 }
}

void VAR_INI()
{
xo=0;yo=0;K=0;lk=0;pp=0;key=0;HL=0;

//Initial Co-ordinates:
H1x=340;H1y=220; //human player 1
H2x=420;H2y=80;  //human player 2
H3x=420;H3y=360; //human player 3
H4x=475;H4y=220; //human player 4
H5x=590;H5y=220; //human player 5
C1x=290;C1y=220; //PC player 1
C2x=210;C2y=80;  //PC player 2
C3x=210;C3y=360; //PC player 3
C4x=155;C4y=220; //PC player 4
C5x=40;C5y=220;  //PC player 5
Bx=330;By=250; //Ball
h=307;k=100; //Aim

go=0;

gx=307;gy=140;gr=10;      //////// GOAL KEEPER COORDINATES
//sx=180;sy=340;sr=10;      //////// SHOOTER COORDINATES
bx=307;by=400;lbs=15;  //////// BALL2 COORDINATES

filflg=0;

H1co=4;H2co=4;H3co=4;H4co=4;H5co=4;
C1co=4;C2co=4;C3co=4;C4co=4;C5co=4;

H1co1=4;H2co1=4;H3co1=4;H4co1=4;H5co1=4;
C1co1=4;C2co1=4;C3co1=4;C4co1=4;C5co1=4;

chooseflag=0;     //To eliminate the rectangle from various screens(helpscreen,credits,etc...)

FLAG=0;shotflag=0;
KEEPFLAG=0;        //1 for alternate keeper

aimsp=0;

pbu=42;pbd=50;          // POWER SELECTOR COORDINATES
powflg=0;
power=0;
no=0;

MM=0;

tm=0;scr=0;

//SELECTION
HPARR[0]=1;
HPARR[1]=0;
HPARR[2]=0;
HPARR[3]=0;
HPARR[4]=0;
HPARR[5]=0;
strthl=0;

//WINSCRNSEL
WIN[0]=1;
WIN[1]=0;
LOS[0]=1;
LOS[1]=1;
}

void main()
{
clrscr();
GRAPHICS();
p:
while(key!=7181)
 HOMEPAGE();
if(MM==1)
 {
  cleardevice();
  VAR_INI();
  goto p;
 }
// SHOOT();
// SHOOTDISPLAY();
getch();
}
