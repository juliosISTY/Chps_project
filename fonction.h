#ifndef ___FONCTIONS___
#define ___FONCTIONS___

#include <time.h>

/*Definition des strucutures */

typedef struct {
	int taille_vecteur;
	double *val;
	double norme;
} Vecteur ;

typedef struct {
	int ligne ;
	int colonne ;
	double **mat;
} Matrice;

typedef enum {
     sain,
     infecté,
     vacciné,
     guéri

}Etat;

typedef struct {
	int nbVoisin;
	Etat etat;
	int valeur;
	double prob_infect;
     int origine;
	int *suivant;
} Noeud;


/*Definition des fonctions partie 2*/
void creer_graphe(Noeud *tab,Matrice *MatTransision);
void infection(Noeud *tab,int aInfecter,int nbNoeud);
void Afficher_graphe(void);
void vaccination(Noeud *tab, int nbreNoeud);




/*Definition des fonctions partie 1*/
void generer_matrice(Matrice *matrice,int nbreNoeud);
void creer_matrice_adjacente(Matrice *matrice,char *dataset);
void genere_vecteur(Vecteur *vec,int nbreNoeud);
void calcul_pageRank(Matrice *matrice,Matrice *Gout , Vecteur *vecteur1,Vecteur *vecteur2,int nbreNoeud,double dampingFactor,double tolerence);
void normaliser_vecteur(Vecteur *vecteur);
void afficher_vecteur(Vecteur *vecteur);
void afficher_matrice(Matrice *matrice);
void calculer_matrice_transition2(Matrice *matrice,Matrice *matriceT);
void generer_matrice_gout(Matrice *Gout,int nbreNoeud);
void vecteur_init0(Vecteur * v,int nbreNoeud);
void generer_data_courbe(int iteration,const char* data );


#endif
