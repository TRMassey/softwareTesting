/***************************************************************************
Author: Tara Massey
Class: Software Engineering II
Assignment: Assignment 4
Purpose: Simple random tester for smithy card in dominion

Please see randomhistory.c for summary and analysis
*************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>


// random test
void randomSmithy(int p, int numPlayers, int maxDeck, struct gameState g);


int main(){

	int i, j;						// counter
	int p=0;						// player
	int numPlayers;					// number of players
	struct gameState g;				// game state
	int maxDeck;					// max deck amount, boundary upper
	int numTests = 20000;			// loop random tests
	int k[10] = {duchy, gardens, province, estate, tribute, mine, cutpurse, ambassador, great_hall, smithy};
	int deckSize = 27;				// will randomize, establishing max size

		//set rand
	srand(time(NULL));

	//Random test loop
	printf("---     TESTING CARD: Smithy    ---\n\n ");
	for(i = 0; i < numTests; i++){

		// RANDOMIZE : number of players, deck amount, hand amount, contents of deck
		numPlayers = (rand()%3)+2;					// random number of players within valid range
		initializeGame(numPlayers, k, 1000, &g);
		maxDeck = rand()%deckSize;					// random deck amount in valid range, allowing for empty
		g.deckCount[p] = maxDeck;					// set for player in question
		g.handCount[p] = rand()%6;					// random starting hand between typical start and empty to test shuffle;
		for(j = 0; j < maxDeck; j++){				// make sure deck is random
			g.deck[p][j] = (rand()%17)+1;
		}

		// CALL: State random inputs and call function
		printf("\nInputs:\nDeck Size: %d\tHand Count: %d\t Players: %d\n", maxDeck, g.handCount[p], numPlayers);
		randomSmithy(p, numPlayers, maxDeck, g);
	}

return 0;
}
		

/****************************************************************
Function: randomSmithy

Purpose: Play smithy card with random combinations. All random
values made in main, and copied over to test state in this function.
Values such as 0 and maximum is allowed for deck and hand size.
******************************************************************/
void randomSmithy(int p, int numPlayers, int maxDeck, struct gameState g){
	int p2 = 1;
	struct gameState testState;		// gamestate under test

		// amount of randomness announced
		printf("\n\nTEST CONDITIONS: Random players, completely random deck, completely random hand, gamestate valid\n\n");
		

		memcpy(&testState, &g, sizeof(struct gameState));
		cardEffect(smithy, 0, 0, 0, &testState, 0, 0);
		
		// Do you gain only three cards?
		printf("\nTest 1: Play Smithy and gain 3 cards:\n");
		if(testState.handCount[p] == g.handCount[p] + 2) // lose smithy (-1) and gain 3 more (+3) = 2
			printf("Passed. Expected hand count: %d   Actual count: %d\n", g.handCount[p] +2, testState.handCount[p]);
		else
			printf("FAILED. Expected size t: %d   Actual size : %d\n", g.handCount[p] +2, testState.handCount[p]);

		// Is the other players deck impacted?
		printf("\nTest 2: Other players' deck size unchanged when smithy is drawn:\n");
		if(testState.deckCount[p2] == g.deckCount[p2])
			printf("Passed. Deck size Expected: %d   Deck size actual: %d\n", g.deckCount[p2], testState.deckCount[p2]);
		else
			printf("FAILED. Deck size expected: %d   Deck size actual: %d\n", g.deckCount[p2], testState.deckCount[p2]);
		

		//Is the other players hand impacted?
		printf("\nTest 2b: Other player's hand size unchanged when smithy is drawn:\n");
		if(testState.handCount[p2] == g.handCount[p2])
			printf("Passed. Deck size expected: %d   Deck size actual: %d\n", g.handCount[p2], testState.handCount[p2]);
		else
			printf("FAILED. Deck size expected: %d   Deck size actual: %d\n", g.handCount[p2], testState.handCount[p2]);
		
		// Did the cards come from the deck? Please note, -3 is problematic when he deck cound is 2 or les.
		printf("\nTest 3: Player is drawing from own pile:\n");
		if(g.deckCount[p] - 3 == testState.deckCount[p])  //  since drawcard has shuffle built in, should always be count - 3
			printf("Passed. Expected: %d   Deck size actual: %d\n", g.deckCount[p] - 3, testState.deckCount[p]);
		else
			printf("FAILED. Expected: %d   Deck size actual: %d\n", g.deckCount[p] - 3, testState.deckCount[p]);

		// Did the smithy card go to the played pile?
		printf("\nTest 4: Smithy card added to played pile after use:\n");
		if(testState.playedCardCount == 1)
			printf("Passed. Expected increase in played pile: %d     To played pile: %d\n", 1, testState.playedCardCount);
		else
			printf("FAILED. Expected increase in played pile: %d   To played pile: %d\n", 1, testState.playedCardCount);
		
		// Did the world state change?
		printf("\nTest 5: : Test supply counts for points and curses that should not have been distributed: \n ");
		if(g.supplyCount[estate] != testState.supplyCount[estate])
			printf("FAILED. Estate Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[estate], testState.supplyCount[estate]);
		if(g.supplyCount[duchy] != testState.supplyCount[duchy])
			printf("FAILED. Duchy Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[duchy], testState.supplyCount[duchy]);
		if(g.supplyCount[province] != testState.supplyCount[province])
			printf("FAILED. Province Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[province], testState.supplyCount[province]);
		if(g.supplyCount[curse] != testState.supplyCount[curse])
			printf("FAILED. Province Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[curse], testState.supplyCount[curse]);
		else
			printf("Passed. Supply counts for curses and victory cards are the same\n");

		// Did supplies change?
		printf("\nTest 6: Test supply counts for treasure that should have been distributed: \n");
		if(g.supplyCount[copper] != testState.supplyCount[copper])
			printf("FAILED. copper Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[copper], testState.supplyCount[copper]);
		if(g.supplyCount[silver] != testState.supplyCount[silver])
			printf("FAILED. silver Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[silver], testState.supplyCount[silver]);
		if(g.supplyCount[gold] != testState.supplyCount[gold])
			printf("FAILED. gold Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[gold], testState.supplyCount[gold]);
		else
			printf("Passed. Supply counts for treasure cards are the same\n");
}