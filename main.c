#include <stdio.h>
#include <stdlib.h>
#include "ret_type.h"
#include "snakeAPI.h"
#include "clientAPI.h"
#include "fonctions.h"

/*
 *       NOM : EL KHARROUBI
 *       Prenom : Karim
 *      
 *
 */

int main(int argc, char* argv[]){

    // Connection to the server & variables pour la fonction connectToServer
	char nomServer[32] = "polydev.cia-polytech-sorbonne.fr";
	char nom1[7] = "Karim2";
	int porte = strtol(argv[2],NULL,10);
	char* p_nom1 = nom1;
	char* p_nomServer = nomServer;
	connectToServer( argv[1], porte, p_nom1);

while(1){
	
    // Fonction bloquante waitForSnakeGame & variables correspondantes
	char typeJeu[55] = "SUPER_PLAYER difficulty=1 timeout=100 seed=123 start=0";
	char* p_typeJeu = &(typeJeu[0]);
	char nomJeu[50];
	char* p_nomJeu = &(nomJeu[0]);
	int X;
	int Y;
	int* p_X = &(X);
	int* p_Y = &(Y);
	int nbMurs;
	int* p_nbMurs = &(nbMurs);
	waitForSnakeGame( argv[3], p_nomJeu, p_X, p_Y, p_nbMurs);

    // Pointeur p_murs qui pointe vers le tableau des coordonées des murs 
	int* p_murs;
	p_murs = ( int *) malloc ( 4*nbMurs* sizeof ( int ) ) ;

	// quiCommence = 0 si je commence, sinon 1
	int quiCommence = getSnakeArena(p_murs);
	printArena();

	// Dimensions de l'arena
	//printf("X = %d\n Y = %d\n", X, Y);

	// Type du move de l'adversaire
	t_return_code type_move_adv = 0;

    // Move de l'adversaire
	t_move move_adv;
	t_move* p_move_adv = &(move_adv);

	// Mon mouvement et mon type de mouvement
	t_move mon_move = 1;
	t_return_code mon_type_mouv;


	int ancienneMove = 10;

	// Cas où c'est l'autre joueur qui commence 
	if(quiCommence){

		// Mes coordonées 
		int ma_position[2] = {X-3, Y/2};
	
		// Boucle pour imprimer les coordonnées des murs 
		/*for (int i = 0; i < 4*nbMurs; i+=4)
		{
			printf("x1=%d\ny1=%d\nx2=%d\ny2=%d\n\n", *(p_murs+i), *(p_murs+i+1), *(p_murs+i+2), *(p_murs+i+3) );
		
		}*/

		// Boucle while qui tourne tant que l'adversaire peut jouer	
		while(type_move_adv == 0){

			type_move_adv = getMove(p_move_adv);
			if(type_move_adv == -1){
				printf("l'adversaire a perdu\n");
				break;
			}

			mon_move = calculMove(ma_position, p_murs, X, Y, mon_move, nbMurs, ancienneMove);
			ancienneMove = mon_move;
		
			mon_type_mouv = sendMove(mon_move);
			if(mon_type_mouv == -1){
				printf("J'ai perdu\n");
				break;
			}
			printArena();

		}
		

	}

	else if(!quiCommence){	// Même fonctionnement que le premier if mais cette fois c'est moi qui commence

			// Boucle pour imprimer coordonées des murs 
			/*for (int i = 0; i < 4*nbMurs; i+=4)
			{
				printf("x1=%d\ny1=%d\nx2=%d\ny2=%d\n\n", *(p_murs+i), *(p_murs+i+1), *(p_murs+i+2), *(p_murs+i+3) );
			
			}*/
		int ma_position[2] = {3, Y/2};
		mon_type_mouv = sendMove(mon_move);
		ancienneMove = mon_move;
		printArena();
		
		while(type_move_adv == 0){

			type_move_adv = getMove(p_move_adv);
			if(type_move_adv == -1){
				printf("l'adversaire a perdu\n");
				break;
			}

			printArena();
			mon_move = calculMove(ma_position, p_murs, X, Y, mon_move, nbMurs, ancienneMove);
			ancienneMove = mon_move;

			mon_type_mouv = sendMove(mon_move);
			if(mon_type_mouv == -1){
				printf("J'ai perdu\n");
				break;
			}
			printArena();
		}

	}
}
	closeConnection();
	free(p_murs);
	return 0;
}
