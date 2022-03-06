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

enum Etat {
     sain,
     infecte,
     vaccine,
     gueri
};

typedef struct {
	int nbVoisin;
	enum etat;
	double prob_infect;
     int origine;
	int *suivant;
} Noeud;


/*Definition des fonctions partie 2*/
void creer_tableau(Noeud **tab,Matrice *MatTransision);
void infection(Noeud **tab,Vecteur *Prob,double x);
void Afficher_graphe(void);




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
