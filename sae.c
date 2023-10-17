#include <stdio.h>
#include <string.h>

enum  {INPUTMAX = 100, NOM_MAX = 30, MAXENTREPRISES = 50, MISSIONMAX = 50}; 
enum {OP = 1, AG, IN};
int g_nbrentreprises = 0;
int g_nbrmissions = 0;
typedef struct s_entreprise
{
    char nom[NOM_MAX];
    int role;
} t_entreprise;

typedef struct s_mission
{
    int identifiant;
    char nom_mission[NOM_MAX];
    float remuneration;    
} t_mission;

t_entreprise entreprises[MAXENTREPRISES];
t_mission missions[MISSIONMAX];

void inscription(){
    char entree[INPUTMAX];
    scanf("%s", entree);
    if (strcmp("OP", entree) == 0)
    {
        entreprises[g_nbrentreprises].role = OP;
    }
    else if (strcmp("AG", entree) == 0)
    {
        entreprises[g_nbrentreprises].role = AG;
    }
    else if (strcmp("IN", entree) == 0)
    {
        entreprises[g_nbrentreprises].role = IN;
    }
    else
    {
        printf("Role incorrect\n");
        return;
    }
    scanf("%s", entree);
    for (int i = 0; i < g_nbrentreprises; i++)
    {
        if (strcmp(entree, entreprises[i].nom) == 0 )
        {
           printf("Nom incorrect\n");
           return;
        }
    }
    strcpy(entreprises[g_nbrentreprises].nom, entree);
    g_nbrentreprises++;
    printf("Inscription realisee (%d)\n", g_nbrentreprises);
}



void publication(){
    int identifiant;
    char nom_mission[NOM_MAX];
    float remuneration;

    scanf("%d", &identifiant);
    missions[g_nbrmissions].identifiant = identifiant;
    scanf("%s", nom_mission);
    strcpy(missions[g_nbrmissions].nom_mission, nom_mission);
    scanf("%f", remuneration);
    if (remuneration < 0)
    {
        printf("Remuneration incorrecte");
        return;
    }
    missions[g_nbrmissions].remuneration = remuneration;
    g_nbrmissions++;
    printf("Mission publiee (%d)", g_nbrmissions);
    
}

int main()
{
    char entree[INPUTMAX];

    do 
    {
        printf("Entrez votre commande: ");
        scanf("%s", &entree);
        if (strcmp("inscription", entree) == 0)
        {
            inscription(); // C1 - inscription
        }
        else if (strcmp("mission", entree) == 0)
        {
            publication(); // C2 - publication
        }
        
    } while (strcmp("exit", entree) != 0);  // C0 - Exit

    return 0;
}
