import streamDeck, { LogLevel } from "@elgato/streamdeck";
import { SendSerialCommand } from "./actions/send-command";

streamDeck.logger.setLevel(LogLevel.TRACE);
streamDeck.logger.info("PLUGIN AVVIATA CORRETTAMENTE!");
streamDeck.actions.registerAction(new SendSerialCommand());

streamDeck.connect();