import { streamDeck, action, KeyDownEvent, SingletonAction } from "@elgato/streamdeck";
import { SerialPort } from "serialport";
@action({ UUID: "com.butzy79.serial-usb-commander2.send" })
export class SendSerialCommand extends SingletonAction<SerialSettings> {

	override async onKeyDown(ev: KeyDownEvent<SerialSettings>): Promise<void> {
		const command = ev.payload.settings.command ?? "ON";
		streamDeck.logger.info(`KEY PRESSED --> Command to send: ${command}`);
		const port = new SerialPort({
			path: "COM7",
			baudRate: 115200
		});

		port.on("open", () => {
			streamDeck.logger.info("SERIAL OPEN");

			port.write(command + "\n", (err) => {
				if (err) {
					streamDeck.logger.error("WRITE ERROR: " + err.message);
				} else {
					streamDeck.logger.info("SERIAL SENT: " + command);
				}

				port.close();
			});
		});

		port.on("error", (err) => {
			streamDeck.logger.error("SERIAL ERROR: " + err.message);
		});
		await ev.action.showOk();
	}
}

type SerialSettings = {
	command?: string;
};