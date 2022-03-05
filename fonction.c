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


       /* float *tab;
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


void calcul_pageRank(Matrice *matrice,Matrice *Gout , Vecteur *vecteur1,Vecteur *vecteur2,int nbreNoeud,double dampingFactor,double tolerence){
              /*Cette fonction permet calculer le pageRank amélioré */

              double erreur=1.0;
              int it=0;
              double B=(1.0-dampingFactor)/nbreNoeud;//constante


              printf("Valeur de B:= %f\n",B );


              clock_t debut=clock();
	          while(erreur > tolerence){


                   erreur=0.0;


                 //cette boucle permet de calculer : Xk+1=d*P*X + ((1-d)/n)*GX
                 for(int i =0; i < vecteur2->taille_vecteur; ++i) {

                        for(int j =0; j <  vecteur2->taille_vecteur; ++j){


                            vecteur2->val[i] += (dampingFactor*(matrice->mat[i][j] * vecteur1->val[j])) + (B*(Gout->mat[i][j]*vecteur1->val[j]));
                        }

	               }

                    normaliser_vecteur(vecteur2);

                    printf("------vecteur des rangs----------\n");
                   afficher_vecteur(vecteur2);


                   for (int i = 0; i < vecteur2->taille_vecteur; ++i)
                   {

                        double delta=vecteur2->val[i]-vecteur1->val[i];
                        erreur+=pow(delta,2);

                   }
                       erreur=sqrt(erreur);



                    printf("Valeur de l'erreur :=%.12f\n",erreur );


                 for (int k = 0; k< vecteur1->taille_vecteur; ++k){
                      vecteur1->val[k]=vecteur2->val[k];
                 }

                it+=1;

                printf("Nombre d'itteration := %d\n",it );
                generer_data_courbe(it,"data.txt");

    }
    clock_t fin=clock();
    double temps=(double)(fin-debut)/CLOCKS_PER_SEC;

   printf("temps execution:= %f\n",temps );

}

/*partie propagation de maladie*/

void creer_graphe(Noeud *tab,Matrice *MatTransision){
    /*Cette fonction permet de creer un graphe*/

     int nbVoisin=0;
     for (size_t j = 0; j < MatTransision->colonne; j++) {

           nbVoisin=0;
           Noeud node;
           node.origine=j;
           node.etat.sain
           node.prob_infect=0.0;
        
           for (size_t i = 0; i < MatTransision->colonne; i++) {
                   /*calcul de numbre de successeur*/

                  if (MatTransision->mat[j][i] !=0)
                  {
                        nbVoisin++;
                  }
           }

           node.suivant=malloc(sizeof*nbVoisin);

           for (size_t k = 0; k < MatTransision->colonne; k++) {
                  
                   /*Construction de la liste des voisins */
                  if (MatTransision->mat[j][k] !=0)
                  {
                        node.suivant[k]=k;
                  }
            }
            
            tab[j]=node;

     }

}


void infection(Noeud *tab,int aInfecter,int nbNoeud){

      /*Cette fonction permet d'infecter des noeud*/

      for (int i = 0; i <  nbNoeud; ++i)
      {
          
      }


     /*propagation*/


      

    
    
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
