import streamDeck from "@elgato/streamdeck";

import { SendSerialCommand } from "./actions/send-command";

streamDeck.logger.setLevel("trace");

streamDeck.actions.registerAction(new SendSerialCommand());

streamDeck.connect();