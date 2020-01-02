# Lurk

### Introduction

Lurk is a peer to peer chat using a blockchain to provide a maximum of security for the user. In fact Lurk uses several method to prevent attacks like man in the middle. Additionally and since it does not require any centralized server, Lurk will not be own by any government and will stay independent. 

## How it works

### Encryption 

To secure any communication within the Lurk network, we use RSA to encrypt messages. 

### Blockchain 

We decided to use a blockchain to secure public keys of each users and ensure a security against identity substition attacks. Each person who wants to use Lurk need to register themselves on the blockchain by adding their IP and their public keys to the latest block. 

### Integrity

The problem we had to face, is that a man in the middle can still intersept the message and modify it without knowing the content. To ensure that the message is not modified, an integrity check is required. It means that both person who wants to communicate, let's call them Alice and Bob, will need to have something in common that the other aren't aware of. There are three possible solution to share this common things:
- An IRL exchange which provide the maximum security
- A normal exchange using RSA but it won't be secure since someone could modify the thing
- Using the whole network. Let's say that Bob want to talk for the first time to Alice. Using this method Bob will announce to a random node of the network that he need the thing in common with Alice. This node will generate a random number and send it to Alice and Bob. Then they will exchange this number and check if they received both the same. Alice and Bob could check if a message has been modified using this number. Unfortunately there are some drawbacks, in fact if the attacker is actually the node who served for the generation of the random number. Also if he achieved to be in the middle of the network of Alice and Bob. 

### Usage drawbacks

Even if Lurk provide a secure user experience they are some usages inconvenient. Here is a non exhaustif list:
- Since Lurk has P2P architecture, a user must do port forwarding to accept someone who wants to interact with him.
- The blockchain might not be secure enough since mining isn't attractive to bring enough work force.
