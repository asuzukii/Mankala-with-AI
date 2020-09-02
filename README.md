# Mankala with AI

This project was completed in Spring of 2019 as an assignment for CS32 in UCLA. The project consisted of implementing the game Mankala with 2 difficulties: dumb AI and smart AI. First I implemented the board and the player features as well as the game. Then, for the dumb AI, I randomized its moves so that it wouldn't optimize to win the game. For the smart AI on the other hand, I recursively called the game function in order for the smart AI player to read a few steps ahead, score each leaf of scenarios (game lost = INT_MIN, game won = INT_MAX, took queen = 100, etc.) and made the player choose based on that. I also implemented alpha beta pruning in order to speed up the computation of each batch, so that it would be able to read deeper into the game in the same amount of time.

This project if I remember correctly got around an 85% due to a few bugs and errors, but overall, it was a very challenging project and a fun one as well!
