import streamDeck from "@elgato/streamdeck";

streamDeck.logger.setLevel("trace");

console.log("START TEST");

streamDeck.connect();

console.log("AFTER CONNECT");