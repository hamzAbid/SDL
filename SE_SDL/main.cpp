#include<stdio.h>
#include<stdlib.h>
#include<sdl/sdl.h>
#include<sdl/sdl_ttf.h>
#include <string.h>

typedef struct tab_processus { int tempsarr ; int tempexe ; struct tab_processus *suivant ; } tab_processus ;

int saisi(SDL_Event ev)
{
    int n;
   switch(ev.key.keysym.sym)
        {
                case SDLK_KP0: {n=0;break;}
                case SDLK_KP1: {n=1;break;}
                case SDLK_KP2: {n=2;break;}
                case SDLK_KP3: {n=3;break;}
                case SDLK_KP4: {n=4;break;}
                case SDLK_KP5: {n=5;break;}
                case SDLK_KP6: {n=6;break;}
                case SDLK_KP7: {n=7;break;}
                case SDLK_KP8: {n=8;break;}
                case SDLK_KP9: {n=9;break;}
        }

    return n;
}
void FIFO(tab_processus tp[10] , int nb )
{
    int i,j;
    tab_processus p;
    for(i=0;i<nb-1;i++)
    {
        for(j=i+1;j<nb;j++)
            if(tp[i].tempsarr > tp[j].tempsarr)
            {
            p=tp[i];
            tp[i]=tp[j];
            tp[j]=p;
            }
    }

}

void PCTE ( tab_processus tp[10] , int nb )
{

    int i,j,c=0;
    tab_processus per,p;

    for(i=0;i<nb-1;i++)
    {
        for(j=i+1;j<nb;j++)
        {
            if (tp[i].tempsarr > tp[j].tempsarr )
               {
                   per = tp[i] ;
                   tp[i] = tp[j];
                   tp[j] = per ;
               }
        }

    for(i=0 ; tp[i].tempsarr == tp[i+1].tempsarr ; i++)
    {
            if(tp[0].tempexe > tp[i+1].tempexe)
            {
            p=tp[0];
            tp[0]=tp[i+1];
            tp[i+1]=p;
            }
    }
    for(i=0;i<nb;i++)
    {
        c = c + tp[i].tempexe ;
        for(j=i+1 ; j<nb ; j++)
        {

            if(tp[j].tempsarr <= c && tp[j].tempexe <= tp[i+1].tempexe )
           {
            p=tp[j];
            tp[j]=tp[i+1];
            tp[i+1]=p;
           }
        }

    }
    }
}

void TOURNIQUET(tab_processus tp[10] ,int nb ,int Q , int TabSejour[10] , int TabAttente[10] )
{
int i,j,l,F=0,total=0;
for (i = 0; i < nb; i++)
{
total = total + tp[i].tempexe;
}
i=0;
while(1)
{
if(tp[i].tempexe != 0 && tp[i].tempsarr <= F ) // Si le Processus na pas encore terminé
{
for (j=1; j<=Q; j++)
{
tp[i].tempexe --;
TabSejour[i]++;
F++;
for (l = 0; l < nb; l++)
{
if(l != i && tp[l].tempexe !=0 && tp[l].tempsarr < F)
TabAttente[l]++ ; // ajout temps attente
}

if(tp[i].tempexe == 0) break;
}
}
else
{

if(F == total)break;
}
i++;
if(i == nb)i=0;
}
}

void tempsejour( tab_processus tp[10] , int nb , int TabSejour[10] )
{
     int i,j,T=0;
     int TS[10];
     for(i=0;i<nb;i++)
     {  T=0;
       for(j=i;j>=0;j--)
       {  T=T+tp[j].tempexe; }

        TS[i]=T-tp[i].tempsarr;

        TabSejour[i]=TS[i] ;
     }

}

void tempsatt(tab_processus tp[10] , int nb , int TabAttente[10] )
{
     int i,j,T=0;
     int TS[10];
     int TATT[10];
     for(i=0;i<nb;i++)
     {  T=0;
       for(j=i;j>=0;j--)
       {  T=T+tp[j].tempexe; }

        TS[i]=T-tp[i].tempsarr;
        TATT[i]=TS[i]-tp[i].tempexe;

        TabAttente[i]=TATT[i];
     }

}

float tempsejour_moyen ( int nb , int TabSejour[10] )
{
    int i,S=0;
    for(i=0;i<nb;i++)
    {
        S=S+TabSejour[i];
    }
    return (float)S/nb ;
}
float tempsatt_moyen ( int nb , int TabAttente[10] )
{
    int i,S=0;
    for(i=0;i<nb;i++)
    {
        S=S+TabAttente[i];
    }
    return (float)S/nb ;
}


int main (int argc , char *argv[])
{
    tab_processus  TAB[10];
    int continuer=1;
    int TabSejour[10] , TabAttente[10];
    int x,y,n,b,tm=1,i=0, te=0;
    int a=0,var,tmo=0, cp=1;
    char G[20];
    char G2[10],G4[10];
    char G3[10],G5[10];
    float Tatt , Tse ;
    SDL_Surface *fenetre=NULL , *text = NULL , *text2 = NULL , *text3 = NULL;
    SDL_Surface *Image;
    SDL_Rect PositionImage ;
    SDL_Surface *Image2;
    SDL_Rect PositionImage2 ;
    SDL_Surface *Image3;
    SDL_Rect PositionImage3 ;
    SDL_Surface *Image4;
    SDL_Rect PositionImage4 ;
    SDL_Surface *Image5;
    SDL_Rect PositionImage5 ;
    SDL_Surface *Image6;
    SDL_Rect PositionImage6 ;


    PositionImage.x =55;
    PositionImage.y=70;

    PositionImage2.x=500;
    PositionImage2.y=450;

    PositionImage3.x=250;
    PositionImage3.y=100;

    PositionImage4.x=250;
    PositionImage4.y=200;

    PositionImage5.x=250;
    PositionImage5.y=300;

    PositionImage6.x=20;
    PositionImage6.y=100;

    SDL_Event ev;
    SDL_Rect position;
    SDL_Rect position2;
    SDL_Rect pos[30][30];


    TTF_Font *police = NULL;
    TTF_Font *police2 = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Color couleurRouge = {255,0,0};
    SDL_Color couleurBleu = {0,0,255};
    SDL_Color couleurBlanc = {255,255,255};

     SDL_Init(SDL_INIT_VIDEO);

    fenetre=SDL_SetVideoMode(870,670,16,SDL_HWSURFACE  | SDL_DOUBLEBUF);

    SDL_FillRect(fenetre,NULL,SDL_MapRGB(fenetre->format,255,255,255));
    //SDL_Flip(fenetre);
     TTF_Init();
    police = TTF_OpenFont("arial.ttf",40);
    police2= TTF_OpenFont("arial.ttf",25);
    position.x =20;
    position.y=5;
    text = TTF_RenderText_Blended(police, "ORDONNANCEMENT DES PROCESSUS",couleurNoire);
    SDL_BlitSurface(text,NULL,fenetre,&position);

    SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image = SDL_LoadBMP("Microprocesseur.bmp");
    SDL_BlitSurface(Image, NULL, fenetre, &PositionImage);

    SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image2 = SDL_LoadBMP("next.bmp");
    SDL_BlitSurface(Image2, NULL, fenetre, &PositionImage2);

    position.x =480;
    position.y=200;
    text = TTF_RenderText_Blended(police, "Réalisé Par :",couleurNoire);
    SDL_BlitSurface(text,NULL,fenetre,&position);
    position.x =480;
    position.y=240;
    text = TTF_RenderText_Blended(police, "Yassine ALALOU",couleurNoire);
    SDL_BlitSurface(text,NULL,fenetre,&position);
    position.x =480;
    position.y=280;
    text = TTF_RenderText_Blended(police, "Hamza ABID",couleurNoire);
    SDL_BlitSurface(text,NULL,fenetre,&position);

    SDL_Flip(fenetre);

    while(continuer)
    {
        if(tm==2){tm=3 ;}
        if (a==1)b=1;
        if (a==2)b=2;
        if (a==3)b=3;
        if (a==4)b=4;
        if (a==5)b=5;
        if (a==6)b=6;
        if (a==7)b=7;
        if (a==8)b=8;
        if (a==9)b=9;
        if (a==10)b=10;
        if (a==11)b=11;
        if (a==12)b=12;
        if (a==13)b=13;
        if (a==14)b=14;
        if (a==15)b=15;
        if (a==16)b=16;
        if (a==17)b=17;
        if (a==18)b=18;
        if (a==19)b=19;
        if (a==20)b=20;
        if (a==21)b=21;
        if (a==22)b=22;
        if (a==23)b=23;

        SDL_WaitEvent(&ev);

        switch(ev.type)
        {

        case SDL_QUIT:
             continuer=0;
             break;

        case SDL_MOUSEBUTTONUP:
            {if(ev.button.button==SDL_BUTTON_LEFT)

              {if(ev.button.x>499 && ev.button.x<600 && ev.button.y>448 && ev.button.y<550 && tm==1 )
        {


    fenetre=SDL_SetVideoMode(870,670,16,SDL_HWSURFACE  | SDL_DOUBLEBUF);
    SDL_FillRect(fenetre,NULL,SDL_MapRGB(fenetre->format,255,255,255));
    position.x =20;
    position.y=7;
    text = TTF_RenderText_Blended(police,"ALGORITHMES :",couleurNoire);
    SDL_BlitSurface(text,NULL,fenetre,&position);

    SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image3 = SDL_LoadBMP("button.bmp");
    SDL_BlitSurface(Image3, NULL, fenetre, &PositionImage3);

    SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image3 = SDL_LoadBMP("button_pcte.bmp");
    SDL_BlitSurface(Image3, NULL, fenetre, &PositionImage4);

    SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image3 = SDL_LoadBMP("button_tourniquet.bmp");
    SDL_BlitSurface(Image3, NULL, fenetre, &PositionImage5);
    tm=2;
    }

            if(ev.button.x>248 && ev.button.x<450 && ev.button.y>98 && ev.button.y<200 && tm==3)
    {

        fenetre=SDL_SetVideoMode(870,670,16,SDL_HWSURFACE  | SDL_DOUBLEBUF);
    SDL_FillRect(fenetre,NULL,SDL_MapRGB(fenetre->format,255,255,255));
    position.x =20;
    position.y=7;
    text = TTF_RenderText_Blended(police,"FIFO:Donner le nombre des processus :",couleurNoire);
    SDL_BlitSurface(text,NULL,fenetre,&position);tm=4;a=1;te=1;

    }

        if(ev.button.x>248 && ev.button.x<450 && ev.button.y>190 && ev.button.y<280 && tm==3)
        {
            fenetre=SDL_SetVideoMode(870,670,16,SDL_HWSURFACE  | SDL_DOUBLEBUF);
    SDL_FillRect(fenetre,NULL,SDL_MapRGB(fenetre->format,255,255,255));
    position.x =20;
    position.y=7;
    text = TTF_RenderText_Blended(police,"PCTE:Donner le nombre des processus :",couleurNoire);
    SDL_BlitSurface(text,NULL,fenetre,&position);tm=4;a=2;te=2;
        }

       if(ev.button.x>248 && ev.button.x<450 && ev.button.y>290 && ev.button.y<380 && tm==3)
        {
            fenetre=SDL_SetVideoMode(870,670,16,SDL_HWSURFACE  | SDL_DOUBLEBUF);
    SDL_FillRect(fenetre,NULL,SDL_MapRGB(fenetre->format,255,255,255));
    position.x =20;
    position.y=7;
    text = TTF_RenderText_Blended(police,"Tourniquet:Donner le nombre des processus :",couleurNoire);
    SDL_BlitSurface(text,NULL,fenetre,&position);tm=4;a=3; te=3 ;
        }

    SDL_Flip(fenetre);
        }



        case SDL_KEYDOWN:
              { int tmo=0;
// FIFO
                if (b==1){      n=saisi(ev);
                                position.x =750;
                                position.y=7;
                                sprintf(G,"%d",n);
                                text = TTF_RenderText_Blended(police,G,couleurNoire);
                                SDL_BlitSurface(text,NULL,fenetre,&position);


    if (n== 1 )
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("1proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
    if (n== 2)
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("2proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
     if ( n == 3)
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("3proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
    if ( n == 4)
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("4proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
    if ( n == 5)
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("5proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
    if ( n == 6)
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("6proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
    if ( n == 7)
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("7proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
    if ( n == 8)
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("8proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
    if ( n == 9)
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("9proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
                                b=-1;a=4;

                                }

                  if (b==2){    n=saisi(ev);
                                position.x =750;
                                position.y=7;
                                sprintf(G,"%d",n);
                                text = TTF_RenderText_Blended(police,G,couleurNoire);
                                SDL_BlitSurface(text,NULL,fenetre,&position);
    if (n== 1 )
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("1proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
    if (n== 2)
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("2proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
     if ( n == 3)
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("3proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
    if ( n == 4)
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("4proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
    if ( n == 5)
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("5proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
    if ( n == 6)
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("6proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
    if ( n == 7)
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("7proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
    if ( n == 8)
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("8proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
    if ( n == 9)
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("9proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
                                b=-1;a=4;
                                }

                 if (b==3){     n=saisi(ev);
                                position.x =800;
                                position.y=7;
                                sprintf(G,"%d",n);
                                text = TTF_RenderText_Blended(police,G,couleurNoire);
                                SDL_BlitSurface(text,NULL,fenetre,&position);
    if (n== 1 )
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("1proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
    if (n== 2)
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("2proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
     if ( n == 3)
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("3proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
    if ( n == 4)
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("4proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
    if ( n == 5)
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("5proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
    if ( n == 6)
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("6proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
    if ( n == 7)
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("7proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
    if ( n == 8)
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("8proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
    if ( n == 9)
    {SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    Image6 = SDL_LoadBMP("9proc.bmp");
    SDL_BlitSurface(Image6, NULL, fenetre, &PositionImage6);}
                                b=-1;a=4;
                    }

    //1
     SDL_Flip(fenetre);
     if( b == 4) {TAB[0].tempsarr=saisi(ev) ;
                position2.x =250;
                position2.y=150;
                sprintf(G2,"%d",TAB[0].tempsarr);
                text3 = TTF_RenderText_Blended(police,G2,couleurNoire);
                SDL_BlitSurface(text3 ,NULL,fenetre,&position2); a=5;}
     SDL_Flip(fenetre);
      if( b==5 )  {TAB[0].tempexe=saisi(ev) ;
                position2.x =500;
                position2.y=150;
                sprintf(G3,"%d",TAB[0].tempexe);
                text3 = TTF_RenderText_Blended(police,G3,couleurNoire);
                SDL_BlitSurface(text3 ,NULL,fenetre,&position2); a=6 ;tmo=1;}
     SDL_Flip(fenetre);
     //2
      if (b == 6) {TAB[1].tempsarr=saisi(ev) ;
                position2.x =250;
                position2.y=200;
                sprintf(G4,"%d",TAB[1].tempsarr);
                text3 = TTF_RenderText_Blended(police,G4,couleurNoire);
                SDL_BlitSurface(text3 ,NULL,fenetre,&position2); a=7; }
    SDL_Flip(fenetre);
      if( b==7 )  {TAB[1].tempexe=saisi(ev) ;
                position2.x =500;
                position2.y=200;
                sprintf(G3,"%d",TAB[1].tempexe);
                text3 = TTF_RenderText_Blended(police,G3,couleurNoire);
                SDL_BlitSurface(text3 ,NULL,fenetre,&position2); a=8 ;tmo=1;}
     SDL_Flip(fenetre);
     //3
    if (b == 8) {TAB[2].tempsarr=saisi(ev) ;
                position2.x =250;
                position2.y=250;
                sprintf(G4,"%d",TAB[2].tempsarr);
                text3 = TTF_RenderText_Blended(police,G4,couleurNoire);
                SDL_BlitSurface(text3 ,NULL,fenetre,&position2); a=9; }
    SDL_Flip(fenetre);
    if( b==9 )  {TAB[2].tempexe=saisi(ev) ;
                position2.x=500;
                position2.y=250;
                sprintf(G3,"%d",TAB[2].tempexe);
                text3 = TTF_RenderText_Blended(police,G3,couleurNoire);
                SDL_BlitSurface(text3 ,NULL,fenetre,&position2); a=10 ;tmo=1;}
     SDL_Flip(fenetre);
     // 4
     if (b == 10) {TAB[3].tempsarr=saisi(ev) ;
                position2.x=250;
                position2.y=300;
                sprintf(G4,"%d",TAB[3].tempsarr);
                text3 = TTF_RenderText_Blended(police,G4,couleurNoire);
                SDL_BlitSurface(text3 ,NULL,fenetre,&position2); a=11; }
    SDL_Flip(fenetre);
    if( b==11 )  {TAB[3].tempexe=saisi(ev) ;
                position2.x=500;
                position2.y=300;
                sprintf(G3,"%d",TAB[3].tempexe);
                text3 = TTF_RenderText_Blended(police,G3,couleurNoire);
                SDL_BlitSurface(text3 ,NULL,fenetre,&position2); a=12 ;tmo=1;}
     SDL_Flip(fenetre);
     // 5
    if (b == 12) {TAB[4].tempsarr=saisi(ev) ;
                position2.x=250;
                position2.y=350;
                sprintf(G4,"%d",TAB[4].tempsarr);
                text3 = TTF_RenderText_Blended(police,G4,couleurNoire);
                SDL_BlitSurface(text3 ,NULL,fenetre,&position2); a=13; }
    SDL_Flip(fenetre);
    if( b==13 )  {TAB[4].tempexe=saisi(ev) ;
                position2.x=500;
                position2.y=350;
                sprintf(G3,"%d",TAB[4].tempexe);
                text3 = TTF_RenderText_Blended(police,G3,couleurNoire);
                SDL_BlitSurface(text3 ,NULL,fenetre,&position2); a=14 ;}
     SDL_Flip(fenetre);
     //6
     if (b == 14) {TAB[5].tempsarr=saisi(ev) ;
                position2.x =250;
                position2.y=400;
                sprintf(G4,"%d",TAB[5].tempsarr);
                text3 = TTF_RenderText_Blended(police,G4,couleurNoire);
                SDL_BlitSurface(text3 ,NULL,fenetre,&position2); a=15; }
    SDL_Flip(fenetre);
    if( b==15 )  {TAB[5].tempexe=saisi(ev) ;
                position2.x=500;
                position2.y=400;
                sprintf(G3,"%d",TAB[5].tempexe);
                text3 = TTF_RenderText_Blended(police,G3,couleurNoire);
                SDL_BlitSurface(text3 ,NULL,fenetre,&position2); a=16 ;}
     SDL_Flip(fenetre);
    //7
    if (b == 16) {TAB[6].tempsarr=saisi(ev) ;
                position2.x =250;
                position2.y=450;
                sprintf(G4,"%d",TAB[6].tempsarr);
                text3 = TTF_RenderText_Blended(police,G4,couleurNoire);
                SDL_BlitSurface(text3 ,NULL,fenetre,&position2); a=17; }
    SDL_Flip(fenetre);
    if( b==17 )  {TAB[6].tempexe=saisi(ev) ;
                position2.x=500;
                position2.y=450;
                sprintf(G3,"%d",TAB[6].tempexe);
                text3 = TTF_RenderText_Blended(police,G3,couleurNoire);
                SDL_BlitSurface(text3 ,NULL,fenetre,&position2); a=18 ;}
     SDL_Flip(fenetre);
     //8
     if (b == 18) {TAB[7].tempsarr=saisi(ev) ;
                position2.x =250;
                position2.y=500;
                sprintf(G4,"%d",TAB[7].tempsarr);
                text3 = TTF_RenderText_Blended(police,G4,couleurNoire);
                SDL_BlitSurface(text3 ,NULL,fenetre,&position2); a=19; }
    SDL_Flip(fenetre);
    if( b==19)  {TAB[7].tempexe=saisi(ev) ;
                position2.x=500;
                position2.y=500;
                sprintf(G3,"%d",TAB[7].tempexe);
                text3 = TTF_RenderText_Blended(police,G3,couleurNoire);
                SDL_BlitSurface(text3 ,NULL,fenetre,&position2); a=20 ;}
     SDL_Flip(fenetre);
     //9
     if (b == 20) {TAB[8].tempsarr=saisi(ev) ;
                position2.x =250;
                position2.y=550;
                sprintf(G4,"%d",TAB[8].tempsarr);
                text3 = TTF_RenderText_Blended(police,G4,couleurNoire);
                SDL_BlitSurface(text3 ,NULL,fenetre,&position2); a=21; }
    SDL_Flip(fenetre);
    if( b==21)  {TAB[8].tempexe=saisi(ev) ;
                position2.x=500;
                position2.y=550;
                sprintf(G3,"%d",TAB[8].tempexe);
                text3 = TTF_RenderText_Blended(police,G3,couleurNoire);
                SDL_BlitSurface(text3 ,NULL,fenetre,&position2); a=22 ;}
     SDL_Flip(fenetre);

    if (ev.key.keysym.sym==SDLK_RETURN )
    {
    fenetre=SDL_SetVideoMode(870,670,16,SDL_HWSURFACE  | SDL_DOUBLEBUF);
    SDL_FillRect(fenetre,NULL,SDL_MapRGB(fenetre->format,255,255,255));
    SDL_Flip(fenetre);

    if(te==1){FIFO (TAB,n); tempsejour(TAB,n,TabSejour);
    tempsatt(TAB,n,TabAttente);}

    if(te==2){PCTE (TAB,n); tempsejour(TAB,n,TabSejour);
    tempsatt(TAB,n,TabAttente);}

    if(te==3){ TOURNIQUET(TAB,n,2,TabSejour,TabAttente);}

    //1
    if (cp <= n)
    {position.x=10;
    position.y=10;
    text2 = TTF_RenderText_Blended(police2," Le 1er processus elu est : temps arrivée: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=500;
    position.y=10;
    sprintf(G5,"%d",TAB[0].tempsarr);
    text2 = TTF_RenderText_Blended(police2,G5,couleurRouge);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=260;
    position.y=40;
    text2 = TTF_RenderText_Blended(police2,"temps d'éxecution: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=500;
    position.y=40;
    sprintf(G5,"%d",TAB[0].tempexe);
    text2 = TTF_RenderText_Blended(police2,G5,couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=560;
    position.y=10;
    text2 = TTF_RenderText_Blended(police2," Le temps de Séjour: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=800;
    position.y=10;
    sprintf(G5,"%d",TabSejour[0]);
    text2 = TTF_RenderText_Blended(police2,G5,couleurBleu);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=560;
    position.y=40;
    text2 = TTF_RenderText_Blended(police2," Le temps d'Attente: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=800;
    position.y=40;
    sprintf(G5,"%d",TabAttente[0]);
    text2 = TTF_RenderText_Blended(police2,G5,couleurBleu);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    cp ++ ;
    }
    //2
    if (cp <= n)
    {position.x=10;
    position.y=70;
    text2 = TTF_RenderText_Blended(police2," Le 2eme processus elu est : temps arrivée: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=500;
    position.y=70;
    sprintf(G5,"%d",TAB[1].tempsarr);
    text2 = TTF_RenderText_Blended(police2,G5,couleurRouge);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=260;
    position.y=100;
    text2 = TTF_RenderText_Blended(police2,"temps d'éxecution: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=500;
    position.y=100;
    sprintf(G5,"%d",TAB[1].tempexe);
    text2 = TTF_RenderText_Blended(police2,G5,couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=560;
    position.y=70;
    text2 = TTF_RenderText_Blended(police2," Le temps de Séjour: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=800;
    position.y=70;
    sprintf(G5,"%d",TabSejour[1]);
    text2 = TTF_RenderText_Blended(police2,G5,couleurBleu);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=560;
    position.y=100;
    text2 = TTF_RenderText_Blended(police2," Le temps d'Attente: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=800;
    position.y=100;
    sprintf(G5,"%d",TabAttente[1]);
    text2 = TTF_RenderText_Blended(police2,G5,couleurBleu);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    cp ++ ;
    }
    //3
    if (cp <= n)
    {position.x=10;
    position.y=130;
    text2 = TTF_RenderText_Blended(police2," Le 3eme processus elu est : temps arrivée: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=500;
    position.y=130;
    sprintf(G5,"%d",TAB[2].tempsarr);
    text2 = TTF_RenderText_Blended(police2,G5,couleurRouge);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=260;
    position.y=160;
    text2 = TTF_RenderText_Blended(police2,"temps d'éxecution: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=500;
    position.y=160;
    sprintf(G5,"%d",TAB[2].tempexe);
    text2 = TTF_RenderText_Blended(police2,G5,couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=560;
    position.y=130;
    text2 = TTF_RenderText_Blended(police2," Le temps de Séjour: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=800;
    position.y=130;
    sprintf(G5,"%d",TabSejour[2]);
    text2 = TTF_RenderText_Blended(police2,G5,couleurBleu);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=560;
    position.y=160;
    text2 = TTF_RenderText_Blended(police2," Le temps d'Attente: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=800;
    position.y=160;
    sprintf(G5,"%d",TabAttente[2]);
    text2 = TTF_RenderText_Blended(police2,G5,couleurBleu);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    cp ++ ;
    }
    //4
    if (cp <= n)
    {position.x=10;
    position.y=190;
    text2 = TTF_RenderText_Blended(police2," Le 4eme processus elu est : temps arrivée: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=500;
    position.y=190;
    sprintf(G5,"%d",TAB[3].tempsarr);
    text2 = TTF_RenderText_Blended(police2,G5,couleurRouge);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=260;
    position.y=220;
    text2 = TTF_RenderText_Blended(police2,"temps d'éxecution: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=500;
    position.y=220;
    sprintf(G5,"%d",TAB[3].tempexe);
    text2 = TTF_RenderText_Blended(police2,G5,couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=560;
    position.y=190;
    text2 = TTF_RenderText_Blended(police2," Le temps de Séjour: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=800;
    position.y=190;
    sprintf(G5,"%d",TabSejour[3]);
    text2 = TTF_RenderText_Blended(police2,G5,couleurBleu);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=560;
    position.y=220;
    text2 = TTF_RenderText_Blended(police2," Le temps d'Attente: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=800;
    position.y=220;
    sprintf(G5,"%d",TabAttente[3]);
    text2 = TTF_RenderText_Blended(police2,G5,couleurBleu);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    cp ++ ;
    }
    //5
    if (cp <= n)
    {position.x=10;
    position.y=250;
    text2 = TTF_RenderText_Blended(police2," Le 5eme processus elu est : temps arrivée: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=500;
    position.y=250;
    sprintf(G5,"%d",TAB[4].tempsarr);
    text2 = TTF_RenderText_Blended(police2,G5,couleurRouge);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=260;
    position.y=280;
    text2 = TTF_RenderText_Blended(police2,"temps d'éxecution: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=500;
    position.y=280;
    sprintf(G5,"%d",TAB[4].tempexe);
    text2 = TTF_RenderText_Blended(police2,G5,couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=560;
    position.y=250;
    text2 = TTF_RenderText_Blended(police2," Le temps de Séjour: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=800;
    position.y=250;
    sprintf(G5,"%d",TabSejour[4]);
    text2 = TTF_RenderText_Blended(police2,G5,couleurBleu);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=560;
    position.y=280;
    text2 = TTF_RenderText_Blended(police2," Le temps d'Attente: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=800;
    position.y=280;
    sprintf(G5,"%d",TabAttente[4]);
    text2 = TTF_RenderText_Blended(police2,G5,couleurBleu);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    cp ++ ;
    }
    //6
    if (cp <= n)
    {position.x=10;
    position.y=310;
    text2 = TTF_RenderText_Blended(police2," Le 6eme processus elu est : temps arrivée: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=500;
    position.y=310;
    sprintf(G5,"%d",TAB[5].tempsarr);
    text2 = TTF_RenderText_Blended(police2,G5,couleurRouge);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=260;
    position.y=340;
    text2 = TTF_RenderText_Blended(police2,"temps d'éxecution: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=500;
    position.y=340;
    sprintf(G5,"%d",TAB[5].tempexe);
    text2 = TTF_RenderText_Blended(police2,G5,couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=560;
    position.y=310;
    text2 = TTF_RenderText_Blended(police2," Le temps de Séjour: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=800;
    position.y=310;
    sprintf(G5,"%d",TabSejour[5]);
    text2 = TTF_RenderText_Blended(police2,G5,couleurBleu);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=560;
    position.y=340;
    text2 = TTF_RenderText_Blended(police2," Le temps d'Attente: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=800;
    position.y=340;
    sprintf(G5,"%d",TabAttente[5]);
    text2 = TTF_RenderText_Blended(police2,G5,couleurBleu);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    cp ++ ;
    }
    //7
    if (cp <= n)
    {position.x=10;
    position.y=370;
    text2 = TTF_RenderText_Blended(police2," Le 7eme processus elu est : temps arrivée: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=500;
    position.y=370;
    sprintf(G5,"%d",TAB[6].tempsarr);
    text2 = TTF_RenderText_Blended(police2,G5,couleurRouge);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=260;
    position.y=400;
    text2 = TTF_RenderText_Blended(police2,"temps d'éxecution: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=500;
    position.y=400;
    sprintf(G5,"%d",TAB[6].tempexe);
    text2 = TTF_RenderText_Blended(police2,G5,couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=500;
    position.y=340;
    sprintf(G5,"%d",TAB[5].tempexe);
    text2 = TTF_RenderText_Blended(police2,G5,couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=560;
    position.y=370;
    text2 = TTF_RenderText_Blended(police2," Le temps de Séjour: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=800;
    position.y=370;
    sprintf(G5,"%d",TabSejour[6]);
    text2 = TTF_RenderText_Blended(police2,G5,couleurBleu);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=560;
    position.y=400;
    text2 = TTF_RenderText_Blended(police2," Le temps d'Attente: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=800;
    position.y=400;
    sprintf(G5,"%d",TabAttente[6]);
    text2 = TTF_RenderText_Blended(police2,G5,couleurBleu);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    cp ++ ;
    }
    //8
    if (cp <= n)
    {position.x=10;
    position.y=430;
    text2 = TTF_RenderText_Blended(police2," Le 8eme processus elu est : temps arrivée: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=500;
    position.y=430;
    sprintf(G5,"%d",TAB[7].tempsarr);
    text2 = TTF_RenderText_Blended(police2,G5,couleurRouge);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=260;
    position.y=460;
    text2 = TTF_RenderText_Blended(police2,"temps d'éxecution: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=500;
    position.y=460;
    sprintf(G5,"%d",TAB[7].tempexe);
    text2 = TTF_RenderText_Blended(police2,G5,couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
     position.x=560;
    position.y=430;
    text2 = TTF_RenderText_Blended(police2," Le temps de Séjour: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=800;
    position.y=430;
    sprintf(G5,"%d",TabSejour[7]);
    text2 = TTF_RenderText_Blended(police2,G5,couleurBleu);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=560;
    position.y=460;
    text2 = TTF_RenderText_Blended(police2," Le temps d'Attente: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=800;
    position.y=460;
    sprintf(G5,"%d",TabAttente[7]);
    text2 = TTF_RenderText_Blended(police2,G5,couleurBleu);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    cp ++ ;
    }
    //9
    if (cp <= n)
    {position.x=10;
    position.y=490;
    text2 = TTF_RenderText_Blended(police2," Le 9eme processus elu est : temps arrivée: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=500;
    position.y=490;
    sprintf(G5,"%d",TAB[8].tempsarr);
    text2 = TTF_RenderText_Blended(police2,G5,couleurRouge);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=260;
    position.y=520;
    text2 = TTF_RenderText_Blended(police2,"temps d'éxecution: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=500;
    position.y=520;
    sprintf(G5,"%d",TAB[8].tempexe);
    text2 = TTF_RenderText_Blended(police2,G5,couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=560;
    position.y=490;
    text2 = TTF_RenderText_Blended(police2," Le temps de Séjour: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=800;
    position.y=490;
    sprintf(G5,"%d",TabSejour[8]);
    text2 = TTF_RenderText_Blended(police2,G5,couleurBleu);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=560;
    position.y=520;
    text2 = TTF_RenderText_Blended(police2," Le temps d'Attente: ",couleurNoire);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    position.x=800;
    position.y=520;
    sprintf(G5,"%d",TabAttente[8]);
    text2 = TTF_RenderText_Blended(police2,G5,couleurBleu);
    SDL_BlitSurface(text2,NULL,fenetre,&position);
    cp ++ ;}
    SDL_Flip(fenetre);

                                Tatt = tempsatt_moyen(n,TabAttente);
                                position.x =2;
                                position.y=550;
                                sprintf(G,"%f",Tatt);
                                text = TTF_RenderText_Blended(police2,"Le Temps d'attente moyen :",couleurNoire);
                                SDL_BlitSurface(text,NULL,fenetre,&position);
                                position.x =320;
                                position.y=550;
                                text = TTF_RenderText_Blended(police2,G,couleurRouge);
                                SDL_BlitSurface(text,NULL,fenetre,&position);


                                Tse = tempsejour_moyen (n,TabSejour) ;
                                position.x =2;
                                position.y=580;
                                sprintf(G,"%f",Tse);
                                text = TTF_RenderText_Blended(police2,"Le Temps de Séjour Moyen :",couleurNoire);
                                SDL_BlitSurface(text,NULL,fenetre,&position);
                                position.x =320;
                                position.y=580;
                                text = TTF_RenderText_Blended(police2,G,couleurRouge);
                                SDL_BlitSurface(text,NULL,fenetre,&position);



     SDL_Flip(fenetre);

    }
    }

    }

    }
    }
    SDL_FreeSurface(fenetre);
    SDL_Quit();
    return 0;

}

