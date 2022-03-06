#include "fonction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

int main(int argc, char **argv)
{


      if (argc !=5)
      {
               
        
        fprintf(stderr,"Usage : <./prog>  <dataset> <nombreNoeud>  <dampingFactor>  <tolérence>  \n");
        exit(EXIT_FAILURE);
           
       }
     srand( time( NULL ) );
     Matrice matrice,matriceT,Gout;
     Vecteur v1,v2;
     Noeud *node=NULL;

       //node=malloc(sizeof(Noeud)*atoi(argv[2]));
         node=malloc(atoi(argv[2])*sizeof(Noeud));
           

           printf("Creation des Matrices ...[OK]\n");
           generer_matrice(&matrice,atoi(argv[2]));
           generer_matrice(&matriceT,atoi(argv[2]));
           generer_matrice_gout(&Gout,atoi(argv[2]));
           afficher_matrice(&matrice);

           printf("Initialisation des vecteurs ...[OK] \n");
           genere_vecteur(&v1,atoi(argv[2]));
           vecteur_init0(&v2,atoi(argv[2]));
           printf("Vecteur de depart\n");
           afficher_vecteur(&v1);

           printf("Vecteur de rangs\n");
           vecteur_init0(&v2,atoi(argv[2]));
          
           printf("Matrice d'ajascence : \n");

           creer_matrice_adjacente(&matrice,argv[1]);
           afficher_matrice(&matrice);
           
           printf("Matrice de transition :\n");
           calculer_matrice_transition2(&matrice,&matriceT);
           afficher_matrice(&matriceT);
           creer_graphe(node,&matrice);
           infection(node,3,atoi(argv[2]));

           //vaccination(node, atoi(argv[2]));
           //printf(" succ=%d \n",node[4].suivant[0]);
           //printf("valeur=%d  etat=%u    pct=%f   succ= %d  \n",node[4].valeur,node[4].etat,node[4].prob_infect,node[4].suivant[0]);
            
            
            printf("Matrice de gout :\n");

           afficher_matrice(&Gout);
         
           printf("Calcul pageRank : \n");

           //calcul_pageRank(&matriceT,&Gout ,&v1,&v2,atoi(argv[2]),atof(argv[3]),atof(argv[4]));
             
  
    
     free(v1.val);
     free(v2.val);
     free(matrice.mat);
     free(matriceT.mat);
     free(Gout.mat);

     
	return 0;
}