#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int main(){

  int i, j;               // counter
  int p, p2;            // indicating which player
  int pos;          // position
  int numPlayers = 2;     // players for valid gamestate
  int numTests = 1;     // large testing spread
  struct gameState g;     // gamestate, original
  struct gameState testState;   // gamestate under test
  int k[10] = {feast, gardens, embargo, remodel, tribute, mine, cutpurse, ambassador, great_hall, village};
  int result;         // return test


  printf("---     TESTING FUNCTION: discardCard    ---\n\n");
  
  for(i = 0; i < numTests; i++){
    
    // set hand basics for each game so the function can be called
    pos = -1;
    p = 0;
    p2 = 1;


    // make sure it's added if not trashed
    initializeGame(numPlayers, k, 1000, &g);
    g.hand[p][0] = steward;
    g.hand[p][1] = estate;
    g.hand[p][2] = duchy;
    g.hand[p][3] = province;
    g.hand[p][4] = great_hall;
    memcpy(&testState, &g, sizeof(struct gameState));
    result = discardCard(province, p, &testState, 0);  // trash flag false
    printf("\nTest 1: Card added to played pile if w/trash flag 0: \n");
    if(testState.playedCardCount == g.playedCardCount + 1)
      printf("Passed. Expected %d    Returned %d\n", g.playedCardCount + 1, testState.playedCardCount);
    else
      printf("FAILED. Expected %d    Returned %d\n", g.playedCardCount + 1, testState.playedCardCount);

    // part b, make sure it didn't go to the other user's hand    printf("Test 1: Card added to played pile if w/trash flag 0: \n");
    printf("Test 1b: Other player didn't gain to hand: \n");
    if(testState.handCount[p2] != g.handCount[p2])
      printf("FAILED. Expected other user's hand to remain %d   It's now: %d\n", g.handCount[p2], testState.handCount[p2]);
    else
      printf("Passed. Expected other user's hand to remain %d   It's now: %d\n", g.handCount[p2], testState.handCount[p2]);
   
    // part c, make sure it didn't go to the other user's deck
    printf("Test 1c: Other player didn't gain to deck: \n");
    if(testState.deckCount[p2] != g.deckCount[p2])
      printf("FAILED. Expected other user's deck to remain %d   It's now: %d\n", g.deckCount[p2], testState.deckCount[p2]);
    else
       printf("Passed. Expected other user's deck to remain %d   It's now: %d\n", g.deckCount[p2], testState.deckCount[p2]);

    // make sure it's added if not trashed
    initializeGame(numPlayers, k, 1000, &g);
    g.hand[p][0] = steward;
    g.hand[p][1] = estate;
    g.hand[p][2] = duchy;
    g.hand[p][3] = province;
    g.hand[p][4] = great_hall;
    memcpy(&testState, &g, sizeof(struct gameState));
    result = discardCard(province, p, &testState, 1);  // trash flag false
    printf("\nTest 2: Card not added to played pile if trash flag set: \n");
    if(testState.playedCardCount == g.playedCardCount)
      printf("Passed. Expected %d    Returned %d\n", g.playedCardCount, testState.playedCardCount);
    else
      printf("FAILED. Expected %d    Returned %d\n", g.playedCardCount, testState.playedCardCount);
    // part b, make sure it didn't go to the other user's hand    printf("Test 1: Card added to played pile if w/trash flag 0: \n");
    printf("Test 2b: Other player didn't gain to hand: \n");
    if(testState.handCount[p2] != g.handCount[p2])
      printf("FAILED. Expected other user's hand to remain %d   It's now: %d\n", g.handCount[p2], testState.handCount[p2]);
    else
      printf("Passed. Expected other user's hand to remain %d   It's now: %d\n", g.handCount[p2], testState.handCount[p2]);
   
    // part c, make sure it didn't go to the other user's deck
    printf("Test 2c: Other player didn't gain to deck: \n");
    if(testState.deckCount[p2] != g.deckCount[p2])
      printf("FAILED. Expected other user's deck to remain %d   It's now: %d\n", g.deckCount[p2], testState.deckCount[p2]);
    else
       printf("Passed. Expected other user's deck to remain %d   It's now: %d\n", g.deckCount[p2], testState.deckCount[p2]);


    // making sure it's removed from hand
    initializeGame(numPlayers, k, 1000, &g);
    g.hand[p][0] = steward;
    g.hand[p][1] = estate;
    g.hand[p][2] = duchy;
    g.hand[p][3] = province;
    g.hand[p][4] = great_hall;
    memcpy(&testState, &g, sizeof(struct gameState));
    result = discardCard(province, p, &testState, 0); 
    int gone = 0; 
    printf("\nTest 3: Card is removed from hand when discarded: \n");
    for(j = 0; j < testState.handCount[p]; j++){
      if(testState.hand[p][j] == province)
        gone = 1;
    }
    if(gone != 1)
      printf("Passed. Card not found in hand.\n");
    else
      printf("Failed. Card found in hand.\n");

    // part b, make sure it didn't go to the other user's hand    printf("Test 1: Card added to played pile if w/trash flag 0: \n");
    printf("Test 3b: Other player didn't gain to hand: \n");
    if(testState.handCount[p2] != g.handCount[p2])
      printf("FAILED. Expected other user's hand to remain %d   It's now: %d\n", g.handCount[p2], testState.handCount[p2]);
    else
      printf("Passed. Expected other user's hand to remain %d   It's now: %d\n", g.handCount[p2], testState.handCount[p2]);
   
    // part c, make sure it didn't go to the other user's deck
    printf("Test 3c: Other player didn't gain to deck: \n");
    if(testState.deckCount[p2] != g.deckCount[p2])
      printf("FAILED. Expected other user's deck to remain %d   It's now: %d\n", g.deckCount[p2], testState.deckCount[p2]);
    else
       printf("Passed. Expected other user's deck to remain %d   It's now: %d\n", g.deckCount[p2], testState.deckCount[p2]);

    // making sure it's removed from hand
    initializeGame(numPlayers, k, 1000, &g);
    g.hand[p][0] = steward;
    g.hand[p][1] = estate;
    g.hand[p][2] = duchy;
    g.hand[p][3] = province;
    memcpy(&testState, &g, sizeof(struct gameState));
    result = discardCard(province, p, &testState, 1);   // gain feast in teststate, disard set for current player
    printf("\nTest 4: Card is removed from hand when trashed: \n");
    if(testState.handCount[p] == g.handCount[p] -1)
      printf("Passed. Expected %d    Returned %d\n", g.handCount[p] -1, testState.handCount[p]);
    else
      printf("FAILED. Expected %d    Returned %d\n", g.handCount[p] -1, testState.handCount[p]);
    
    // part b, make sure it didn't go to the other user's hand    printf("Test 1: Card added to played pile if w/trash flag 0: \n");
    printf("Test 4b: Other player didn't gain to hand: \n");
    if(testState.handCount[p2] != g.handCount[p2])
      printf("FAILED. Expected other user's hand to remain %d   It's now: %d\n", g.handCount[p2], testState.handCount[p2]);
    else
      printf("Passed. Expected other user's hand to remain %d   It's now: %d\n", g.handCount[p2], testState.handCount[p2]);
   
    // part c, make sure it didn't go to the other user's deck
    printf("Test 4c: Other player didn't gain to deck: \n");
    if(testState.deckCount[p2] != g.deckCount[p2])
      printf("FAILED. Expected other user's deck to remain %d   It's now: %d\n", g.deckCount[p2], testState.deckCount[p2]);
    else
       printf("Passed. Expected other user's deck to remain %d   It's now: %d\n", g.deckCount[p2], testState.deckCount[p2]);

    // check if reduces to 0
    initializeGame(numPlayers, k, 1000, &g);
    g.hand[p][0] = province;
    g.handCount[p] = 1;
    memcpy(&testState, &g, sizeof(struct gameState));
    testState.handCount[p] = 1;
    result = discardCard(province, p, &testState, 0);   // gain feast in teststate, disard set for current player
    printf("\nTest 4: One card in hand, will reduce to 0: \n");
    if(testState.handCount[p] == g.handCount[p] -1)
      printf("Passed. Expected %d    Returned %d\n", g.handCount[p] -1, testState.handCount[p]);
    else
      printf("FAILED. Expected %d    Returned %d\n", g.handCount[p] -1, testState.handCount[p]);
 
    // part b, make sure it didn't go to the other user's hand    printf("Test 1: Card added to played pile if w/trash flag 0: \n");
    printf("Test 4b: Other player didn't gain to hand: \n");
    if(testState.handCount[p2] != g.handCount[p2])
      printf("FAILED. Expected other user's hand to remain %d   It's now: %d\n", g.handCount[p2], testState.handCount[p2]);
    else
      printf("Passed. Expected other user's hand to remain %d   It's now: %d\n", g.handCount[p2], testState.handCount[p2]);
   
    // part c, make sure it didn't go to the other user's deck
    printf("Test 4c: Other player didn't gain to deck: \n");
    if(testState.deckCount[p2] != g.deckCount[p2])
      printf("FAILED. Expected other user's deck to remain %d   It's now: %d\n", g.deckCount[p2], testState.deckCount[p2]);
    else
       printf("Passed. Expected other user's deck to remain %d   It's now: %d\n", g.deckCount[p2], testState.deckCount[p2]);


    // last card set if an option
    initializeGame(numPlayers, k, 1000, &g);
    g.hand[p][0] = steward;
    g.hand[p][1] = estate;
    g.hand[p][2] = duchy;
    g.hand[p][3] = province;
    g.hand[p][4] = great_hall;
    memcpy(&testState, &g, sizeof(struct gameState));
    result = discardCard(province, p, &testState, 0);   // gain feast in teststate, disard set for current player
    printf("\nTest 5: Makes sure if more cards available, last card set: \n");
    if( testState.hand[p][testState.handCount[p]] == -1)  // handcount decreased, now at handcount
      printf("Passed. Expected %d    Returned %d\n", -1, testState.hand[p][testState.handCount[p]]);
    else
      printf("FAILED. Expected %d    Returned %d\n", -1, testState.hand[p][testState.handCount[p]]);
  
    // part b, make sure it didn't go to the other user's hand    printf("Test 1: Card added to played pile if w/trash flag 0: \n");
    printf("Test 5b: Other player didn't gain to hand: \n");
    if(testState.handCount[p2] != g.handCount[p2])
      printf("FAILED. Expected other user's hand to remain %d   It's now: %d\n", g.handCount[p2], testState.handCount[p2]);
    else
      printf("Passed. Expected other user's hand to remain %d   It's now: %d\n", g.handCount[p2], testState.handCount[p2]);
   
    // part c, make sure it didn't go to the other user's deck
    printf("Test 5c: Other player didn't gain to deck: \n");
    if(testState.deckCount[p2] != g.deckCount[p2])
      printf("FAILED. Expected other user's deck to remain %d   It's now: %d\n", g.deckCount[p2], testState.deckCount[p2]);
    else
       printf("Passed. Expected other user's deck to remain %d   It's now: %d\n", g.deckCount[p2], testState.deckCount[p2]);

  
    //test for world state changes, will indicate if any victory cards have been given out inappropriately
    printf("\nTest 6: : Test supply counts for points and curses that should not have been distributed: \n ");
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
    printf("\nTest 7: Test supply counts for treasure that should have been distributed: \n");
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
