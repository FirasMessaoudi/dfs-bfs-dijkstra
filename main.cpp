#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

//______________________________________

int G[100][100]; // La matrice d'adjacence dont la taille physique du nombre de lignes et de celui des colonnes est 100
                 // Il s'agit évidemment d'une matrice carrée
int graph[100][100];
int visited[100]; // Ce tableau sert à indiquer si les noeuds (leur indice) du graphe ont été visités ou non lors du parcours
                  // Ce tableau sera utilisé pour les fonctions des deux parcours BFS et DFS, on prévoit donc de le réinitialiser à zéro avant chaque parcours

int q[100]; // Il s'agit ici d'une file qui servira après pour la fonction du parcours BFS

 // On désigne par n le nombre de noeuds (nodes) de notre graphe

int f=0,r=-1; // Ces variables seront utilisées par la suite dans la fonction du parcours en largeur (BFS)
int i,e,d,k,j,src,dest,poids,l,n;


typedef struct
{
   int index;
   int degree;
   char color; 
}node;
 
 typedef struct{
	int longeur;
	int trace;
}noeud;


int minDistance(noeud dist[], int visited[])
{
   int min = INT_MAX, min_index,i; // Initialisation de min à la plus grande valeur possible (INT_MAX) pour d'éventuelles mises à jour 
   for (i = 0; i < n; i++)
   {
       if ((visited[i] == 0) && (dist[i].longeur <= min)) // S'il y a une distance inférieure à min et que le noeud correspondant n'a pas été visité, on considère ce noeud ainsi que son indice 
       {
          min = dist[i].longeur;
          min_index=i; 
       }
   }
   return min_index;
}


int Welsh_Powell(int G[100][100],int n)  
{ 
  FILE *fichier1=NULL;
     
    fichier1=fopen("output.txt","a");
     
    fprintf(fichier1,"\n \n");
     int i,j,k,ok,found,firstUncoloured,allColored; 
     char c;
     // 
     node vertices[n];  
     for(i=0; i<n; i++) 
     {
         vertices[i].index=i;  
         vertices[i].color='-';  
         vertices[i].degree=0;  
         for(j=0; j<n; j++) 
         {
             if(G[i][j]!=0) 
			 vertices[i].degree++;   
		
         }
     }
      
     for(i=0; i<n-1; i++)
        for(j=i+1; j<n; j++)
        {
            if(vertices[i].degree<vertices[j].degree)
            {
                 node temp; // temp est un node temporaire pour faire la permutation 
                 temp=vertices[i];
                 vertices[i]=vertices[j];
                 vertices[j]=temp;
            }
            else if(vertices[i].degree==vertices[j].degree)
            {
            	if(vertices[i].index>vertices[j].index){//si deux noeuds ont le meme degré on fait le tri selon l'ordre croissant des indices
            		 node temp; // temp est un node temporaire pour faire la permutation 
                 temp=vertices[i];
                 vertices[i]=vertices[j];
                 vertices[j]=temp;
            		
				}
			}
        }
                 
         
      
	    int nb=0;
        for(c='A'; c<='Z'; c++)
         
        {
            // On va colorer the first uncoloured vertex, il faudrait donc le retrouver dans vertices 
            firstUncoloured=0;
            i=0;
            while((i<n)&&(firstUncoloured==0))
            {
                 if(vertices[i].color=='-') firstUncoloured=1; // Dès que l'on le retrouve, on s'arrête 
                 else i++;
            }
           if (firstUncoloured!=0)
 
           { 
           vertices[i].color=c; 
             nb++;
             
             
             
            for(i=0; i<n; i++)    
            { 
                if(vertices[i].color=='-') 
                {
                    ok=1; 
                    for(j=0; (j<n)&&(ok==1); j++) 
                    {
                            found=0;
                            for(k=0; (k<n)&&(found==0); k++)  
                            {
                                if(vertices[k].index==j)//noeud adjascent
								 found=1; 
                            }
                            if(found==1)   
                            if((vertices[k-1].color==c)&&((G[vertices[i].index][j]!=0)||(G[j][vertices[i].index]!=0)))//ont le memme couleur et ne sont pas adjascent
							 ok=0;                         
							 
                        }
                        if(ok==1) 
                         {
						 vertices[i].color=c;
                    
                         } 
                         
                    }
                }
                
       }
       
             
        }
      
             fprintf(fichier1," le nombre chromatique du graphe est %i .",nb);
      return nb;      
}

	
	
void remplissage(int G[100][100]){
    FILE *output=NULL;
	FILE *input=NULL;
    
	output=fopen("output.txt","w");
	input=fopen("input.txt","r");
if (input!=NULL)
{
while(!feof(input)){  

		fscanf(input,"%d",&d);  
        fscanf(input,"%d",&n);
	  	fscanf(input,"%d",&e);
	  
	  
	    
	    	for ( k=0;k<e;k++)
            { 
              fscanf(input,"%i %i %i",&src,&dest,&poids);
              G[src-1][dest-1]=poids;
               	 if(d==0)
                 G[dest-1][src-1]=poids;		
	     	} 
	    
}
fclose(input);
} else printf("EMPTY FILE");

//AFFICHAGE DE LA MATRICE D'adjacence dans le fichier
for(i=0;i<n;i++)
{
  for(j=0;j<n;j++) 
    {
   fprintf(output,"%i ",G[i][j]);
	}
fprintf(output,"\n");
}	//AFFICHAGE SUR CONSOLE
     for (i=0; i<n; i++) {
            for (j=0; j<n; j++) {
                printf("%d ",G[i][j]);
            }
            printf("\n");
        }   
	
fclose(output);	
}
	
// Implémentation de la fonction récursive dfs qui sert à parcourir le graphe en profondeur
void dfs(int v)
{  
	FILE *output=NULL;
    
	output=fopen("output.txt","a");
	fprintf(output,"%i ",v+1)   ; 

     printf("%i ",v+1); // Pourquoi écrit-on v+1 et non pas v, car on parcourt tous nos tableaux à partir de l'indice 0 tandis que dans l'affichage on affiche les indices des noeuds de 1 à n
     int i;             // Autrement dit, quand nous avons un noeud (i=0), on sous-entend le noeud 1 dans le graphe
     visited[v]=1; // Quand visite un noeud et que l'on affiche, on le marque "visité" pour ne pas le revisiter dans les prochains appels
     for (i=0;i<n;i++)
        if((G[v][i]!=0) && (visited[i]==0)) // S'il y a un edge entre le noeud v et un autre noeud i et que ce noeud i n'a pas été visité, on le prend.
        {
           dfs(i); // L'auto-appel récursif de la fonction dfs pour le noeud i ayant rempli la condition ci-dessus
        }
      
}

void DFS(int v) // Cette fonction fait appel à la fonction dfs et sert essentiellement à faire l'affichage du parcours DFS selon le format de l'output décrit dans l'énoncé
{ 
     // LE PARCOURS DFS
    // On réinitialise les cases du tableau visited à des zéros pour le parcours DFS
    int i;
    for(i=0;i<n;i++)
    {
      visited[i]=0;
    }
    FILE *output=NULL;
    
	output=fopen("output.txt","a");
    printf("\nDFS(%i)\n",v);
    fprintf(output,"\nDFS(%i)\n",v);
    dfs(v-1); // Appel de la fonction dfs implémentée ci-dessus
    /* DFS(1)
       1 2 4 3 5 7 6

       DFS(7)
       7 5 4 2 1 3 6 */
    printf(" \n");
    fprintf(output,"\n");
}

// L'idée de la fonction bfs est de recourir à la récursivité pour faire le parcours en largeur.
// L'affichage des noeuds, on le fait ultérieurement dans la fonction suivante.
// On se contente ici de remplir une file q en appliquant le principe du parcours en largeur
void bfs(int v)
{ 
   
     int i;
     for(i=0;i<n;i++)
        if((G[v][i]!=0) && (visited[i]==0))
        {
           q[++r]=i;
        }
     if(f<=r)
     {
         visited[q[f]]=1;
         bfs(q[f++]);
     }
}

void BFS(int v)
{ 
	FILE *output=NULL;
    
	output=fopen("output.txt","a");
      // LE PARCOURS BFS
    // On suppose qu'initialement aucun noeud n'a été visité, on affecte donc à toutes les cases de visited ainsi que toutes les cases de q la valeur zéro
    int i;
    for(i=0;i<n;i++)
    {
      q[i]=0;
      visited[i]=0;
    } 	fprintf(output,"\n");
    printf("\nBFS(%i)\n%i ",v,v); // Le parcours commence à partir de v, on l'afffiche alors le premier.
    fprintf(output,"\nBFS(%i)\n%i ",v,v);
    f=0; r=-1; // Réinitialisation de f et r avant d'appeler la fonction bfs qui nous donnera le résultat du parcours en largeur
    bfs(v-1); // Appel de la fonction bfs implémentée au dessus; on passe comme paramètre l'indice (v-1) qui correspond au noeud v (dans l'énoncé)
    int reached[100]={0}; // reached est ici un tableau (initialisé à zéro) qui sert à vérifier si un noeud est visité ou pas lors du défilement de la file q dont le principe est FIFO
    reached[v-1]=1; // Initialement, ce noeud v est visité puisque on commence le parcours à partir de lui
    for(i=0;i<f;i++) // La file q est pleine est remplie de f indices de noeuds venus des appels récursifs de la fonction bfs
                     // On parcourt la file de sa tête à sa queue (premier entré premier sorti)
        if(reached[q[i]]==0) // On teste si ce noeud a été défilé et affiché ou non
        {
            printf("%d ",q[i]+1);
			fprintf(output,"%d ",q[i]+1);  /* BFS(1)
            
                                     1 2 3 4 5 6 7

                                     BFS(7)
                                     7 5 6 4 2 3 1 */

            reached[q[i]]=1; // Après avoir affiché ce noeud, on le marque visité.
        }
    printf("\n");
    fprintf(output,"\n");
    
    
}
    
void dijkstra(int src, int dst)
{
     noeud dist[n]; // On a besoin d'un tableau de distances que l'on nomme dist et dont la taille logique est égale à V 
     int visited[n]; // On a besoin d'un tableau booléen que l'on nomme visited et dont la taille logique est égale à V
     int i,j,u;
     for (i = 0; i < n; i++)
     {
        dist[i].longeur = INT_MAX;
		dist[i].trace=-1; // Initialisation des cases de dist à une grande valeur (INT_MAX)
        visited[i] = 0; // Initialement, tous les noeuds du graphe (la matrice) ne sont pas visités, on leur affecte alors la valeur nulle 
     }
      
  
     dist[src].longeur = 0; // La distance d'un noeud avec lui-même est nulle 
      
     for (i = 0; i < n-1; i++) // Deux boucles imbriquées qui servent à remplir le tableau dist avec les distances minimales en faisant appel à la fonction minDistance(int dist[], int visited[]) 
     {
     
       u = minDistance(dist, visited);
  
       visited[u] = 1;
  
       for (j = 0; j < n; j++)
         if ( ( visited[j]==0 ) && ( G[u][j] !=0 ) && ( dist[u].longeur != INT_MAX ) && ( dist[u].longeur+G[u][j] < dist[j].longeur) ){
		 
            dist[j].longeur = dist[u].longeur + G[u][j];
            dist[j].trace=u;
        }
     }
     
    // printSolution(dist, src, dst); /* For each test case your program should output (in a separate line) a single number C - the length of the shortest path 
                                    //from vertex A to vertex B. In case there is no such path, your program should output a single word "NO" (without quotes)*/
    	FILE *output=NULL;
    
	output=fopen("output.txt","a");
                                    
       if((dist[dst].longeur==INT_MAX)||(dist[src].longeur==INT_MAX))
       {
	   printf("NO\n");
	   fprintf(output,"NO\n");
       }
	   else{
     
      printf("\nle plus court chemin (");
      fprintf(output,"\nle plus court chemin (");
	  
      
      int path[n];//un tableau qui sert à contenir le plus court chemin 
       i=0;
        int k=dst;
       while(k!=src)
        {
       path[i]=k;
       i++;
          k=dist[k].trace;
                                       
        };
        path[i]=k;
         printf("%d-",src+1);
         fprintf(output,"%d-",src+1);
          while(i-- && i>0)
        {
        printf("%d-",path[i]+1);
        fprintf(output,"%d-",path[i]+1);
		}
		
	      printf("%d",path[i]+1);
	      fprintf(output,"%d",path[i]+1);
      
      
      printf(") entre les sommets %d et %d du graphe est ",src+1,dst+1);
      fprintf(output,") entre les sommets %d et %d du graphe est ",src+1,dst+1);
      printf("%i .\n",dist[dst].longeur-dist[src].longeur);
      fprintf(output,"%i.\n",dist[dst].longeur-dist[src].longeur);
      }
}
  


    
    


int main(int argc, char *argv[]) { 


remplissage(G);

DFS(1);

DFS(n);

BFS(1);

BFS(n);

dijkstra(0,n-1);             
printf("\nle nombre chromatique du graphe est %i .",Welsh_Powell(G,n));
            
	  
  return 0;     
     	

}

