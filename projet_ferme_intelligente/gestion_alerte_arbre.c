//Gestion des alertes par priorité 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Structure pour une alerte
typedef struct alerte {
    int ID;
    char *description;
    int priorite;  // Priorité de l'alerte, plus petit est plus prioritaire
} alerte;

// Structure du nœud de l'arbre AVL
typedef struct arbre_avl {
    alerte *alerte;
    struct arbre_avl *gauche;
    struct arbre_avl *droit;
    int hauteur;
} arbre_avl;

// Fonction pour obtenir la hauteur d'un nœud
int hauteur(arbre_avl *n) {
    if (n == NULL) return 0;
    return n->hauteur;
}

// Fonction pour obtenir le facteur de balance d'un nœud
int facteur_balance(arbre_avl *n) {
    if (n == NULL) return 0;
    return hauteur(n->gauche) - hauteur(n->droit);
}

// Fonction pour effectuer une rotation droite
arbre_avl* rotation_droite(arbre_avl *y) {
    arbre_avl *x = y->gauche;
    arbre_avl *T2 = x->droit;

    // Effectuer la rotation
    x->droit = y;
    y->gauche = T2;

    // Mettre à jour les hauteurs
    y->hauteur = fmax(hauteur(y->gauche), hauteur(y->droit)) + 1;
    x->hauteur = fmax(hauteur(x->gauche), hauteur(x->droit)) + 1;

    return x;
}

// Fonction pour effectuer une rotation gauche
arbre_avl* rotation_gauche(arbre_avl *x) {
    arbre_avl *y = x->droit;
    arbre_avl *T2 = y->gauche;

    // Effectuer la rotation
    y->gauche = x;
    x->droit = T2;

    // Mettre à jour les hauteurs
    x->hauteur = fmax(hauteur(x->gauche), hauteur(x->droit)) + 1;
    y->hauteur = fmax(hauteur(y->gauche), hauteur(y->droit)) + 1;

    return y;
}

// Fonction pour insérer une alerte dans l'arbre AVL
arbre_avl* inserer_arbre_avl(arbre_avl *racine, alerte *a) {
    if (racine == NULL) {
        arbre_avl *nouveau = (arbre_avl *)malloc(sizeof(arbre_avl));
        nouveau->alerte = a;
        nouveau->gauche = nouveau->droit = NULL;
        nouveau->hauteur = 1;
        return nouveau;
    }

    if (a->priorite < racine->alerte->priorite) {
        racine->gauche = inserer_arbre_avl(racine->gauche, a);
    } else if (a->priorite > racine->alerte->priorite) {
        racine->droit = inserer_arbre_avl(racine->droit, a);
    } else {
        return racine; // Pas de doublons
    }

    // Mettre à jour la hauteur du nœud actuel
    racine->hauteur = 1 + fmax(hauteur(racine->gauche), hauteur(racine->droit));

    // Vérifier et corriger les facteurs de balance
    int balance = facteur_balance(racine);

    // Si le nœud devient déséquilibré, il existe 4 cas :

    // Cas de rotation à droite
    if (balance > 1 && a->priorite < racine->gauche->alerte->priorite) {
        return rotation_droite(racine);
    }

    // Cas de rotation à gauche
    if (balance < -1 && a->priorite > racine->droit->alerte->priorite) {
        return rotation_gauche(racine);
    }

    // Cas de rotation gauche-droite
    if (balance > 1 && a->priorite > racine->gauche->alerte->priorite) {
        racine->gauche = rotation_gauche(racine->gauche);
        return rotation_droite(racine);
    }

    // Cas de rotation droite-gauche
    if (balance < -1 && a->priorite < racine->droit->alerte->alerte->priorite) {
        racine->droit = rotation_droite(racine->droit);
        return rotation_gauche(racine);
    }

    return racine;
}

// Fonction pour afficher l'arbre AVL en ordre
void afficher_arbre_avl(arbre_avl *racine) {
    if (racine != NULL) {
        afficher_arbre_avl(racine->gauche);
        printf("Alerte ID: %d - Description: %s - Priorité: %d\n", racine->alerte->ID, racine->alerte->description, racine->alerte->priorite);
        afficher_arbre_avl(racine->droit);
    }
}

// Fonction pour créer une alerte
alerte* creer_alerte(int ID, char *description, int priorite) {
    alerte *nouvelle_alerte = (alerte *)malloc(sizeof(alerte));
    nouvelle_alerte->ID = ID;
    nouvelle_alerte->description = description;
    nouvelle_alerte->priorite = priorite;
    return nouvelle_alerte;
}

// Exemple d'utilisation dans le main
int main() {
    arbre_avl *racine = NULL;

    // Création de quelques alertes
    alerte *alerte1 = creer_alerte(1, "Alerte température élevée", 1);
    alerte *alerte2 = creer_alerte(2, "Alerte humidité trop basse", 3);
    alerte *alerte3 = creer_alerte(3, "Alerte fuite détectée", 2);

    // Insertion des alertes dans l'arbre AVL
    racine = inserer_arbre_avl(racine, alerte1);
    racine = inserer_arbre_avl(racine, alerte2);
    racine = inserer_arbre_avl(racine, alerte3);

    // Affichage des alertes en ordre de priorité
    afficher_arbre_avl(racine);
    return 0;
}

