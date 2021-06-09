# **Chess game project**

# Members

- Juliusz Neuman
- Arkadiusz Rybski
- Krystian Szewczak

# Modules

Modules are in separate libs.

Modules:

- Chess - implements chess logic: pieces, board, moves.
- Communicator - provides communication between User and program. 
- Controller - controls game.
- Engine - gets moves to prompt user or choose move for AI player.
- Game - creates connection between Chess catalog elements, implements making moves and player classes.
- Loader - implements loading game, storing it and creating new one.
- Logger - implements singleton logger with multiple possible channels.
- Runner - is responsible for launching program, what's more provides and iplements commands to be compatibile with the state and the mode of the game.
- View - implements viewing game.

# Tests

- Tests specific for given library should be placed in its directory.
- Tests combining multiple libraries should be placed in common tests directory.
