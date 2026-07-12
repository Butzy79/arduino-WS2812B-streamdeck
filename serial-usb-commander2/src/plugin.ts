import streamDeck from "@elgato/streamdeck";
import {LogLevel} from "@elgato/streamdeck";

import { SendSerialCommand } from "./actions/send-command";

streamDeck.logger.setLevel(LogLevel.INFO);
streamDeck.logger.info("PLUGIN AVVIATA CORRETTAMENTE!");
streamDeck.actions.registerAction(new SendSerialCommand());

streamDeck.connect();
