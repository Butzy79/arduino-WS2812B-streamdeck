import streamDeck from "@elgato/streamdeck";

import { SendSerialCommand } from "./actions/increment-counter";

streamDeck.logger.setLevel("trace");

streamDeck.actions.registerAction(new SendSerialCommand());

streamDeck.connect();