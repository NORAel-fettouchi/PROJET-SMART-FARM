#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include "declaration.h"
// capteur 

capteur *creat_capteur1(int id_capteur,char *type){
	capteur *cap=(capteur*)malloc(sizeof(capteur));
	cap->ID=id_capteur;
	cap->type=(char*)malloc(20*sizeof(char));
	strcpy(cap->type,type);
	cap->val=0;
	return cap;
}

capteur *creat_capteur(char *type){
	capteur *P=(capteur*)malloc(sizeof(capteur));
	int id;
	printf("entrez id du capteur %s :",type);
	scanf("%d",&id);
	P->ID=id;
	P->type=(char*)malloc((sizeof(char)*strlen(type))+1);
	strcpy(P->type,type);
	P->val=0;
	return P;
}

void supp_capteur(capteur *c){
	if(c!=NULL){
		free(c->type);
	    free(c);
	}
	return;
}

void affich_capteur(capteur *c){
	if(c!=NULL){
		printf("ID : %d\nTYPE : %s\nVALEUR : %d",c->ID,c->type,c->val);
	}
	else printf("capteur non valid!");
	return ;
}
//Changer la valeur d'un capteur deja existant version 0
void chang_val_cap(capteur **c,int nvl_val){
	if(*c==NULL){
	printf("Erorr : Capteur invalide!");
	return;
	}
	(*c)->val=nvl_val;
	return;
}
//Changer la valeur d'un capteur deja existant version 1
void chang_val_cap1(capteur **c,char *type,int nvl_val){
	if(*c==NULL){
	printf("Erorr !");
	return;
	}
	(*c)->val=nvl_val;
	return;
}



/*------------------------------------------------------------------------------------------------------------PANNEAUX SOLAIRES-----*/

//Ajouter un nouveau panneau solaire
Panneaux_Sol *CreatPannSol(int id){
	Panneaux_Sol *nv=(Panneaux_Sol*)malloc(sizeof(Panneaux_Sol));
	nv->ID=id;
	nv->ajustement_panneaux=0;
	nv->etat_journnee=NULL;
	nv->luminosite=NULL;
	nv->next=NULL;
	return nv;
}


void Ajout_pann_sol(Panneaux_Sol **P,int id){
	Panneaux_Sol *nv=CreatPannSol(id);
	if(*P==NULL){
		*P=nv;
		return;
	}
	Panneaux_Sol *ptr=*P;
	while(ptr->next!=NULL){
		ptr=ptr->next;
	}
	ptr->next=nv;
	return;
}

//Ajouter un capteur a un panneau solaire 
void ajout_cap_a_pann_sol(Panneaux_Sol *P,int id_cap,char *type,int val){
	if(P==NULL){
		printf("\nError :l'id %d du panneau solaire est invalide !\n");return;
	}
    P->luminosite=(capteur*)malloc(sizeof(capteur));
	P->luminosite=creat_capteur1(id_cap,type);
	chang_val_cap(&(P->luminosite),val);
	
}

//Recherche d'un panneau solaire avec un id specifique et le retourner
Panneaux_Sol *Recherch_pann_sol(Panneaux_Sol *P,int id){
    Panneaux_Sol *curr=P;
	while(curr!=NULL && curr->ID!=id){
		curr=curr->next;
	}
	if(curr==NULL){
		printf("\nl'id : %d est invalide (panneau non trouvee)!\n",id);
		return NULL;
	}
	else return curr;
}
//Supprimer un panneau solaire selon son id  
void delet_pann_sol(Panneaux_Sol **P, int id){
	Panneaux_Sol *to_remove=NULL;
	if(*P==NULL){
		printf("il n'existe plus de panneaux solaires");
		return ;
	}
	else if((*P)->ID==id){
		to_remove=*P;
		*P=(*P)->next;
		if(to_remove->luminosite!=NULL)supp_capteur(to_remove->luminosite);
		if(to_remove->etat_journnee!=NULL)free(to_remove->etat_journnee);
		free(to_remove);
	}
	else{
			Panneaux_Sol *ptr=*P;
		    Panneaux_Sol *before=NULL;
		while(ptr!=NULL && ptr->ID!=id){
			before=ptr;
			ptr=ptr->next;
		}
		if(ptr==NULL)printf("\nid de panneau solaire n'est pas trouvee!\n");
		else if(ptr->ID==id){
		to_remove=ptr;
		before->next=ptr->next;
		if(to_remove->luminosite!=NULL)supp_capteur(to_remove->luminosite);
		if(to_remove->etat_journnee!=NULL)free(to_remove->etat_journnee);
		free(to_remove);	
		}
	}
	return;
}


//Modifie la valeur du capteur de luminosite 
void lecture_lumunosite(Panneaux_Sol *P){
	if(P==NULL){
		printf("\nPanneau n'existe pas !!\n");
		return;
	}
	int l;
	printf("\nentrer la valeur de lumunosité :\n");
	scanf("%d",&l);
	P->luminosite->val=l;
	return;
}

//les traitements possibles selon les valeurs de capteur de luminosité
void ajustement_pann_sol(Panneaux_Sol *P){
	if(P==NULL){
		printf("\npanneau solaire non valide !\n");
		return ;
	}
	if(P->luminosite!=NULL){
		if(P->luminosite->val<=300 && P->luminosite->val>100){printf("\n(Nuages)");
		printf("\nActivation d'ajustement des panneaux solaires \n");
		P->ajustement_panneaux=1;
	    }
	    else if(P->luminosite->val>300){printf("\n(Jour)");
	    printf("\nDesactivation d'ajustement des panneaux solaires \n");
		P->ajustement_panneaux=0;	
		}
		else if(P->luminosite->val<=100){printf("\n(Nuit)");
		printf("\nActivation d'ajustement des panneaux solaires \n");
		P->ajustement_panneaux=1;		
			
		}
	}
	else printf("\nCapteur non defini pour ce panneau solaire !\n");

	return;
}
//-----------------------------------------------------------------------------------------------AFFICHAGE
//afficher un panneau  
void affich_pann(Panneaux_Sol *P){
	if(P!=NULL){
		printf("\nID : %d",P->ID);
		if(P->etat_journnee!=NULL)printf("\nEtat de la journnee : %s\n",P->etat_journnee);
		else printf("\nEtat de la journnee : Non definie\n");
		if(P->luminosite!=NULL)printf("\nLuminosite : %d\n",P->luminosite->val);
		else printf("\nLuminosite : Non definie\n");
		printf("\nAjustement : %d\n",P->ajustement_panneaux);
		//Ajustement =1 ==>sys d'ajust est activee et 0==> n'est pas activee
	}
	return;
}

//Afficha de l'etat de tous les panneaux solaires existant
void affiche_tt_panneaux(Panneaux_Sol *P){
	if(P==NULL){
		printf("Aucune panneau solaire ni declarer dans le systeme !!");return;
	}
	Panneaux_Sol *curr=P;
	printf("-----------------------------Affichage des donnees liee a chaque panneau solaire-----------------------------");
	while(curr!=NULL){
	printf("-------------------------------------------------------------------------------------------------------------");
	    affich_pann(curr);
		curr=curr->next;
	}
	return;
}

//Affiche des donnees liee a un panneau solaire selon son ID (on va chercher dans la liste chainnée jusqu'a trouver l'id recherchee)
void affich_pann_selon_id(Panneaux_Sol *P,int id){
	if(P==NULL){
		printf("Error (Panneau non valide)!");return;
	}
	Panneaux_Sol *curr=P,*trouvee=NULL;
	for(curr=P;curr!=NULL;curr=curr->next){
		if(curr->ID==id)trouvee=curr;
	}
	if(trouvee==NULL){printf("L'id : %d est invalide (N'existe pas) !",id);
	return;
	}
	else{
		affich_pann(trouvee);
	}
	return;
}

//----------------------------------------------------------------FONCTIONS DE GESTION DES PANNEAUX SOLAIRES
//Gestion des capteurs
void gestion_cap_pann(Panneaux_Sol *P){
	if(P==NULL){
		printf("Aucune Panneau Solair n'est defini");
	}
	int i,choix,id_cap,val;
	/*
	Panneaux_Sol *trouve=NULL;
	printf("\nEntrer l'id du panneau solaire que vous souhaiter gerer  (tapez 0000 pour retourner):");
	scanf("%d",&i);
	if(i=000)return;
	trouve=Recherch_pann_sol(P,i);
	if(trouve==NULL)return;
	
    else {*/
	do{
		printf("\n\n1-Ajouter Capteur\n2-Supprimer Cpateur\n3-Changer la valeur d'un capteur \n");
	    printf("\nEntrer votre choix :");scanf("%d",&choix);
	}while(choix!=1&&choix!=2&&choix!=3);
	
	switch(choix){
		case 1 :{
			printf("\nEntrer l'id du capteur :");scanf("%d",&id_cap);
			ajout_cap_a_pann_sol(P,id_cap,"luminosite",0);
			printf("\nLe capteur de luminosite est ajoute avec succes!\n");
			break;
		}
		case 2 :{
			supp_capteur(P->luminosite);//Si il ya plusiur capteur on ferais des cas
			printf("\nLe capteur de luminosite est supprimee avec succes!\n");
			break;
		}
		case 3 :{
			printf("\nEntrer la nvl valeur du capteur :");scanf("%d",&val);
			chang_val_cap(&(P->luminosite),val);
			break;
		}
	}
//	}
	return ;
}

//------------------------------------------------------------------------------------------------FONCTION DE GESTION DES PANNEAUX SOLAIRES

int  gestion_panneaux(Panneaux_Sol **P){
	printf("\n---------------------------------------------------Gestion des panneaux solaires----------------------------------------------------\n");
	printf("-1 :Affichage les donnees liees a tous les panneaux solaires \n");
	printf("-2 :Afficher un panneau solaire selon son id \n");
	printf("-3 :Ajouter un panneau solaire \n");//en donnant l'id de ce panneau
	printf("-4 :Supprimer un panneau solaire selon son id \n");//Seolon son id
	printf("-5 :Gerer les capteurs des panneau solaire (avec un id specifique)");
	int choix=0;int id;
	do{
		printf("\n\nSaisir votre choix :");
		scanf("%d",&choix);
	}while(choix!=1 &&choix!=2 && choix!=3 &&choix!=4&&choix!=5);
	
	switch(choix){
		case 1 :{
			affiche_tt_panneaux(*P);
			break;
		}
		case 2 :{
			printf("\n\nEntrer l'id du panneau solaire:");
			scanf("%d",&id);
			affich_pann_selon_id(*P,id);
			break;
		}
		case 3 :{
			printf("\n\nEntrer l'id du panneau solaire:");
			scanf("%d",&id);
			Ajout_pann_sol(P,id);
			break;
		}
		case 4 :{
			printf("\n\nEntrer l'id du panneau :");
			scanf("%d",&id);
			Panneaux_Sol *recherch_pann=Recherch_pann_sol(*P,id);
			if(recherch_pann==NULL)break;
			else{
			delet_pann_sol(P,id);
			break;				
			}
		}
		case 5 :{
			printf("\n\nEntrer l'id du panneau:");
			scanf("%d",&id);
            if(Recherch_pann_sol(*P,id)!=NULL){
			gestion_cap_pann(*P);
			break;				
			}
			else{break;
			}

		}
	}
	ajustement_pann_sol(*P);
	
	
	int var;
	printf("\n\n-0 : Retourner au menu precedent(sinon fin):");
	scanf("%d",&var);
	return var;
}












// Fonction pour gérer l'état de la journée
/*
char* read_day_status() {
    int i = 0;
    char *ptr = (char *)malloc(10 * sizeof(char)); // Allocation mémoire pour la chaîne
    if (!ptr) {
        printf("Erreur d'allocation mémoire!\n");
        return NULL;
    }
    printf("\n**********Lecture de l'état de la journée**********\n");
    printf("1/Jour\t\t2/Nuit\t\t3/Nuages\n");
    do {
        printf("\nEntrer votre choix : ");
        scanf("%d", &i);
    } while (i != 1 && i != 2 && i != 3);
    if (i == 1) strcpy(ptr, "jour");
    else if (i == 2) strcpy(ptr, "nuit");
    else strcpy(ptr, "nuage");

    return ptr;
}
*/


