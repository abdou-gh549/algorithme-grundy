#include <stdio.h>
#include <stdlib.h>

#define MAXBORNE    100

int grundy[MAXBORNE];

int calculeNbrGrandy(int currentPile){
    int p,q;
    int tabNimber[MAXBORNE] = {0};

    for(p = 1; p < currentPile; p++){
        for(q = 1; q<p; q++){
            if(p + q == currentPile){
                // nbr de grundy pour 2 pile => p xor q
                int nbG = grundy[p] ^ grundy[q];
                // sauv nbr de grandy deja calucluer
                tabNimber[ nbG ] = 1;
            }
        }
    }
    // choisir le nombre de grundy le plus petit qui n'exist pas dans les pile fils
    for(p = 0; p<MAXBORNE; p++ ){
        if(tabNimber[p] == 0)
            return p;
    }
}


/* retourne le nombre de Grundy de la position (0 => perdant, >0 : gagnant) */
int jeu_ordi(int tas[], int nb_tas, int *tas_choisi, int *pions) {
    int nimber=0;
    int i = 0;

    /** calcul du nombre de Grundy (nimber) de la position **/

    /******* A REMPLACER **********/

    for( i = 0; i<nb_tas; i++){
        nimber ^= grundy[ tas[i] ];
    }

    /******************************/


    if (nimber==0) {
        /** position perdante : on joue le premier coup qui nous tombe sous la main */
        *tas_choisi=0;
        *pions = 1;
        return 0;
    } else {
        /** position gagnante  : on doit trouver un coup gagnant *****/

        /**************** A REMPLIR **********************************/
        int ai = -1;
        for( i = 0; i<nb_tas; i++){
            if( (nimber ^ grundy[ tas[i] ]) <= (grundy[ tas[i] ])){
                ai = i;
                break;
            }
        }
        int p, q;
        for(p = 1; p < tas[ai]; p++){
            if( (nimber ^ grundy[ tas[ai] ] ) == ( grundy[p] ^ grundy[tas[ai]-p] )){
                        *tas_choisi = ai;
                        *pions = p;
                         return nimber;
            }
        }

        return nimber;
    }
}


void construit_tableau(int borne) {
    /** initialisation **/
    grundy[0] = grundy[1] = grundy[2] = 0;
    /** calcul nombre de grundy pour le rest**/
    int i;
    for(i = 3; i<=borne;i++){
        grundy[i] = calculeNbrGrandy(i);
    }
}

void joue_grundy(int initial) {
    int tas[initial];
    int nb_tas=1;
    int ordi_joue=1;

    tas[0] = initial;
    printf("Jeu de Grundy, avec %d pions\n",initial);
    printf("Les tas avec 1 ou 2 pions sont ignores. Le jeu s'arrete quand il n'y a plus de tas disponibles.\n");
    printf("L'ordinateur commence.");
    while (nb_tas>0) {
        int i,p;
        /* affichage */
        printf("%d tas secable(s) : ",nb_tas);
        for (i=0;i<nb_tas-1;i++) { printf("%d, ",tas[i]);  }
        printf("%d\n",tas[i]);
        if (ordi_joue) {
           /* jeu de l'ordinateur */
           /* calcul du nombre de grundy */
           int ret = jeu_ordi(tas,nb_tas,&i,&p);
           printf("Calcul de l'ordinateur : grundy = %d (position %s)\n",ret,(ret==0 ? "perdante" : "gagnante"));
           printf("Ordinateur coupe un tas a %d pions en separant %d pions (reste %d pions)\n",tas[i],p,tas[i]-p);
        } else {
            /* jeu de l'humain */
            p=-1;
            i = nb_tas;
            while (i==nb_tas) {
                printf("Nombre de pions dans le tas a couper ? ");
                scanf("%d",&p);
                i=0; while (i<nb_tas && tas[i]!=p) i++;
                if (i==nb_tas) { printf("Tas non trouve.\n"); }
            }
            p=0;
            while (p<1) {
                printf("Nombre de pions a separer du tas ? ");
                scanf("%d",&p);
                if (p<1 || p>=tas[i] || 2*p==tas[i]) {
                    printf("Nombre invalide, ou separation du tas en parties egales. Recommencer.\n");
                    p=0;
                }
            }
            printf("Humain : separation du tas %d (pions %d) en %d+%d\n",i,tas[i],p,tas[i]-p);
        }
        ordi_joue = !ordi_joue;
        tas[i] = tas[i]-p;
        if (tas[i]<=2) {
            if (p<=2) {
                printf("Ces deux tas sont mis de cote.\n");
                while (i<nb_tas-1) { tas[i] = tas[i+1]; i++; }
                nb_tas--;
            } else {
                printf("Le petit tas est mis de cote1\n");
                tas[i]=p;
            }
        } else if (p<=2) {
            printf("Le petit tas est mis de cote2 %d\n",p);
        } else {
            tas[nb_tas]=p;
            nb_tas++;
        }
    }
    if (ordi_joue) {
        printf("L'ordinateur a perdu.\n");
    } else {
        printf("L'ordinateur a gagne.\n");
    }
}


int main()
{
    int i;
    int nb;
    printf("Taille du jeu (max %d) : ",MAXBORNE-1);
    scanf("%d",&nb),
    construit_tableau(nb);
    printf("Tableau construit.\n");
    for (i=0;i<=nb;i++) {
        printf("Grundy[%d]=%d\n",i,grundy[i]);
    }
    joue_grundy(nb);
    return 0;
}
	