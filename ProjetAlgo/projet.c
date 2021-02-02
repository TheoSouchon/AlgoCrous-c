#include <string.h>
#include <stdio.h>
#include <math.h>
#include "projet.h"
#include <stdlib.h>

/* CODE LOGEMENT */ 
Logement lirelog(FILE *fe) //Fonction qui lit un logement à partir d'un flot donné, prend en paramètres un pointeur sur fichier fe, et retourne une variable structurée de type Logement
{
	Logement ligne; //Déclaration d'une variable structurée de type Logement.
	fscanf(fe," %s %s %s %s %s %s", ligne.idlog,ligne.cite,ligne.type, ligne.disp, ligne.adapte, ligne.idoccup); //Lecture d'une ligne dans le fichier.
	
	return ligne;
}

int Chargement(Logement *TLog[], int maxLog) /*Fonction qui charge les données du fichier 'logements.don' dans un tableau, prend en paramètres un tableau de pointeurs sur Logement TLog, un entier maxlog qui correspond à la taille physique du tableau. */

{
	int i=0; //Déclaration et initialisation de l'indice de parcours de tableau à 0
	Logement log;  //Déclaration d'une variable log de type Logement.
	FILE *fe; //Déclaration d'un pointeur fe sur FILE.

	fe=fopen("logements.don","r"); //Ouverture du fichier 'logements.don' en mode lecture.
	if (fe==NULL)//Si le pointeur fe pointe sur NULL.
		{ 
			printf("Problème d'ouverture fichier\n"); 
			return -1; 
		}

	log=lirelog(fe);
	while(feof(fe)==0)//Tant qu'on n'est pas en fichier de fichier.
	{	
		if (i==maxLog)//Si la taille logique est égale à la taille physique 
		{ 
			printf("Pb capacité\n");
			fclose(fe); //Fermeture du fichier.
			return -2; 
		}
		TLog[i]=(Logement*)malloc(sizeof(Logement)); //On alloue une place de la taille d'un logement pour un pointeur sur logement dans le tableau TLog.
		if (TLog[i]==NULL) //Si le pointeur TLog[i] pointe sur NULL.
	 	{ 
	 		printf("Problème malloc\n");
	 		fclose(fe); //Fermeture du fichier.
	 		exit(1);
	 	}

	 	*TLog[i]=log; //Le pointeur TLog[i] pointe sur log. 
	 	i++; //Incrémentation du i.
	 	log=lirelog(fe); //Lecture d'un autre logement.
	}
	return i; //Retourne la taille logique TLog.

}
void AffichLogement(Logement **Log, int tailleLog) //Fonction qui affiche un logement à l'écran.
{
	int i=0;
	for (i=0; i<tailleLog-1; i++) //Parcours du tableau Log.
	{
		printf("%s %s %s %s %s %s\n",Log[i]->idlog,Log[i]->cite, Log[i]->type,Log[i]->disp,Log[i]->adapte,Log[i]->idoccup );
	}
}

int RechLogementOccup(Logement **Log, int n) //Fonction qui recherche les logements occupés (idoccup!='RIEN'), prend en paramètres le tableau de pointeurs sur logement Log qui a n élèments.
{
	int res; 
	if (n==0)  //Si le tableau contient 0 élèments 
		{
			 return -1;
		} 
	res=strcmp(Log[n-1]->idoccup,"RIEN"); //Compare l'idoccup du dernier logement du tableau (indice n-1) avec 'Rien' et réceptionne le résultat de la comparaison dans res.
	if (res!=0) //Si l'idoccup n'est pas égale à "RIEN"
		{
			return n-1; //Retourne la position du logement occupé. 
		}
	else return RechLogementOccup(Log,n-1); //Sinon appel de la fonction RechLogementOccup qui prend en paramètres le tableau Log qui a n-1 élèments.


}
void AffichLogementOccup(Logement **Log, Liste e, int tailleLog, char *idEtudRech)//Fonction qui affiche les logements occupés je l'ai faite en récursive
{
	int retourR, pos,t;
	*idEtudRech=0;
	Liste position;
	char EtudRech[6];

	if (tailleLog==1) return;
	retourR=RechLogementOccup(Log,tailleLog); //Recherche de la position du premier logement occupé 
	if (retourR!=-1) // S'il trouve le logement occupé 
	{
		printf(" %s %s %s %s %s %s\n",Log[retourR]->idlog,Log[retourR]->cite, Log[retourR]->type,Log[retourR]->disp,Log[retourR]->adapte,Log[retourR]->idoccup );
		strcpy(idEtudRech,Log[retourR]->idoccup); // JE COPIE L'ID DE LETUDIANT QUI OCCUPE LE LOGEMENT QUON A TROUVE DANS ID ETUD RECH
		position=RechercheIdentiteOccup(e,idEtudRech); 
	
		if (position==NULL) //Si l'étudiant n'est pas dans le tableau
			printf("Etudiant pas dans le tableau\n");
		
		else //Si l'étudiant est dans le tableau
		{
			printf("%s %s %s %s %s %d %s\n", position->etudi.idetud,position->etudi.civ,position->etudi.nom,position->etudi.prenom,position->etudi.boursier,position->etudi.echelon,position->etudi.handicap);
			t=tailleLog-(tailleLog-retourR);
			AffichLogementOccup(Log,e, tailleLog-(tailleLog-retourR),idEtudRech);
		}
	}	
	else return; //S'il n'y a plus de logement occupé on s'arrête
}


Liste RechercheIdentiteOccup(Liste e, char idEtudRech[]) //Fonction récursive qui recherche un étudiant dans la liste des étudiants en lui passant en paramètres la liste des étudiants, et l'id de l'étudiant recherché. Cette fonction retourne l'adresse de l'étudiant recherché dans la liste. 
{
	int res; //Variable de comparaison.

	if (e==NULL) return NULL; //Condition d'arrêt, si la liste est vide

	res=strcmp(e->etudi.idetud,idEtudRech); //Comparaison entre les id etudiant dans la liste des étudiants, et l'idEtud recherché passé en paramètres
	if (res==0) return e; //Si ils sont égaux on retourne l'adresse de l'id etudiant recherché dans la liste
	else 
		return RechercheIdentiteOccup(e->suivant, idEtudRech); //Sinon on appelle la fonction RechercheIdentiteOccup qui continue la recherche en lui passant en paramètres l'adresse du maillon suivant. 
}

int rechRminLog(Logement **log,int d,int n) //Fonction qui recherche le rang du minimum et retourne sa position, prend en paramètres le tableau de pointeurs sur demande dem, un entier qui correspond au rang du début, et un entier n qui correspond au nombre d'élèments du tableau.
{
	int rmin,i;
	rmin=d;

	for(i=d+1 ;i<n; i++)
	{
		if (strcmp(log[i]->cite,log[rmin]->cite)<0)
			{
				rmin=i;
				return rmin;
			}

	}
	return rmin;
}

void permuteLogement(Logement **log, int a, int b)//Fonction qui permet de faire la permutation entre l'élément à l'indice a avec l'élément à l'indice b.
{
	Logement *temp;

	temp=log[a];log[a]=log[b];log[b]=temp;
}

void triLogement(Logement **log,int n)//Fonction tri qui fait appel aux fonctions rechRminAttente et permuteAttente, prend en paramètres un tableaux de pointeurs sur logement log, et son nombre d'élèments n.
{
	int k,r;
	for(k=0;k<n-1;k++)
	{
		r=rechRminLog(log,k,n);
		permuteLogement(log,r,k);
	}
}

/* CODE ETUDIANT */ 

Liste listeVide(void)//Fonction qui retourne une liste d'étudiants vide.
{
	return NULL ;
}

Liste insertiontet(Liste e, Etudiant x)
{
	 Maillon *m;

	 m=(Maillon*) malloc (sizeof(Maillon));
	 if (m==NULL)
	 {
	 	 printf("Pb malloc\n");
	 	 exit(1);
	 }
	 m->etudi=x;
	 m->suivant=e;

	 return m;

}

void afficherEnsemble(Liste e) /*Fonction en version récursive qui affiche une liste, elle prend en paramètre l'adresse de début de liste*/
{
	if (e==NULL) //Si e pointe sur NULL.
	{
		return;
	}
	printf("%s %s %s %s %s %d %s\n",e->etudi.idetud,e->etudi.civ,e->etudi.nom,e->etudi.prenom,e->etudi.boursier,e->etudi.echelon,e->etudi.handicap);
	afficherEnsemble(e->suivant);//Appel de la fonction afficherEnsemble.
}


Etudiant lireetud(FILE *fe) 
{
	Etudiant ligne;

	fscanf(fe," %s %s %s %s %s %d %s", ligne.idetud,ligne.civ,ligne.nom, ligne.prenom, ligne.boursier, &ligne.echelon,ligne.handicap);
	
	return ligne;
}

Liste ChargementListe (Liste l) //Fonction qui charge une liste à partir du fichier "etudiants.don", prend en paramètres une liste l et retourne cette liste chargée.
{
	Etudiant e; //Déclaration d'une variable de type Etudiant.
	FILE *fe; //Déclaration d'un pointeur fe sur FILE. 

	l=listeVide(); //Initialisation d'une liste d'étudiants à NULL.
 
	fe=fopen("etudiants.don","r"); 
	if(fe==NULL) //Si fe pointe sur NULL.
	{
		printf("Problème ouverture fichier\n");
		exit(1);	
	}
	e=lireetud(fe);
	while(feof(fe)==0)
	{
		l=insertiontet(l,e);
		e=lireetud(fe);

	}
	fclose(fe);
	return l;
}


/* INSERTION nouvel etudiant */

Etudiant Saisie(void) //Fonction de saisie d'une variable structurée de type Etudiant et qui la retourne. 
{
	Etudiant Etud;

	printf("Veuillez saisir les informations de l'étudiant\n:");
	printf("ID ETUDIANT   CIVILITÉ   NOM   PRENOM   BOURSIER(NULL SINON)   ECHELON   HANDICAP\n");
	scanf("%s %s %s %s %s %d %s",Etud.idetud, Etud.civ, Etud.nom, Etud.prenom, Etud.boursier, &Etud.echelon, Etud.handicap);
	
	return Etud;
}

Liste InsertionEtudiantEnTete(Liste Etud,Etudiant Etudiant)  //Fonction d'insertion d'un étudiant en tête de la liste des étudiants, qui prend en paramètres la liste des étudiants et une variable structurée de type Etudiant. Cette fonction retourne la nouvelle liste. 
{
	Maillon *m; //Déclaration d'un pointeur sur maillon 

	m=(Maillon *)malloc(sizeof(Maillon)); //On alloue dynamiquement de l'espace dans la liste des Etudiants
	if (m==NULL) //Si le maillon est vide
	{
		printf("Problème malloc"); exit(1);
	}
	m->etudi=Etudiant; //On insère la structure de type Etudiant a sa place(m->etudi) dans la liste des Etudiants
	m->suivant=Etud; //On met l'adresse de la liste Etud dans le pointeur m->suivant. 	
	
	return m; //On retourne la nouvelle liste. 
	
}
Liste InsertionTrieeEtudiant(Liste Etud, Etudiant Etudiant) //Fonction d'insertion triée d'un étudiant dans la liste des étudiants, qui prend en paramètres la liste des étudiants et une variable structurée de type Etudiant. Cette fonction retourne la nouvelle liste. 
{
	int comp; //Variable de comparaison. 

	if (Etud==NULL) return InsertionEtudiantEnTete(Etud, Etudiant); //Si la liste est vide, on insère au début  en appelant la fct InsertionEtudiantenTete.

	comp=strcmp(Etudiant.idetud, Etud->etudi.idetud); //On compare entre les id étudiants figurant dans la liste, et idEtud saisi.
	if (comp>0) return InsertionEtudiantEnTete(Etud, Etudiant); //Si l'id etudiant saisi est plus grand (avant) que l'id étudiant dans la liste, on l'insère avant en appelant la fct InsertionEtudianten<ete.
	if (comp==0) //Si l'étudiant est dans la liste
	{
			printf("Cet étudiant figure déjà dans la liste: %s %s %s %s %s %d %s\n",Etud->etudi.idetud, Etud->etudi.civ, Etud->etudi.nom, Etud->etudi.prenom, Etud->etudi.boursier, Etud->etudi.echelon, Etud->etudi.handicap);
			return Etud; //On retourne la liste des étudiants
	}

	Etud->suivant=InsertionTrieeEtudiant(Etud->suivant, Etudiant); //else on appelle la fonction InsertionTriee en lui passant en paramètres l'adresse du prochain maillon de la liste.
	
	return Etud;

}
/* CHARGEMENT DEMANDE EN ATTENTE LOGEMENT */ 

Demande lirelogAttente(FILE *fe) //Fonction qui lit une demande à partir d'un flot donné et retourne une variable structurée de type Demande
{
	Demande ligne; //Déclaration d'une variable ligne de type Demande

	fscanf(fe," %s %s %d %s %s", ligne.iddem,ligne.idetud,&ligne.echelon, ligne.cite, ligne.type); //Lit une demande dans le fichier "demandesEnAttentes.don" 
	
	return ligne; 
}

int ChargementAttente(Demande *Tdem[], int maxLog) /*Fonction qui charge les données du fichier ‘demandeEnAttente.don’ dans un tableau
Elle prend en paramètres un tableau de pointeurs Tdem sur Demande, la taille physique maxlog qui est un entier, elle retourne un entier. */


{
	int i=0; //Déclaration et initialisation de l'indice de parcours de tableau à 0
	Demande dem; //Déclaration d'une variable dem de type Demande.
	FILE *fe; //Déclaration d'un pointeur fe sur fichier FILE.
	fe=fopen("demandesEnAttente.don","r"); //Ouverture du fichier 'demandesEnAttente.don' en mode lecture.
	if (fe==NULL) //Si le pointeur pointe sur NULL.
	{ 
		printf("Problème d'ouverture du fichier\n"); //Message d'erreur.
		return -1; 
	}

	dem=lirelogAttente(fe); //Lecture d'une ligne dans le fichier demandesEnAttentes.don
	while(feof(fe)==0) //Tant qu'on n'est pas en fichier de fichier.
	{	
		if (i==maxLog) //Si la taille logique est égale à la taille physique
		{ 
			printf("Problème de capacité\n"); //Message d'erreur indiquant que le tableau est plein.
			fclose(fe); //Fermeture du fichier
			return -2; 
		}

		Tdem[i]=(Demande*)malloc(sizeof(Demande)); //On alloue une place de la taille d'une Demande pour un pointeur sur Demande dans le tableau Tdem.
		if (Tdem[i]==NULL) //Si le pointeur pointe sur NULL
	 	{
		 	 printf("Problème malloc\n"); 
		 	 fclose(fe); //Fermeture du fichier.
		 	 exit(1); 
	 	}

	 	*Tdem[i]=dem; //Le pointeur Tdem[i] pointe sur dem.
	 	i++; //Incrémentation du i.

	 	dem=lirelogAttente(fe); //On lit une autre demande dans le fichier.
	 }

	return i;
}

void AffichLogementAttente(Demande **dem, int tailleLog) //Fonction qui affiche les logements en attente à l'écran, prend en paramètres le tableau de pointeurs dem sur Demande et sa taille logique taillelog en entier, ne retourne rien.
{ 
	int i=0; 
	for (i=0; i<tailleLog; i++) //Parcours du tableau dem de l'indice 0 à tailleLog-1.
	{
		printf("%s %s %d %s %s\n",dem[i]->iddem,dem[i]->idetud, dem[i]->echelon,dem[i]->cite,dem[i]->type); 
	} 

}

//////Fonctions du tri par permutation. /////
int rechRminAttente (Demande **dem,int d,int n) //Fonction qui recherche le rang du minimum et retourne sa position, prend en paramètres le tableau de pointeurs sur demande dem, un entier qui correspond au rang du début, et un entier n qui correspond au nombre d'élèments du tableau.
{
	int rmin,i;
	rmin=d;

	for(i=d+1;i<n;i++)
	{
		if (dem[i]->echelon >= dem[rmin]->echelon)
		 rmin=i;
			
	}
	return rmin; 
}

void permuteAttente(Demande **dem, int a, int b)//Fonction qui permet de faire la permutation entre l'élément à l'indice a avec l'élément à l'indice b.
{
	Demande *temp;

	temp=dem[a]; 
	dem[a]=dem[b]; //Permutation 
	dem[b]=temp;
}

void triDemandeAttente(Demande **dem,int n)//Fonction tri qui fait appel aux fonctions rechRminAttente et permuteAttente, prend en paramètres un tableaux de pointeurs sur Demande dem, et son nombre d'élèments.
{
	int k,r; 

	for(k=0;k<n-1;k++)
	{
		r=rechRminAttente(dem,k,n); //Récéptionne la position dans r.
		permuteAttente(dem,r,k); 
	}
}
void DecalageSupp(Demande**dem,int pos,int *taille) //Fonction qui supprime une demande, prend en paramètres le tableau de pointeurs sur Demande dem, la position à laquelle on veut supprimer et un pointeur sur entier qui pointe sur la taille logique du tableau Tdem.
{
    int i;
    Demande *nvt;
    nvt=dem[pos];

    for (i = pos; i < (*taille); ++i)
    {
            dem[i]=dem[i+1]; //Décalage à gauche.
    }
    *taille=(*taille)-1;
    free(nvt); //Libère l'espace réservé à l'adresse nvt.
}


void traitementAttente(Demande **dem, Logement **log, int* tailleDem, int tailleLog) /* Fonction qui traite les demandes en attente, attribue un logement inoccupé à un étudiant demandeur en fonction du type et la cité du logement demandé, prend en paramètres le tableau de pointeurs dem sur Demande,
 un tableau de pointeurs log sur Logement, un pointeur sur entier tailleDem et un entier tailleLog */
{    
    int cmp1, cmp2, i=0, j=0; // Déclaration des variables intermédiaires de comparaison, et des indices de parcours de tableau et leur initialisation à 0,

    for(i=0; i<*tailleDem; i++) //Parcours du tableau des demandes 
    {
        for(j=0; j<tailleLog ; j++) //Parcours du tableau de logements 
        {   
            if(strcmp(log[j]->idoccup,"RIEN")==0) // Si le logement est inoccupé,  on voit alors les cités et le type de logements demandés. 
            {   
                cmp1=strcmp(dem[i]->cite, log[j]->cite); // On compare la cité demandée avec les cités existantes dans le tableau log.
                cmp2=strcmp(dem[i]->type, log[j]->type); // On compare le type de logement demandé avec le type de logements existants dans le tableau log.
                if(cmp1==0 && cmp2==0) // Si la cité ET le type demandé concordent avec un type et une cité dans le tableau log, on l'attribue.
                { 		
                 	
                    printf("Le logement qui sera attribué pour %s est: %s\n", dem[i]->iddem,log[j]->idlog ); 
                    strcpy(log[j]->idoccup, dem[i]->idetud); //On attribue à un logement l'id étudiant qui va l'occuper.
                    strcpy(log[j]->disp,"ND"); //Le logement attribué devient non disponible "ND" pour un autre demandeur. 
                    DecalageSupp(dem, i, tailleDem); // On supprime alors la demande traitée, on fait appel à la fonction suppression et on lui passe en paramètres le tableau dem oû on veut effectuer la suppression, la position i de la demande traitée qu'on veut supprimer, et la taille dem.
                    i--; // Décrémentation de i
           
                    break; // On sort de la deuxième boucle.
                }


            }
        }

    }
}



int RechercheEtudLog(Logement **TLog, int tailleLog,char idEtudRech[]) /*Fonction qui permet de rechercher un logement à partir de l'idEtudiant qui l'occupe et retourne la position de ce logement
Prend en paramètres le tableau de pointeurs sur Logement TLog, un entier tailleLog qui corre, et un tableau de caractères idEtudRech */
{
    int i, comp; //Déclaration de l'indice de parcours de tableau et de la variable intermédiaire de comparaison cmp.
    for (i = 0; i < tailleLog; ++i) //Parcours du tableau de logements.
    {
        comp=strcmp(TLog[i]->idoccup,idEtudRech); //Compare l'id étudiant qui occupe le logement à l'indice i avec l'id de l'étudiant qu'on recherche.
        if(comp==0) //Si l'idoccup=idEtudRech 
         return i; //Retourne la position du logement qui a comme idoccup idEtudRech.
    }
   	 return -1; //L'étudiant n'est logé dans aucun logement.
}

void liberationLogement (Logement **Tlog, Demande **dem, int *tailleDem, int *tailleLog) /*Fonction qui permet de libérer un logement occupé à partir de l'id de l'étudiant qui l'occupe.
 Cette fonction prend en paramètres le tableau de pointeurs sur Logement TLog, le tableau de pointeurs dem sur Demande et deux pointeurs sur entier tailleDem et tailleLog qui correspondent respectivement aux tailles logiques des tableaux dem et TLog. */ 
{ char idEtudRech[7]; // Déclaration d'un tableau de 7 caractères.
    int pos; 
    printf("Saissiez l'étudiant qui occupe un logement\n");   
    scanf("%s", idEtudRech); 
    pos=RechercheEtudLog(Tlog,*tailleLog, idEtudRech); //Appel de la fonction RechercheEtudLog qui retourne la position pos,lui passe en paramètres le tableau Tlog, la taillelogique du tableau, et l'idEtudRech qu'on recherche dans les logements et  
    if (pos!=-1) //Si le logement occupé par idEtudRech existe. 
    {
    
	   	strcpy(Tlog[pos]->idoccup, "RIEN"); //Le logement à l'indice pos devient inoccupé, idoccup='RIEN'
	    strcpy(Tlog[pos]->disp, "D"); //Le logement à l'indice pos devient disponible.
	    traitementAttente(dem,Tlog,tailleDem, *tailleLog); //Appel de la fonction qui traite les demandes pour voir si le logement qui a été libéré convient à une demande attente et traiter cette dernière, lui passe en paramètre les tableau de pointeurs tdem et TLog, l'adresse de tailledem, et la taille logique du tableau TLog  
	}
	else printf("Cet étudiant n'a de pas de logement attribué\n");  //Si la pos==-1, alors il n'y a pas de logement attribué à idEtudRech.

}

void ReecritureAttente (Demande**Tdem,int taille) // Fonction qui permet de sauvegarder 
{
    FILE*fe;
    fe=fopen("demandesEnAttente.don","w+");

    for (int i = 0; i < taille; ++i)
    {
        fprintf(fe, "%s %s %d %s %s \n",Tdem[i]->iddem,Tdem[i]->idetud,Tdem[i]->echelon,Tdem[i]->cite,Tdem[i]->type);
    }
    fclose(fe);
}
void ReecritureLogement (Logement** TLog,int taille) // est ce qu'on met la taille en pointeur ?
{
    FILE*fe;
    fe=fopen("logements.don","w+");

    for (int i = 0; i < taille; ++i)
    {
        fprintf(fe, "%s %s %s %s %s %s \n",TLog[i]->idlog,TLog[i]->cite,TLog[i]->type,TLog[i]->disp,TLog[i]->adapte, TLog[i]->idoccup);
    }
    fclose(fe);
}



int RechercheDemandeAttente(Demande **Dem, int tailleDem,char *IdDemRech) //Fonction de rechercher une demande de logement en attente dans le tableau des demandes de logements en attente en lui passant en paramètres le tableau des demandes, sa taille logique ainsi que l'id demande recherché. 
{
	int comp, i; //Variable de comparaison et i indice du tableau 

	for (i = 0; i < tailleDem; i++) //Pour i commençant à partir de 0 et plus petit que la taille du tableau, on incrémente i 
	{
		comp=strcmp(Dem[i]->iddem,IdDemRech); //Comparaison entre les id demande du tableau en fonction de i,et l'idDemande recherché.  
		if(comp==0) // Si on trouve l'idDemRecherché dans le tableau 
		 return i; //On retourne sa position dans le tableau
	}
	return -1; //On retour -1 s'il n'est pas dans le tableau 
}
void SaisieDemande(Demande *Dem, Demande **TDem, int *tailleDem, Liste etud) //Fonction qui ne retourne rien, qui fait une saisie contrôlée des données concernant une nouvelle demande en attente, et qui prend en paramètres une variable structurée de type demande, le tableau de pointeurs sur demande, sa taille logique, et la liste des étudiants. 
{
	int RetourRechIdAttente;  //RetourRechIdAttente variable qui receptionne le retour de la fonction RechercheDemandeAttente.
	Liste position; //Position: variable de type Liste qui receptionne le return de la fonction RechercheIdentiteOccup.

	printf("Veuillez saisir les informations concernant la demande en attente\n");
	printf("ID Demande: ");
	scanf("%s%*c",Dem->iddem);

	RetourRechIdAttente=RechercheDemandeAttente(TDem,*tailleDem, Dem->iddem); //Appel de la fonction RechercheDemandeAttente qui recherche un id demande en lui passant en paramètre le tableau des demandes en attente, ainsi que sa taille logique, et l'ID demande qu'on recherche. 
	while(RetourRechIdAttente!=-1) //Tant que l'id demande recherché existe  dans le tableau des demandes en attente. 
	{
		printf("Cet identifiant est déjà utilisé, Veuillez choisir un autre:\n"); //On re-saisit l'id demande.
		scanf("%s",Dem->iddem);
		RetourRechIdAttente=RechercheDemandeAttente(TDem,*tailleDem, Dem->iddem); //On re-contrôle la saisie.
	}

	printf("ID ETUDIANT :"); //Saisie 
	scanf("%s%*c",Dem->idetud);
	position=RechercheIdentiteOccup(etud, Dem->idetud);
	while(position==NULL) //Tant que l'étudiant n'est pas dans la liste des étudiants.
	{
		printf("Cet etudiant n'existe pas, Veuillez saisir qui existe\n"); //On re-saisit l'identifiant.
		scanf("%s",Dem->idetud);
		position=RechercheIdentiteOccup(etud, Dem->idetud); //On re-contrôle la saisie.
	}
	//Saisie de l'échelon, le nom de la cité, et le type du logement 
	printf("ECHELON :"); 
	scanf("%d%*c", &Dem->echelon);
	printf("CITE :");
	scanf("%s%*c",Dem->cite);
	printf("TYPE :");
	scanf("%s%*c",Dem->type);

}

void InsertionDemande(Demande **TDem, int *tailleDem, Liste etud, Demande *Dem) //Fonction qui permet d'insérer une demande en attente avec une saisie contrôlée, qui prend en paramètres un tableau de pointeurs des demandes de logement en attente, sa taille logique, la liste des étudiants, et un pointeur sur une structure de type Demande.
{
	Dem=(Demande*)malloc(sizeof(Demande)); //On alloue de l'espace dynamiquement pour la structure Demande qu'on veut insérer dans le tableau de pointeurs de demande.
	if (Dem==NULL) //Si l'espace n'est pas alloué 
	{
		printf("Problème malloc\n");
		exit(1); 
	}
	SaisieDemande(Dem, TDem, tailleDem,etud); // Je saisis les informations concernant la demande en attente
	(*tailleDem)++; //La saisie contrôlée s'est bien passée, on incrèmente la taille du tableau des demandes afin d'insérer une nouvelle demande
	TDem[(*tailleDem)-1]=Dem; //On insère la demande saisie à la position taille-1 		
}

void EffacFic (void)
{
    FILE*fe;

    fe=fopen("etudiants.don","w+");
	
	fprintf(fe, " ");

    fclose(fe);
}


Liste ReecritureChainee (Liste etud, FILE *fe)
{

    if (etud==NULL) return etud;

    fprintf(fe, "%s ",etud->etudi.idetud);
    fprintf(fe, "%s ",etud->etudi.civ);
    fprintf(fe, "%s ",etud->etudi.nom);
    fprintf(fe, "%s ",etud->etudi.prenom);
    fprintf(fe, "%s ",etud->etudi.boursier);
    fprintf(fe, "%d ",etud->etudi.echelon);
    fprintf(fe, "%s",etud->etudi.handicap);
    fprintf(fe,"\n");
    etud->suivant=ReecritureChainee(etud->suivant,fe);

   
    return etud;
   
}

int rechercheDem(Demande **dem,char *iddem,int taille)
{
	int i;

	for (i = 0; i < taille; ++i)
	{
		if (strcmp(dem[i]->iddem,iddem)==0)
		 return i;
	}
	printf("erreur : cette demande n'existe pas\n");exit(1);
}

int AffichageMenu()
{	
	int option;

	printf("         <-------Menu-------->\n");
	printf("0- Pour quitter\n");
	printf("1- Affichage de la liste des logements\n");
	printf("2- Affichage de la liste des étudiants\n");
	printf("3- Affichage de la liste des logements en mentionnant l'identité de l'étudiant qui l'occupe\n");
	printf("4- Affichage de la liste des demandes de logements en attente\n");
	printf("5- Traitement des demandes en attente\n");
	printf("6- Rechercher une demande de logement en attente\n");
	printf("7- Insertion d'un nouvel étudiant et sa demande de logement \n");
	printf("8- Annulation d'une demande de logement en attente non-encore traitée \n");
	printf("9- Libération d'un logement lors d'un départ d'étudiant ce qui déclenche le traitement des demandes en attente\n");
	
	printf("Veuillez choisir une option par son numéro ou quitter le menu:\n");
	scanf("%d",&option);
	
	return option;
}
char ReponseUtilisateur()
{	
	char choix;

	printf("Voulez-vous effectuer une autre opération? O/N\n");
	scanf("%*c%c",&choix);
	return choix;
}

