#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "declaration.h"
//-----------------------------fonction pour la gestion de la ferme :
void gestion_ferme(ferme *F,alertes **A,file *file_notif){
	int choix;
	printf("clique sur :\n1: pour la gestion des serres\n2: pour la gestion de champ ouvert\n3: pour la gestion du reserve d'eau\n4: pour la gestion des panneaux solaires\n5: pour afficher les alertes\n6: pour afficher les notifications\n");
do{
	printf("\n==> Entrez votre choix : ");
	scanf("%d",&choix);
}while(choix!=1 && choix!=2 && choix!=3 && choix!=4 && choix!=5 && choix!=6 );
    switch(choix){
    	case 1:
    		gestion_serres(&(F->serres),A,file_notif);
    		break;
    	case 2:
    		gestion_champs(&(F->champs),A,file_notif);
    		break;
    	case 3:
    		gestion_reserves_eau(&(F->reserves_eau),A,file_notif);
    		break;
    	case 4:
    		gestion_panneaux(&(F->panneaux_sol),file_notif);
    		break;
    	case 5:
    		afficher_alertes(*A);
    		break;
    	case 6:
    		afficher_File(file_notif);
    		break;
    	
	}
}

//------------------------------- fonction pour la gestion des serres :
void gestion_serres(serres **S,alertes **A,file *file_notif){
	int choix;
	int id_serre,id_temp,id_hum,id_pluit;
	notification *nv=NULL;
	// Affichage des options disponibles pour la gestion des serres
    printf("\n--------gestion des serres--------\n");
	printf("clique sur :\n1: pour l'affichage\n2: pour ajouter une serre\n3: pour supprimer une serre\n4: pour changer la val d'un capteur\n");
do{
	printf("entrez votre choix : ");
	scanf("%d",&choix);
}while(choix!=1 && choix!=2 && choix!=3 && choix!=4);
    switch(choix){
    	case 1:
    		// Affichage des serres
    		afficher_serres(*S);
    		break;
    	case 2:
    	    // Ajouter une nouvelle serre
    		printf("entrez id de la nouvelle serre :");
    		scanf("%d",&id_serre);
    		printf("entrez id du capteur temperature|humidite|pluit:");
    		scanf("%d|%d|%d",&id_temp,&id_hum,&id_pluit);
    		serre *ns=creat_serre(id_serre,id_temp,id_hum,id_pluit);
    		ajouter_serres(S,ns);
    		nv=creat_notif("Ajout d'une serre ",id_serre);// Créer une notification pour l'ajout de serre
            Enfiler(file_notif,nv);
    		fichier__serres(*S,id_serre);// Mettre à jour le fichier des serres
    		break;
    	case 3:
    		if(*S==NULL){
		      printf("il n'y a pas de serres !\n");
		      return;
	        }
    		printf("entrez l'id de la serre a supprimer :");
    		scanf("%d",&id_serre);
    		supprimer_serres(S,id_serre);
    		nv=creat_notif("suppression d'une serre ",id_serre);// Créer une notification pour la suppression de serre
            Enfiler(file_notif,nv);
    		break;
    	case 4:
    		// Modifier les valeurs des capteurs d'une serre existante
    		printf("entrez id du serre :");
    		scanf("%d",&id_serre);
    		int val_temp,val_hum,val_pluit;
    		printf("entrez la nouvelle val du capteur temperature|humidite|pluit (-1 si tu veut garder sa valeur) :");
    		scanf("%d|%d|%d",&val_temp,&val_hum,&val_pluit);
    		changer_cap_value_serre(*S,id_serre,val_temp,val_hum,val_pluit);
    		nv=creat_notif("Changement des valeurs des capterus d'une serre ",id_serre);// Créer une notification pour le changement de valeurs
            Enfiler(file_notif,nv);
            // Ajuster les serres et mettre à jour le fichier
    		ajustement_serres(*S,A,file_notif);
    		fichier__serres(*S,id_serre);
    		break;
    	
	}
}
//---------------------------------------------------- fonction pour la gestion des champs :
void gestion_champs(champs **CH,alertes **A,file *file_notif){
	int choix;
	int id_champ,id_temp,id_hum,id_ph;
	notification *nv=NULL;
	printf("\n--------gestion des champs--------\n");
	// Affichage des options disponibles pour la gestion des champs
	printf("clique sur :\n1: pour l'affichage\n2: pour ajouter un champ\n3: pour supprimer un champ\n4: pour changer la val d'un capteur\n");
do{
	printf("entrez votre choix : ");
	scanf("%d",&choix);
}while(choix!=1 && choix!=2 && choix!=3 && choix!=4);
    switch(choix){
    	case 1:
    		// Affichage des champs ouverts
    		afficher_champs(*CH);
    		break;
    	case 2:
    		// Ajouter un nouveau champ
    		printf("entrez id du nouveau champ :");
    		scanf("%d",&id_champ);
    		printf("entrez id du capteur temperature|humidite|ph:");
    		scanf("%d|%d|%d",&id_temp,&id_hum,&id_ph);
    		champ_ouvert *nch=creat_champ(id_champ,id_temp,id_hum,id_ph);
    		ajouter_champs(CH,nch);
    		nv=creat_notif("Ajout d'un champ ",id_champ);// Créer une notification pour l'ajout de champ
            Enfiler(file_notif,nv);
    		fichier__champs(*CH,id_champ);// Mettre à jour le fichier des champs
    		break;
    	case 3:
    		if(*CH==NULL){
		      printf("il n'y a pas de champs !\n");
		      return;
	        }
    		printf("entrez l'id du champ a supprimer :");
    		scanf("%d",&id_champ);
    		supprimer_champs(CH,id_champ);
    		nv=creat_notif("suppression d'un champ ",id_champ);// Créer une notification pour la suppression de champ
            Enfiler(file_notif,nv);
    		break;
    	case 4:
    		// Modifier les valeurs des capteurs d'un champ existant
    		printf("entrez id du champ :");
    		scanf("%d",&id_champ);
    		int val_temp,val_hum,val_ph;
    		printf("entrez la nouvelle val du capteur temperature|humidite|ph (-1 si tu veut garder sa valeur) :");
    		scanf("%d|%d|%d",&val_temp,&val_hum,&val_ph);
    		changer_cap_value_champ(*CH,id_champ,val_temp,val_hum,val_ph);
    		nv=creat_notif("Changement des valeurs des capterus d'un champ ",id_champ);// Créer une notification pour le changement de valeurs
            Enfiler(file_notif,nv);
            // Ajuster les champs et mettre à jour le fichier
    		ajustement_champs(*CH,A,file_notif);
    		fichier__champs(*CH,id_champ);
    		break;
    	
	}
}

// ---------------------------------------------fonction pour la gestion des panneaux solaires :
void gestion_panneaux(panneaux_sol **P,file *file_notif){
	int choix;
	int id_panneau,id_lum;
	notification *nv=NULL;
	printf("\n-------gestion des panneaux-------\n");
	// Affichage des options disponibles pour la gestion des panneaux solaires
	printf("clique sur :\n1: pour l'affichage\n2: pour ajouter un panneau\n3: pour supprimer un panneaux\n4: pour changer la val d'un capteur\n");
do{
	printf("entrez votre choix : ");
	scanf("%d",&choix);
}while(choix!=1 && choix!=2 && choix!=3 && choix!=4);
    switch(choix){
    	case 1:
    		// Affichage des panneaux solaires
    		afficher_panneaux(*P);
    		break;
    	case 2:
    		// Ajouter un nouveau panneau solaire
    		printf("entrez id du nouveau panneau :");
    		scanf("%d",&id_panneau);
    		printf("entrez id du capteur luminosite:");
    		scanf("%d",&id_lum);
    		panneau_sol *np=creat_panneau(id_panneau,id_lum);
    		ajouter_panneaux(P,np);
    		nv=creat_notif("Ajout d'un panneau ",id_panneau);// Créer une notification pour l'ajout de panneau
            Enfiler(file_notif,nv);
    		fichier__panneaux(*P,id_panneau);// Mettre à jour le fichier des panneaux
    		break;
    	case 3:
    		if(*P==NULL){
		      printf("il n'y a aucun panneau !\n");
		      return;
	        }
    		printf("entrez l'id du panneau a supprimer :");
    		scanf("%d",&id_panneau);
    		supprimer_panneaux(P,id_panneau);
    		nv=creat_notif("suppression d'un panneau ",id_panneau);// Créer une notification pour la suppression de panneau
            Enfiler(file_notif,nv);
    		break;
    	case 4:
    		// Modifier les valeurs des capteurs d'un panneau solaire existant
    		printf("entrez id du panneau :");
    		scanf("%d",&id_panneau);
    		int nvl_val;
    		printf("entrez la nouvelle val de son cap luminosite :");
    		scanf("%d",&nvl_val);
    		changer_cap_value_panneau(*P,id_panneau,nvl_val);
    		nv=creat_notif("Changement des valeurs des capterus d'un panneau ",id_panneau);// Créer une notification pour le changement de valeurs
            Enfiler(file_notif,nv);
            // Ajuster les panneaux solaires et mettre à jour le fichier
    		ajustement_panneau_sol(*P,file_notif);
    		fichier__panneaux(*P,id_panneau);
    		break;
    		
    	
	}
}
//------------------------------------------------- fonction pour la gestion des reserves d'eaux :
void gestion_reserves_eau(reserves_eau **R,alertes **A,file *file_notif){
	int choix;
	int id_reserve,id_niveau,id_fuit,id_pression;
	notification *nv=NULL;
	printf("\n-------gestion des reserves-------\n");
	// Affichage des options disponibles pour la gestion des réserves d'eau
	printf("clique sur :\n1: pour l'affichage\n2: pour ajouter un reserve\n3: pour supprimer un reserve\n4: pour changer la val d'un capteur\n");
do{
	printf("\nentrez votre choix : ");
	scanf("%d",&choix);
}while(choix!=1 && choix!=2 && choix!=3 && choix!=4);
    switch(choix){
    	case 1:
    		// Affichage des réserves d'eau
    		afficher_reserves(*R);
    		break;
    	case 2:
    		// Ajouter une nouvelle réserve d'eau
    		printf("entrez id du nouveau reserve :");
    		scanf("%d",&id_reserve);
    		printf("entrez id du capteur niveau|fuit|pression:");
    		scanf("%d|%d|%d",&id_niveau,&id_fuit,&id_pression);
    		reserve_eau *nr=creat_reserve(id_reserve,id_niveau,id_fuit,id_pression);
    		ajouter_reserves(R,nr);
    		nv=creat_notif("Ajout d'un reserve ",id_reserve);// Créer une notification pour l'ajout de réserve
            Enfiler(file_notif,nv);
    		fichier__reserves(*R,id_reserve);// Mettre à jour le fichier des réserves
    		break;
    	case 3:
    		if(*R==NULL){
		      printf("il n'y a aucun reserve !\n");
		      return;
	        }
    		printf("entrez l'id du reserve a supprimer :");
    		scanf("%d",&id_reserve);
    		supprimer_reserves(R,id_reserve);
    		nv=creat_notif("suppression d'un reserve ",id_reserve);// Créer une notification pour la suppression de réserve
            Enfiler(file_notif,nv);
    		break;
    	case 4:
    	    // Modifier les valeurs des capteurs d'une réserve existante
    		printf("entrez id du reserve :");
    		scanf("%d",&id_reserve);
    		int val_niveau,val_fuit,val_pression;
    		printf("entrez la nouvelle val du capteur niveau_eau|fuit|pression (-1 si tu veut garder sa valeur) :");
    		scanf("%d|%d|%d",&val_niveau,&val_fuit,&val_pression);
    		changer_cap_value_reserve(*R,id_reserve,val_niveau,val_fuit,val_pression);
    		nv=creat_notif("Changement des valeurs des capterus d'un reserve ",id_reserve);// Créer une notification pour le changement de valeurs
            Enfiler(file_notif,nv);
            // Ajuster les réserves d'eau et mettre à jour le fichier
    		ajustement_reserves(*R,A,file_notif);
    		fichier__reserves(*R,id_reserve);
    		break;
    	
	}
}
