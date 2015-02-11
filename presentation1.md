# Finite State Machines

![Finite State Machine](presentation1/fsm.png)

## As a computational device
Finite State Machines, typically, are used as a computational device. They accept some input, usually depicted as a string of characters, and usually return a boolean, based on where the string of input directed the machine's *state*. This is the strictest sense of a "Finite State Machine."

## As data storage
Using a slightly looser interpretation of the term Finite State Machine, it can be used to store data and behaviors. One such instance is a very simplistic form of AI. Imagine a computer controlled adversary in some version of a video game:

1. The adversary starts out in a passive state.
  2. Once the adversary notices a player, the adversary moves into a aggressive state.
3. The aggressive state dictates certain behaviors, including attacking the player.
  4. Once the player deals enough damage to the adversary, the adversary moves into a panic state.
5. ... And so on.

The data isn't explicit, like storing numbers in a linked list, but rather implicit in the behaviors and events that dictate the state transitions.

## In my blog