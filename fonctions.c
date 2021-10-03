#include <stdio.h>
#include <stdlib.h>
#include "snakeAPI.h"
#include "clientAPI.h"

/*
 *       NOM : EL KHARROUBI
 *       Prenom : Karim
 *      
 *
 */

// fonction pour calculer la nouvelle position
t_move calculMove(int ma_position[2], int* p_mur, int x, int y, t_move mon_move, int n_murs, int ancienneMove){

			// Variables que j'utilise pour savoir si je ne peux pas aller dans une direction, elles seront à 1 quand la direction n'est pas possibles
			int pas_nord = 0;
			int pas_est = 0;
			int pas_sud = 0;
			int pas_ouest = 0;
			int yGrand, yPetit, xGrand, xPetit;


			// Mes mouvements possibles,
			//Nord
			int nord[2];
			nord[0] = ma_position[0];	// ça correspond à la coordonnées X si je vais vers le nord
			nord[1] = ma_position[1]-1; // ça correspond à la coordonnées Y si je vais vers le nord
			//Est
			int est[2];
			est[0] = ma_position[0]+1;
			est[1] = ma_position[1];
			//Sud
			int sud[2];
			sud[0] = ma_position[0];
			sud[1] = ma_position[1]+1;
			//Ouest
			int ouest[2];
			ouest[0] = ma_position[0]-1;
			ouest[1] = ma_position[1];



			// printf pour voir les coordonnées de ma position et celles des mouvements nord, sud, est & ouest
			/*printf("position x = %d\n", ma_position[0]);
			printf("position y = %d\n\n", ma_position[1]);
			printf("nord x = %d\n", nord[0]);
			printf("nord y = %d\n", nord[1]);
			printf("sud x = %d\n", sud[0]);
			printf("sud y = %d\n", sud[1]);
			printf("ouest x = %d\n", ouest[0]);
			printf("ouest y = %d\n", ouest[1]);
			printf("est x = %d\n", est[0]);
			printf("est y = %d\n", est[1]);*/


			
			for (int i = 0; i < 4*n_murs; i+=4){

				if(*(p_mur+i+1) > *(p_mur+i+3)){
					yGrand = *(p_mur+i+1);
					yPetit = *(p_mur+i+3);
				}
				if(*(p_mur+i+1) < *(p_mur+i+3)){
					yGrand = *(p_mur+i+3);
					yPetit = *(p_mur+i+1);
				}
				if(*(p_mur+i+1) == *(p_mur+i+3)){
					yGrand = *(p_mur+i+3);
					yPetit = *(p_mur+i+1);
				}
				if(*(p_mur+i) > *(p_mur+i+2)){
					xGrand = *(p_mur+i);
					xPetit = *(p_mur+i+2);
				}
				if(*(p_mur+i) < *(p_mur+i+2)){
					xGrand = *(p_mur+i+2);
					xPetit = *(p_mur+i);
				}
				if(*(p_mur+i) == *(p_mur+i+2)){
					xGrand = *(p_mur+i+2);
					xPetit = *(p_mur+i);
				}

				// Nord
				if(nord[1] >= yPetit && nord[1] <= yGrand && nord[0] == xGrand && nord[0] == xPetit){
					//printf("le numero i du tableau est : %d avec %d %d\n", i, *(p_mur+i), *(p_mur+i+1));
					pas_nord = 1;
				}
				if(nord[1] == -1){
					pas_nord = 1;
				}
				// Est 
				if(est[0] >= xPetit && est[0] <= xGrand && est[1] == yPetit && est[1] == yGrand){
					//printf("le numero i du tableau est : %d avec %d %d\n", i, *(p_mur+i), *(p_mur+i+1));
					pas_est = 1;
				}
				if(est[0] == x){
					pas_est = 1;
				}
				// Sud
				if(sud[1] >= yPetit && sud[1] <= yGrand && sud[0] == xGrand && sud[0] == xPetit){
					pas_sud = 1;
					//printf("le numero i du tableau est : %d avec %d %d\n", i, *(p_mur+i), *(p_mur+i+1));
				}
				if(sud[1] == y ){
					pas_sud = 1;
				}
				// Ouest
				if(ouest[0] >= xPetit && ouest[0] <= xGrand && ouest[1] == yPetit && ouest[1] == yGrand ){
					//printf("le numero i du tableau est : %d avec %d %d / %d %d\n", i, *(p_mur+i), *(p_mur+i+1), *(p_mur+i+2), *(p_mur+i+3));
					pas_ouest = 1;
				}
				if(ouest[0] == -1){
					pas_ouest = 1;
				}


			}

			// Printf pour voir quels sont selon la boucle les mouvements que je ne peux pas faire
			/*printf("pas nord = %d\n", pas_nord);
			printf("pas est = %d\n", pas_est );
			printf("pas sud = %d\n", pas_sud);
			printf("pas ouest = %d\n", pas_ouest );*/

			// Séries de conditions if pour déterminer la direction à prendre d'après la boucle for (à finir) : 
			//une seule non possibilité
		    if(pas_nord  && ancienneMove == 1)
				mon_move = 1;
			else if(pas_nord)
				mon_move = 3;
			else if(pas_est && ancienneMove == 0)
				mon_move = 0;
			else if(pas_est )
				mon_move = 2;
			else if(pas_sud && ancienneMove == 3)
				mon_move = 3;
			else if(pas_sud)
				mon_move = 1;
			else if(pas_ouest && ancienneMove == 2)
				mon_move = 2;
			else if(pas_ouest )
				mon_move = 0;

			// Deux possibilités
			if(pas_nord && pas_est && ancienneMove == 1)
				mon_move = 2;
			else if(pas_nord && pas_est)
				mon_move = 3;
			else if(pas_nord && pas_ouest && ancienneMove == 0)
				mon_move = 1;
			else if(pas_nord && pas_ouest)
				mon_move = 2;
			else if(pas_nord && pas_sud && ancienneMove == 3)
				mon_move = 3;
			else if(pas_nord && pas_sud)
				mon_move = 1;
			else if(pas_sud && pas_ouest && ancienneMove == 2)
				mon_move = 1;
			else if(pas_sud && pas_ouest)
				mon_move = 0;
			else if(pas_sud && pas_est && ancienneMove == 1)
				mon_move = 0;
			else if(pas_sud && pas_est)
				mon_move = 3;
			//else if(pas_sud && pas_est)
			else if(pas_est && pas_ouest && ancienneMove == 0)
				mon_move = 0;
			else if(pas_est && pas_ouest)
				mon_move = 2;



			// Seule possibilité = nord
			if( pas_est && pas_sud && pas_ouest)
				mon_move = 0;
			// Seule possibilité = est
			else if(pas_nord && pas_sud && pas_ouest)
				mon_move = 1;
			// Seule possibilité = sud
			else if(pas_nord && pas_est && pas_ouest)
				mon_move = 2;
			// Seule possibilité = ouest
			else if(pas_nord && pas_est && pas_sud)
				mon_move = 3;

			// Aucune possibilité
			if( pas_nord && pas_est && pas_sud && pas_ouest)
				mon_move = 0;

			// Printf pour savoir quel move mon snake va faire
			//printf("LE MOVE QUE LE SNAKE FAIT EST = %d\n", mon_move);

			//Mise à jour ma_position pour que les tableaux nord, sud, est & ouest s'incremente à chaque fois
			if(mon_move == 0)
				--ma_position[1];
			else if(mon_move == 1)
				++ma_position[0];
			else if(mon_move == 2)
				++ma_position[1];
			else if(mon_move == 3)
				--ma_position[0];

			return mon_move;

}

// fonction pour savoir où il y a des impasses, elle ne reconnait que ceux en forme de A et au max de longueur=2
/*void pasDimpasse(int* p_mur, int impasse[50][2], int n_murs){

	int yGrand,yPetit,xGrand,xPetit;
	int* p_impasse;
	p_impasse = (int*) impasse;

	int tabMur[1000];
	for(int j = 0; j<1999; j++){
		tabMur[j] = 0;
	}
	int* p_tabMur;
	p_tabMur = (int*) tabMur;

	// Boucle pour avoir tableau de mur 
	for (int i = 0; i < 4*n_murs; i+=4){

		// Série de if pour classer les coordonées x & y de p_mur
		if(*(p_mur+i+1) > *(p_mur+i+3)){
			yGrand = *(p_mur+i+1);
			yPetit = *(p_mur+i+3);
		}
		if(*(p_mur+i+1) < *(p_mur+i+3)){
			yGrand = *(p_mur+i+3);
			yPetit = *(p_mur+i+1);
		}
		if(*(p_mur+i+1) == *(p_mur+i+3)){
			yGrand = *(p_mur+i+3);
			yPetit = *(p_mur+i+1);
		}
		if(*(p_mur+i) > *(p_mur+i+2)){
			xGrand = *(p_mur+i);
			xPetit = *(p_mur+i+2);
		}
		if(*(p_mur+i) < *(p_mur+i+2)){
			xGrand = *(p_mur+i+2);
			xPetit = *(p_mur+i);
		}
		if(*(p_mur+i) == *(p_mur+i+2)){
			xGrand = *(p_mur+i+2);
			xPetit = *(p_mur+i);
		}

		xPetit = tabMur[i/4];
		yPetit = tabMur[i/4+1];
		xGrand = tabMur[i/4+2];
		yGrand = tabMur[i/4+3];	
	}

	//boucle for pour savoir quand tabMur finit
	int k = 0;
	while(tabMur[k] != 0 && tabMur[k+1] != 0){
		++k;
	}

	int c =0;
	for(int m = 0; m < k/4; m+=4){

		// Si mur horizontal
		if(tabMur[m] == tabMur[m+2]){

			// s'il y a un mur a sa droite 
			for(int n = 4; n < k/4 - 4; n+=4){

				if(tabMur[n] == tabMur[m] && tabMur[n+1] == tabMur[m+2]){

					// & s'il y a un mur à sa gauche 
					for(int o = 8; o < k/4-8; o+=4){
						if(tabMur[o] == tabMur[m]-1 && tabMur[o+1] == tabMur[m+3]){

							// & s'il y a un mur en bas à sa gauche
							for(int p = 12; p < k/4-12; p+=4){
								if(tabMur[p] == tabMur[o] && tabMur[p+1] == tabMur[o+1]+1){

									// & s'il y a un mur en bas à droite 
									for(int q = 16; q < k/4-16; k+=4){
										if(tabMur[q] == tabMur[p+2] && tabMur[q+1] == tabMur[n+1]-1){

											*(p_impasse+c) = *(p_tabMur+m);
											*(p_impasse+c+1) = *(p_tabMur+m+3)+1;
										}
									}


								}
							}

						// sinon si c'est une impasse unitaire
						}

						else{
							*(p_impasse+c) = *(p_tabMur+m);
							*(p_impasse+c+1) = *(p_tabMur+m+3);
							c+=2;
						}
					}
				}
			}

		}

	}
}*/

/*
// fonction pour mettre à jour position tête du snake
void updateDebutSnakeAdv(int positionAdv[50][2], t_move* p_move_adv){

	if(*(p_move_adv) == 0){
			positionAdv[0][1]--;
		}
		else if(*(p_move_adv) == 1){
			positionAdv[0][0]++;
		}
		else if(*(p_move_adv) == 2){
			positionAdv[0][1]++;
		}
		else if(*(p_move_adv) == 3){
			positionAdv[0][0]--;
		}
}

// fonction pour mettre à jour position corps du snake
void updatePosSnake(int positionAdv[50][2], int compteur){
	
	// Conversion forcée pointeur pour pouvoir compiler 
	int* p;
	p = (int*)positionAdv;

	//Update nouvelles positions cases snake
	for(int i = 2*(compteur+1); i > 0; i-=2){
		*(p+i) = *(p+i-2);
		*(p+i+1) = *(p+i-1);
	}
}

// fonction pour connaître position snake adv ou moi, elle ne marche que pour corps = 2 cases
void calculMoveAdv(int positionAdv[50][2], t_move* p_move_adv, int* p_tour,int* p_compteur){
	int compteur = *(p_compteur);

	// Conversion forcée pointeur pour pouvoir compiler 
	int* p;
	p = (int*)positionAdv;

	//Si c'est le premier tour
	if(*(p_tour) == 0){

		positionAdv[1][0] = positionAdv[0][0];
		positionAdv[1][1] = positionAdv[0][1];

		updateDebutSnakeAdv(positionAdv, p_move_adv);

	}

	

	

	else if(*(p_tour)%10 == 0 && *(p_tour)!=0) {
		compteur = *(p_tour)/10;

		//Remplissage nouvelle case snake
		*(p+2+2*compteur) == *(p+2+2*compteur-2); 	// [2+compteur][0] = [case précedente][0]
		*(p+2+2*compteur+1) == *(p+2+2*compteur-1);	// [2+compteur][1] = [case précedente][1]

		

		updatePosSnake(positionAdv, compteur);

		updateDebutSnakeAdv(positionAdv, p_move_adv); // Update de la premiere case du snake en fonction de son move
													  // IMPORTANT de le faire après que la deuxième case ait les coordonées de la première 
	}

	else{
		

			
				updatePosSnake(positionAdv, compteur);
				updateDebutSnakeAdv(positionAdv, p_move_adv);
			
		

		//	for(int k = 0; k < 10; k++){
		//	printf("tab[%d] = %d ;	\n",k, *(p+k));
			
	}	
		
}
*/
