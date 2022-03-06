#include "fonction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <time.h>



void generer_matrice(Matrice *matrice,int nbreNoeud){

    /*
      Cette fonction permet de creer une matrice par defaut
      initialiser a Zero
    */

    matrice->ligne=nbreNoeud;
    matrice->colonne=nbreNoeud;

    matrice->mat=(double**)malloc(nbreNoeud*sizeof(double*));

     for (int i = 0; i < nbreNoeud; i ++){
        matrice->mat[i] = (double*)malloc(nbreNoeud*sizeof(double));
    }

    if (matrice->mat == NULL) {

        exit(0);

    } else {

        for (int i = 0; i < nbreNoeud; i ++) {
            for (int j = 0; j < nbreNoeud; j ++) {
                matrice->mat[i][j]=0;

            }
        }
    }

}





void generer_matrice_gout(Matrice *Gout,int nbreNoeud){

    /*
      Cette fonction permet de creer la matrice GOUT
    */

    Gout->ligne=nbreNoeud;
    Gout->colonne=nbreNoeud;

    Gout->mat=(double**)malloc(nbreNoeud*sizeof(double*));

     for (int i = 0; i < nbreNoeud; i ++){
        Gout->mat[i] = (double*)malloc(nbreNoeud*sizeof(double));
    }

    if (Gout->mat == NULL) {

        exit(0);

    } else {

        for (int i = 0; i < nbreNoeud; i ++) {
            for (int j = 0; j < nbreNoeud; j ++) {
                Gout->mat[i][j]=1.0;

            }
        }
    }

}




void creer_matrice_adjacente(Matrice *matrice,char *dataset){

    /*
      Cette fonction permet de creer la matrice d'adjascence
      via le fichier qui nous sert de dataset
    */


   int i, j, node1, node2;
   FILE *fichier=NULL;

   //dataset/p2p-Gnutella09.txt

    fichier = fopen(dataset, "r");

    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier..\n");
        printf("Verifier si vous avez renseigné le bon fichier!");

        exit(1);
    }

   char line[256],delim[] ="\t ", *ptr =NULL;

    while(fgets(line, sizeof(line),fichier)){
        if (line[0]!='#')
        {

            ptr = strtok(line, delim);
            i=0;
            while(ptr != NULL){
                if (i==0)
                {
                    node1=atoi(ptr);

                }else{
                     node2=atoi(ptr);
                }
                i++;

                    ptr = strtok(NULL, delim);
          }

           // printf("Node 1: %d, Node 2: %d\n", node1, node2);
            matrice->mat[node1][node2] = 1;
           // printf("In matrice A[%d][%d]: %f\n", node1, node2, matrice->mat[node1][node2]);

        }

    }

}


void calculer_matrice_transition2(Matrice *matrice,Matrice *matriceT){

    /*Cette fonction permet de calculer la matrice de transition*/

      for (int i = 0; i < matrice->ligne; ++i)
      {
            for (int j = 0; j < matrice->ligne; ++j)
            {
                     if (matrice->mat[i][j]==0.0)
                      {
                            matriceT->mat[j][i]=0.0;
                      }else{
                           matriceT->mat[j][i]=1.0;
                      }

            }
      }


        /*float *tab;
        tab=malloc(matrice->ligne*sizeof(tab));
        if(tab==NULL)
            fprintf(stderr, "malloc erreur");
        for(int i=0;i<matrice->ligne;i++){
            for(int j=0;j<matrice->ligne;j++){
                if(matrice->mat[i][j]==1.0){
                    tab[i]=tab[i]+1;
            }
        }

      }*/
      printf("\n");


     /*Transformation en matrice de transition*/

         int link_out=0;

          for (int j = 0; j < matriceT->ligne; ++j)
          {
                  link_out=0;

                  for (int i = 0; i < matriceT->ligne; ++i)
                  {
                       link_out=link_out+ matriceT->mat[i][j];
                  }


                   if (link_out !=0)
                   {

                       for (int l = 0; l<matriceT->ligne; ++l){

                            matriceT->mat[l][j]=matriceT->mat[l][j]/link_out;
                      }

                   }

          }

}


void genere_vecteur(Vecteur *vec,int nbreNoeud){
    /*
      Cette fonction permet de generer un vecteur
      de position initial
    */


   srand((double)time(NULL));

   vec->val = (double*) malloc(nbreNoeud*sizeof(double));

   if ( vec->val == NULL)
   {
   	  exit(1);
   }

    vec->taille_vecteur =nbreNoeud;

     for (int i = 0; i < nbreNoeud; ++i)
     {
     	 vec->val[i]=1.0/nbreNoeud;
     }
}


void vecteur_init0(Vecteur * v,int nbreNoeud){

       /*Cette fonction permet de generer un vecteur
        initialisé a zéro
        */

       v->val = (double*) malloc(nbreNoeud*sizeof(double));
       if (v->val==NULL)
       {
           exit(0);
       }

      v->taille_vecteur =nbreNoeud;

      for (int i = 0; i <  v->taille_vecteur; ++i)
      {
           v->val[i]=0;
      }
}




/*partie propagation de maladie*/

void creer_graphe(Noeud *tab,Matrice *MatTransision){
    /*Cette fonction permet de creer un graphe*/

     int nbVoisin=0;
     int  j ,k,l=0;
     for (j = 0; j < MatTransision->colonne; j++) {

           nbVoisin=0;
           Noeud node;
           node.valeur=j;
           node.etat=sain;
           node.prob_infect=5.0;
           node.transmis=faux;
        
           for (int i = 0; i < MatTransision->colonne; i++) {
                   /*calcul de numbre de successeur*/

                  if (MatTransision->mat[j][i] !=0)
                  {
                        nbVoisin++;
                  }
           }

           printf("nb voisin de (%d) = %d \n",j,nbVoisin);
           node.suivant=(int*)malloc(sizeof(int)*nbVoisin);
            l=0;
           for (k = 0; k < MatTransision->colonne; k++) {
                  
                   /*Construction de la liste des voisins */
                  if (MatTransision->mat[j][k] !=0)
                  {
     
                        printf("(%d)------> (%d ):\n",j,k);
                        node.suivant[l]=k;
                        printf("suivant[%d]=%d\n",j,node.suivant[k]);
                        l++;
                         
                  }
                  //printf("j=(%d) et k=(%d) \n",j,k);
            }
            
            //printf("into the fonction valeur=%d  etat=%u    pct=%f   transmis=%u \n",node.valeur,node.etat,node.prob_infect,node.transmis);
            node.nbVoisin=nbVoisin;
            tab[j]=node;

     }

}


void infection(Noeud *tab,int aInfecter,int nbNoeud){
    /*
      Cette fonction simule la propagation du virus 
      dans un grave
    */

      int n,last=-1;
      int dejaVu[aInfecter];


      /*Ce tableau va permettre de stocker des valeur deja tirer par le redome*/
      for (int i = 0; i < aInfecter; ++i)
                dejaVu[i]=-1;

   
      for (int i = 0; i < aInfecter; ++i){  


                n = rand() % 4 + 1;
                for (int i = 0; i < aInfecter; ++i)
                {    
                     while (dejaVu[i]==n)
                     {
                           n = rand() % 4 + 1;   
                     }
                    
                      tab[n].etat=infecté;
                }
                printf("Le patients zero numero %d : %d \n",i,n);
                dejaVu[i]=n;
                 //int n = (rand()/(int) RAND_MAX)*(4-0)+0;   
                // printf("Noeud porteur du virus initialement : %d \n",n);
                 //tab[n].etat=infecté;
                 //last=n;
                
        }
           
         
    printf("Bilan des patients 0 :\n");
    printf("------------------------------------------------------------------------------------\n");    
    for (int i = 0; i < nbNoeud; ++i)
    {
        printf("Noeud: %d, status: %u   transmis: %u \n", tab[i].valeur,tab[i].etat,tab[i].transmis);
    }
      
    /*Propagation du virus*/
    

    printf("Propagation du virus\n");
    printf("------------------------------------------------------------------------------------\n"); 
    int phase=0;

    do{

    for (int i = 0; i < nbNoeud; ++i){
        
          if (tab[i].etat==1 && tab[i].transmis==0)
          {
              tab[i].transmis=vrai;
              for (int j = 0; j < tab[i].nbVoisin; ++j)
              {
                    /*infection des voisins*/

                    printf("Le Noeud %d peut potentielement infecter le Noeud %d \n",i,tab[i].suivant[j]);

                    n = rand() % 100 ;  
                    printf("Probabilité := %d\n", n);
                    
                    if (n<= 80)
                    {
                        if (tab[tab[i].suivant[j]].etat!=1)
                        {
                      
                            tab[tab[i].suivant[j]].etat=infecté;
                            tab[tab[i].suivant[j]].origine=i;
                            printf("Noeud %d infecte le Noeud %d \n",i,tab[i].suivant[j]);
                        
                        } 
                     

                    }
                   
              }
     
          }
       }
         

        for (int i = 0; i < nbNoeud; ++i){
        printf("Noeud: %d, status: %u   nbVoisin: %d    transmis: %u \n", tab[i].valeur,tab[i].etat,tab[i].nbVoisin,tab[i].transmis);
        }

       printf("Phase: %d\n",phase);

        char rep,y='y',n='n';


        do{

          printf("Voulez-vous appliquer une  vaccination dans cette phase[y/n]: ");
          scanf("%c",&rep);

        }while(!strcmp(&rep,&y) || !strcmp(&rep,&n));

        if (strcmp(&rep,&y))
        {
              
              printf("Hello world !\n");            
          
        }

      phase++;

  }while(phase <5);


}




/*partie vaccination des individus*/

void vaccination(Noeud *tab, int nbreNoeud){

    //srand((int)time(NULL));
    printf("----------------------------------------------\n");


    // cherche max tab de rangs
    double max = tab[0].prob_infect;
    for (int i = 0; i <  nbreNoeud; ++i)
      {
        if (tab[i].prob_infect>max)
            max = tab[i].prob_infect;
               
      }
    printf("valeur max=%f  \n",max);
    
    // compte le nombre le nbre d'individus ayant une proba d'infection entre [max; max-0.2]
    int nbIndividus = 0;
    for (int i = 0; i <  nbreNoeud; ++i)
      {
        if (tab[i].prob_infect>=(max - 0.2))
            nbIndividus++;
               
      }

    printf("most infected individus = %d  \n",nbIndividus);

    // 
    int y = (rand()/(int) RAND_MAX)*(100-30)+30;
    int nbIndaVacc = (int) ((nbIndividus*y)/100);

    printf("y = %d nbre individus à vacciner= %d  \n",y,nbIndaVacc);

    // Vaccination
    for (int i = 0; i <  nbreNoeud; ++i)
      {
        if (tab[i].prob_infect>=(max - 0.2) && nbIndaVacc>0)
        {
            if (tab[i].valeur==i)
            {
                tab[i].etat=vacciné;
                int val = (rand()/(int) RAND_MAX)*(100-1)+1;
                printf("choix vaccination = %d  \n", val);
                if (val<=24)
                    tab[i].etat=guéri;
                    tab[i].prob_infect = 0.0;

            }
            nbIndaVacc--;
        }

        printf("etat des nodes valeur=%d  etat=%u    pct=%f  \n",tab[i].valeur,tab[i].etat,tab[i].prob_infect);
        printf("----------------------------------------------\n");

        if (nbIndaVacc==0)
            break;
               
      }


}



/*---------------------------------------------------------------------------------------------*/


void generer_data_courbe(int iteration,const char* data ){

    /*Cette fonction permet de recuperer
     le nombre d'itteration par tour de boucle
    */

       FILE* fichier;

        fichier = fopen(data,"a+");
        if (!fichier) {
            perror("fopen");
            exit(EXIT_FAILURE);
    }

    fprintf(fichier, "%d\n",iteration);
    fclose(fichier);

}



void normaliser_vecteur(Vecteur *vecteur){
        /*
          paramtre: vecteur
          Cette fonction permet de normaliser un vecteur
        */

         double somme=0.0;

	     for (int i = 0; i < vecteur->taille_vecteur; ++i)
	     {
	     	     somme+=vecteur->val[i];
	     }

         vecteur->norme=somme;

         for (int j = 0; j < vecteur->taille_vecteur; ++j)
         {
         	vecteur->val[j]=(vecteur->val[j]/vecteur->norme);
         }

}



void afficher_vecteur(Vecteur *vecteur){

    /*
      Cette fonction permet d'afficher un vecteur
    */

    for (int i = 0; i < vecteur->taille_vecteur; ++i)
    {
    	  printf("%f \n",vecteur->val[i]);
    }
}


void afficher_matrice(Matrice *matrice){

    /*
      Cette fonction permet d'afficher une matrice

    */
	for (int i = 0; i < matrice->ligne; ++i)
       {

       	        for ( int j = 0; j < matrice->colonne; ++j)
       	        {
       	        	printf("%f\t",matrice->mat[i][j]);

       	        }
                printf("\n");

       }

}
