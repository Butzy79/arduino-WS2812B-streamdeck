import streamDeck from "@elgato/streamdeck";

import { SendSerialCommand } from "./actions/send-command";

console.log("PLUGIN STARTED");

streamDeck.logger.setLevel("trace");

streamDeck.actions.registerAction(new SendSerialCommand());

console.log("ACTION REGISTERED");

streamDeck.connect();

console.log("CONNECT CALLED");