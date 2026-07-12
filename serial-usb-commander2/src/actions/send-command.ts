import { streamDeck, action, KeyDownEvent, SingletonAction } from "@elgato/streamdeck";

@action({ UUID: "com.butzy79.serial-usb-commander2.send" })
export class SendSerialCommand extends SingletonAction<SerialSettings> {

	override async onKeyDown(ev: KeyDownEvent<SerialSettings>): Promise<void> {

		const command = ev.payload.settings.command ?? "ON";

		streamDeck.logger.info(`KEY PRESSED. Command to send: ${command}`);

		const { SerialPort } = await import("serialport");

		const port = new SerialPort({
			path: "COM5",
			baudRate: 115200
		});

		port.on("open", () => {
			streamDeck.logger.info("SERIAL OPEN");
		});

		port.on("error", (err) => {
			streamDeck.logger.error(`SERIAL ERROR: ${err.message}`);
		});

		await ev.action.showOk();
	}
}

type SerialSettings = {
	command?: string;
};