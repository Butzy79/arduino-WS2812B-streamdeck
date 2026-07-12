import { streamDeck, action, KeyDownEvent, SingletonAction } from "@elgato/streamdeck";
import { SerialPort } from "serialport";

type SerialSettings = {
	command?: string;
};

@action({ UUID: "com.butzy79.serial-usb-commander2.send" })
export class SendSerialCommand extends SingletonAction<SerialSettings> {

	override async onKeyDown(ev: KeyDownEvent<SerialSettings>): Promise<void> {
		const command = ev.payload.settings.command ?? "ON";
		streamDeck.logger.info(`KEY PRESSED -> Command to send: ${command}`);

		// 1. CREA LA PORTA CON AUTOOPEN DISABILITATO
		const port = new SerialPort({
			path: "COM7",
			baudRate: 115200,
			autoOpen: false // <--- FONDAMENTALE! Evita che parta prima di agganciare i listener
		});

		// 2. AGGANCIA TUTTI I LISTENER PRIMA DI APRIRE
		port.on("open", () => {
			streamDeck.logger.info("SERIAL OPEN");

			port.write(command + "\n", (err) => {
				if (err) {
					streamDeck.logger.error("WRITE ERROR: " + err.message);
				} else {
					streamDeck.logger.info("SERIAL SENT: " + command);
				}

				// Chiudi sempre dopo aver finito per liberare la porta COM
				port.close((closeErr) => {
					if (closeErr) streamDeck.logger.error("CLOSE ERROR: " + closeErr.message);
					else streamDeck.logger.info("SERIAL CLOSED");
				});
			});
		});

		port.on("error", (err) => {
			streamDeck.logger.error("SERIAL ERROR: " + err.message);
		});

		// 3. APRI LA PORTA MANUALMENTE ADESSO CHE I LISTENER SONO PRONTI
		port.open((err) => {
			if (err) {
				streamDeck.logger.error("MANUAL OPEN ERROR: " + err.message);
			}
		});

		// Mostra la spunta verde di successo sul tasto dello Stream Deck
		await ev.action.showOk();
	}
}