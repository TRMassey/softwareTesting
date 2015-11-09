#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int main(){

	int i, j; 					 	// counter
	int p, p2;					// indicating which player
	int pos;					// position
	int numActions;				// number of numActions for player
	int amount;					// coins
	int found;					 // bool
	int choice1, choice2, choice3; // player options
	int deckSize;				// size of deck
	int odecksize;				// other player's deck size
	int pileSize;				// pile of usable cards
	int numPlayers = 2;  		// players for valid gamestate
	int numTests = 1; 		// large testing spread
	struct gameState g;			// gamestate, original
	struct gameState testState;		// gamestate under test
	int k[10] = {feast, gardens, embargo, remodel, tribute, mine, cutpurse, ambassador, great_hall, steward};
	char testCard[] = "Steward";	 // card under test



	printf("---     TESTING CARD: %s    ---\n\n", testCard);
	
	for(i = 0; i < numTests; i++){
		
		// set hand basics for each game so the function can be called
		pos = -1;
		p = 0;
		p2 = 1;


		/******************************** Choice One **************************/
		printf("***************TESTING CHOICE ONE: One***************\n");
		// copy into a test state so I don't destroy the world
		initializeGame(numPlayers, k, 1000, &g);
		memcpy(&testState, &g, sizeof(struct gameState));


		// begin test for Choice One
		deckSize = testState.handCount[p];										// how many are originally in hand before play
		odecksize = testState.deckCount[p2];									// how many are originall in other's hand before play
		numActions = testState.numActions;											// numActions available
		pileSize = testState.deckCount[p];										// pile of non-trashed cards before play
		amount = g.coins;																// current coins at 0

		// play the steward card, changes to counts will occur from this point out. Choice 1
		cardEffect(steward, 1, 0, 0, &testState, 0, 0);
		
		// test to make sure player gains two cards with choice 1
		printf("\nTest 1: Play Steward, choice1, and gain two cards:\n");
		if(g.handCount[p] + 1 == testState.handCount[p]) // lose steward (-1) and gain 2 (+2) = 1
			printf("Passed. Expected hand count: %d   Hand count finish: %d\n", g.handCount[p] +1, testState.handCount[p]);
		else
			printf("FAILED. Deck size start: %d   Deck size finish: %d\n", g.handCount[p] +1, testState.handCount[p]);

		// test to make sure player gains 2 numActions
		printf("\nTest 2: Play Steward, choice1, make sure no numActions are given:\n");
		if(numActions == testState.numActions) 
			printf("Passed. Expected gained actions: %d   Gained Actions finish: %d\n", 0, testState.numActions - numActions);
		else
			printf("FAILED. Expected gained actions: %d   Gained Actions finish: %d\n", 0, testState.numActions - numActions);	

		// test to make sure player gains no money
		printf("\nTest 3: Play Steward, choice1, make sure no coins are given:\n");
		if(amount == testState.coins) 
			printf("Passed. Expected coins gained: %d   Coins gained finish: %d\n", 0, testState.coins - amount);
		else
			printf("FAILED. Expected coins gained: %d   Coins gained finish: %d\n", 0, testState.coins - amount);	

		//test to make sure the card is going to the played pile after use. Already established other players deck is unchanged
		printf("\nTest 4: Steward card added to played pile after use:\n");
		if(testState.playedCardCount == 1)
			printf("Passed. Expected increase in played pile: %d     To played pile: %d\n", 1, testState.playedCardCount);
		else
			printf("FAILED. Expected increase in played pile: %d   To played pile: %d\n", 1, testState.playedCardCount);

		//test to make sure the other player's hand didn't change. No cards given, none taken from
		printf("\nTest 5: Other player's deck size unchanged when steward is drawn:\n");
		if(testState.deckCount[p2] == odecksize)
			printf("Passed. Deck size start: %d   Deck size finish: %d\n", odecksize, testState.deckCount[p2]);
		else
			printf("FAILED. Deck size start: %d   Deck size finish: %d\n", odecksize, testState.deckCount[p2]);

		//test to make sure the other player's hand didn't change. No cards given, none taken from
		printf("\nTest 6: Other player's hand size unchanged when steward is drawn:\n");
		if(testState.handCount[p2] == g.handCount[p2])
			printf("Passed. Hand size start: %d   Hand size finish: %d\n", g.handCount[p2], testState.handCount[p2]);
		else
			printf("FAILED. Hand size start: %d   Hand size finish: %d\n", g.handCount[p2], testState.handCount[p2]);

		//test to make sure the cards come from own player's pile, and is not stealing from elsewhere
		printf("\nTest 7: Player is drawing from own pile:\n");
		if(g.deckCount[p] -2 == testState.deckCount[p]) //  5 in deck - 2 taken from it
			printf("Passed. Expected: %d   Deck size finish: %d\n", g.deckCount[p] - 2, testState.deckCount[p]);
		else
			printf("FAILED. Expected: %d   Deck size finish: %d\n", g.deckCount[p] - 2, testState.deckCount[p]);

		
		//test for world state changes, will indicate if any victory cards have been given out inappropriately
		printf("\nTest 8: : Test supply counts for points and curses that should not have been distributed: \n ");
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

		// test for changes in money supply that shouldn't have been activated, will test for money being given to players
		printf("\nTest 9: Test supply counts for treasure that should have been distributed: \n");
		if(g.supplyCount[copper] != testState.supplyCount[copper])
			printf("FAILED. Copper Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[copper], testState.supplyCount[copper]);
		if(g.supplyCount[silver] != testState.supplyCount[silver])
			printf("FAILED. Silver Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[silver], testState.supplyCount[silver]);
		if(g.supplyCount[gold] != testState.supplyCount[gold])
			printf("FAILED. Gold Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[gold], testState.supplyCount[gold]);
		else
			printf("Passed. Supply counts for treasure cards are the same\n");


		/************************* Choice Two ************************************/
		printf("***************TESTING CHOICE ONE: Two ***************\n");
		initializeGame(numPlayers, k, 1000, &g);
		memcpy(&testState, &g, sizeof(struct gameState));

		// begin test for Choice 2
		deckSize = testState.handCount[p];										// how many are originally in hand before play
		odecksize = testState.deckCount[p2];									// how many are originall in other's hand before play
		numActions = testState.numActions;											// numActions available
		pileSize = testState.deckCount[p];										// pile of non-trashed cards before play
		amount = g.coins + 2;																// current coins at 0

		// play the steward card, changes to counts will occur from this point out. Choice 2
		cardEffect(steward, 2, 0, 0, &testState, 0, 0);

		// test to make sure player gains no cards
		printf("\nTest 1: Play Steward, choice2, and gain no cards:\n");
		if(g.handCount[p] -1 == testState.handCount[p]) 
			printf("Passed. Expected hand count: %d   Hand count finish: %d\n", g.handCount[p] -1, testState.handCount[p]);
		else
			printf("FAILED. Hand size start: %d   Hand size finish: %d\n", g.handCount[p] -1, testState.handCount[p]);

		// test to make sure player gains no numActions
		printf("\nTest 2: Play Steward, choice2, make sure no numActions are given:\n");
		if(numActions == testState.numActions) 
			printf("Passed. Expected Actions: %d   Actions gained finish: %d\n", numActions, testState.numActions - g.numActions);
		else
			printf("FAILED. Expeccted Actions %d   Actions gained finish: %d\n", numActions, testState.numActions - g.numActions);	

		// test to make sure player gains two coins
		printf("\nTest 3: Play Steward, choice2, make sure two coins are given:\n");
		if(amount == testState.coins)
			printf("Passed. Expected hand count: %d   Hand count finish: %d\n", amount, testState.coins);
		else
			printf("FAILED. Deck size start: %d   Deck size finish: %d\n", amount, testState.coins);	

		//test to make sure the card is going to the played pile after use. Already established other players deck is unchanged
		printf("\nTest 4: Steward card added to played pile after use:\n");
		if(testState.playedCardCount == 1)
			printf("Passed. Expected increase in played pile: %d     To played pile: %d\n", 1, testState.playedCardCount);
		else
			printf("FAILED. Expected increase in played pile: %d   To played pile: %d\n", 1, testState.playedCardCount);

		
//test to make sure the other player's hand didn't change. No cards given, none taken from
		printf("\nTest 5: Other player's deck size unchanged when steward is drawn:\n");
		if(testState.deckCount[p2] == odecksize)
			printf("Passed. Deck size start: %d   Deck size finish: %d\n", odecksize, testState.deckCount[p2]);
		else
			printf("FAILED. Deck size start: %d   Deck size finish: %d\n", odecksize, testState.deckCount[p2]);

		//test to make sure the other player's hand didn't change. No cards given, none taken from
		printf("\nTest 6: Other player's hand size unchanged when steward is drawn:\n");
		if(testState.handCount[p2] == g.handCount[p2])
			printf("Passed. Hand size start: %d   Hand size finish: %d\n", g.handCount[p2], testState.handCount[p2]);
		else
			printf("FAILED. Hand size start: %d   Hand size finish: %d\n", g.handCount[p2], testState.handCount[p2]);

		//test to make sure the cards come from own player's pile, and is not stealing from elsewhere
		printf("\nTest 7: Player isn't drawing more from own pile:\n");
		if(g.deckCount[p] == testState.deckCount[p]) //  
			printf("Passed. Expected: %d   Deck size finish: %d\n", g.deckCount[p] - 2, testState.deckCount[p]);
		else
			printf("FAILED. Expected: %d   Deck size finish: %d\n", g.deckCount[p] - 2, testState.deckCount[p]);

		
		//test for world state changes, will indicate if any victory cards have been given out inappropriately
		printf("\nTest 8: : Test supply counts for points and curses that should not have been distributed: \n ");
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

		// test for changes in money supply that shouldn't have been activated, will test for money being given to players
		printf("\nTest 9: Test supply counts for treasure that should have been distributed: \n");
		if(g.supplyCount[copper] != testState.supplyCount[copper])
			printf("FAILED. Copper Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[copper], testState.supplyCount[copper]);
		if(g.supplyCount[silver] != testState.supplyCount[silver])
			printf("FAILED. Silver Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[silver], testState.supplyCount[silver]);
		if(g.supplyCount[gold] != testState.supplyCount[gold])
			printf("FAILED. Gold Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[gold], testState.supplyCount[gold]);
		else
			printf("Passed. Supply counts for treasure cards are the same\n");


		/********************************** Choice 3 *************************************/
		printf("***************TESTING CHOICE ONE: Else ***************\n");
		initializeGame(numPlayers, k, 1000, &g);
		g.hand[p][0] = steward;
		g.hand[p][1] = estate;
		g.hand[p][2] = duchy;
		g.hand[p][3] = province;
		g.hand[p][4] = great_hall;
		g.deck[p][0] = steward;
		g.deck[p][1] = feast;
		g.deck[p][2] = province;
		g.deck[p][3] = gardens;
		g.deck[p][4] = mine;
		memcpy(&testState, &g, sizeof(struct gameState));

		// begin test for Choice 3
		amount = g.coins;																// current coins at 0
		numActions = g.numActions;

		// play the steward card, changes to counts will occur from this point out. Choice 3
		cardEffect(steward, 3, duchy, estate, &testState, 0, 0);

		// test to make sure player gains no cards
		printf("\nTest 1: Play Steward, choice3, and discard two cards:\n");
		if(g.handCount[p] -3 == testState.handCount[p])  // steward -1, -2 trashing
			printf("Passed. Expected hand count: %d   Hand count finish: %d\n", g.handCount[p] -3, testState.handCount[p]);
		else
			printf("FAILED. Deck size start: %d   Deck size finish: %d\n", g.handCount[p] -3, testState.handCount[p]);

		// test to make sure player gains no numActions
		printf("\nTest 2: Play Steward, choice2, make sure no numActions are given:\n");
		if(numActions == testState.numActions) 
			printf("Passed. Expected Actions gained: %d   Actions gained finish: %d\n", 0, testState.numActions - g.numActions);
		else
			printf("FAILED. Expeccted Actions  gained: %d   Actions gained finish: %d\n", 0, testState.numActions - g.numActions);	

		// test to make sure player gains no coins
		printf("\nTest 3: Play Steward, choice3, make sure two coins are given:\n");
		if(amount == testState.coins)
			printf("Passed. Expected coins gained: %d   coins gained finish: %d\n", 0, testState.coins - amount);
		else
			printf("FAILED. Expected coins gained: %d   coins gained finish: %d\n", 0, testState.coins - amount);	

		//test to make sure removed cards are no longer in hand
		printf("\nTest 4: Make sure the removed cards aren't in hand:\n");
		found = 0;
		for(j = 0; j < testState.handCount[p]; j++){
			if(testState.hand[p][j] == duchy || testState.hand[p][j] == estate)
				found = 1;
		}

		if(found != 1)
			printf("Passed. Removed cards no longer in hand\n");
		else
			printf("FAILED. Removed cards not trashed\n");
	

		//test to make sure removed cards are no longer in deck
		printf("\nTest 5: Make sure the removed cards aren't in deck:\n");
		found = 0;
		for(j = 0; j < testState.deckCount[p]; j++){
			if(testState.deck[p][j] == duchy || testState.deck[p][j] == estate)
				found = 1;
		}

		if(found != 1)
			printf("Passed. Removed cards not in deck\n");
		else
			printf("FAILED. Removed cards in deck.\n");

		printf("\nTest5b: Discard count should not be inremented if trashed: \n");
		if(testState.discardCount[p] >= 2)
			printf("Passed. Removed cards trashed\n");
		else
			printf("FAILED. Removed cards not trashed.\n");

		//test to make sure the other player's hand didn't change. No cards given, none taken from
		printf("\nTest 6: Other player's deck size unchanged when steward is drawn:\n");
		if(testState.deckCount[p2] == odecksize)
			printf("Passed. Deck size start: %d   Deck size finish: %d\n", odecksize, testState.deckCount[p2]);
		else
			printf("FAILED. Deck size start: %d   Deck size finish: %d\n", odecksize, testState.deckCount[p2]);

		//test to make sure the other player's hand didn't change. No cards given, none taken from
		printf("\nTest 7: Other player's hand size unchanged when steward is drawn:\n");
		if(testState.handCount[p2] == g.handCount[p2])
			printf("Passed. Hand size start: %d   Hand size finish: %d\n", g.handCount[p2], testState.handCount[p2]);
		else
			printf("FAILED. Hand size start: %d   Hand size finish: %d\n", g.handCount[p2], testState.handCount[p2]);

		//test to make sure the cards come from own player's pile, and is not stealing from elsewhere
		printf("\nTest 8: Player is not drawing more cards from own pile:\n");
		if(g.deckCount[p] == testState.deckCount[p]) // drew no additional cards
			printf("Passed. Expected: %d   Deck size finish: %d\n", g.deckCount[p], testState.deckCount[p]);
		else
			printf("FAILED. Expected: %d   Deck size finish: %d\n", g.deckCount[p], testState.deckCount[p]);

		
		//test for world state changes, will indicate if any victory cards have been given out inappropriately
		printf("\nTest 9: : Test supply counts for points and curses that should not have been distributed: \n ");
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

		// test for changes in money supply that shouldn't have been activated, will test for money being given to players
		printf("\nTest 10: Test supply counts for treasure that should have been distributed: \n");
		if(g.supplyCount[copper] != testState.supplyCount[copper])
			printf("FAILED. Copper Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[copper], testState.supplyCount[copper]);
		if(g.supplyCount[silver] != testState.supplyCount[silver])
			printf("FAILED. Silver Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[silver], testState.supplyCount[silver]);
		if(g.supplyCount[gold] != testState.supplyCount[gold])
			printf("FAILED. Gold Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[gold], testState.supplyCount[gold]);
		else
			printf("Passed. Supply counts for treasure cards are the same\n");

	}

	return 0;
}