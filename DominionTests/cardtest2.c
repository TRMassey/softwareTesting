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
	int played;					// number of cards played from deck
	int deckSize;				// size of deck
	int odecksize;				// other player's deck size
	int pileSize;				// pile of usable cards
	int numPlayers = 2;  		// players for valid gamestate
	int numTests = 1; 			// large testing spread
	int amount;					// total value of accumulated coins
	int totalDrawn;				// cards drawn before +2 coins, should be discarded by end
	int drawnTreasure;			// treasure card counter
	struct gameState g;			// gamestate, original
	struct gameState testState;		// gamestate under test
	int k[10] = {duchy, gardens, province, estate, tribute, mine, cutpurse, ambassador, great_hall, adventurer};
	char testCard[] = "adventurer";	 // card under test



	printf("---     TESTING CARD: %s    ---\n\n ", testCard);
	
	for(i = 0; i < numTests; i++){
		
		// set hand basics for each game so the function can be called
		pos = -1;
		p = 0;
		p2 = 1;

		// copy into a test state so I don't destroy the world
		initializeGame(numPlayers, k, 1000, &g);
		memcpy(&testState, &g, sizeof(struct gameState));


		// begin test
		deckSize = testState.handCount[p];										// how many are originally in hand before play
		odecksize = testState.deckCount[p2];									// how many are originall in other's hand before play
		played = testState.handCount[p] - testState.discardCount[p];			// how many cards were played
		pileSize = testState.deckCount[p];										// pile of non-trashed cards before play
		totalDrawn = 0;															// amount drawn to get to 2 coin cards
		drawnTreasure = 0;														// number of coin cards drawn
		amount = 0;																// value of accumulated coin cards
		int preCount;
		
		// test to make sure cards are drawn until two coin cards
		// will show if less than or more than is allowed due to error
		printf("\nTest 1: Play Adventurer and draw until two coins are drawn:\n");
		initializeGame(numPlayers, k, 1000, &g);
		memcpy(&testState, &g, sizeof(struct gameState));
		testState.hand[p][0] = adventurer;
		testState.hand[p][1] = duchy;
		testState.hand[p][2] = estate;
		testState.hand[p][3] = province;
		testState.hand[p][4] = gardens;
		testState.deck[p][0] = copper;
		testState.deck[p][1] = silver;
		testState.deck[p][2] = gold;
		testState.deck[p][3] = copper;
		testState.deck[p][4] = silver;
		preCount = testState.handCount[p];
		cardEffect(adventurer, 0, 0, 0, &testState, 0, 0);		// should have two coin cards when done
		if(testState.handCount[p] - preCount == 2) 
			printf("Passed. Coin card amount expected: %d   count finish: %d\n", 2, testState.handCount[p] - preCount);
		else 
			printf("FAILED. Coin card amount expeccted: %d   count finish: %d\n", 2, testState.handCount[p] - preCount);
		printf("Coin cards Found: ");
		for(j = 0; j < testState.handCount[p]; j++){
			if(testState.hand[p][j] == copper){
				printf("copper, ");
				amount += 1;
			}
			if(testState.hand[p][j] == silver){
				printf("silver, ");
				amount += 2;
			}
			if(testState.hand[p][j] == gold){
				printf("gold, ");
				amount += 3;
			}
		}

		// test to make sure the value provided is right
		printf("\nTest 1b: Gained cards, coin ammount unchanged till use:\n");
		if(g.coins == testState.coins)
			printf("Passed. Coin amount the same\n");
		else
			printf("FAILED. Coin amount different\n");


		printf("\nTest 1c: Check test one again, but with gold drawn:\n");
		initializeGame(numPlayers, k, 1000, &g);
		memcpy(&testState, &g, sizeof(struct gameState));
		testState.hand[p][0] = adventurer;
		testState.hand[p][1] = duchy;
		testState.hand[p][2] = estate;
		testState.hand[p][3] = province;
		testState.hand[p][4] = gardens;
		testState.deck[p][0] = gold;
		testState.deck[p][1] = silver;
		testState.deck[p][2] = gold;
		testState.deck[p][3] = copper;
		testState.deck[p][4] = gold;
		preCount = testState.handCount[p];
		cardEffect(adventurer, 0, 0, 0, &testState, 0, 0);		// should have two coin cards when done
		
		if(testState.handCount[p] - preCount == 2) 
			printf("Passed. Coin card amount expected: %d   count finish: %d\n", 2, testState.handCount[p] - preCount);
		else 
			printf("FAILED. Coin card amount expeccted: %d   count finish: %d\n", 2, testState.handCount[p] - preCount);
		printf("Coin cards Found: ");
		for(j = 0; j < testState.handCount[p]; j++){
			if(testState.hand[p][j] == copper){
				printf("copper, ");
				amount += 1;
			}
			if(testState.hand[p][j] == silver){
				printf("silver, ");
				amount += 2;
			}
			if(testState.hand[p][j] == gold){
				printf("gold, ");
				amount += 3;
			}
		}

		// check to make sure drawnTreasure is matching amount of distributed coin cards
		initializeGame(numPlayers, k, 1000, &g);
		memcpy(&testState, &g, sizeof(struct gameState));
		testState.hand[p][0] = adventurer;
		testState.hand[p][1] = duchy;
		testState.hand[p][2] = estate;
		testState.hand[p][3] = province;
		testState.hand[p][4] = gardens;
		testState.deck[p][0] = gardens;
		testState.deck[p][1] = silver;
		testState.deck[p][2] = gold;
		testState.deck[p][3] = copper;
		testState.deck[p][4] = duchy;
		cardEffect(adventurer, 0, 0, 0, &testState, 0, 0);	

		printf("\nTest 2: Make sure all cards were discarded that were not coins:\n");
		if(1 == testState.discardCount[p]) // will gain one non-coincard prior to 2 with this deck
			printf("Passed. Expected discard amount: %d   Discarded finish: %d\n", 1, testState.discardCount[p]);
		else
			printf("FAILED. Expected disccard amount: %d  Discarded finish: %d\n", 1, testState.discardCount[p]);
		

		//test to make sure the other player's hand didn't change. No cards given, none taken from
		printf("\nTest 3: Other player's deck size unchanged when adventurer is drawn:\n");
		if(testState.deckCount[p2] == odecksize)
			printf("Passed. Deck size start: %d   Deck size finish: %d\n", odecksize, testState.deckCount[p2]);
		else
			printf("FAILED. Deck size start: %d   Deck size finish: %d\n", odecksize, testState.deckCount[p2]);


		//test to make sure the other player's hand didn't change. No cards given, none taken from
		printf("\nTest 3b: Other player's hand size unchanged when adventurer is drawn:\n");
		if(testState.handCount[p2] == g.handCount[p2])
			printf("Passed. Hand size start: %d   Hand size finish: %d\n", g.handCount[p2], testState.handCount[p2]);
		else
			printf("FAILED. Hand size start: %d   Hand size finish: %d\n", g.handCount[p2], testState.handCount[p2]);


		//test to make sure the cards come from own player's pile, and is not stealing from elsewhere
		printf("\nTest 4: Player is drawing and keeping only two cards from own pile:\n");
		if(g.deckCount[p] -3 == testState.deckCount[p]) // -1 bc of this hand, has one noncoin card pulled
			printf("Passed. Expected: %d   Deck size finish: %d\n", g.deckCount[p] - 3, testState.deckCount[p]);
		else
			printf("FAILED. Expected: %d   Deck size finish: %d\n", g.deckCount[p] - 3, testState.deckCount[p]);

		//test to make sure the card is going to the played pile after use. Already established other players deck is unchanged
		printf("\nTest 5: Adventurer card added to played pile after use:\n");
		if(testState.playedCardCount == 1)
			printf("Passed. Expected increase in played pile: %d     To played pile: %d\n", 1, testState.playedCardCount);
		else
			printf("FAILED. Expected increase in played pile: %d   To played pile: %d\n", 1, testState.playedCardCount);

		// test for changes in money supply that shouldn't have been activated, will test for money being given to players
		printf("\nTest 6: Test supply counts for treasure that should have been distributed: \n");
		if(g.supplyCount[copper] != testState.supplyCount[copper])
			printf("FAILED. Estate Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[copper], testState.supplyCount[copper]);
		if(g.supplyCount[silver] != testState.supplyCount[silver])
			printf("FAILED. Duchy Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[silver], testState.supplyCount[silver]);
		if(g.supplyCount[gold] != testState.supplyCount[gold])
			printf("FAILED. Duchy Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[gold], testState.supplyCount[gold]);
		else
			printf("Passed. Supply counts for treasure cards are the same\n");
		
		//test for world state changes, will indicate if any victory cards have been given out inappropriately
		printf("\nTest 7: : Test supply counts for points and curses that should not have been distributed: \n ");
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

	}

	return 0;
}